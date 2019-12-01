#include <stdio.h>
#include "./typedef.c"


#ifndef CONFIG
#define CONFIG

char varlogFile[50] = "vardump.log";


void setConfig(){

    printf("Please give details for default basic configuration :\n");
    printf("Name of Variable store File (Including Extension):\t");
    scanf("%s",varlogFile);

}

void showConfig(){

    printf("Details for default basic configuration :\n");
    printf("Name of Variable store File (Including Extension): %s\n",varlogFile);
    

}

#endif