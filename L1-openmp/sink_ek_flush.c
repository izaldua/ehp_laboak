/*  EHP, Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)

    sink_ek_flush.c       OpenMP
 
    Ekoizle - kontsumitzaile sinkronizazioa, adierazle batez
    Flush eragiketen beharra sinkrozizazioa ondo gauzatzeko (-O2)
******************************************************************************/


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


void main ()
{
  int  y = 0, prest = 0;


  #pragma omp parallel 
  {
    int tid = omp_get_thread_num ();

    if (tid == 1)
    {
      y = 5;
      #pragma omp flush (y)

      prest = 1;
      #pragma omp flush (prest)
    }

    else
    {
      while (prest == 0)
      {
        #pragma omp flush (prest)
      }

      #pragma omp flush (y)

      printf ("\n  tid %d --  y %d \n", tid, y);
    }
  }
}
