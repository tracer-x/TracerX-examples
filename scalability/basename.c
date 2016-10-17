/* base_name from Coreutils 6.10

   Copyright (C) 2016 National University of Singapore
   Copyright (C) 1990, 1998, 1999, 2000, 2001, 2003, 2004, 2005, 2006,
   2007 Free Software Foundation, Inc.

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

#include <klee/klee.h>

#define INPUT_SIZE 2

#define BUFFER_SIZE 1024
#define BUFFER_NUMBER 10

#define DOUBLE_SLASH_IS_DISTINCT_ROOT 0
#define ISSLASH(C) ((C) == '/' || (C) == '\\')
#define FILE_SYSTEM_PREFIX_LEN(Filename) 0
#define FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE 0

#define bool unsigned short
#define true 1
#define false 0

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

size_t strlen(const char *str)
{
  const char *c = str;
  while (*c) c++;
  return (size_t) (c - str);
}

char *strndup(const char *str, const size_t n)
{
  const char *c = str;
  size_t len = strlen(str);
  char *newstr = my_malloc();
  size_t i;
  
  len = (len < n ? len : n);
  for (i = 0; i < len; ++i) {
    newstr[i] = str[i];
  }
  newstr[i] = 0;
  return newstr;
}

/* Return a newly allocated copy of at most N bytes of STRING.
   In other words, return a copy of the initial segment of length N of
   STRING.  */
char *
xstrndup (const char *string, size_t n)
{
  char *s = strndup (string, n);
  return s;
}

/* Return the address of the last file name component of NAME.  If
   NAME has no relative file name components because it is a file
   system root, return the empty string.  */

char *
last_component (char const *name)
{
  char const *base = name + FILE_SYSTEM_PREFIX_LEN (name);
  char const *p;
  bool saw_slash = false;

  while (ISSLASH (*base))
    base++;

  for (p = base; *p; p++)
    {
      if (ISSLASH (*p))
        saw_slash = true;
      else if (saw_slash)
        {
          base = p;
          saw_slash = false;
        }
    }

  return (char *) base;
}

/* Return the length of the basename NAME.  Typically NAME is the
   value returned by base_name or last_component.  Act like strlen
   (NAME), except omit all trailing slashes.  */

size_t
base_len (char const *name)
{
  size_t len;
  size_t prefix_len = FILE_SYSTEM_PREFIX_LEN (name);

  for (len = strlen (name);  1 < len && ISSLASH (name[len - 1]);  len--)
    continue;

  if (DOUBLE_SLASH_IS_DISTINCT_ROOT && len == 1
      && ISSLASH (name[0]) && ISSLASH (name[1]) && ! name[2])
    return 2;

  if (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE && prefix_len
      && len == prefix_len && ISSLASH (name[prefix_len]))
    return prefix_len + 1;

  return len;
}

char *
base_name (char const *name)
{
  char const *base = last_component (name);
  size_t length;

  /* If there is no last component, then name is a file system root or the
     empty string.  */
  if (! *base)
    return xstrndup (name, base_len (name));

  /* Collapse a sequence of trailing slashes into one.  */
  length = base_len (base);
  if (ISSLASH (base[length]))
    length++;

  /* On systems with drive letters, `a/b:c' must return `./b:c' rather
     than `b:c' to avoid confusion with a drive letter.  On systems
     with pure POSIX semantics, this is not an issue.  */
  if (FILE_SYSTEM_PREFIX_LEN (base))
    {
      char *p = my_malloc();
      p[0] = '.';
      p[1] = '/';
      my_memcpy (p + 2, base, length);
      p[length + 2] = '\0';
      return p;
    }

  /* Finally, copy the basename.  */
  return xstrndup (base, length);
}

int
main (int argc, char **argv)
{
  char input[INPUT_SIZE];
  
  klee_make_symbolic(input, INPUT_SIZE * sizeof(char), "input");
  input[1] = 0;
  
  base_name(input);
  return 0;
}
