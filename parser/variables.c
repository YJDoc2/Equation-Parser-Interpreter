#include "./typedef.c"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef VARIABLES
#define VARIABLES
// $0 - $9 variables array
float default_var[10];
//Custom variables linked list
Var *var_start,*var_end;


Result setDefVar(int place,float val){

    Result ret;

    if(place>9 ||place<0){    //Error if anything except 0 - 9
        ret.status = OUT_OF_BOUND;
        strcpy(ret.error_info,"Out Of Bound Predefined Variable Assignment");
          
    }else{
        default_var[place] = val;
        ret.status = SUCCESS;
        ret.data = val;
    } 
    return ret;
}

Result getDefVar(int place){

    Result ret;
    float val = 0;

    if(place>9){
        ret.status = OUT_OF_BOUND;
        strcpy(ret.error_info,"Out Of Bound Predefined Variable Access");
          
    }else{
        val = default_var[place];
        ret.status = SUCCESS;
        ret.data = val;
    } 
    return ret;
}

Result getVar(char *name){

    Var *temp = var_start;
    Result ret;
    if(var_start == NULL){ //In case no variable has been defined yet
        ret.status = VARIABLE_NOT_DEFINED;
        sprintf(ret.error_info,"Variable %s not defined",name);

    }else{
        while(temp != NULL){
            if(strcmp(temp->name,name) == 0){
                break;
            }else{
                temp = temp->next;
            }
        }
        if(temp == NULL){//In case no variable with given name has been defined yet
            ret.status = VARIABLE_NOT_DEFINED;
            sprintf(ret.error_info,"Variable '%s' not defined",name);
        }else{
            ret.status = SUCCESS;
            ret.data = temp->val;

        }
    }

    return ret;
}

Result setVar(char *name,float val){

    Result ret;
    Var *temp,*iter;

    if(var_start == NULL){ //For First Custom Variable
        temp = (Var *)malloc(sizeof(Var));
        strcpy(temp->name,name);
        temp->val = val;
        var_start = temp;
        var_end = temp;

    }else{
        ret = getVar(name);
        if(ret.status == SUCCESS){
            iter = var_start;
            while(iter != NULL){
                if(strcmp(iter->name,name) == 0){
                    break;
                }else{
                    iter = iter->next;
                }
            }
            iter->val = val;
            ret.data = val;
            return ret;
        }else{
            temp = (Var *)malloc(sizeof(Var));
            strcpy(temp->name,name);
            temp->val = val;
            var_end->next = temp;
            var_end = temp;
        }
        
    }
    var_end->next = NULL;
    ret.status = SUCCESS;
    ret.data = val;
    return ret;
    
}

Result clearVars(){

    Var *temp = var_start;
    Var *t;
    Result ret;
    int c =0;
    for(;c<10;c++){
        default_var[c] = 0.0;
    }
    while(temp != NULL){

        t = temp;
        temp = temp->next;
        free(t);
    }
    var_start = NULL;
    var_end = NULL;
    ret.status = SUCCESS;
    ret.data = 0;
    return ret;
}

Result showVars(){

    int c =0;
    Var *temp =var_start;
    printf("Default Vars :\n");
    for(;c<10;c++){
        printf("$%d : %lf\n",c,default_var[c]);
    }
    printf("Defined Vars :\n");
    while (temp!=NULL)
    {
        printf("%s : %lf\n",temp->name,temp->val);
        temp = temp->next;
    }
}


#endif