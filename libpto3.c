#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "libpto3.h"

void puntoDinamico()
{ 
    printf("\n ----------PuntoDinamico---------- \n");
    cJSON *fileSystemInfo=cJSON_CreateArray();
    cJSON *arrayJSON=cJSON_CreateArray();
    FILE *fd;
    char str[100]; 

    fd = fopen("/proc/filesystems", "r");

    cJSON_AddItemToObject(fileSystemInfo,"asdasd",arrayJSON);

    while(fscanf(fd, "%*s %s", str) == 1)
    {
        cJSON_AddItemToArray(arrayJSON,cJSON_CreateString(str));
    }
    printf("\n%s\n",cJSON_Print(fileSystemInfo));
}