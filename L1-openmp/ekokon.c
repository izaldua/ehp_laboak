/*  Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)
    OpenMP laborategia

    ekokon.c       bertsio paraleloa OSATZEKO

    Sinkronizazioko ariketa: ekoizleak eta kontsumitzaileak
    Ekoizleek datuak ilara batean utzi; kontsumitzaileek ilaratik hartu 2naka
*************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


// Aldagai globalak 

#define DATUKOP 50	// sortu eta kontsumitu behar diren datuak
#define TAM 10		// aldatu probak egiteko

int  ilara[TAM];
int  zenbat = 0, ik = 0, ie = 0;	// ADI: zenbat, aldagai partekatua
int  eko_batura, kon_batura;		// kontrola: sortzen eta kontsumitzen diren datuen batura

omp_lock_t sar;		// sarraila



// Ekoizleen datuak sortzea simulatzen duen funtzioa

int DATUA_SORTU ()
{
  int  dat;

  usleep (rand () % 100000);	// datuak ekoizteko denbora simulatzeko
  dat = rand () % 20;		// datuak, 0tik 19ra
 
  return (dat);
}


// Datuen kontsumoa simulatzen duen funtzioa

void DATUAK_KONTSUMITU (int dat1, int dat2)
{
  usleep ((dat1 + dat2) * 20000);	// kontsumo denbora, datuen baturarekiko proportzionala
}


// EKOIZLEEN kodea: datuak sortu eta ilaran sartu

void EKOIZLEA (int tid)
{

   // OSATZEKO
   // kalkulatu ilararen okupazio maximoa eta batezbestekoa

} 


// KONTSUMITZAILEEN kodea: ilarako datuak kontsumitu, binaka

void KONTSUMITZAILEA (int tid)
{

   // OSATZEKO

}



int main (int argc, char *argv[])
{
  int  tid, eko_kop, kon_kop;

  struct timespec  t0, t1;
  double  tex;

  printf (" Ekoizle kopurua         --> ");
  scanf  ("%d", &eko_kop); 
  printf (" Kontsumitzaile kopurua  --> ");
  scanf  ("%d", &kon_kop);  

// adierazi hari kopurua


// hasieratu sarrailak


  clock_gettime (CLOCK_REALTIME, &t1);


// Paraleloan exekutatu behar den kodea. Lehenengo prozesuak, ekoizleak;
// gainerakoak, kontsumitzaileak



// sarrailak askatu


  clock_gettime (CLOCK_REALTIME, &t1);
  tex = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / (double)1e9;

  printf ("\n Ekoizleak:          %d -- batura  %d\n", eko_kop, eko_batura);
  printf ("\n Kontsumitzaileak:   %d -- batura  %d\n", kon_kop, kon_batura);
  printf ("\n Ilararen okupazioa: %f (bb) -- %d (max)\n", (float) okup/DATUKOP, okupmax);
  printf ("\n Tex. = %1.3f ms\n\n", tex*1000);

  return (0);
}
