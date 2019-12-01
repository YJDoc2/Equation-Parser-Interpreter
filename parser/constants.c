#include "./typedef.c"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef CONSTANTS
#define CONSTANTS

Var *const_start,*const_end;


Result setConst(char *name,float val,char *info){

    Result ret;
    Var *temp;

    temp = (Var *)malloc(sizeof(Var));
    strcpy(temp->name,name);
    strcpy(temp->info,info);
    temp->val = val;

    if(const_start == NULL){ //For First Constant
        const_start = temp;
        const_end = temp;

    }else{
        const_end->next = temp;
        const_end = temp;
    }
    const_end->next = NULL;
    ret.status = SUCCESS;
    ret.data = val;
    return ret;

}
Result getConst(char *name){

    Var *temp = const_start;
    Result ret;
    if(const_start == NULL){ //In case no constant has been defined yet
        ret.status = VARIABLE_NOT_DEFINED;
        sprintf(ret.error_info,"Constant %s not defined",name);
    }else{
        while(temp != NULL){
            if(strcmp(temp->name,name) == 0){
                break;
            }else{
                temp = temp->next;
            }
        }
        if(temp == NULL){//In case no constant with given name has been defined yet
            ret.status = VARIABLE_NOT_DEFINED;
            sprintf(ret.error_info,"Constant '%s' not defined",name);
        }else{
            ret.status = SUCCESS;
            ret.data = temp->val;
        }
    }
    return ret;
}

void initConst(){
    setConst("PI",3.14159,"Mathematical Pi");
    setConst("e",2.71828,"Euler's Number");
    setConst("phi",1.61803,"Golden Ratio");
    setConst("h",6.62607e-34,"Plank's Constant");
    setConst("hbar",1.05457e-34,"Reduced Plank's : h/(2*pi)");
    setConst("N",6.02214e23,"Avagadro's Number");
    setConst("Kb",1.380649e-23,"Boltzmann Constant");
    setConst("G",6.67430e-11,"Universal Gravitational Const");
    setConst("c",299792458,"Speed of Light");
    setConst("Me",9.1093837e-31,"Mass of Elctron");
    setConst("Mp",1.6726219e-27,"Mass of Proton");
    setConst("Mn",1.6749275e-27,"Mass of Neutron");
    setConst("Qe",1.6021e-19,"Elementary Charge of Electron");
    setConst("eps0",8.8541878e-12,"Vaccum Permitivitty");
    setConst("mu0",1.256637e-6,"Vaccum Permeability");
    setConst("R",8.314463,"Universal Gas Const");
}

void showConst(){

    Var *temp =const_start;
    printf("Defined Constants :\n");
    while (temp!=NULL)
    {
        printf("%s : %e :  %s\n",temp->name,temp->val,temp->info);
        temp = temp->next;
    }
}
#endif