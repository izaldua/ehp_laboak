/*
    fibopar.c	OpenMP bertsioa   -- task
    fibonacci segidaren osagaien kalkulu errekurtsiboa
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int fibo (int x)
{
  int  f1, f2;


  if (x<2) return (x);
  else
  {
    f1 = fibo (x-1);

    f2 = fibo (x-2);

    return (f1 + f2);
  }
}


void main (int argc, char *argv[])
{
  int  N, emaitza;


  N = atoi (argv[1]);

  emaitza = fibo (N);


  printf ("\n\n fibo (%d)  =  %d\n\n", N, emaitza);
}
