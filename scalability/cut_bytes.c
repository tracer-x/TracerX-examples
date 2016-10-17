/* cut_bytes from Coreutils 6.10

   Copyright (C) 2016 National University of Singapore
   Copyright (C) 1997-2007 Free Software Foundation, Inc.
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
#include <unistd.h>
#include <klee/klee.h>

#define bool unsigned short
#define true 1
#define false 0

static size_t eol_range_start;
static size_t max_range_endpoint;
static unsigned char *printable_field;
static bool complement;
static bool output_delimiter_specified;

#define INPUT_SIZE 8

int input_ptr = 0;

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
  klee_make_symbolic(&flag, sizeof(int), "flag");

  if (flag)
    return true;
  return false;
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

/* Read from stream STREAM, printing to standard output any selected bytes.  */

static void
cut_bytes (char *input)
{
  size_t byte_idx;	/* Number of bytes in the line so far. */
  /* Whether to begin printing delimiters between ranges for the current line.
     Set after we've begun printing data corresponding to the first range.  */
  bool print_delimiter;

  byte_idx = 0;
  print_delimiter = false;
  while (1)
    {
      int c;		/* Each character from the file. */

      c = input[input_ptr++];

      if (c == '\n')
	{
	  // putchar ('\n');
	  byte_idx = 0;
	  print_delimiter = false;
	}
      else if (c == EOF)
	{
	  // if (byte_idx > 0)
	    // putchar ('\n');
	  break;
	}
      else
	{
	  bool range_start;
	  bool *rs = output_delimiter_specified ? &range_start : NULL;
	  if (print_kth (++byte_idx, rs))
	    {
	      /* if (rs && *rs && print_delimiter) */
	      /* 	{ */
	      /* 	  fwrite (output_delimiter_string, sizeof (char), */
	      /* 		  output_delimiter_length, stdout); */
	      /* 	} */
	      print_delimiter = true;
	      // putchar (c);
	    }
	}
    }
}

int
main (int argc, char **argv)
{
  char input[INPUT_SIZE];

  klee_make_symbolic(input, INPUT_SIZE * sizeof(char), "input");
  input[INPUT_SIZE - 1] = '\0';

  klee_make_symbolic(&output_delimiter_specified, sizeof(output_delimiter_specified), "output_delimiter_specified");
  
  cut_bytes(input);
}
