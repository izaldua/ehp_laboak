/*  EHP, Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)

    mzut.c  --  serieko bertsioa
    OpenMP-ren oinarrizko kontzeptuak freskatzeko ariketa
  
     - begizten paralelizazioa
     - aldagai motak
     - ale larriko / ale xeheko paralelismoa
     - iterazioen banaketa (scheduling)
*******************************************************************************/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define  ERR 200000
#define  ZUT 300
#define  BALMAX 60


double   mat[ERR][ZUT];



// matrizearen hasierako balioak (ausaz); ez paralelizatu
static void hasieratu_mat (double mat[ERR][ZUT])
{
  int  i, j;


  for (i=0; i<ERR; i++)
  for (j=0; j<ZUT; j++)
    mat[i][j] = rand () % BALMAX - (j % 59);
}


// sarrera-fitxategia irakurtzeko errutina; eskaera kopurua itzultzen du
int irakurri_eskaerak (char *feskaerak, int *zutabeak)
{
  FILE  *fitx;
  int   i, x;


  fitx = fopen (feskaerak, "r");

  i = x = 0;
  while (x != EOF) {
    x = fscanf (fitx, "%d", zutabeak + i);
    i++;
  }

  fclose (fitx);
  return (i-1);
}


// irteera-fitxategia idazteko errutina: emaitzak
void idatzi_emaitzak (char *fsol, int kop, double *emaitzak)
{
  FILE  *fitx;
  int   i;


  fitx = fopen (fsol, "w");

  for (i=0; i<kop; i++)
    fprintf (fitx, "%10.3f\n", emaitzak[i]);  

  fclose (fitx);
  return;
}


// "kalkulua": prozesatu matrizearen zutabeak
void prozesatu_eskaerak (double mat[ERR][ZUT], int *zutabeak, int kop, double *emaitzak)
{
  int     i, j, zutabe;
  double  y, batura;

  #pragma omp parallel for private(i, j, zutabe)
  for (j=0; j<kop; j++)
  {
    zutabe = zutabeak[j];
    batura = 0.0;
    #pragma omp parallel for private(y) reduction(+:batura)
    for (i=0; i<ERR; i++)
    {
      y = mat[i][zutabe];
      if (y > 0) batura += exp (y / 100); 
    }
    emaitzak[j] = batura;
  }
}



// programa nagusia
int main (int argc, char *argv[])
{
  int     esk_kop, zutabeak[ZUT];
  double  *emaitzak, Tex;
  struct timespec  t1, t0;
  char    fsol[20];


  if (argc != 2) 
  {
    printf ("\n Exekutatzeko: %s f1\n\n", argv[0]);
    return 0;
  }


  hasieratu_mat (mat);

  esk_kop = irakurri_eskaerak (argv[1], zutabeak);
  emaitzak = malloc (esk_kop * sizeof (double));


  clock_gettime (CLOCK_REALTIME, &t0);

  prozesatu_eskaerak (mat, zutabeak, esk_kop, emaitzak);

  clock_gettime (CLOCK_REALTIME, &t1);
  Tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) /(double) 1e9;

  strcpy (fsol, argv[1]);
  strcat (fsol, "_sol");
  idatzi_emaitzak (fsol, esk_kop, emaitzak);

  printf ("\n Eskaerak: %d -- Azken emaitza: %1.3f\n", esk_kop, emaitzak[esk_kop - 1]);
  printf (" Tex (serie): %1.3f ms\n\n", Tex*1000);

  return (0);
} 

