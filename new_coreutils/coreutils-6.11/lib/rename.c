/* Work around the bug in some systems whereby rename fails when the source
   file has a trailing slash.  The rename functions of SunOS 4.1.1_U1 and
   mips-dec-ultrix4.4 have this bug.

   Copyright (C) 2001, 2002, 2003, 2005, 2006 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* written by Volker Borchert */

#include <config.h>
#undef rename

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dirname.h"
#include "xalloc.h"

/* Rename the file SRC to DST, removing any trailing
   slashes from SRC.  Needed for SunOS 4.1.1_U1.  */

int
rpl_rename (char const *src, char const *dst)
{
  char *src_temp;
  int ret_val;
  size_t s_len = strlen (src);

  if (s_len && src[s_len - 1] == '/')
    {
      src_temp = xstrdup (src);
      strip_trailing_slashes (src_temp);
    }
  else
    src_temp = (char *) src;

  ret_val = rename (src_temp, dst);

  if (src_temp != src)
    free (src_temp);

  return ret_val;
}
