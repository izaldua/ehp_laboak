
/*  EHP, Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)

    taskloop.c       OpenMP

    for begizta baten paralelizazioa taskloop sasiaginduarekin
******************************************************************************/


#include <stdio.h>
#include <omp.h>
#include <unistd.h>

#define N 20


int main ()
{
  int  i, A[N], tid;


  for (i=0; i<N; i++) A[i] = -1;

  #pragma omp parallel
  {
    #pragma omp single
    {    
      #pragma omp taskloop private (i, tid)  grainsize (3) 
      for (i = 0; i<N; i++) 
      {
        tid = omp_get_thread_num();

        A[i] = tid;

        usleep (1000);
        printf ("\n i %2d  tid %d", i, tid);
      }
    }
  }

  printf ("\n\n A-ren balio berriak\n");
  for (i=0; i<N; i++)  printf ("%3d", A[i]);
  printf ("\n\n");
  return (0);
} 
