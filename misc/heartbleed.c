/*
 * Simplified HeartBleed from OpenSSL 1.0.1f
 * Modifications copyright 2016 National University of Singapore
 * 
 * OpenSSL Copyright (c) 1998-2011 The OpenSSL Project.  All rights
 * reserved. Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * See license/openssl-1.0.1f.txt for full license text.
 */

/*

A possible script for running with KLEE follows.

#!/bin/bash
# A shell script to automate things up.
clang heartbleed.c -emit-llvm -g -O0 -c
clang heartbleed.c -S -emit-llvm -g -O0 -c
rm -rf heartbleed.klee-out
klee -taint=controlflow --output-dir=heartbleed.klee-out -exit-on-error heartbleed.bc

*/

#include <stdlib.h>
#include <string.h>

#include <klee/klee.h>

#define TLS1_HB_REQUEST		1
#define TLS1_HB_RESPONSE	1

#define IDEA_INT unsigned int

#define s2n(l,c)        (*((c)++)=(unsigned char)(((l)     )&0xff), \
                         *((c)++)=(unsigned char)(((l)>> 8L)&0xff))

#define n2s(c,l)        (l =((IDEA_INT)(*((c)++)))<< 8L, \
                         l|=((IDEA_INT)(*((c)++)))      )

int main() {
  unsigned char input[4];
  unsigned char *p, *pl;
  unsigned short hbtype;
  unsigned int payload;
  unsigned int padding = 16; /* Use minimum padding */

  /* Another issue is to track the source of this input */
  p = &(input[0]);

  // We taint only the first byte of the payload
  klee_set_taint(1, &(p[1]), sizeof(unsigned char));

  hbtype = *p++;

  klee_make_symbolic(&hbtype, sizeof(unsigned short), "hbtype");

  unsigned char *q = p;

  klee_assert(klee_get_taint(q++, 1) == 1);
  klee_assert(klee_get_taint(q, 1) == 0);

  n2s(p, payload);

  // Here we check for taintedness: It seems both bytes
  // become tainted, possibly due to bitwise or in n2s.
  // This can be considered an overtainting.
  unsigned char *r = &payload;
  klee_assert(klee_get_taint(r++, 1) == 1);
  klee_assert(klee_get_taint(r, 1) == 1);

 pl = p;

  if (hbtype == TLS1_HB_REQUEST) {
    unsigned char *buffer, *bp;
    
    /* Allocate memory for the response, size is 1 bytes
     * message type, plus 2 bytes payload length, plus
     * payload, plus padding
     */
    buffer = malloc(1 + 2 + payload + padding);
    bp = buffer;

    /* Enter response type, length and copy payload */
    *bp++ = TLS1_HB_RESPONSE;
    unsigned char *b = bp, *c = &payload;
    s2n(payload, bp);

    klee_assert(klee_get_taint(c++, 1) == 1);
    klee_assert(klee_get_taint(c, 1) == 1);

    klee_assert(klee_get_taint(b++, 1) == 1);
    klee_assert(klee_get_taint(b, 1) == 1);

    memcpy(bp, pl, payload);
    bp += payload;

    free(buffer);
  }

  return 0;
}
