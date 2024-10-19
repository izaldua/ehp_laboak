/*  Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)
    OpenMP laborategia

    habi.c       OpenMP adibide sinple bat

    Matrize bat prozesatzea atal paralelo habiaratuetan

    Adibidea: exekutatu baino lehen, export OMP_NUM_THREADS=2,2
    Gero, adierazi barneko atal paraleloen hari kopurua klausula batez
    Adibidez, num_threads (2*(tid+1))
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

#define N 6
#define M 8

int  tid;
#pragma omp threadprivate (tid)


void main ()
{
  int  i, j;
  int  A[N][M];


  // paralelismo habiaratua (nested)
  // matrize bat prozesatzea bi mailako habiaratzearekin 
  //  adi   tid -- threadprivate / copyin

  // aktibatu habiaratzea
  omp_set_nested (1);
 
  // 1. atal paraleloa
  #pragma omp parallel 
  {
    tid = omp_get_thread_num ();

    #pragma omp for private (i)
    for (i=0; i<N; i++)
    {
      // atal paralelo bat beste baten barruan
      #pragma omp parallel copyin (tid) 	// num_threads (2*(tid+1))
      {
        int  tid2 = omp_get_thread_num(); 

        #pragma omp for  private (j)
        for (j=0; j<M; j++)
          A[i][j] = tid*10 + tid2;

        printf ("\n tid = %d -- tid2 = %d", tid, tid2);
      }
    }
  }


  printf ("\n\n  2 mailako habiaratzea (nested) \n\n");
  for (i=0; i<N; i++)
  {
    for (j=0; j<M; j++) printf ("%3d", A[i][j]);
    printf ("\n");
  }
  printf ("\n");
}

