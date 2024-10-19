/*  PAR, Procesadores de Alto Rendimiento - GII (Ingenieria de Computadores) 

    dependfor.c

    paralelizar un for con dependencias entre iteraciones - OpenMP
*************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Constantes y variables 

#define N 100000

int     A[N], B[N];

//  RUTINAS AUXILIARES

// Imprime en pantalla el string Texto y el tiempo de ejecucion (ms): t1-t0
void TiempoEjec (char *Texto, struct timespec *t0, struct timespec *t1)
{
  double  tej;

  tej = (t1->tv_sec - t0->tv_sec) + (t1->tv_nsec - t0->tv_nsec) / (double)1e9;
  printf ("%s = %1.3f ms\n\n", Texto, tej*1000);
}

void ImprimeVector_int (int *V, int L1, int L2)
{
  int  i;

  for (i=L1; i<(L1+L2); i++)  printf ("%8d", V[i]);
  printf ("\n");
}


// función fun1
int fun1 (int y, int x)
{
  int  k;
  k = (x + y) % 100;
  usleep (1);
  return (k);
}


// PROGRAMA PRINCIPAL

void main (int argc, char *argv[])
{
  int     i, tid, sumaser;
  struct timespec  t0, t1, t2, t3;
  sumaser = 0;
  
  clock_gettime (CLOCK_REALTIME, &t0);

// EJECUCION SERIE 
  // Valores iniciales
  for (i=0; i<N; i++)  {
    A[i] = i % 100;
    B[i] = (i*33) % 50;
  }
  
  #pragma omp parallel reduction(+:sumaser)
  { 
    #pragma omp single
    {
      for (i=4; i<N; i++)  {
        #pragma omp task depend(in: B[i-4]) depend(out: B[i])
	{
	  B[i] = fun1 (A[i], B[i-4]);
	}
	sumaser +=B[i];
      }
    }
  }

  clock_gettime (CLOCK_REALTIME, &t1);
   
  printf ("B serie   -->   ");
  ImprimeVector_int (B, N/2, 10);
  printf ("\n");
  printf ("suma serie = %d\n", sumaser);


  TiempoEjec (" Tserie", &t0, &t1);
}
