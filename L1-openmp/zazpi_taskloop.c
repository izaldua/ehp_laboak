/*
 Algebra linealeko funtzio sinplea
 	for (int i = 0; i < n; ++i)
     	     y[i] = a*x[i] + y[i];
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000

     
void zazpi(float a, float * x, float * y)
{
  for (int i=0; i<N; ++i)
      y[i] = a*x[i] + y[i];
}

// Bektorea pantailaratzeko
void EmanBektorea (float *V, int L1, int L2)
{
  int  i;
  #pragma omp parallel
  #pragma omp taskloop 
  for (i=L1; i<(L1+L2); i++) printf ("%8.2f", V[i]);
  printf ("\n");
}


// Pantailaratzen du "Testua" string-a eta exkuzio-denbora (ms): t1-t0
void ExekDenbora (char *Testua, struct timespec *t0, struct timespec *t1)
{
  double  tex;
  tex = (t1->tv_sec - t0->tv_sec) + (t1->tv_nsec - t0->tv_nsec) / (double)1e9;
  printf ("%s = %1.3f ms\n\n", Testua, tex*1000);
}

void main()
{   
  int  i;
  float  *x, *y;
  struct timespec  t0, t1;

  x  = malloc (N*sizeof(float));
  y  = malloc (N*sizeof(float));
  
// hasieratzea
  for (i=0; i<N; i++)
  {
    x[i] = (float) (i % 100);
    y[i] = (float) ((N/2-i+25) % 31);
  }

  printf ("\nx hasieran -->   ");
  EmanBektorea (x, N/2, 10);
  printf ("y hasieran -->   ");
  EmanBektorea (y, N/2, 10);
  printf ("\n");
    
  clock_gettime (CLOCK_REALTIME, &t0);  
  zazpi(2.0, x, y);
  clock_gettime (CLOCK_REALTIME, &t1);

  printf ("y bukaeran -->   ");
  EmanBektorea (y, N/2, 10);
  printf ("\n");
  
  ExekDenbora ("\n Tex (serie)", &t0, &t1);
}
