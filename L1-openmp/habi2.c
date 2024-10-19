/*  Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)
    OpenMP laborategia

    habi2.c	

    Paralelismo habiaratua ikusteko.  Aurretik
      export OMP_NESTED="TRUE"
      export OMP_NUM_THREADS="12,6"    
       12 hari lehen atal paraleloan
       2-k bigarren atal paralelora doaz eta 6na hari sortzen dute

*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000


void matrize_karratua (int X[][N], int Y[][N])
{
  int  i, j, k;


  #pragma omp parallel for private (i, j, k)
  for (i=0; i<N; i++)
  for (j=0; j<N; j++)
  { 
    Y[i][j] = 0;
    for (k=0; k<N; k++)
      Y[i][j] = Y[i][j] + X[i][k] * X[k][j];
  }
}


int main (int argc, char *argv[])
{
  int  i, j, tid, kont5 = 0, batura;
  int  A[N][N], A2[N][N], B[N][N], B2[N][N], C[N][N];

  struct timespec  t1, t2;
  double  Tex;


  // hasierako balioak
  for (i=0; i<N; i++)
  for (j=0; j<N; j++)  
  {
    A[i][j] = (i + j) % 5;
    B[i][j] = (j - 2*i) % 7;
  }

  clock_gettime (CLOCK_REALTIME, &t1);

  #pragma omp parallel private (tid)
  {
    tid = omp_get_thread_num ();

    if (tid == 0) 
      matrize_karratua (A, A2);

    else if (tid == 1) 
      matrize_karratua (B, B2);

    #pragma omp barrier

    #pragma omp for private (i, j, batura) reduction (+:kont5)
    for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    {
      batura = A2[i][j] + B2[i][j];
      if (batura == 5) kont5 ++;
      C[i][j] = batura;
    }     
  }

  clock_gettime (CLOCK_REALTIME, &t2);
  Tex = (t2.tv_sec-t1.tv_sec) + (t2.tv_nsec-t1.tv_nsec) / (double)1e9;

  printf ("\n kont5 %d  C[%d][%d] %d\n", kont5, N/2, N/2, C[N/2][N/2]);
  printf ("\n Tex = %.3f (s)\n", Tex);
  return (0);
}
