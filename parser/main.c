#include <stdio.h>
#include <string.h>
#include "./config.c"
#include "./help.c"
#include "./constants.c"
#include "./variables.c"
#include "./inbuilt.c"
#include "./parser.c"
#include "./linwrap.c"
#include "./polywrap.c"

int checkExit(char in[]){
    if((in[0] == 'q' || in[0] == 'Q' && in[1] != 'e') || strcmp(in,"back\n")==0){
        return 1;
    }else{
        return 0;
    }
    
         
}

int checkAndEvalInternalFn(char in[]){

    Result ret;

    if(strcmp(in,"showvars")==0){
        showVars();
        return 1;
    }else if(strcmp(in,"showconst")==0){
        showConst();
        return 1;
    }else if(strcmp(in,"vardump")==0){
        ret = vardump();
        if(ret.status != SUCCESS){
            printf("Error Occured...%s\n",ret.error_info);
        }
        return 1;
    }else if(strcmp(in,"varload")==0){
        ret = varload();
        if(ret.status != SUCCESS){
            printf("Error Occured...%s\n",ret.error_info);
        }
        return 1;
    }else if(strcmp(in,"varclear")==0){
        clearVars();
    }else{
        return 0;
    }
}

void polyInterface(){
    Result ret;
    char in[50];
    printf("\nType 'help' to read help page,'back' or 'q' to go back to general parser\n");
    printf("Type 'coeff' to give equaiton by coefficients.\n");
    printf("Type 'div' to use division by linear factor.");
    printf("Type equation to parse it and find roots.\n\n");
    printf("Do not use Variables including 'x' or 'X' \n");
    printf("Roots will be Accurate upto 0.0001\n");
    printf("Use coeff for giving polynomial corfficients,use div for polynomial division by a linear factor\n\n");
    while(1){
        printf("poly> ");
        fgets(in,50,stdin);
        if(checkExit(in)){
            return;
        }
        if(strcmp(in,"coeff\n")==0){
            int degree;
            degree=getPoly();
            evalPoly(degree);	
            displayRoot();
            flushRootList();
            char c =getchar();
        }else if(strcmp(in,"div\n") == 0){
            int degree;
	        getDivisor();
	        degree=getPoly();
	        Remainder=polyDiv(degree);
	        displayQ(polyQtnt,degree);
        }else{
            in[strlen(in)-1] = '\0';
            ret = solvePoly(in);
            if(ret.status != SUCCESS){
                printf("Error Occured...%s\n",ret.error_info);
            }else{
                Quotient *temp;
                temp=rootstart;
                if (rootstart==NULL){
                    printf("No Real Roots are Found \n");
                }else{
                    while (temp!=NULL){
                        printf("Root = %f \n",temp->coef);			//Display the variables from top -> bottom
                        temp=temp->next;
                    }
                }
            }
        }
    }

}


void linInterface(){
    Result ret;
    char in[50];
    printf("\nType 'help' to read help page,'back' or 'q' to go back to general parser.\n");
    printf("Type 'solve' to parse linear equation and solve them.");
    printf("use 'coeff' to give linear equations by coeffitients.\n\n");
    printf("Do not use Variables including 'x' or 'X' \n");
    printf("Solutions will be Accurate upto 0.0001\n\n");
    while(1){
        printf("lin>> ");
        fgets(in,50,stdin);
        if(checkExit(in)){
            return;
        }
        if(strcmp(in,"coeff\n")==0){
            inputCoeff();
            solveLinear();
            displayLinearSoln();
            char c =getchar();
        }else if(strcmp(in,"solve\n")==0){
           linearSolve();
        }else{
            printf("lease Enter 'Coeff' to Read coeff or 'solve' to parse Equation.\nUse 'back' or 'q' to Return to Genearl Parser\n\n");
        }
    }
}

void main(){

    char in[150];
    Result r;
    r.status = ERROR;
    in[0] = '\0';
    printf("\n\n-----General Equation Parser-----\n\n");
    printf("Type 'back' or 'q' or 'Q' to Exit.\n");
    printf("Type 'help' to read help page.\n");
    printf("Type 'linsolve' to use linear equation solver.\n");
    printf("Type 'polysolve' to use polynomial solver.\n\n");
    initConst();
    while(1){
        printf(">>>>> ");
        fflush(stdin);
        memset(in,'\0',100);
        fgets(in,100,stdin);
        in[strlen(in)-1] = '\0';
        if(strchr(in,' ')==in){
            continue;
        }
        if(checkExit(in)){
            break;
        }
        if(strcmp(in,"help")==0){
            showHelp();
        }else if(strcmp(in,"polysolve")==0){
            polyInterface();
        }else if(strcmp(in,"linsolve")==0){
            linInterface();
        }else if(checkAndEvalInternalFn(in) ==0){
            r = parse(in,in+strlen(in));
            if(r.status != SUCCESS){
                printf("Error Occured...%s\n",r.error_info);
            }else{
                if(absolute(r.data)<1E-3 || absolute(r.data)>1E3){
                    printf("%0.5e\n",r.data);
                }else{
                    printf("%f\n",r.data);
                }
            }
            
        }
    }
}