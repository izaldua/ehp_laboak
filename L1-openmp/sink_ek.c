/*  EHP, Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)

    sink_ek.c       OpenMP

    Ekoizle - kontsumitzaile sinkronizazioa, adierazle batez

    -O0  ondo dabil
    -O2  gaizki dabil (kontsistentzia)
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
      prest = 1;
    }

    else
    {
      while (prest == 0) { }

      printf ("\n  tid %d --  y %d \n", tid, y);
    }
  }
}
