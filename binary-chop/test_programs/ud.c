/* Obtained from http://www.mrtc.mdh.se/projects/wcet/benchmarks.html,
 * with LLBMC and KLEE harnessing added */

/* MDH WCET BENCHMARK SUITE. File version $Id: ud.c,v 1.4 2005/11/11 10:32:53 ael01 Exp $ */


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
/*                                                                       */
/*                                                                       */
/*************************************************************************/
/*                                                                       */
/*  FILE: ludcmp.c                                                       */
/*  SOURCE : Turbo C Programming for Engineering                         */
/*                                                                       */
/*  DESCRIPTION :                                                        */
/*                                                                       */
/*     Simultaneous linear equations by LU decomposition.                */
/*     The arrays a[][] and b[] are input and the array x[] is output    */
/*     row vector.                                                       */
/*     The variable n is the number of equations.                        */
/*     The input arrays are initialized in function main.                */
/*                                                                       */
/*                                                                       */
/*  REMARK :                                                             */
/*                                                                       */
/*  EXECUTION TIME :                                                     */
/*                                                                       */
/*                                                                       */
/*************************************************************************/

/*************************************************************************
 *  This file:
 *
 *  - Name changed to "ud.c"
 *  - Modified for use with Uppsala/Paderborn tool
 *    : doubles changed to int
 *    : some tests removed
 *  - Program is much more linear, all loops will run to end
 *  - Purpose: test the effect of conditional flows
 *
 *************************************************************************/






/*
** Benchmark Suite for Real-Time Applications, by Sung-Soo Lim
**
**    III-4. ludcmp.c : Simultaneous Linear Equations by LU Decomposition
**                 (from the book C Programming for EEs by Hyun Soon Ahn)
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

long int a[50][50], b[50], x[50];

int ludcmp(int nmax, int n);


/*  static double fabs(double n) */
/*  { */
/*    double f; */

/*    if (n >= 0) f = n; */
/*    else f = -n; */
/*    return f; */
/*  } */

int wcet;
void tracerx_check() { printf("Timing of Path:%d\n",wcet); klee_assert(wcet < 584);}

int main()
{
  wcet = 0;
  int      i, j, nmax = 50, n = 5, chkerr;
  long int /* eps, */ w;

  /* eps = 1.0e-6; */

  /* Init loop */
  /* for(i = 0; i <= n; i++) */
  /*   { */
  /*     w = 0.0;              /\* data to fill in cells *\/ */
  /*     for(j = 0; j <= n; j++) */
  /*       { */
  /*         a[i][j] = (i + 1) + (j + 1); */
  /*         if(i == j)            /\* only once per loop pass *\/ */
  /*           a[i][j] *= 2.0; */
  /*         w += a[i][j]; */
  /*       } */
  /*     b[i] = w; */
  /*   } */

#ifdef LLBMC
  for (int i = 0; i < 50; ++i) {
    b[i] = __llbmc_nondef_long_int();
    x[i] = __llbmc_nondef_long_int();
    for (int j = 0; j < 50; ++j) {
      a[i][j] = __llbmc_nondef_long_int();
    }
  }
#else
  klee_make_symbolic(a, 50 * 50 * sizeof(long int), "a");
  klee_make_symbolic(b, 50 * sizeof(long int), "b");
  klee_make_symbolic(x, 50 * sizeof(long int), "x");
#endif

  /*  chkerr = ludcmp(nmax, n, eps); */
  chkerr = ludcmp(nmax,n);
  tracerx_check(wcet);
}

int ludcmp(int nmax, int n)
{
  int i, j, k;
  long w, y[100];

  /* if(n > 99 || eps <= 0.0) return(999); */
  /*for(i = 0; i < n; i++)w
    {
      for(j = i+1; j <= n; j++) 
        {
          w = a[j][i];
	  wcet++;
          if(i != 0){            
            for(k = 0; k < i; k++){
              w -= a[j][k] * a[k][i];wcet++;
	    }
	  }
	  klee_assume(a[i][i]>0);
          a[j][i] = w / a[i][i];
	  wcet++;
        }
      for(j = i+1; j <= n; j++) 
        {
          w = a[i+1][j];wcet++;
          for(k = 0; k <= i; k++){ 
            w -= a[i+1][k] * a[k][j];wcet++;
          }a[i+1][j] = w;wcet++;
        }
    }
  y[0] = b[0];wcet++;
  for(i = 1; i <= n; i++)       
    {
      w = b[i];wcet++;
      for(j = 0; j < i; j++){    
        w -= a[i][j] * y[j];wcet++;
      }y[i] = w;wcet++;
    }
  x[n] = y[n] / a[n][n];wcet++;
  for(i = n-1; i >= 0; i--)     
    {
      w = y[i];wcet++;
      for(j = i+1; j <= n; j++){ 
        w -= a[i][j] * x[j];wcet++;
      }
      x[i] = w / a[i][i] ;wcet++;
    }*/
  return(0);
}

