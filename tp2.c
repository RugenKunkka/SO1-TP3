/*
**  main.c
**  TP2
**
**  Created by Orecchini Alem Stefano Mauricio on 14/08/2021.
**  Copyright © 2021 Orecchini Alem Stefano Mauricio. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON.h"
#include "tp2.h"

#define BUFFSIZE 1024 //cantidad de caracteres max q va a tener cada renglon
#define CONVERTIR_DE_KB_A_MB 1024//factor de conversion de KB MB 

/*
C-strings Realice las siguientes actividades:

Obtener la memoria ram total, libre y disponible en Megabytes. A partir del archivo /proc/meminfo.
Obtener la memoria swap Ocupada. A partir del archivo /proc/meminfo.
Crear un programa en C que imprima información referida al CPU, a partir del archivo /proc/cpuinfo:
Modelo de CPU.
Cantidad de cores
Cantidad de thread por cores.
*/
//


/*void showMemInfo();
void procesarMemInfo(char[],cJSON*,int);
void showCpuInfo(int);
void procesarCpuMemInfo(char [],cJSON *);
void showProcVersion(int);*/

void showMemInfo(int flag)
{
    cJSON *memInfo=cJSON_CreateObject();
    cJSON_AddItemToObject(memInfo, "NAME", cJSON_CreateString("----------MemInfo----------"));
    printf("\n ----------MemInfo---------- \n");
    int contador=0;
    FILE *fd;
    char renglon1[BUFFSIZE];
    fd = fopen("/proc/meminfo","r");
    while(fgets(renglon1, BUFFSIZE, fd)){ //preguntarle al profe
        if(contador==1||contador==2||contador==3||contador==5){
            //tenes que encontrar el tab, tomas el renglon y recortas dsps del espacio y eso es todo
            procesarMemInfo(renglon1,memInfo,flag);
            //printf(" %s",renglon1);//%s\n
        }
        contador++;
    }
    fclose(fd);
    fflush (fd);

    if(flag==1) printf("\n %s \n",cJSON_Print(memInfo));
}


void procesarMemInfo(char cadena[],cJSON *memInfo, int flag)//la cadena es el renglón que tomé del archivo y le envié
{
    char delimitador[] = " ";
    char *titulo;
    float *valor;
    char *token = strtok(cadena, delimitador);//es el split de Java pero con la diferencia de que no te devuelte el arreglo completo
    //si no que a construyendo el String desde que empieza el string hasta que encuentre un delimitador
    if(token != NULL){
        int contador=0;
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            if(contador==0){
                if(flag==0) printf("%s",token);//imprime que info es por ejemplo.. memoria libre: 
                //necesito copiar el contenido del token que es un char[] a otra variable.. eso necesito.. pm...
                titulo=token;
            }
            if(contador==1){
                float memoria= (float)(atof(token)/CONVERTIR_DE_KB_A_MB);//castio a flotante el valor xq la division par ala conversion va a dar de pto flotante
                valor=&memoria;
                if(flag==0){
                    printf(" %.4f", memoria);//muestro solamente 4 decimales del float resultante de memoria
                    printf(" MB\n");
                }
            }
            
            token = strtok(NULL, delimitador);//es como si tomara el valor que sigue dsps del delimitador y asi sucesivamente hasta que 
            //encuentra null y listo
            contador++;
        }
        cJSON_AddItemToObject(memInfo, titulo, cJSON_CreateNumber(*valor));   
    }
}

void showCpuInfo(int flag)
{
    cJSON *cpuInfo=cJSON_CreateObject();
    cJSON_AddItemToObject(cpuInfo, "NAME", cJSON_CreateString("----------CpuInfo----------"));

    printf("\n----------CpuInfo----------\n");
    int contador=0;
    int contadorDeTrhreads=0;
    int cantidadDeCores=0;
    FILE *fd;//Puntero a variable tipo File
    char renglon1[BUFFSIZE];
    fd = fopen("/proc/cpuinfo","r");
    while(fgets(renglon1, BUFFSIZE, fd)){ //preguntarle al profe
        if(contador==1||contador==4||contador==11){
            if(flag==0) {printf("%s",renglon1);}//%s\n
            else {procesarCpuMemInfo(renglon1,cpuInfo);}
        }
        if (contador==11)
        {
            cantidadDeCores=atoi(&renglon1[12]);//ya se que está en la posicion 12 entonces tomo el dato de la cant de cpus
        }
        
        contador++;
        if(strstr(renglon1, "initial apicid") != NULL){contadorDeTrhreads++;}//sería el contains de String de Java
    }
    if(flag==0){
        printf("cpu threads     : %d \n",contadorDeTrhreads);//cant de hilos total
        printf("cpu threads/core: %d \n",contadorDeTrhreads/cantidadDeCores);//calculo la cant de hilos por core
    }
    cJSON_AddItemToObject(cpuInfo, "cpu threads", cJSON_CreateNumber(contadorDeTrhreads)); 
    cJSON_AddItemToObject(cpuInfo, "cpu threads/core", cJSON_CreateNumber((contadorDeTrhreads/cantidadDeCores))); 

    if(flag==1) {printf("\n %s \n",cJSON_Print(cpuInfo));}
    
    fclose(fd);
    fflush (fd);

}

void procesarCpuMemInfo(char cadena[],cJSON *cpuInfo)//la cadena es el renglón que tomé del archivo y le envié
{
    char delimitador[] = "\t:";
    char *titulo;
    const char *valor;
    char *token = strtok(cadena, delimitador);//es el split de Java pero con la diferencia de que no te devuelte el arreglo completo
    //si no que a construyendo el String desde que empieza el string hasta que encuentre un delimitador
    if(token != NULL){
        int contador=0;
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            if(contador==0){
                titulo=token;
                
            }
            if(contador==1){
                valor=token;
            }
            
            token = strtok(NULL, delimitador);//es como si tomara el valor que sigue dsps del delimitador y asi sucesivamente hasta que 
            //encuentra null y listo
            contador++;
        }
        cJSON_AddItemToObject(cpuInfo, titulo, cJSON_CreateString(valor));   
    }
}

//-------------------------------
void showProcVersion(int flag)
{ 
    cJSON *procInfo=cJSON_CreateObject();
    cJSON *arrayJSON=cJSON_CreateArray();
    char **arrayPalabras=NULL;
    char buffer[BUFFSIZE];
    char *bufferPalabra;
    FILE *fd = fopen("/proc/version", "r");
    printf("\n ----------ProcVersion---------- \n");
    while (fgets(buffer, BUFFSIZE, fd))
    {                     
        for (unsigned int i = 0;buffer[i]; ++i){buffer[i] = toupper(buffer[i]);}
             
        bufferPalabra= strtok (buffer," ,");
                        
        for(unsigned int linea=0 ;bufferPalabra!= NULL;linea ++) 
        {           
            arrayPalabras=(char**)realloc(arrayPalabras,(BUFFSIZE)*sizeof(char)); 
            arrayPalabras[linea]= (char*)malloc(sizeof(char) * (strlen(buffer) + 1)*sizeof(char));   

            strcpy(arrayPalabras[linea],bufferPalabra); 
                         
            bufferPalabra = strtok (NULL, " ,");      
            arrayPalabras[linea+1] = NULL;
        }

        cJSON_AddItemToObject(procInfo,"Pto2_CJSON",arrayJSON);


        if(flag==0) 
            for ( unsigned int i = 0; arrayPalabras[i] !=NULL; i++)
                printf("Palabra[%d]: %s\n",i,arrayPalabras[i]);

        if(flag==1)
            for(unsigned int i=0; arrayPalabras[i] !=NULL;i++)
                cJSON_AddItemToArray(arrayJSON,cJSON_CreateString(arrayPalabras[i]));


        free(arrayPalabras); 
    }

    fclose(fd);
    if(flag==1) 
        printf("\n%s\n",cJSON_Print(procInfo));
}