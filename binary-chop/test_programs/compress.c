/* MDH WCET BENCHMARK SUITE. File version $Id: compress.c,v 1.7 2005/12/21 09:37:18 jgn Exp $ */

/*
 * Compress - data compression program
 *
 * Adopted from SPEC95 for WCET-calculation by Thomas Lundqvist, 1997-11-28.
 * Only compression is done on a buffer (small one) containing
 * totally random data. This should come closer to a worst case
 * compared to the original SPEC95-version.
 *
 * All unused code removed by Jakob Engblom, february 2000.  Cleaned
 * up for IAR compilation.
 *
 * Removed the prototype declaration of "code_int getcode();" that is
 * niether defined nor used. Christer Sandberg
 *
 * Changes:
 * JG 2005/12/20: Changed declaration of maxmaxcode to avoid warning
 * JG 2012/09/28: Comment within comment removed
 */ 

/* #define DO_TRACING */

#ifdef DO_TRACING   /* ON PC */

#include <stdio.h>
#define TRACE(x) trace((x))
#undef TEST                   /* finished testing! */

/*
void trace(char *s)
{
    printf("%s\n",s);
}
*/

#else               /* ON TARGET */

#define TRACE(x)
#undef TEST

#endif

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif


#define BUFFERSIZE	50
#define IN_COUNT        BUFFERSIZE

#define HSIZE	257		/* 95% occupancy */
#define BITS 16
#define INIT_BITS 9			/* initial number of bits/code */



/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

#define	min(a,b)	((a>b) ? b : a)

/*
 * Set USERMEM to the maximum amount of physical user memory available
 * in bytes.  USERMEM is used to determine the maximum BITS that can be used
 * for compression.
 *
 * SACREDMEM is the amount of physical memory saved for others; compress
 * will hog the rest.
 */
/* For SPEC95 use, SACREDMEM automatically set to 0.
	Jeff Reilly, 1/15/95				*/

#define SACREDMEM	0

/* For SPEC95 use, USERMEM automatically set to 450000.
	Jeff Reilly, 1/15/95				*/
# define USERMEM 	450000	/* default user memory */

#ifdef interdata		/* (Perkin-Elmer) */
#define SIGNED_COMPARE_SLOW	/* signed compare is slower than unsigned */
#endif

/* For SPEC95 use, PBITS and BITS automatically set to 16.
	Jeff Reilyy, 1/15/95				*/
#define PBITS	16
#define BITS 16
#define HSIZE	257		/* 95% occupancy was 69001 */


/*
 * a code_int must be able to hold 2**BITS values of type int, and also -1
 */
#if BITS > 15
typedef long int	code_int;
#else
typedef int		code_int;
#endif

#ifdef SIGNED_COMPARE_SLOW
typedef unsigned long int count_int;
typedef unsigned short int count_short;
#else
typedef long int	  count_int;
#endif

typedef	unsigned char	char_type;

/* Defines for third byte of header */
#define BIT_MASK	0x1f
#define BLOCK_MASK	0x80
/* Masks 0x40 and 0x20 are free.  I think 0x20 should mean that there is
   a fourth header byte (for expansion).
*/

/* Global variables */
int n_bits;				/* number of bits/code */
int maxbits = BITS;			/* user settable max # bits/code */
code_int maxcode;			/* maximum code, given n_bits */
#if BITS > 15
code_int maxmaxcode = 1L << BITS;	/* should NEVER generate this code */
#else
code_int maxmaxcode = 1 << BITS;	/* should NEVER generate this code */
#endif

# define MAXCODE(n_bits)	((1 << (n_bits)) - 1)


#define htabof(i)	htab[i]
#define codetabof(i)	codetab[i]

code_int hsize = HSIZE;			/* for dynamic table sizing */
count_int fsize;

/*
 * To save much memory, we overlay the table used by compress() with those
 * used by decompress().  The tab_prefix table is the same size and type
 * as the codetab.  The tab_suffix table needs 2**BITS characters.  We
 * get this from the beginning of htab.  The output stack uses the rest
 * of htab, and contains characters.  There is plenty of room for any
 * possible stack (stack used to be 8000 characters).
 */

#define tab_prefixof(i)	codetabof(i)
#define tab_suffixof(i)	((char_type *)(htab))[i]
#define de_stack		((char_type *)&tab_suffixof(1<<BITS))

code_int free_ent = 0;			/* first unused entry */
int exit_stat = 0;

int nomagic = 1;	/* Use a 3-byte magic number header, unless old file */
int zcat_flg = 0;	/* Write output on stdout, suppress messages */
int quiet = 1;		/* don't tell me about compression */

/*
 * block compression parameters -- after all codes are used up,
 * and compression rate changes, start over.
 */
int block_compress = BLOCK_MASK;
int clear_flg = 0;
long int ratio = 0;
#define CHECK_GAP 10000	/* ratio check interval */
count_int checkpoint = CHECK_GAP;
/*
 * the next two codes should not be changed lightly, as they must not
 * lie within the contiguous general code space.
 */
#define FIRST	257	/* first free entry */
#define	CLEAR	256	/* table clear output code */

int force = 0;
char ofname [100];
int InCnt;
int apsim_InCnt;
unsigned char *InBuff;
unsigned char *OutBuff;

char orig_text_buffer[BUFFERSIZE];
char comp_text_buffer[BUFFERSIZE+5];

count_int htab [HSIZE];
unsigned short codetab [HSIZE];
char buf[BITS];



/*---------------------------------------------------- */
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/


/*----------------------------------------- Prototypes */
void initbuffer(void);
void compress(void);
void cl_hash(count_int hsize);		/* reset code table */
unsigned int getbyte(void);
void putbyte( char c );
void cl_block (void);
void output( code_int code );
void writebytes( char *buf, int n );
int wcet;
void tracerx_check() { printf("Timing of Path:%d\n",wcet); klee_assert(wcet < 1000);}

int main(void)
{
   wcet = 0;
   int count = IN_COUNT;
   wcet += 1;

   initbuffer();
   wcet += 1;

   /*if(maxbits < INIT_BITS) maxbits = INIT_BITS;*/
   /* With our setting, maxbits = 16,
                        INIT_BITS = 9 */
   /*if (maxbits > BITS) maxbits = BITS;*/
   maxbits = BITS;
   maxmaxcode = 1 << maxbits;
   wcet += 2;

   InCnt = count;
   apsim_InCnt = IN_COUNT + 3;
   InBuff = (unsigned char *)orig_text_buffer;
   OutBuff = (unsigned char *)comp_text_buffer;
   wcet += 4;

   compress();
   wcet += 1;
   tracerx_check();
   return (0);

}



void initbuffer(void)
{
   int seed = 1;
   wcet += 1;
   int i;
   int tabort;

   for (i = 0 ; i < BUFFERSIZE ; i++) {
      /* Generates random integers between 0 and 8095 */
      tabort = i;
      seed = ((seed * 133) + 81) % 8095;

      orig_text_buffer[i] = seed % 256;
      wcet += 3;
   }
}



static int offset;
long int in_count = 1;			/* length of input */
long int bytes_out;			/* length of compressed output */
long int out_count = 0;			/* # of codes output (for debugging) */


void compress(void)
{
   register long fcode;
   register code_int i = 0;wcet += 1;
   register int c;
   register code_int ent;
   register int disp;
   register code_int hsize_reg;
   register int hshift;


   offset = 0;
   bytes_out = 3;		/* includes 3-byte header mojo */
   out_count = 0;
   clear_flg = 0;
   ratio = 0;
   in_count = 1;
   checkpoint = CHECK_GAP;
   maxcode = MAXCODE(n_bits = INIT_BITS);
   free_ent = ((block_compress) ? (FIRST) : (256) );
   wcet += 9;

   ent = getbyte ();wcet += 1;

   hshift = 0;wcet += 1;
   for ( fcode = (long) hsize;  fcode < 65536L; fcode *= 2L )
   {
      hshift++;wcet += 1;
   }

   hshift = 8 - hshift;		
   wcet += 1;

   hsize_reg = hsize;
   cl_hash( (count_int) hsize_reg);		
   wcet += 2;


   while ( InCnt > 0 )           
   {
      int apsim_bound111 = 0;wcet += 1;
      c = getbyte();   
      wcet += 1;

      in_count++;
      fcode = (long) (((long) c << maxbits) + ent);
      i = ((c << hshift) ^ ent);	
      wcet += 3;

      if ( htabof (i) == fcode ) {
         ent = codetabof (i);
         wcet += 1;
         continue;
      } else if ( (long)htabof (i) < 0 ) { 
         wcet += 1;
         goto nomatch;
      }


      disp = hsize_reg - i;		
      wcet += 1;
      if ( i == 0 ) {
         disp = 1;wcet += 1;
      }

probe:

      if ( (i -= disp) < 0 ) {  
         i += hsize_reg;wcet += 1;
      }

      if ( htabof (i) == fcode ) {
         ent = codetabof (i);wcet += 2;
         continue;
      }

      if ( (long)htabof (i) > 0 && (++apsim_bound111 < in_count) )
         wcet += 1;
         goto probe;
nomatch:

      out_count++;
      ent = c;
      wcet += 1;
      if ( free_ent < maxmaxcode ) {
         codetabof (i) = free_ent++;
         htabof (i) = fcode;		
         wcet += 2;
      } else if ( ((count_int)in_count >= checkpoint) && (block_compress) ) {
         cl_block ();
         wcet += 1;
      }

   }
   if(bytes_out > in_count) { 
      exit_stat = 2;
      wcet += 1;
   }
   return;
}


void cl_block (void)		
{
   register long int rat;

   checkpoint = in_count + CHECK_GAP;
   wcet += 1;

   if(in_count > 0x007fffff) {	

      rat = bytes_out >> 8;wcet += 1;
      if(rat == 0) {		/* Don't divide by zero */
         rat = 0x7fffffff;wcet += 1;
      } else {
         rat = in_count / rat;wcet += 1;
      }
   } else {
      rat = (in_count << 8) / bytes_out;wcet += 1;	/* 8 fractional bits */
   }
   if ( rat > ratio ) {
      ratio = rat;wcet += 1;
   } else {
      ratio = 0;
      cl_hash ( (count_int) hsize );
      wcet += 2;


      free_ent = FIRST;
      clear_flg = 1;
      output ( (code_int) CLEAR );
      wcet += 3;
   }
}

void cl_hash(count_int hsize)		/* reset code table */
{
   register count_int *htab_p = htab+hsize;wcet += 1;
   register long i;
   register long m1 = -1;wcet += 1;

   i = hsize - 16;wcet += 1;
   do {				/* might use Sys V memset(3) here */

      *(htab_p-16) = m1;
      *(htab_p-15) = m1;
      *(htab_p-14) = m1;
      *(htab_p-13) = m1;
      *(htab_p-12) = m1;
      *(htab_p-11) = m1;
      *(htab_p-10) = m1;
      *(htab_p-9) = m1;
      *(htab_p-8) = m1;
      *(htab_p-7) = m1;
      *(htab_p-6) = m1;
      *(htab_p-5) = m1;
      *(htab_p-4) = m1;
      *(htab_p-3) = m1;
      *(htab_p-2) = m1;
      *(htab_p-1) = m1;
      htab_p -= 16;
      wcet += 17;
   } while ((i -= 16) >= 0);
   for ( i += 16; i > 0; i-- ) {
      *--htab_p = m1;wcet += 1;
   }
}



unsigned int getbyte(void)
{
   if( InCnt > 0 && (apsim_InCnt-- > 0)) {
      InCnt--;wcet += 1;
      return( (unsigned int)*InBuff++ );
   } else {
      return( -1 );wcet += 1;
   }
}

void putbyte( char c )
{
   *OutBuff++ = c;wcet += 1;       		 /* apsim_unknown comp_text_buffer */
}


void writebytes( char *buf, int n )
{
   int i;
   for( i=0; (i<n) && /*apsim*/ (i < BITS) ; i++ ) {
      *OutBuff++ = buf[i];wcet += 1;       		 /* apsim_unknown comp_text_buffer */
   }
}

/* apsim_rel 111 < 112 */

char_type lmask[9] = {0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00};
char_type rmask[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

void output( code_int code )
{
   /*
   * On the VAX, it is important to have the register declarations
   * in exactly the order given, or the asm will break.
   */
   register int r_off = offset, bits= n_bits;
   register char * bp = buf;
   wcet += 2;

   if ( code >= 0 ) {
      /*
      * byte/bit numbering on the VAX is simulated by the following code
      */
      /*
      * Get to the first byte.
      */
      bp += (r_off >> 3);
      r_off &= 7;
      wcet += 2;
      /*
      * Since code is always >= 8 bits, only need to mask the first
      * hunk on the left.
      */
      *bp = ((*bp & rmask[r_off]) | (code << r_off)) & lmask[r_off];  /* apsim_unknown buf */
      bp++;
      bits -= (8 - r_off);
      code >>= 8 - r_off;
      wcet += 4;
      /* Get any 8 bit parts in the middle (<=1 for up to 16 bits). */
      if ( bits >= 8 ) {

         *bp++ = code;  /* apsim_unknown buf */
         code >>= 8;
         bits -= 8;
         wcet += 3;
      }

      /* Last bits. */
      if(bits) {
         *bp = code;			 /* apsim_unknown buf */
         wcet += 1;
      }

      offset += n_bits;
      wcet += 1;
      if ( offset == (n_bits << 3) ) {
         bp = buf;
         bits = n_bits;
         bytes_out += bits;
         wcet += 3;
         do {
            putbyte(*bp++);
            wcet += 1;
         } while(( --bits) && ((bp - buf < BITS)));
         offset = 0;
         wcet += 1;
      }
      /*
      * If the next entry is going to be too big for the code size,
      * then increase it, if possible.
      */
      if ( free_ent > maxcode || ((clear_flg > 0))) {
         /*
         * Write the whole buffer, because the input side won't
         * discover the size increase until after it has read it.
         */
         if ( offset > 0 ) {
            writebytes( buf, n_bits );
            bytes_out += n_bits;
            wcet += 2;
         }
         offset = 0;
         wcet += 1;
         if ( clear_flg ) {
            maxcode = MAXCODE (n_bits = INIT_BITS);
            clear_flg = 0;
            wcet += 2;
         } else {
            n_bits++;
            wcet += 1;
            if ( n_bits == maxbits )
            {
               maxcode = maxmaxcode;
               wcet += 1;
            }
            else
            {
               maxcode = MAXCODE(n_bits);
               wcet += 1;
            }
         }
      }
   } else {
      /*
      * At EOF, write the rest of the buffer.
      */
      if ( offset > 0 )
      {
         writebytes( buf, ((offset + 7) / 8) );
         wcet += 1;
      }
      bytes_out += (offset + 7) / 8;
      offset = 0;
      wcet += 2;
   }
}

