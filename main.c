/*
*Alumno : Orecchini Alem Stefano Mauricio
*/

#include <dlfcn.h>
#include <errno.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>

#include "tp2.h"
#include "libpto3.h"




int main(int argc, char **argv) 
{

  int flagS=0;
  int flagJ=0;
  int flagA=0;
  int flagD=0;

  int opcion=0;

  while ((opcion = getopt(argc, argv, "s::j::a::d::"))!=-1) //argc es la cantidad de argumentos pasados (minimo 1). argv es una lista de esos parametros (parametros 0 = nombre del programa)
  {
    switch (opcion)
    {
      case 'a':
        flagA=1;
        break;
      case 's':
        flagS=1;
        break;
      case 'j':
        flagJ=1;
        break;  
      case 'd':
        flagD=1;
        break;  
      default:
        break;
    }

  }

  if(flagS==1 && flagJ==1)
  {
    showMemInfo(1);
    showCpuInfo(1);
  }
  else if(flagA==1 && flagJ==1)
  {
    showProcVersion(1);
  }
  else if (flagS==1)
  {
    showMemInfo(0);
    showCpuInfo(0);
  }
  else if (flagA==1)
  {
    showProcVersion(0);
  }
  else if (flagD==1)
  {
    void *handle = dlopen("libpto3.so", RTLD_LAZY);
    void* (*punto3)(void);
    *(void **) (&punto3) = dlsym(handle,"puntoDinamico"); 
    punto3();
    dlclose("libpto3.so");
    //puntoDinamico();
  }

  
  

  return 0;
}


