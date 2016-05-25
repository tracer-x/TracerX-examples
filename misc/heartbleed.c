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

  klee_set_taint(1, &(p[2]), 2 * sizeof(unsigned char));

  hbtype = *p++;
  n2s(p, payload);
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
    s2n(payload, bp);

    klee_assert(klee_get_taint(&payload, sizeof payload) == 0);

    memcpy(bp, pl, payload);
    bp += payload;

    free(buffer);
  }

  return 0;
}
