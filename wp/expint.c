/* Obtained from http://www.mrtc.mdh.se/projects/wcet/benchmarks.html,
 * with LLBMC and KLEE harnessing added */

/* $Id: expint.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

/************************************************************************
 * FROM:
 *   http://sron9907.sron.nl/manual/numrecip/c/expint.c
 *
 * FEATURE:
 *   One loop depends on a loop-invariant value to determine
 *   if it run or not.
 *
 ***********************************************************************/
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

long int expint(int n, long int x);
int wcet;
void tracerx_check() {
  printf("Timing of Path:%d\n", wcet);
  klee_assert(wcet < 50001);
}
int main(void) {
  wcet = 0;
  // with  expint(50,21) as argument, runs the short path
  // in expint.   expint(50,1)  gives the longest execution time

  // We make the second argument symbolic
  // expint(50,1);

  long int x;
#ifdef LLBMC
  x = __llbmc_nondef_signed_long_int();
  __llbmc_assume(x >= 1);
  __llbmc_assume(x <= 21);
#else
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_assume(x >= 1);
  klee_assume(x <= 21);
#endif

  expint(50, x);
  tracerx_check();
  return 0;
}

long int foo(long int x) {
  wcet++;
  return (x * x + (8 * x)) << (4 - x);
}

/* Function with same flow, different data types,
   nonsensical calculations */
long int expint(int n, long int x) {
  int i, ii, nm1;
  long int a, b, c, d, del, fact, h, psi, ans;

  nm1 = n - 1; /* arg=50 --> 49 */
  wcet++;

  if (x > 1) /* take this leg? */
  {
    b = x + n;
    wcet++;
    c = 2e6;
    wcet++;
    d = 3e7;
    wcet++;
    h = d;
    wcet++;

    for (i = 1; i <= 100; i++) /* MAXIT is 100 */
    {
      a = -i * (nm1 + i);
      wcet++;
      b += 2;
      wcet++;
      d = 10 * (a * d + b);
      wcet++;
      c = b + a / c;
      wcet++;
      del = c * d;
      wcet++;
      h *= del;
      wcet++;
      if (del < 10000) {
        wcet++;
        ans = h * -x;
        wcet++;
        return ans;
      }
    }
  } else /* or this leg? */
  {
    // For the current argument, will always take
    // '2' path here:
    ans = nm1 != 0 ? 2 : 1000;
    wcet++;
    fact = 1;
    wcet++;
    for (i = 1; i <= 100; i++) /* MAXIT */
    {
      fact *= -x / i;
      wcet++;
      if (i != nm1) { /* depends on parameter n */
        del = -fact / (i - nm1);
        wcet++;
      } else /* this fat piece only runs ONCE */
      {      /* runs on iter 49 */
        psi = 0x00FF;
        wcet++;
        for (ii = 1; ii <= nm1; ii++) { /*  */
          psi += ii + nm1;
          wcet++;
        }
        del = psi + fact * foo(x);
        wcet++;
      }
      ans += del;
      wcet++;
      /* conditional leave removed */
    }
  }
  return ans;
}

/*  #define MAXIT 100 */
/*  #define EULER 0.5772156649 */
/*  #define FPMIN 1.0e-30 */
/*  #define EPS 1.0e-7 */
/*  float expint(int n, float x) */
/*  { */
/*    void nrerror(char error_text[]); */
/*    int i,ii,nm1; */
/*    float a,b,c,d,del,fact,h,psi,ans; */

/*    nm1=n-1; */
/*    if (n < 0 || x < 0.0 || (x==0.0 && (n==0 || n==1))) */
/*    nrerror("bad arguments in expint");                */
/*     else {  */
/*    if (n == 0)  */
/*      ans=exp(-x)/x; */
/*    else  */
/*      { */
/*        if (x == 0.0)  */
/*          ans=1.0/nm1; */
/*        else  */
/*          { */
/*            if (x > 1.0) { */
/*              b=x+n; */
/*              c=1.0/FPMIN; */
/*              d=1.0/b; */
/*              h=d; */

/*              for (i=1;i<=MAXIT;i++)  */
/*              { */
/*                a = -i*(nm1+i); */
/*                b += 2.0; */
/*                d=1.0/(a*d+b); */
/*                c=b+a/c; */
/*                del=c*d; */
/*                h *= del; */
/*                if (fabs(del-1.0) < EPS)  */
/*                  { */
/*                    ans=h*exp(-x); */
/*                    return ans; */
/*                  } */
/*              } */

/*            nrerror("continued fraction failed in expint");*/
/*          }  */
/*          else  */
/*            { */
/*              ans = (nm1!=0 ? 1.0/nm1 : -log(x)-EULER); */
/*            fact=1.0; */
/*            for (i=1;i<=MAXIT;i++) { */
/*              fact *= -x/i; */
/*              if (i != nm1) del = -fact/(i-nm1); */
/*              else { */
/*                psi = -EULER; */
/*                for (ii=1;ii<=nm1;ii++) psi += 1.0/ii; */
/*                del=fact*(-log(x)+psi); */
/*              } */
/*              ans += del; */
/*              if (fabs(del) < fabs(ans)*EPS) return ans; */
/*            } */
/*            nrerror("series failed in expint"); */
/*          } */
/*        } */
/*      } */
/*    } */
/*    return ans; */
/*  } */
