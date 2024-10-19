/*
    fibopar.c	OpenMP bertsioa   -- task
    fibonacci segidaren osagaien kalkulu errekurtsiboa
*******************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int  kop[48];


int fibo (int x)
{
  int  f1, f2;


  if (x<2) return (x);
  else
  {
    #pragma omp task shared (f1) 
    {
      f1 = fibo (x-1);
//      printf ("\n  fibo(%d)  tid = %d", x-1, omp_get_thread_num ());
    }

    #pragma omp task shared (f2)
    {
      f2 = fibo (x-2);
//      printf ("\n  fibo(%d)  tid = %d", x-2, omp_get_thread_num ());
    }

    #pragma omp taskwait

//    kop[omp_get_thread_num ()]  ++;
//    printf ("\n  emaitza = %d  tid = %d", f1+f2, omp_get_thread_num ());
    return (f1 + f2);
  }
}


void main (int argc, char *argv[])
{
  int  N, i, emaitza;


  N = atoi (argv[1]);
//  for (i=0; i<32; i++) kop[i] = 0;


  #pragma omp parallel 
  {
    #pragma omp single
    {
       emaitza = fibo (N);
    }
  }


  printf ("\n\n  fibo (%d)  =  %d\n\n", N, emaitza);
//  for (i=0; i<omp_get_max_threads (); i++) printf ("\n  kop[%d] %d\n", i, kop[i]);
}
