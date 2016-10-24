/* set_fields - from cut.c of Coreutils 6.10. Adapted as KLEE input.

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

#define INPUT_SIZE 10

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

#define bool signed char
#define false 0
#define true 1
#define _(X) X
#define FATAL_ERROR(X) exit(1)
#define isblank(c) ((c) == ' ' || (c) == '\t')
#define ISDIGIT(c) ((unsigned int)(c) - '0' <= 9)
#define TYPE_SIGNED(t) (!((t)0 < (t) - 1))

#define verify_true(R)                                                         \
  (!!sizeof(struct {                                                           \
       unsigned int verify_error_if_negative_size__ : (R) ? 1 : -1;            \
     }))

#define DECIMAL_DIGIT_ACCUMULATE(Accum, Digit_val, Type)                       \
  ((void)(&(Accum) == (Type *)NULL),      /* The type matches.  */                  \
   (void)verify_true(!TYPE_SIGNED(Type)), /* The type is unsigned.  */         \
   (void)verify_true(sizeof(Accum) == sizeof(Type)), /* Added check.  */       \
   (((Type) - 1 / 10 < (Accum) ||                                              \
     (Type)((Accum) * 10 + (Digit_val)) < (Accum))                             \
        ? false                                                                \
        : (((Accum) = (Accum) * 10 + (Digit_val)), true)))

/* This is simply a shorthand for the common case in which
   the third argument to x2nrealloc would be `sizeof *(P)'.
   Ensure that sizeof *(P) is *not* 1.  In that case, it'd be
   better to use X2REALLOC, although not strictly necessary.  */
#define X2NREALLOC(P, PN)                                                      \
  ((void)verify_true(sizeof *(P) != 1), x2nrealloc(P, PN, sizeof *(P)))

#define ADD_RANGE_PAIR(rp, low, high)                                          \
  do {                                                                         \
    if (low == 0 || high == 0)                                                 \
      FATAL_ERROR(_("fields and positions are numbered from 1"));              \
    if (n_rp >= n_rp_allocated) {                                              \
      (rp) = X2NREALLOC(rp, &n_rp_allocated);                                  \
    }                                                                          \
    rp[n_rp].lo = (low);                                                       \
    rp[n_rp].hi = (high);                                                      \
    ++n_rp;                                                                    \
  } while (0)

struct range_pair {
  size_t lo;
  size_t hi;
};

/* Change the size of an allocated block of memory P to N bytes,
   with error checking.  */

void *xrealloc(void *p, size_t n) {
  p = realloc(p, n);
  if (!p && n != 0)
    exit(1);
  return p;
}

void *x2nrealloc(void *p, size_t *pn, size_t s) {
  size_t n = *pn;

  if (!p) {
    if (!n) {
      /* The approximate size to use for initial small allocation
         requests, when the invoking code specifies an old size of
         zero.  64 bytes is the largest "small" request for the
         GNU C library malloc.  */
      enum {
        DEFAULT_MXFAST = 64
      };

      n = DEFAULT_MXFAST / s;
      n += !n;
    }
  } else {
    /* Set N = ceil (1.5 * N) so that progress is made if N == 1.
       Check for overflow, so that N * S stays in size_t range.
       The check is slightly conservative, but an exact check isn't
       worth the trouble.  */
    if ((size_t) - 1 / 3 * 2 / s <= n)
      exit(1);
    n += (n + 1) / 2;
  }

  *pn = n;
  return xrealloc(p, n * s);
}

/* Return a newly allocated copy of at most N bytes of STRING.
   In other words, return a copy of the initial segment of length N of
   STRING.  */
char *xstrndup(const char *string, size_t n) {
  char *s = strndup(string, n);
  if (!s)
    exit(1);
  return s;
}

void *xmalloc(size_t n) {
  void *p = malloc(n);
  if (!p && n != 0)
    exit(1);
  return p;
}

void *xzalloc(size_t s) { return memset(xmalloc(s), 0, s); }

/* The largest field or byte index used as an endpoint of a closed
   or degenerate range specification;  this doesn't include the starting
   index of right-open-ended ranges.  For example, with either range spec
   `2-5,9-', `2-3,5,9-' this variable would be set to 5.  */
static size_t max_range_endpoint;

/* If nonzero, this is the index of the first field in a range that goes
   to end of line. */
static size_t eol_range_start;

/* This is a bit vector.
   In byte mode, which bytes to output.
   In field mode, which DELIM-separated fields to output.
   Both bytes and fields are numbered starting with 1,
   so the zeroth bit of this array is unused.
   A field or byte K has been selected if
   (K <= MAX_RANGE_ENDPOINT and is_printable_field(K))
    || (EOL_RANGE_START > 0 && K >= EOL_RANGE_START).  */
static unsigned char *printable_field;

/* Comparison function for qsort to order the list of
   struct range_pairs.  */
static int compare_ranges(const void *a, const void *b) {
  int a_start = ((const struct range_pair *)a)->lo;
  int b_start = ((const struct range_pair *)b)->lo;
  return a_start < b_start ? -1 : a_start > b_start;
}

static inline void mark_printable_field(size_t i) {
  size_t n = i / CHAR_BIT;
  printable_field[n] |= (1 << (i % CHAR_BIT));
}

/* Given the list of field or byte range specifications FIELDSTR, set
   MAX_RANGE_ENDPOINT and allocate and initialize the PRINTABLE_FIELD
   array.  If there is a right-open-ended range, set EOL_RANGE_START
   to its starting index.  FIELDSTR should be composed of one or more
   numbers or ranges of numbers, separated by blanks or commas.
   Incomplete ranges may be given: `-m' means `1-m'; `n-' means `n'
   through end of line.  Return true if FIELDSTR contains at least
   one field specification, false otherwise.  */

/* FIXME-someday:  What if the user wants to cut out the 1,000,000-th
   field of some huge input file?  This function shouldn't have to
   allocate a table of a million bits just so we can test every
   field < 10^6 with an array dereference.  Instead, consider using
   an adaptive approach: if the range of selected fields is too large,
   but only a few fields/byte-offsets are actually selected, use a
   hash table.  If the range of selected fields is too large, and
   too many are selected, then resort to using the range-pairs (the
   `rp' array) directly.  */

static bool set_fields(const char *fieldstr) {
  size_t initial = 1; /* Value of first number in a range.  */
  size_t value = 0;   /* If nonzero, a number being accumulated.  */
  bool lhs_specified = false;
  bool rhs_specified = false;
  bool dash_found = false;  /* True if a '-' is found in this field.  */
  bool field_found = false; /* True if at least one field spec
                               has been processed.  */

  struct range_pair *rp = NULL;
  size_t n_rp = 0;
  size_t n_rp_allocated = 0;
  size_t i;
  bool in_digits = false;

  /* Collect and store in RP the range end points.
     It also sets EOL_RANGE_START if appropriate.  */

  for (;;) {
    klee_join("set_fields", dash_found, eol_range_start, field_found, fieldstr,
              in_digits, initial, lhs_specified, rhs_specified, value);

    if (*fieldstr == '-') {
      in_digits = false;
      /* Starting a range. */
      if (dash_found)
        FATAL_ERROR(_("invalid byte or field list"));
      dash_found = true;
      fieldstr++;

      initial = (lhs_specified ? value : 1);
      value = 0;
    } else if (*fieldstr == ',' || isblank(*fieldstr) || *fieldstr == '\0') {
      in_digits = false;
      /* Ending the string, or this field/byte sublist. */
      if (dash_found) {
        dash_found = false;

        if (!lhs_specified && !rhs_specified)
          FATAL_ERROR(_("invalid range with no endpoint: -"));

        /* A range.  Possibilities: -n, m-n, n-.
           In any case, `initial' contains the start of the range. */
        if (!rhs_specified) {
          /* `n-'.  From `initial' to end of line. */
          eol_range_start = initial;
          field_found = true;
        } else {
          /* `m-n' or `-n' (1-n). */
          if (value < initial)
            FATAL_ERROR(_("invalid decreasing range"));

          /* Is there already a range going to end of line? */
          if (eol_range_start != 0) {
            /* Yes.  Is the new sequence already contained
               in the old one?  If so, no processing is
               necessary. */
            if (initial < eol_range_start) {
              /* No, the new sequence starts before the
                 old.  Does the old range going to end of line
                 extend into the new range?  */
              if (eol_range_start <= value) {
                /* Yes.  Simply move the end of line marker. */
                eol_range_start = initial;
              } else {
                /* No.  A simple range, before and disjoint from
                   the range going to end of line.  Fill it. */
                ADD_RANGE_PAIR(rp, initial, value);
              }

              /* In any case, some fields were selected. */
              field_found = true;
            }
          } else {
            /* There is no range going to end of line. */
            ADD_RANGE_PAIR(rp, initial, value);
            field_found = true;
          }
          value = 0;
        }
      } else {
        /* A simple field number, not a range. */
        ADD_RANGE_PAIR(rp, value, value);
        value = 0;
        field_found = true;
      }

      if (*fieldstr == '\0') {
        break;
      }

      fieldstr++;
      lhs_specified = false;
      rhs_specified = false;
    } else if (ISDIGIT(*fieldstr)) {
      /* Record beginning of digit string, in case we have to
         complain about it.  */
      static char const *num_start;
      if (!in_digits || !num_start)
        num_start = fieldstr;
      in_digits = true;

      if (dash_found)
        rhs_specified = 1;
      else
        lhs_specified = 1;

      /* Detect overflow.  */
      if (!DECIMAL_DIGIT_ACCUMULATE(value, *fieldstr - '0', size_t)) {
        /* In case the user specified -c$(echo 2^64|bc),22,
           complain only about the first number.  */
        /* Determine the length of the offending number.  */
        size_t len = strspn(num_start, "0123456789");
        char *bad_num = xstrndup(num_start, len);
        fprintf(stderr, "byte offset %s is too large", bad_num);
        free(bad_num);
        exit(EXIT_FAILURE);
      }

      fieldstr++;
    } else
      FATAL_ERROR(_("invalid byte or field list"));
  }

  max_range_endpoint = 0;
  for (i = 0; i < n_rp; i++) {
    if (rp[i].hi > max_range_endpoint)
      max_range_endpoint = rp[i].hi;
  }

  /* Allocate an array large enough so that it may be indexed by
     the field numbers corresponding to all finite ranges
     (i.e. `2-6' or `-4', but not `5-') in FIELDSTR.  */

  printable_field = xzalloc(max_range_endpoint / CHAR_BIT + 1);

  qsort(rp, n_rp, sizeof(rp[0]), compare_ranges);

  /* Set the array entries corresponding to integers in the ranges of RP.  */
  for (i = 0; i < n_rp; i++) {
    size_t j;
    size_t rsi_candidate;

    /* Record the range-start indices, i.e., record each start
       index that is not part of any other (lo..hi] range.  */
    rsi_candidate = rp[i].lo;

    for (j = rp[i].lo; j <= rp[i].hi; j++)
      mark_printable_field(j);
  }

  free(rp);

  return field_found;
}

int main(int argc, char **argv) {
  char fieldstr[INPUT_SIZE];

  klee_make_symbolic(fieldstr, INPUT_SIZE * sizeof(char), "fieldstr");
  set_fields(fieldstr);
  return 0;
}
