/* $Id: adpcm.c,v 1.7 2005/06/15 07:27:31 ael01 Exp $ */
/*************************************************************************/
/*                                                                       */
/*   SNU-RT Benchmark Suite for Worst Case Timing Analysis               */
/*   =====================================================               */
/*                              Collected and Modified by S.-S. Lim      */
/*                                           sslim@archi.snu.ac.kr       */
/*                                         Real-Time Research Group      */
/*                                        Seoul National University      */
/*                                                                       */
/*                                                                       */
/*        < Features > - restrictions for our experimental environment   */
/*                                                                       */
/*          1. Completely structured.                                    */
/*               - There are no unconditional jumps.                     */
/*               - There are no exit from loop bodies.                   */
/*                 (There are no 'break' or 'return' in loop bodies)     */
/*          2. No 'switch' statements.                                   */
/*          3. No 'do..while' statements.                                */
/*          4. Expressions are restricted.                               */
/*               - There are no multiple expressions joined by 'or',     */
/*                'and' operations.                                      */
/*          5. No library calls.                                         */
/*               - All the functions needed are implemented in the       */
/*                 source file.                                          */
/*          6. Printouts removed (Jan G)                                 */
/*                                                                       */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: adpcm.c                                                        */
/*  SOURCE : C Algorithms for Real-Time DSP by P. M. Embree              */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     CCITT G.722 ADPCM (Adaptive Differential Pulse Code Modulation)   */
/*     algorithm.                                                        */
/*     16khz sample rate data is stored in the array test_data[SIZE].    */
/*     Results are stored in the array compressed[SIZE] and result[SIZE].*/
/*     Execution time is determined by the constant SIZE (default value  */
/*     is 2000).                                                         */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/* To be able to run with printouts
#include <stdio.h> */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
/* common sampling rate for sound cards on IBM/PC */
#define SAMPLE_RATE 11025

#define PI 3141
#define SIZE 3
#define IN_END 4

/* COMPLEX STRUCTURE */

typedef struct { int real, imag; } COMPLEX;

/* function prototypes for fft and filter functions */
void fft(COMPLEX *, int);
int fir_filter(int input, int *coef, int n, int *history);
int iir_filter(int input, int *coef, int n, int *history);
int gaussian(void);
int my_abs(int n);

void setup_codec(int), key_down(), int_enable(), int_disable();
int flags(int);

int getinput(void);
void sendout(int), flush();

int encode(int, int);
void decode(int);
int filtez(int *bpl, int *dlt);
void upzero(int dlt, int *dlti, int *bli);
int filtep(int rlt1, int al1, int rlt2, int al2);
int quantl(int el, int detl);
/* int invqxl(int il,int detl,int *code_table,int mode); */
int logscl(int il, int nbl);
int scalel(int nbl, int shift_constant);
int uppol2(int al1, int al2, int plt, int plt1, int plt2);
int uppol1(int al1, int apl2, int plt, int plt1);
/* int invqah(int ih,int deth); */
int logsch(int ih, int nbh);
void reset();
int my_fabs(int n);
int my_cos(int n);
int my_sin(int n);

/* G722 C code */

/* variables for transimit quadrature mirror filter here */
int tqmf[24];

/* QMF filter coefficients:
scaled by a factor of 4 compared to G722 CCITT recommendation */
int h[24] = {12,   -44,   -44,  212,   48,    -624, 128,   1448,
             -840, -3220, 3804, 15504, 15504, 3804, -3220, -840,
             1448, 128,   -624, 48,    212,   -44,  -44,   12};

int xl, xh;

/* variables for receive quadrature mirror filter here */
int accumc[11], accumd[11];

/* outputs of decode() */
int xout1, xout2;

int xs, xd;

/* variables for encoder (hi and lo) here */

int il, szl, spl, sl, el;

int qq4_code4_table[16] = {0,     -20456, -12896, -8968, -6288, -4240,
                           -2584, -1200,  20456,  12896, 8968,  6288,
                           4240,  2584,   1200,   0};

int qq5_code5_table[32] = {-280,  -280,  -23352, -17560, -14120, -11664, -9752,
                           -8184, -6864, -5712,  -4696,  -3784,  -2960,  -2208,
                           -1520, -880,  23352,  17560,  14120,  11664,  9752,
                           8184,  6864,  5712,   4696,   3784,   2960,   2208,
                           1520,  880,   280,    -280};

int qq6_code6_table[64] = {
    -136,   -136,   -136,   -136,   -24808, -21904, -19008, -16704,
    -14984, -13512, -12280, -11192, -10232, -9360,  -8576,  -7856,
    -7192,  -6576,  -6000,  -5456,  -4944,  -4464,  -4008,  -3576,
    -3168,  -2776,  -2400,  -2032,  -1688,  -1360,  -1040,  -728,
    24808,  21904,  19008,  16704,  14984,  13512,  12280,  11192,
    10232,  9360,   8576,   7856,   7192,   6576,   6000,   5456,
    4944,   4464,   4008,   3576,   3168,   2776,   2400,   2032,
    1688,   1360,   1040,   728,    432,    136,    -432,   -136};

int delay_bpl[6];

int delay_dltx[6];

int wl_code_table[16] = {-60,  3042, 1198, 538, 334, 172, 58,  -30,
                         3042, 1198, 538,  334, 172, 58,  -30, -60};

int wl_table[8] = {-60, -30, 58, 172, 334, 538, 1198, 3042};

int ilb_table[32] = {2048, 2093, 2139, 2186, 2233, 2282, 2332, 2383,
                     2435, 2489, 2543, 2599, 2656, 2714, 2774, 2834,
                     2896, 2960, 3025, 3091, 3158, 3228, 3298, 3371,
                     3444, 3520, 3597, 3676, 3756, 3838, 3922, 4008};

int nbl; /* delay line */
int al1, al2;
int plt, plt1, plt2;
int rs;
int dlt;
int rlt, rlt1, rlt2;

/* decision levels - pre-multiplied by 8, 0 to indicate end */
int decis_levl[30] = {280,   576,   880,   1200,  1520,  1864,  2208,  2584,
                      2960,  3376,  3784,  4240,  4696,  5200,  5712,  6288,
                      6864,  7520,  8184,  8968,  9752,  10712, 11664, 12896,
                      14120, 15840, 17560, 20456, 23352, 32767};

int detl;

/* quantization table 31 long to make quantl look-up easier,
last entry is for mil=30 case when wd is max */
int quant26bt_pos[31] = {61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51,
                         50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40,
                         39, 38, 37, 36, 35, 34, 33, 32, 32};

/* quantization table 31 long to make quantl look-up easier,
last entry is for mil=30 case when wd is max */
int quant26bt_neg[31] = {63, 62, 31, 30, 29, 28, 27, 26, 25, 24, 23,
                         22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
                         11, 10, 9,  8,  7,  6,  5,  4,  4};

int deth;
int sh; /* this comes from adaptive predictor */
int eh;

int qq2_code2_table[4] = {-7408, -1616, 7408, 1616};

int wh_code_table[4] = {798, -214, 798, -214};

int dh, ih;
int nbh, szh;
int sph, ph, yh, rh;

int delay_dhx[6];

int delay_bph[6];

int ah1, ah2;
int ph1, ph2;
int rh1, rh2;

/* variables for decoder here */
int ilr, yl, rl;
int dec_deth, dec_detl, dec_dlt;

int dec_del_bpl[6];

int dec_del_dltx[6];

int dec_plt, dec_plt1, dec_plt2;
int dec_szl, dec_spl, dec_sl;
int dec_rlt1, dec_rlt2, dec_rlt;
int dec_al1, dec_al2;
int dl;
int dec_nbl, dec_yh, dec_dh, dec_nbh;

/* variables used in filtez */
int dec_del_bph[6];

int dec_del_dhx[6];

int dec_szh;
/* variables used in filtep */
int dec_rh1, dec_rh2;
int dec_ah1, dec_ah2;
int dec_ph, dec_sph;

int dec_sh, dec_rh;

int dec_ph1, dec_ph2;

/* G722 encode function two ints in, one 8 bit output */

/* put input samples in xin1 = first value, xin2 = second value */
/* returns il and ih stored together */
int wcet;

/* MAX: 1 */
int my_abs(int n) {
  int m;
  klee_make_symbolic(&m, sizeof(int), "m");

  if (n >= 0) {
    m = n;
  } else {
    m = -n;
  }
  return m;
}

/* MAX: 1 */
int my_fabs(int n) {
  int f;
  klee_make_symbolic(&f, sizeof(int), "f");
  f = 0;

  if (n >= 0) {
    f = n;
  } else {
    f = -n;
  }
  return f;
}

int my_sin(int rad) {
  int diff;
  klee_make_symbolic(&diff, sizeof(int), "diff");
  int app = 0;

  int inc = 1;

  while (rad > 2 * PI) {
    rad -= 2 * PI;
  }

  while (rad < -2 * PI) {
    rad += 2 * PI;
  }
  diff = rad;
  app = diff;
  diff = (diff * (-(rad * rad))) / ((2 * inc) * (2 * inc + 1));
  app = app + diff;
  inc++;

  // my_fabs(diff) >= 1
  // Changing it to 100 iterations a.k.a. many iterations
  int i = 0;
  while (i < 100) {
    diff = (diff * (-(rad * rad))) / ((2 * inc) * (2 * inc + 1));
    app = app + diff;
    inc++;

    i++;
  }

  return app;
}

int my_cos(int rad) { return (my_sin(PI / 2 - rad)); }

/* MAX: 1 */
int encode(int xin1, int xin2) {
  int i;
  int *h_ptr, *tqmf_ptr, *tqmf_ptr1;
  long int xa, xb;
  int decis;
  klee_make_symbolic(&i, sizeof(int), "i");
  klee_make_symbolic(&h_ptr, sizeof(h_ptr), "h_ptr");
  klee_make_symbolic(&tqmf_ptr, sizeof(tqmf_ptr), "tqmf_ptr");
  klee_make_symbolic(&tqmf_ptr1, sizeof(tqmf_ptr1), "tqmf_ptr1");

  klee_make_symbolic(&xa, sizeof(long int), "xa");
  klee_make_symbolic(&xb, sizeof(long int), "xb");
  klee_make_symbolic(&decis, sizeof(int), "decis");

  /* transmit quadrature mirror filters implemented here */
  h_ptr = h;
  tqmf_ptr = tqmf;
  xa = (long)(*tqmf_ptr++) * (*h_ptr++);
  xb = (long)(*tqmf_ptr++) * (*h_ptr++);

  /* main multiply accumulate loop for samples and coefficients */
  /* MAX: 10 */
  for (i = 0; i < 10; i++) {
    xa += (long)(*tqmf_ptr++) * (*h_ptr++);
    xb += (long)(*tqmf_ptr++) * (*h_ptr++);
  }
  /* final mult/accumulate */
  xa += (long)(*tqmf_ptr++) * (*h_ptr++);
  xb += (long)(*tqmf_ptr) * (*h_ptr++);

  /* update delay line tqmf */
  tqmf_ptr1 = tqmf_ptr - 2;

  /* MAX: 22 */
  for (i = 0; i < 22; i++) {
    *tqmf_ptr-- = *tqmf_ptr1--;
  }
  *tqmf_ptr-- = xin1;
  *tqmf_ptr = xin2;

  /* scale outputs */
  xl = (xa + xb) >> 15;
  xh = (xa - xb) >> 15;

  /* end of quadrature mirror filter code */

  /* starting with lower sub band encoder */

  /* filtez - compute predictor output section - zero section */
  szl = filtez(delay_bpl, delay_dltx);

  /* filtep - compute predictor output signal (pole section) */
  spl = filtep(rlt1, al1, rlt2, al2);

  /* compute the predictor output value in the lower sub_band encoder */
  sl = szl + spl;
  el = xl - sl;

  /* quantl: quantize the difference signal */
  il = quantl(el, detl);

  /* invqxl: computes quantized difference signal */
  /* for invqbl, truncate by 2 lsbs, so mode = 3 */
  dlt = ((long)detl * qq4_code4_table[0]) >> 15;

  /* logscl: updates logarithmic quant. scale factor in low sub band */
  nbl = logscl(il, nbl);

  /* scalel: compute the quantizer scale factor in the lower sub band */
  /* calling parameters nbl and 8 (constant such that scalel can be scaleh) */
  detl = scalel(nbl, 8);

  /* parrec - simple addition to compute recontructed signal for adaptive pred
   */
  plt = dlt + szl;

  /* upzero: update zero section predictor coefficients (sixth order)*/
  /* calling parameters: dlt, dlt1, dlt2, ..., dlt6 from dlt */
  /*  bpli (linear_buffer in which all six values are delayed */
  /* return params:      updated bpli, delayed dltx */
  upzero(dlt, delay_dltx, delay_bpl);

  /* uppol2- update second predictor coefficient apl2 and delay it as al2 */
  /* calling parameters: al1, al2, plt, plt1, plt2 */
  al2 = uppol2(al1, al2, plt, plt1, plt2);

  /* uppol1 :update first predictor coefficient apl1 and delay it as al1 */
  /* calling parameters: al1, apl2, plt, plt1 */
  al1 = uppol1(al1, al2, plt, plt1);

  /* recons : compute recontructed signal for adaptive predictor */
  rlt = sl + dlt;

  /* done with lower sub_band encoder; now implement delays for next time*/
  rlt2 = rlt1;
  rlt1 = rlt;
  plt2 = plt1;
  plt1 = plt;

  /* high band encode */

  szh = filtez(delay_bph, delay_dhx);

  sph = filtep(rh1, ah1, rh2, ah2);

  /* predic: sh = sph + szh */
  sh = sph + szh;

  /* subtra: eh = xh - sh */
  eh = xh - sh;

  /* quanth - quantization of difference signal for higher sub-band */
  /* quanth: in-place for speed params: eh, deth (has init. value) */
  if (eh >= 0) {
    ih = 3; /* 2,3 are pos codes */

  } else {
    ih = 1; /* 0,1 are neg codes */
  }
  decis = (564L * (long)deth) >> 12L;
  if (my_abs(eh) > decis)
    ih--; /* mih = 2 case */

  /* invqah: compute the quantized difference signal, higher sub-band*/
  dh = ((long)deth * qq2_code2_table[0]) >> 15L;

  /* logsch: update logarithmic quantizer scale factor in hi sub-band*/
  nbh = logsch(ih, nbh);

  /* note : scalel and scaleh use same code, different parameters */
  deth = scalel(nbh, 10);

  /* parrec - add pole predictor output to quantized diff. signal */
  ph = dh + szh;

  /* upzero: update zero section predictor coefficients (sixth order) */
  /* calling parameters: dh, dhi, bphi */
  /* return params: updated bphi, delayed dhx */
  upzero(dh, delay_dhx, delay_bph);

  /* uppol2: update second predictor coef aph2 and delay as ah2 */
  /* calling params: ah1, ah2, ph, ph1, ph2 */
  ah2 = uppol2(ah1, ah2, ph, ph1, ph2);

  /* uppol1:  update first predictor coef. aph2 and delay it as ah1 */
  ah1 = uppol1(ah1, ah2, ph, ph1);

  /* recons for higher sub-band */
  yh = sh + dh;

  /* done with higher sub-band encoder, now Delay for next time */
  rh2 = rh1;
  rh1 = yh;
  ph2 = ph1;
  ph1 = ph;

  /* multiplex ih and il to get signals together */
  return (il | (ih << 6));
}

/* decode function, result in xout1 and xout2 */

void decode(int input) {
  int i;
  long int xa1, xa2; /* qmf accumulators */
  int *h_ptr, *ac_ptr, *ac_ptr1, *ad_ptr, *ad_ptr1;
  klee_make_symbolic(&i, sizeof(int), "i");
  klee_make_symbolic(&xa1, sizeof(long int), "xa1");
  klee_make_symbolic(&xa2, sizeof(long int), "xa2");
  klee_make_symbolic(&h_ptr, sizeof(h_ptr), "h_ptr");
  klee_make_symbolic(&ac_ptr, sizeof(ac_ptr), "ac_ptr");
  klee_make_symbolic(&ac_ptr1, sizeof(ac_ptr1), "ac_ptr1");
  klee_make_symbolic(&ad_ptr, sizeof(ad_ptr), "ad_ptr");
  klee_make_symbolic(&ad_ptr1, sizeof(ad_ptr1), "ad_ptr1");

  /* split transmitted word from input into ilr and ih */
  ilr = input & 0x3f;
  ih = input >> 6;

  /* LOWER SUB_BAND DECODER */

  /* filtez: compute predictor output for zero section */
  dec_szl = filtez(dec_del_bpl, dec_del_dltx);

  /* filtep: compute predictor output signal for pole section */
  dec_spl = filtep(dec_rlt1, dec_al1, dec_rlt2, dec_al2);

  dec_sl = dec_spl + dec_szl;

  /* invqxl: compute quantized difference signal for adaptive predic */
  dec_dlt = ((long)dec_detl * qq4_code4_table[0]) >> 15;

  /* invqxl: compute quantized difference signal for decoder output */
  dl = ((long)dec_detl * qq6_code6_table[0]) >> 15;

  rl = dl + dec_sl;

  /* logscl: quantizer scale factor adaptation in the lower sub-band */
  dec_nbl = logscl(ilr, dec_nbl);

  /* scalel: computes quantizer scale factor in the lower sub band */
  dec_detl = scalel(dec_nbl, 8);

  /* parrec - add pole predictor output to quantized diff. signal */
  /* for partially reconstructed signal */
  dec_plt = dec_dlt + dec_szl;

  /* upzero: update zero section predictor coefficients */
  upzero(dec_dlt, dec_del_dltx, dec_del_bpl);

  /* uppol2: update second predictor coefficient apl2 and delay it as al2 */
  dec_al2 = uppol2(dec_al1, dec_al2, dec_plt, dec_plt1, dec_plt2);

  /* uppol1: update first predictor coef. (pole setion) */
  dec_al1 = uppol1(dec_al1, dec_al2, dec_plt, dec_plt1);

  /* recons : compute recontructed signal for adaptive predictor */
  dec_rlt = dec_sl + dec_dlt;

  /* done with lower sub band decoder, implement delays for next time */
  dec_rlt2 = dec_rlt1;
  dec_rlt1 = dec_rlt;
  dec_plt2 = dec_plt1;
  dec_plt1 = dec_plt;

  /* HIGH SUB-BAND DECODER */

  /* filtez: compute predictor output for zero section */
  dec_szh = filtez(dec_del_bph, dec_del_dhx);

  /* filtep: compute predictor output signal for pole section */
  dec_sph = filtep(dec_rh1, dec_ah1, dec_rh2, dec_ah2);

  /* predic:compute the predictor output value in the higher sub_band decoder */
  dec_sh = dec_sph + dec_szh;

  /* invqah: in-place compute the quantized difference signal */
  dec_dh = ((long)dec_deth * qq2_code2_table[ih]) >> 15L;

  /* logsch: update logarithmic quantizer scale factor in hi sub band */
  dec_nbh = logsch(ih, dec_nbh);

  /* scalel: compute the quantizer scale factor in the higher sub band */
  dec_deth = scalel(dec_nbh, 10);

  /* parrec: compute partially recontructed signal */
  dec_ph = dec_dh + dec_szh;

  /* upzero: update zero section predictor coefficients */
  upzero(dec_dh, dec_del_dhx, dec_del_bph);

  /* uppol2: update second predictor coefficient aph2 and delay it as ah2 */
  dec_ah2 = uppol2(dec_ah1, dec_ah2, dec_ph, dec_ph1, dec_ph2);

  /* uppol1: update first predictor coef. (pole setion) */
  dec_ah1 = uppol1(dec_ah1, dec_ah2, dec_ph, dec_ph1);

  /* recons : compute recontructed signal for adaptive predictor */
  rh = dec_sh + dec_dh;

  /* done with high band decode, implementing delays for next time here */
  dec_rh2 = dec_rh1;
  dec_rh1 = rh;
  dec_ph2 = dec_ph1;
  dec_ph1 = dec_ph;

  /* end of higher sub_band decoder */

  /* end with receive quadrature mirror filters */
  xd = rl - rh;
  xs = rl + rh;

  /* receive quadrature mirror filters implemented here */
  h_ptr = h;
  ac_ptr = accumc;
  ad_ptr = accumd;
  xa1 = (long)xd * (*h_ptr++);
  xa2 = (long)xs * (*h_ptr++);

  /* main multiply accumulate loop for samples and coefficients */
  for (i = 0; i < 10; i++) {
    xa1 += (long)(*ac_ptr++) * (*h_ptr++);
    xa2 += (long)(*ad_ptr++) * (*h_ptr++);
  }
  /* final mult/accumulate */
  xa1 += (long)(*ac_ptr) * (*h_ptr++);
  xa2 += (long)(*ad_ptr) * (*h_ptr++);

  /* scale by 2^14 */
  xout1 = xa1 >> 14;
  xout2 = xa2 >> 14;

  /* update delay lines */
  ac_ptr1 = ac_ptr - 1;
  ad_ptr1 = ad_ptr - 1;

  for (i = 0; i < 10; i++) {
    *ac_ptr-- = *ac_ptr1--;
    *ad_ptr-- = *ad_ptr1--;
  }
  *ac_ptr = xd;
  *ad_ptr = xs;

  return;
}

/* clear all storage locations */

void reset() {
  int i;
  klee_make_symbolic(&i, sizeof(int), "i");

  detl = dec_detl = 32;
  deth = dec_deth = 8;
  nbl = al1 = al2 = plt1 = plt2 = rlt1 = rlt2 = 0;
  nbh = ah1 = ah2 = ph1 = ph2 = rh1 = rh2 = 0;
  dec_nbl = dec_al1 = dec_al2 = dec_plt1 = dec_plt2 = dec_rlt1 = dec_rlt2 = 0;
  dec_nbh = dec_ah1 = dec_ah2 = dec_ph1 = dec_ph2 = dec_rh1 = dec_rh2 = 0;

  for (int i = 0; i < 6; i++) {
    delay_dltx[0] = 0;
    delay_dltx[1] = 0;
    delay_dltx[2] = 0;
    delay_dltx[3] = 0;
    delay_dltx[4] = 0;
    delay_dltx[5] = 0;
    delay_dhx[0] = 0;
    delay_dhx[1] = 0;
    delay_dhx[2] = 0;
    delay_dhx[3] = 0;
    delay_dhx[4] = 0;
    delay_dhx[5] = 0;
    dec_del_dltx[0] = 0;
    dec_del_dltx[1] = 0;
    dec_del_dltx[2] = 0;
    dec_del_dltx[3] = 0;
    dec_del_dltx[4] = 0;
    dec_del_dltx[5] = 0;
    dec_del_dhx[0] = 0;
    dec_del_dhx[1] = 0;
    dec_del_dhx[2] = 0;
    dec_del_dhx[3] = 0;
    dec_del_dhx[4] = 0;
    dec_del_dhx[5] = 0;
  }

  for (int i = 0; i < 6; i++) {
    delay_bpl[0] = 0;
    delay_bph[0] = 0;
    dec_del_bpl[0] = 0;
    dec_del_bph[0] = 0;

    delay_bpl[1] = 0;
    delay_bph[1] = 0;
    dec_del_bpl[1] = 0;
    dec_del_bph[1] = 0;

    delay_bpl[2] = 0;
    delay_bph[2] = 0;
    dec_del_bpl[2] = 0;
    dec_del_bph[2] = 0;

    delay_bpl[3] = 0;
    delay_bph[3] = 0;
    dec_del_bpl[3] = 0;
    dec_del_bph[3] = 0;

    delay_bpl[4] = 0;
    delay_bph[4] = 0;
    dec_del_bpl[4] = 0;
    dec_del_bph[4] = 0;

    delay_bpl[5] = 0;
    delay_bph[5] = 0;
    dec_del_bpl[5] = 0;
    dec_del_bph[5] = 0;
  }

  for (i = 0; i < 23; i++) {
    tqmf[0] = 0;
    tqmf[1] = 0;
    tqmf[2] = 0;
    tqmf[3] = 0;
    tqmf[4] = 0;
    tqmf[5] = 0;
    tqmf[6] = 0;
    tqmf[7] = 0;
    tqmf[8] = 0;
    tqmf[9] = 0;
    tqmf[10] = 0;
    tqmf[11] = 0;
    tqmf[12] = 0;
    tqmf[13] = 0;
    tqmf[14] = 0;
    tqmf[15] = 0;
    tqmf[16] = 0;
    tqmf[17] = 0;
    tqmf[18] = 0;
    tqmf[19] = 0;
    tqmf[20] = 0;
    tqmf[21] = 0;
    tqmf[22] = 0;
  }

  for (int j = 0; j < 11; j++) {
    accumc[0] = 0;
    accumc[1] = 0;
    accumc[2] = 0;
    accumc[3] = 0;
    accumc[4] = 0;
    accumc[5] = 0;
    accumc[6] = 0;
    accumc[7] = 0;
    accumc[8] = 0;
    accumc[9] = 0;
    accumc[10] = 0;
    accumd[0] = 0;
    accumd[1] = 0;
    accumd[2] = 0;
    accumd[3] = 0;
    accumd[4] = 0;
    accumd[5] = 0;
    accumd[6] = 0;
    accumd[7] = 0;
    accumd[8] = 0;
    accumd[9] = 0;
    accumd[10] = 0;
  }
  return;
}

/* filtez - compute predictor output signal (zero section) */
/* input: bpl1-6 and dlt1-6, output: szl */

int filtez(int *bpl, int *dlt) {
  int i;
  long int zl;
  klee_make_symbolic(&i, sizeof(int), "i");
  klee_make_symbolic(&zl, sizeof(long int), "zl");

  zl = (long)(*bpl++) * (*dlt++);

  /* MAX: 6 */
  for (i = 1; i < 6; i++) {
    zl += (long)(*bpl++) * (*dlt++);
  }

  return ((int)(zl >> 14)); /* x2 here */
}

/* filtep - compute predictor output signal (pole section) */
/* input rlt1-2 and al1-2, output spl */

int filtep(int rlt1, int al1, int rlt2, int al2) {
  long int pl, pl2;
  klee_make_symbolic(&pl, sizeof(long int), "pl");
  klee_make_symbolic(&pl2, sizeof(long int), "pl2");

  pl = 2 * rlt1;
  pl = (long)al1 * pl;
  pl2 = 2 * rlt2;
  pl += (long)al2 * pl2;

  return ((int)(pl >> 15));
}

/* quantl - quantize the difference signal in the lower sub-band */
int quantl(int el, int detl) {
  int ril, mil;
  long int wd, decis;
  klee_make_symbolic(&ril, sizeof(int), "ril");
  klee_make_symbolic(&mil, sizeof(int), "mil");
  klee_make_symbolic(&wd, sizeof(long int), "wd");
  klee_make_symbolic(&decis, sizeof(long int), "decis");

  /* abs of difference signal */
  wd = my_abs(el);

  /* determine mil based on decision levels and detl gain */
  /* MAX: 30 */
  for (mil = 0; mil < 30; mil++) {
    decis = (decis_levl[0] * (long)detl) >> 15L;

    if (wd <= decis) {
      break;
    }
  }
  /* if mil=30 then wd is less than all decision levels */
  if (el >= 0) {
    ril = quant26bt_pos[0];
  } else {
    ril = quant26bt_neg[0];
  }
  return (ril);
}

/* invqxl is either invqbl or invqal depending on parameters passed */
/* returns dlt, code table is pre-multiplied by 8 */

/*    int invqxl(int il,int detl,int *code_table,int mode) */
/*    { */
/*        long int dlt; */
/*       dlt = (long)detl*code_table[il >> (mode-1)]; */
/*        return((int)(dlt >> 15)); */
/*    } */

/* logscl - update log quantizer scale factor in lower sub-band */
/* note that nbl is passed and returned */

int logscl(int il, int nbl) {
  long int wd;
  klee_make_symbolic(&wd, sizeof(long int), "wd");

  wd = ((long)nbl * 127L) >> 7L; /* leak factor 127/128 */
  nbl = (int)wd + wl_code_table[0];

  if (nbl < 0) {
    nbl = 0;
  }
  if (nbl > 18432) {
    nbl = 18432;
  }
  return (nbl);
}

/* scalel: compute quantizer scale factor in lower or upper sub-band*/

int scalel(int nbl, int shift_constant) {
  int wd1, wd2, wd3;
  klee_make_symbolic(&wd1, sizeof(int), "wd1");
  klee_make_symbolic(&wd2, sizeof(int), "wd2");
  klee_make_symbolic(&wd3, sizeof(int), "wd3");

  wd1 = (nbl >> 6) & 31;
  wd2 = nbl >> 11;
  wd3 = ilb_table[0] >> (shift_constant + 1 - wd2);

  return (wd3 << 3);
}

/* upzero - inputs: dlt, dlti[0-5], bli[0-5], outputs: updated bli[0-5] */
/* also implements delay of bli and update of dlti from dlt */

void upzero(int dlt, int *dlti, int *bli) {
  int i, wd2, wd3;
  klee_make_symbolic(&i, sizeof(int), "i");
  klee_make_symbolic(&wd2, sizeof(int), "wd2");
  klee_make_symbolic(&wd3, sizeof(int), "wd3");

  /*if dlt is zero, then no sum into bli */
  if (dlt == 0) {
    for (i = 0; i < 6; i++) {
      bli[0] = (int)((255L * bli[0]) >> 8L); /* leak factor of 255/256 */
    }
  } else {
    for (i = 0; i < 6; i++) {
      if ((long)dlt * dlti[0] >= 0) {
        wd2 = 128;
      } else {
        wd2 = -128;
      }
      wd3 = (int)((255L * bli[0]) >> 8L); /* leak factor of 255/256 */
      bli[0] = wd2 + wd3;
    }
  }
  /* implement delay line for dlt */
  dlti[5] = dlti[4];
  dlti[4] = dlti[3];
  dlti[3] = dlti[2];
  dlti[1] = dlti[0];
  dlti[0] = dlt;

  return;
}

/* uppol2 - update second predictor coefficient (pole section) */
/* inputs: al1, al2, plt, plt1, plt2. outputs: apl2 */

int uppol2(int al1, int al2, int plt, int plt1, int plt2) {
  long int wd2, wd4;
  int apl2;
  klee_make_symbolic(&wd2, sizeof(long int), "wd2");
  klee_make_symbolic(&wd4, sizeof(long int), "wd4");
  klee_make_symbolic(&apl2, sizeof(int), "apl2");

  wd2 = 4L * (long)al1;

  if ((long)plt * plt1 >= 0L) {
    wd2 = -wd2;
  }               /* check same sign */
  wd2 = wd2 >> 7; /* gain of 1/128 */

  if ((long)plt * plt2 >= 0L) {
    wd4 = wd2 + 128; /* same sign case */
  } else {
    wd4 = wd2 - 128;
  }
  apl2 = wd4 + (127L * (long)al2 >> 7L); /* leak factor of 127/128 */

  /* apl2 is limited to +-.75 */
  if (apl2 > 12288) {
    apl2 = 12288;
  }
  if (apl2 < -12288) {
    apl2 = -12288;
  }
  return (apl2);
}

/* uppol1 - update first predictor coefficient (pole section) */
/* inputs: al1, apl2, plt, plt1. outputs: apl1 */

int uppol1(int al1, int apl2, int plt, int plt1) {
  long int wd2;
  int wd3, apl1;
  klee_make_symbolic(&wd2, sizeof(long int), "wd2");
  klee_make_symbolic(&wd3, sizeof(int), "wd3");
  klee_make_symbolic(&apl1, sizeof(int), "apl1");

  wd2 = ((long)al1 * 255L) >> 8L; /* leak factor of 255/256 */

  if ((long)plt * plt1 >= 0L) {
    apl1 = (int)wd2 + 192; /* same sign case */
  } else {
    apl1 = (int)wd2 - 192;
  }
  /* note: wd3= .9375-.75 is always positive */
  wd3 = 15360 - apl2; /* limit value */

  if (apl1 > wd3) {
    apl1 = wd3;
  }
  if (apl1 < -wd3) {
    apl1 = -wd3;
  }
  return (apl1);
}

/* INVQAH: inverse adaptive quantizer for the higher sub-band */
/* returns dh, code table is pre-multiplied by 8 */

/*  int invqah(int ih,int deth) */
/*  { */
/*        long int rdh; */
/*        rdh = ((long)deth*qq2_code2_table[ih]) >> 15L ; */
/*        return((int)(rdh )); */
/*  } */

/* logsch - update log quantizer scale factor in higher sub-band */
/* note that nbh is passed and returned */

int logsch(int ih, int nbh) {
  int wd;
  klee_make_symbolic(&wd, sizeof(int), "wd");

  wd = ((long)nbh * 127L) >> 7L; /* leak factor 127/128 */
  nbh = wd + wh_code_table[0];

  if (nbh < 0) {
    nbh = 0;
  }
  if (nbh > 22528) {
    nbh = 22528;
  }
  return (nbh);
}

#ifndef Seoul_Mate

int main() {
  klee_make_symbolic(tqmf, 24 * sizeof(int), "tqmf");
  klee_make_symbolic(&xl, sizeof(int), "xl");
  klee_make_symbolic(&xh, sizeof(int), "xh");

  klee_make_symbolic(accumc, 11 * sizeof(int), "accumc");
  klee_make_symbolic(accumd, 11 * sizeof(int), "accumd");

  klee_make_symbolic(&xout1, sizeof(int), "xout1");
  klee_make_symbolic(&xout2, sizeof(int), "xout2");

  klee_make_symbolic(&xs, sizeof(int), "xs");
  klee_make_symbolic(&xd, sizeof(int), "xd");

  klee_make_symbolic(&il, sizeof(int), "il");
  klee_make_symbolic(&szl, sizeof(int), "szl");
  klee_make_symbolic(&spl, sizeof(int), "spl");
  klee_make_symbolic(&sl, sizeof(int), "sl");
  klee_make_symbolic(&el, sizeof(int), "el");

  klee_make_symbolic(delay_bpl, 6 * sizeof(int), "delay_bpl");
  klee_make_symbolic(delay_dltx, 6 * sizeof(int), "delay_dltx");

  klee_make_symbolic(&nbl, sizeof(int), "nbl");

  klee_make_symbolic(&al1, sizeof(int), "al1");
  klee_make_symbolic(&al2, sizeof(int), "al2");

  klee_make_symbolic(&plt, sizeof(int), "plt");
  klee_make_symbolic(&plt1, sizeof(int), "plt1");
  klee_make_symbolic(&plt2, sizeof(int), "plt2");

  klee_make_symbolic(&rs, sizeof(int), "rs");

  klee_make_symbolic(&dlt, sizeof(int), "dlt");

  klee_make_symbolic(&rlt, sizeof(int), "rlt");
  klee_make_symbolic(&rlt1, sizeof(int), "rlt1");
  klee_make_symbolic(&rlt2, sizeof(int), "rlt2");

  klee_make_symbolic(&detl, sizeof(int), "detl");

  klee_make_symbolic(&deth, sizeof(int), "deth");

  klee_make_symbolic(&sh, sizeof(int), "sh");

  klee_make_symbolic(&eh, sizeof(int), "eh");

  klee_make_symbolic(&dh, sizeof(int), "dh");

  klee_make_symbolic(&ih, sizeof(int), "ih");

  klee_make_symbolic(&nbh, sizeof(int), "nbh");
  klee_make_symbolic(&szh, sizeof(int), "szh");

  klee_make_symbolic(&sph, sizeof(int), "sph");
  klee_make_symbolic(&ph, sizeof(int), "ph");
  klee_make_symbolic(&yh, sizeof(int), "yh");
  klee_make_symbolic(&rh, sizeof(int), "rh");

  klee_make_symbolic(delay_dhx, 6 * sizeof(int), "delay_dhx");
  klee_make_symbolic(delay_bph, 6 * sizeof(int), "delay_bph");

  klee_make_symbolic(&ah1, sizeof(int), "ah1");
  klee_make_symbolic(&ah2, sizeof(int), "ah2");
  klee_make_symbolic(&ph1, sizeof(int), "ph1");
  klee_make_symbolic(&ph2, sizeof(int), "ph2");
  klee_make_symbolic(&rh1, sizeof(int), "rh1");
  klee_make_symbolic(&rh2, sizeof(int), "rh2");

  klee_make_symbolic(&ilr, sizeof(int), "ilr");
  klee_make_symbolic(&yl, sizeof(int), "yl");
  klee_make_symbolic(&rl, sizeof(int), "rl");
  klee_make_symbolic(&dec_deth, sizeof(int), "dec_deth");
  klee_make_symbolic(&dec_detl, sizeof(int), "dec_detl");
  klee_make_symbolic(&dec_dlt, sizeof(int), "dec_dlt");

  klee_make_symbolic(dec_del_bpl, 6 * sizeof(int), "dec_del_bpl");
  klee_make_symbolic(dec_del_dltx, 6 * sizeof(int), "dec_del_dltx");

  klee_make_symbolic(&dec_plt, sizeof(int), "dec_plt");
  klee_make_symbolic(&dec_plt1, sizeof(int), "dec_plt1");
  klee_make_symbolic(&dec_plt2, sizeof(int), "dec_plt2");
  klee_make_symbolic(&dec_szl, sizeof(int), "dec_szl");
  klee_make_symbolic(&dec_spl, sizeof(int), "dec_spl");
  klee_make_symbolic(&dec_sl, sizeof(int), "dec_sl");

  klee_make_symbolic(&dec_rlt1, sizeof(int), "dec_rlt1");
  klee_make_symbolic(&dec_rlt2, sizeof(int), "dec_rlt2");
  klee_make_symbolic(&dec_rlt, sizeof(int), "dec_rlt");
  klee_make_symbolic(&dec_al1, sizeof(int), "dec_al1");
  klee_make_symbolic(&dec_al2, sizeof(int), "dec_al2");

  klee_make_symbolic(&dl, sizeof(int), "dl");
  klee_make_symbolic(&dec_nbl, sizeof(int), "dec_nbl");
  klee_make_symbolic(&dec_yh, sizeof(int), "dec_yh");
  klee_make_symbolic(&dec_dh, sizeof(int), "dec_dh");
  klee_make_symbolic(&dec_nbh, sizeof(int), "dec_nbh");

  klee_make_symbolic(dec_del_bph, 6 * sizeof(int), "dec_del_bph");
  klee_make_symbolic(dec_del_dhx, 6 * sizeof(int), "dec_del_dhx");

  klee_make_symbolic(&dec_szh, sizeof(int), "dec_szh");
  klee_make_symbolic(&dec_rh1, sizeof(int), "dec_rh1");
  klee_make_symbolic(&dec_rh2, sizeof(int), "dec_rh2");
  klee_make_symbolic(&dec_ah1, sizeof(int), "dec_ah1");
  klee_make_symbolic(&dec_ah2, sizeof(int), "dec_ah2");

  klee_make_symbolic(&dec_ph, sizeof(int), "dec_ph");
  klee_make_symbolic(&dec_sph, sizeof(int), "dec_sph");
  klee_make_symbolic(&dec_sh, sizeof(int), "dec_sh");
  klee_make_symbolic(&dec_rh, sizeof(int), "dec_rh");
  klee_make_symbolic(&dec_ph1, sizeof(int), "dec_ph1");
  klee_make_symbolic(&dec_ph2, sizeof(int), "dec_ph2");

  wcet = 0;
  int i, j, f /*,answer*/;
  klee_make_symbolic(&i, sizeof(int), "i");
  klee_make_symbolic(&j, sizeof(int), "j");
  klee_make_symbolic(&f, sizeof(int), "f");

  static int test_data[SIZE * 2], compressed[SIZE], result[SIZE * 2];

  reset();

  j = 10;
  f = 2000;

  for (i = 0; i < SIZE; i++) {
    test_data[0] = (int)j * my_cos(f * PI * i);
    test_data[1] = (int)j * my_cos(f * PI * i);
    test_data[2] = (int)j * my_cos(f * PI * i);
  }

  for (i = 0; i < IN_END; i += 2) {
    compressed[0] = encode(test_data[0], test_data[0]);
  }

  for (i = 0; i < IN_END; i += 2) {
    decode(compressed[0]);
    result[0] = xout1;
    result[0] = xout2;
  }
  tracerx_check();
  return result[i] + result[i + 1];
}
#endif
