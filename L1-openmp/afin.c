/*  EHP, Errendimendu Handiko Prozesadoreak - IIG (Konputagailuen Ingeniaritza)

    afinitatea.c       OpenMP

    Hariak sistemako nukleoen artean nola banatzen diren ikusteko
    OMP_PLACES ingurune-aldagaia
******************************************************************************/

 #include <stdio.h>
 #include <omp.h>


 int main ()
 {
   int  tid, non, lekuak;


   printf ("\n\n  proc_bind = close\n");

   #pragma omp parallel private (tid, non, lekuak)  proc_bind (close)
   {
     tid = omp_get_thread_num ();
     non = omp_get_place_num ();
     lekuak = omp_get_num_places ();

     printf ("tid %2d  non %2d  lekuak %2d\n", tid, non, lekuak);
   }

   printf ("\n\n  proc_bind = spread\n");

   #pragma omp parallel private (tid, non, lekuak)  proc_bind (spread)
   {
     tid = omp_get_thread_num ();
     non = omp_get_place_num ();
     lekuak = omp_get_num_places ();

     printf ("tid %2d  non %2d  lekuak %2d\n", tid, non, lekuak);
   }

   printf ("\n\n  proc_bind = master\n");

   #pragma omp parallel private (tid, non, lekuak)  proc_bind (master)
   {
     tid = omp_get_thread_num ();
     non = omp_get_place_num ();
     lekuak = omp_get_num_places ();

     printf ("tid %2d  non %2d  lekuak %2d\n", tid, non, lekuak);
   }
 }


