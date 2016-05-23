/*
 * This is a modified GNU Coreutils 6.11 echo for running with KLEE.
 * Modifications copyright 2016 National University of Singapore.
 * 
 * See license/COPYING for license.
 */
#include <klee/klee.h>


typedef long unsigned int size_t;

enum { DEFAULT_ECHO_TO_XPG = 0 };

enum
  {
    _ISupper = ((0) < 8 ? ((1 << (0)) << 8) : ((1 << (0)) >> 8)),
    _ISlower = ((1) < 8 ? ((1 << (1)) << 8) : ((1 << (1)) >> 8)),
    _ISalpha = ((2) < 8 ? ((1 << (2)) << 8) : ((1 << (2)) >> 8)),
    _ISdigit = ((3) < 8 ? ((1 << (3)) << 8) : ((1 << (3)) >> 8)),
    _ISxdigit = ((4) < 8 ? ((1 << (4)) << 8) : ((1 << (4)) >> 8)),
    _ISspace = ((5) < 8 ? ((1 << (5)) << 8) : ((1 << (5)) >> 8)),
    _ISprint = ((6) < 8 ? ((1 << (6)) << 8) : ((1 << (6)) >> 8)),
    _ISgraph = ((7) < 8 ? ((1 << (7)) << 8) : ((1 << (7)) >> 8)),
    _ISblank = ((8) < 8 ? ((1 << (8)) << 8) : ((1 << (8)) >> 8)),
    _IScntrl = ((9) < 8 ? ((1 << (9)) << 8) : ((1 << (9)) >> 8)),
    _ISpunct = ((10) < 8 ? ((1 << (10)) << 8) : ((1 << (10)) >> 8)),
    _ISalnum = ((11) < 8 ? ((1 << (11)) << 8) : ((1 << (11)) >> 8))
  };


char *program_name;


static int
hextobin (unsigned char c)
{
  switch (c)
    {
    default: return c - '0';
    case 'a': case 'A': return 10;
    case 'b': case 'B': return 11;
    case 'c': case 'C': return 12;
    case 'd': case 'D': return 13;
    case 'e': case 'E': return 14;
    case 'f': case 'F': return 15;
    }
}





int
main (int argc, char **argv)
{
  _Bool display_return = 1;
  _Bool allow_options;
  _Bool do_v9 = DEFAULT_ECHO_TO_XPG;

  klee_make_symbolic(&allow_options, sizeof(_Bool), "allow_options");

  program_name = argv[0];
  ;
  ;
# 107 "echo_nosyscall.c"
  --argc;
  ++argv;

  if (allow_options)
    while (argc > 0 && *argv[0] == '-')
      {
	char const *temp = argv[0] + 1;
	size_t i;





	for (i = 0; temp[i]; i++)
	  switch (temp[i])
	    {
	    case 'e': case 'E': case 'n':
	      break;
	    default:
	      goto just_echo;
	    }

	if (i == 0)
	  goto just_echo;



	while (*temp)
	  switch (*temp++)
	    {
	    case 'e':
	      do_v9 = 1;
	      break;

	    case 'E':
	      do_v9 = 0;
	      break;

	    case 'n':
	      display_return = 0;
	      break;
	    }

	argc--;
	argv++;
      }

 just_echo:

  if (do_v9)
    {
      while (argc > 0)
	{
	  char const *s = argv[0];
	  unsigned char c;

	  while ((c = *s++))
	    {
	      if (c == '\\' && *s)
		{
		  switch (c = *s++)
		    {
		    case 'a': c = '\a'; break;
		    case 'b': c = '\b'; break;
		    case 'c': return 0;
		    case 'f': c = '\f'; break;
		    case 'n': c = '\n'; break;
		    case 'r': c = '\r'; break;
		    case 't': c = '\t'; break;
		    case 'v': c = '\v'; break;
		    case 'x':
		      {
			unsigned char ch = *s;

			unsigned short int __ctype_b_loc1;
			klee_make_symbolic(&__ctype_b_loc1, sizeof(unsigned short int), "__ctype_b_loc1");
			unsigned short int __ctype_b_loc2;
			klee_make_symbolic(&__ctype_b_loc2, sizeof(unsigned short int), "__ctype_b_loc2");

			if (! (__ctype_b_loc1 & (unsigned short int) _ISxdigit))
			  goto not_an_escape;
			s++;
			c = hextobin (ch);
			ch = *s;
			if ((__ctype_b_loc2 & (unsigned short int) _ISxdigit))
			  {
			    s++;
			    c = c * 16 + hextobin (ch);
			  }
		      }
		      break;
		    case '0':
		      c = 0;
		      if (! ('0' <= *s && *s <= '7'))
			break;
		      c = *s++;

		    case '1': case '2': case '3':
		    case '4': case '5': case '6': case '7':
		      c -= '0';
		      if ('0' <= *s && *s <= '7')
			c = c * 8 + (*s++ - '0');
		      if ('0' <= *s && *s <= '7')
			c = c * 8 + (*s++ - '0');
		      break;
		    case '\\': break;

		    not_an_escape:
		    default:
		      break;
		    }
		}

	    }
	  argc--;
	  argv++;
	  if (argc > 0){

	  }
	}
    }
  else
    {
      while (argc > 0)
	{
	  argc--;
	  argv++;
	  if (argc > 0){

	  }
	}
    }

  if (display_return){

  }
  return 0;
}
