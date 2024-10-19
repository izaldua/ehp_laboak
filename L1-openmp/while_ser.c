/*  EHP, Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)

    while_ser.c	

    while begizta bat paralelizatzea, task-en bidez

    konpilatzean  -lm
    PARALELIZATZEKO
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num()  0
  #define omp_get_max_threads() 1
#endif


#define N 10000

int A[N][N];
int iterkop[64];



// kalkulua simulatzen duen funtzioa (denbora sintetikoa)
float kalkulatu (int i)
{
  int    j, bpos = 0, bneg = 0;
  float  emaitza;


  for (j=1; j<N; j++)
    if (A[i][j] > 0) bpos += A[i][j];
    else             bneg += A[i][j];

  emaitza = sqrt ((float) (bpos*bpos + bneg*bneg));
  iterkop[omp_get_thread_num()] ++;

  usleep ((700*i) % 2000);
  return (emaitza);
}



void main ()
{
  int     i, j, k, azkena, err;
  float   emaitza[N], maximoa = 0.0;
  struct  timespec  t1, t0;
  double  Tex;


  // hasierako balioak (adibide hutsa)

  for (i=0; i<N; i++)
  for (j=1; j<N; j++)
    A[i][j] = rand() % 100 - 50;

  for (i=0; i<N; i++) A[i][0] = 1;
  A[9000][0] = -1;



  clock_gettime (CLOCK_REALTIME, &t0);

  // while begizta bat: paralelismoa task-en bidez 

  i = 0;
  while (A[i][0] > 0)
  {
    emaitza[i] = kalkulatu (i);
    i++;
  }
  azkena = i;

  for (k=0; k<azkena; k++) 
    if (maximoa < emaitza[k]) 
    {
      maximoa = emaitza[k];  
      err = k;
    }


  clock_gettime (CLOCK_REALTIME, &t1);
  Tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) /(double) 1e9;

  printf ("\n   max = %1.2f -- errenkada = %d \n", maximoa, err);
  printf ("   Tex: %1.3f s\n\n", Tex);
  for (i=0; i<omp_get_max_threads(); i++) printf ("   tid = %d   %d iterazio\n\n", i, iterkop[i]);
}
