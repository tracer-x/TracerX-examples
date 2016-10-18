/* print_formatted from Coreutils 6.10 printf.c

   Copyright (C) 2016 National University of Singapore
   Copyright (C) 1990-2007 Free Software Foundation, Inc.

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

/* Usage: printf format [argument...]

   A front end to the printf function that lets it be used from the shell.

   Backslash escapes:

   \" = double quote
   \\ = backslash
   \a = alert (bell)
   \b = backspace
   \c = produce no further output
   \f = form feed
   \n = new line
   \r = carriage return
   \t = horizontal tab
   \v = vertical tab
   \ooo = octal number (ooo is 1 to 3 digits)
   \xhh = hexadecimal number (hhh is 1 to 2 digits)
   \uhhhh = 16-bit Unicode character (hhhh is 4 digits)
   \Uhhhhhhhh = 32-bit Unicode character (hhhhhhhh is 8 digits)

   Additional directive:

   %b = print an argument string, interpreting backslash escapes,
     except that octal escapes are of the form \0 or \0ooo.

   The `format' argument is re-used as many times as necessary
   to convert all of the given arguments.

   David MacKenzie <djm@gnu.ai.mit.edu> */

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <klee/klee.h>

#define EXIT_FAILURE 1

#define BUFFER_SIZE 1024
#define BUFFER_NUMBER 10

#define bool unsigned short
#define true 1
#define false 0

#define ISDIGIT(c) ((unsigned int) (c) - '0' <= 9)

char buffer_pool[BUFFER_NUMBER][BUFFER_SIZE];
size_t next_buffer = 0;

char *my_malloc()
{
  if (next_buffer < BUFFER_NUMBER) {
    return (char *) buffer_pool[next_buffer++];
  }
  return NULL;
}

char *my_memcpy(char *dest, const char *src, size_t n)
{
  size_t i;
  char *p = dest;
  for (i = 0; i < n; ++i)
    *p++ = *src++;
  return dest;
}

char *my_strchr(char *str, char c)
{
  while (*str) {
    if (*str == c)
      return str;
    str++;
  }
  return NULL;
}

/* The official name of this program (e.g., no `g' prefix).  */
#define PROGRAM_NAME "printf"

#define AUTHORS "David MacKenzie"

#define isodigit(c) ((c) >= '0' && (c) <= '7')
#define hextobin(c) ((c) >= 'a' && (c) <= 'f' ? (c) - 'a' + 10 : \
		     (c) >= 'A' && (c) <= 'F' ? (c) - 'A' + 10 : (c) - '0')
#define octtobin(c) ((c) - '0')

/* The value to return to the calling program.  */
static int exit_status;

/* True if the POSIXLY_CORRECT environment variable is set.  */
static bool posixly_correct;

/* This message appears in N_() here rather than just in _() below because
   the sole use would have been in a #define.  */
static char const *const cfcc_msg =
  "warning: %s: character(s) following character constant have been ignored";

/* The name this program was run with. */
char *program_name;

static void
verify_numeric (const char *s, const char *end)
{
  if (*end)
    {
      exit_status = EXIT_FAILURE;
    }
}

#define STRTOX(TYPE, FUNC_NAME, LIB_FUNC_EXPR)				 \
static TYPE								 \
FUNC_NAME (char const *s)						 \
{									 \
  char *end;								 \
  TYPE val;								 \
									 \
  if (*s == '\"' || *s == '\'')						 \
    {									 \
      unsigned char ch = *++s;						 \
      val = ch;								 \
    }									 \
  else									 \
    {									 \
      val = (LIB_FUNC_EXPR);						 \
      verify_numeric (s, end);						 \
    }									 \
  return val;								 \
}									 \

STRTOX (intmax_t,    vstrtoimax, strtoimax (s, &end, 0))
STRTOX (uintmax_t,   vstrtoumax, strtoumax (s, &end, 0))
STRTOX (long double, vstrtold,  strtold (s, &end))

/* Output a single-character \ escape.  */

static void
print_esc_char (char c)
{
  switch (c)
    {
    case 'a':			/* Alert. */
      //      putchar ('\a');
      break;
    case 'b':			/* Backspace. */
      //putchar ('\b');
      break;
    case 'c':			/* Cancel the rest of the output. */
      exit (EXIT_SUCCESS);
      break;
    case 'f':			/* Form feed. */
      //putchar ('\f');
      break;
    case 'n':			/* New line. */
      //putchar ('\n');
      break;
    case 'r':			/* Carriage return. */
      //putchar ('\r');
      break;
    case 't':			/* Horizontal tab. */
      //putchar ('\t');
      break;
    case 'v':			/* Vertical tab. */
      //putchar ('\v');
      break;
    default:
      //putchar (c);
      break;
    }
}

/* Print a \ escape sequence starting at ESCSTART.
   Return the number of characters in the escape sequence
   besides the backslash.
   If OCTAL_0 is nonzero, octal escapes are of the form \0ooo, where o
   is an octal digit; otherwise they are of the form \ooo.  */

static int
print_esc (const char *escstart, bool octal_0)
{
  const char *p = escstart + 1;
  int esc_value = 0;		/* Value of \nnn escape. */
  int esc_length;		/* Length of \nnn escape. */

  if (*p == 'x')
    {
      /* A hexadecimal \xhh escape sequence must have 1 or 2 hex. digits.  */
      for (esc_length = 0, ++p;
	   esc_length < 2 && isxdigit (*p);
	   ++esc_length, ++p)
	esc_value = esc_value * 16 + hextobin (*p);
      // putchar (esc_value);
    }
  else if (isodigit (*p))
    {
      /* Parse \0ooo (if octal_0 && *p == '0') or \ooo (otherwise).
         Allow \ooo if octal_0 && *p != '0'; this is an undocumented
         extension to POSIX that is compatible with Bash 2.05b.  */
      for (esc_length = 0, p += octal_0 && *p == '0';
	   esc_length < 3 && isodigit (*p);
	   ++esc_length, ++p)
	esc_value = esc_value * 8 + octtobin (*p);
      // putchar (esc_value);
    }
  else if (*p && my_strchr ("\"\\abcfnrtv", *p))
    print_esc_char (*p++);
  else if (*p == 'u' || *p == 'U')
    {
      char esc_char = *p;
      unsigned int uni_value;

      uni_value = 0;
      for (esc_length = (esc_char == 'u' ? 4 : 8), ++p;
	   esc_length > 0;
	   --esc_length, ++p)
	{
	  uni_value = uni_value * 16 + hextobin (*p);
	}

      // print_unicode_char (stdout, uni_value, 0);
    }
  else
    {
      // putchar ('\\');
      if (*p)
	{
	  // putchar (*p);
	  p++;
	}
    }
  return p - escstart - 1;
}

/* Print string STR, evaluating \ escapes. */

static void
print_esc_string (const char *str)
{
  for (; *str; str++)
    if (*str == '\\')
      str += print_esc (str, true);
  //    else
  //  putchar (*str);
}

/* Evaluate a printf conversion specification.  START is the start of
   the directive, LENGTH is its length, and CONVERSION specifies the
   type of conversion.  LENGTH does not include any length modifier or
   the conversion specifier itself.  FIELD_WIDTH and PRECISION are the
   field width and precision for '*' values, if HAVE_FIELD_WIDTH and
   HAVE_PRECISION are true, respectively.  ARGUMENT is the argument to
   be formatted.  */

static void
print_direc (const char *start, size_t length, char conversion,
	     bool have_field_width, int field_width,
	     bool have_precision, int precision,
	     char const *argument)
{
  char *p;		/* Null-terminated copy of % directive. */

  /* Create a null-terminated copy of the % directive, with an
     intmax_t-wide length modifier substituted for any existing
     integer length modifier.  */
  {
    char *q;
    char const *length_modifier;
    size_t length_modifier_len;

    switch (conversion)
      {
      case 'd': case 'i': case 'o': case 'u': case 'x': case 'X':
	length_modifier = PRIdMAX;
	length_modifier_len = sizeof PRIdMAX - 2;
	break;

      case 'a': case 'e': case 'f': case 'g':
      case 'A': case 'E': case 'F': case 'G':
	length_modifier = "L";
	length_modifier_len = 1;
	break;

      default:
	length_modifier = start;  /* Any valid pointer will do.  */
	length_modifier_len = 0;
	break;
      }

    p = my_malloc ();
    q = my_memcpy (p, start, length);
    q = my_memcpy (q, length_modifier, length_modifier_len);
    *q++ = conversion;
    *q = '\0';
  }

  switch (conversion)
    {
    case 'd':
    case 'i':
      {
	intmax_t arg = vstrtoimax (argument);
      }
      break;

    case 'o':
    case 'u':
    case 'x':
    case 'X':
      {
	uintmax_t arg = vstrtoumax (argument);
      }
      break;

    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'f':
    case 'F':
    case 'g':
    case 'G':
      {
	long double arg = vstrtold (argument);
      }
      break;

    case 'c':
      break;

    case 's':
      break;
    }

  free (p);
}

/* Print the text in FORMAT, using ARGV (with ARGC elements) for
   arguments to any `%' directives.
   Return the number of elements of ARGV used.  */

static int
print_formatted (const char *format, int argc, char **argv)
{
  int save_argc = argc;		/* Preserve original value.  */
  const char *f;		/* Pointer into `format'.  */
  const char *direc_start;	/* Start of % directive.  */
  size_t direc_length;		/* Length of % directive.  */
  bool have_field_width;	/* True if FIELD_WIDTH is valid.  */
  int field_width = 0;		/* Arg to first '*'.  */
  bool have_precision;		/* True if PRECISION is valid.  */
  int precision = 0;		/* Arg to second '*'.  */
  char ok[UCHAR_MAX + 1];	/* ok['x'] is true if %x is allowed.  */

  for (f = format; *f; ++f)
    {
      switch (*f)
	{
	case '%':
	  direc_start = f++;
	  direc_length = 1;
	  have_field_width = have_precision = false;
	  if (*f == '%')
	    {
	      //	      putchar ('%');
	      break;
	    }
	  if (*f == 'b')
	    {
	      /* FIXME: Field width and precision are not supported
		 for %b, even though POSIX requires it.  */
	      if (argc > 0)
		{
		  print_esc_string (*argv);
		  ++argv;
		  --argc;
		}
	      break;
	    }

	  memset (ok, 0, sizeof ok);
	  ok['a'] = ok['A'] = ok['c'] = ok['d'] = ok['e'] = ok['E'] =
	    ok['f'] = ok['F'] = ok['g'] = ok['G'] = ok['i'] = ok['o'] =
	    ok['s'] = ok['u'] = ok['x'] = ok['X'] = 1;

	  for (;; f++, direc_length++)
	    switch (*f)
	      {
#if (__GLIBC__ == 2 && 2 <= __GLIBC_MINOR__) || 3 <= __GLIBC__
	      case 'I':
#endif
	      case '\'':
		ok['a'] = ok['A'] = ok['c'] = ok['e'] = ok['E'] =
		  ok['o'] = ok['s'] = ok['x'] = ok['X'] = 0;
		break;
	      case '-': case '+': case ' ':
		break;
	      case '#':
		ok['c'] = ok['d'] = ok['i'] = ok['s'] = ok['u'] = 0;
		break;
	      case '0':
		ok['c'] = ok['s'] = 0;
		break;
	      default:
		goto no_more_flag_characters;
	      }
	no_more_flag_characters:;

	  if (*f == '*')
	    {
	      ++f;
	      ++direc_length;
	      if (argc > 0)
		{
		  intmax_t width = vstrtoimax (*argv);
		  if (INT_MIN <= width && width <= INT_MAX)
		    field_width = width;

		  ++argv;
		  --argc;
		}
	      else
		field_width = 0;
	      have_field_width = true;
	    }
	  else
	    while (ISDIGIT (*f))
	      {
		++f;
		++direc_length;
	      }
	  if (*f == '.')
	    {
	      ++f;
	      ++direc_length;
	      ok['c'] = 0;
	      if (*f == '*')
		{
		  ++f;
		  ++direc_length;
		  if (argc > 0)
		    {
		      intmax_t prec = vstrtoimax (*argv);
		      if (prec < 0)
			{
			  /* A negative precision is taken as if the
			     precision were omitted, so -1 is safe
			     here even if prec < INT_MIN.  */
			  precision = -1;
			}
		      if (INT_MAX >= prec)
			precision = prec;

		      ++argv;
		      --argc;
		    }
		  else
		    precision = 0;
		  have_precision = true;
		}
	      else
		while (ISDIGIT (*f))
		  {
		    ++f;
		    ++direc_length;
		  }
	    }

	  while (*f == 'l' || *f == 'L' || *f == 'h'
		 || *f == 'j' || *f == 't' || *f == 'z')
	    ++f;

	  {
	    unsigned char conversion = *f;
	  }

	  print_direc (direc_start, direc_length, *f,
		       have_field_width, field_width,
		       have_precision, precision,
		       (argc <= 0 ? "" : (argc--, *argv++)));
	  break;

	case '\\':
	  f += print_esc (f, false);
	  break;

	default: {
	  //	  putchar (*f);
	}
	}
    }

  return save_argc - argc;
}

int
main (int argc, char **argv)
{
  char format[8];
  int my_argc = 5;
  char my_argv[3][5];
  int args_used;
  
  klee_make_symbolic(format, 8 * sizeof(char), "format");
  klee_make_symbolic(my_argv, 3 * 5 * sizeof(char), "my_argv");
  argc = my_argc;
  argv = (char **)my_argv;

  format[7] = '\0';
  my_argv[0][4] = '\0';
  my_argv[1][4] = '\0';
  my_argv[2][4] = '\0';
  
  argc -= 2;
  argv += 2;

  do
    {
      args_used = print_formatted (format, argc, argv);
      argc -= args_used;
      argv += args_used;
    }
  while (args_used > 0 && argc > 0);

  return 0;
}
