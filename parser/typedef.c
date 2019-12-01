#include<stdio.h>
#ifndef TYPEDEF
#define TYPEDEF


typedef enum
{
    SUCCESS,ERROR,ASSIGN_ERROR,VARIABLE_NOT_DEFINED,OUT_OF_BOUND,MATH_ERROR,NO_REAL_ROOTS,FILE_ERROR
}resultStatus;


typedef struct result
{
    float data;
    resultStatus status;
    char error_info[100];
}Result;
typedef struct var
{
    float val;
    char name[30];
    char info[30];
    struct var *next;
}Var;

#endif
