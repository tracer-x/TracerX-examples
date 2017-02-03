/* cut_fields from Coreutils 6.10

   Copyright (C) 2016 National University of Singapore
   Copyright (C) 1993, 1996, 1997-2007 Free Software Foundation, Inc.
   Copyright (C) 1984 David M. Ihnat

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Written by David Ihnat.  */

/* POSIX changes, bug fixes, long-named options, and cleanup
   by David MacKenzie <djm@gnu.ai.mit.edu>.

   Rewrite cut_fields and cut_bytes -- Jim Meyering.  */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/posix1_lim.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif

#define MIN_CHUNK 64
#define GETNDELIM2_MAXIMUM SSIZE_MAX

#define BUFFER_SIZE 1024
#define BUFFER_NUMBER 10

#define bool unsigned short
#define true 1
#define false 0

char buffer_pool[BUFFER_NUMBER][BUFFER_SIZE];
size_t next_buffer = 0;

static size_t eol_range_start;
static size_t max_range_endpoint;
static unsigned char *printable_field;
static bool complement;
static bool suppress_non_delimited;
static char *field_1_buffer;
static size_t field_1_bufsize;
static unsigned char delim;

#define INPUT_SIZE 8

int input_ptr = 0;

char *my_malloc()
{
  if (next_buffer < BUFFER_NUMBER) {
    return (char *) buffer_pool[next_buffer++];
  }
  return NULL;
}

static inline bool
is_printable_field (size_t i)
{
  size_t n = i / CHAR_BIT;
  return (printable_field[n] >> (i % CHAR_BIT)) & 1;
}

static bool
is_range_start_index (size_t i)
{
  int flag;
#ifdef LLBMC
  flag = __llbmc_nondef_int();
#else
  klee_make_symbolic(&flag, sizeof(int), "flag");
#endif

  if (flag)
    return true;
  return false;
}

ssize_t
getndelim2 (char **lineptr, size_t *linesize, size_t offset, size_t nmax,
            int delim1, int delim2, char *input)
{
  size_t nbytes_avail;          /* Allocated but unused bytes in *LINEPTR.  */
  char *read_pos;               /* Where we're reading into *LINEPTR. */
  ssize_t bytes_stored = -1;
  char *ptr = *lineptr;
  size_t size = *linesize;

  if (!ptr)
    {
      size = nmax < MIN_CHUNK ? nmax : MIN_CHUNK;
      ptr = my_malloc();
      if (!ptr)
        return -1;
    }

  if (size < offset)
    goto done;

  nbytes_avail = size - offset;
  read_pos = ptr + offset;

  if (nbytes_avail == 0 && nmax <= size)
    goto done;

  for (;;)
    {
      /* Here always ptr + size == read_pos + nbytes_avail.  */

      int c;

      /* We always want at least one byte left in the buffer, since we
         always (unless we get an error while reading the first byte)
         NUL-terminate the line buffer.  */

      if (nbytes_avail < 2 && size < nmax)
        {
          size_t newsize = size < MIN_CHUNK ? size + MIN_CHUNK : 2 * size;
          char *newptr;

          if (! (size < newsize && newsize <= nmax))
            newsize = nmax;

          if (GETNDELIM2_MAXIMUM < newsize - offset)
            {
              size_t newsizemax = offset + GETNDELIM2_MAXIMUM + 1;
              if (size == newsizemax)
                goto done;
              newsize = newsizemax;
            }

          nbytes_avail = newsize - (read_pos - ptr);
          // newptr = realloc (ptr, newsize);
          newptr = my_malloc();
          if (!newptr)
            goto done;
          ptr = newptr;
          size = newsize;
          read_pos = size - nbytes_avail + ptr;
        }

      c = input[input_ptr++];
      if (c == EOF)
        {
          /* Return partial line, if any.  */
          if (read_pos == ptr)
            goto done;
          else
            break;
        }

      if (nbytes_avail >= 2)
        {
          *read_pos++ = c;
          nbytes_avail--;
        }

      if (c == delim1 || c == delim2)
        /* Return the line.  */
        break;
    }

  /* Done - NUL terminate and return the number of bytes read.
     At this point we know that nbytes_avail >= 1.  */
  *read_pos = '\0';

  bytes_stored = read_pos - (ptr + offset);

 done:
  *lineptr = ptr;
  *linesize = size;
  return bytes_stored;
}

static bool
print_kth (size_t k, bool *range_start)
{
  bool k_selected
    = ((0 < eol_range_start && eol_range_start <= k)
       || (k <= max_range_endpoint && is_printable_field (k)));

  bool is_selected = k_selected ^ complement;
  if (range_start && is_selected)
    *range_start = is_range_start_index (k);

  return is_selected;
}

/* Read from stream STREAM, printing to standard output any selected fields.  */

static void
cut_fields (char *input)
{
  int c;
  size_t field_idx = 1;
  bool found_any_selected_field = false;
  bool buffer_first_field;

  c = input[input_ptr++];
  
  if (c == EOF)
    return;

  --input_ptr; // ungetc (c, stream);

  /* To support the semantics of the -s flag, we may have to buffer
     all of the first field to determine whether it is `delimited.'
     But that is unnecessary if all non-delimited lines must be printed
     and the first field has been selected, or if non-delimited lines
     must be suppressed and the first field has *not* been selected.
     That is because a non-delimited line has exactly one field.  */
  buffer_first_field = (suppress_non_delimited ^ !print_kth (1, NULL));

  while (1)
    {
      if (field_idx == 1 && buffer_first_field)
	{
	  ssize_t len;
	  size_t n_bytes;

	  len = getndelim2 (&field_1_buffer, &field_1_bufsize, 0,
			    ((size_t) -1), delim, '\n', input);
	  if (len < 0)
	    {
	      int is_error;
	      
	      //	      free (field_1_buffer);
	      field_1_buffer = NULL;

#ifdef LLBMC
        is_error = __llbmc_nondef_int();
#else
        klee_make_symbolic(&is_error, sizeof(int), "is_error");
#endif

        if (is_error)
          break;

        exit(1);
      }

      n_bytes = len;
      assert(n_bytes != 0);

      /* If the first field extends to the end of line (it is not
         delimited) and we are printing all non-delimited lines,
         print this one.  */
      if (field_1_buffer[n_bytes - 1] != delim) {
        if (suppress_non_delimited) {
                  /* Empty.  */
		}
	      else
		{
		  // fwrite (field_1_buffer, sizeof (char), n_bytes, stdout);
		  /* Make sure the output line is newline terminated.  */
		  // if (field_1_buffer[n_bytes - 1] != '\n')
		    // putchar ('\n');
		}
	      continue;
	    }
	  if (print_kth (1, NULL))
	    {
	      /* Print the field, but not the trailing delimiter.  */
	      // fwrite (field_1_buffer, sizeof (char), n_bytes - 1, stdout);
	      found_any_selected_field = true;
	    }
	  ++field_idx;
	}

      if (c != EOF)
	{
	  if (print_kth (field_idx, NULL))
	    {
	      if (found_any_selected_field)
		{
		  // fwrite (output_delimiter_string, sizeof (char),
		  //  output_delimiter_length, stdout);
		}
	      found_any_selected_field = true;

	      while ((c = input[input_ptr++]) != delim && c != '\n' && c != EOF)
		{
		  // putchar (c);
		}
	    }
	  else
	    {
	      while ((c = input[input_ptr++]) != delim && c != '\n' && c != EOF)
		{
		  /* Empty.  */
		}
	    }
	}

      if (c == '\n')
	{
	  c = input[input_ptr++];
	  if (c != EOF)
	    {
	      --input_ptr;
	      c = '\n';
	    }
	}

      if (c == delim)
	++field_idx;
      else if (c == '\n' || c == EOF)
	{
	  // if (found_any_selected_field
	  //    || !(suppress_non_delimited && field_idx == 1))
	  //  putchar ('\n');
	  if (c == EOF)
	    break;
	  field_idx = 1;
	  found_any_selected_field = false;
	}
    }
}

int
main (int argc, char **argv)
{
  char input[INPUT_SIZE];

#ifdef LLBMC
  for (int i = 0; i < INPUT_SIZE; ++i) {
    input[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(input, INPUT_SIZE * sizeof(char), "input");
#endif
  input[INPUT_SIZE - 1] = '\0';

#ifdef LLBMC
  delim = __llbmc_nondef_unsigned_char();
#else
  klee_make_symbolic(&delim, sizeof(delim), "delim");
#endif

  cut_fields(input);
}
