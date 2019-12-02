#include<stdio.h>
#include<string.h>
#include "typedef.c"

#ifndef LINEAR
#define LINEAR

float augmentedM[14][14],tempM[14][14],X[14];
int numVars=0;
float det;

//! Convert all i=1;i<=....to i=0;i<....
//!Please convert all dependencies ......

void initLinear(){
    memset(augmentedM,0.0,sizeof(augmentedM[0][0])*11*11);//<---Initializing Array to 0--->// 
    memset(tempM,0.0,sizeof(tempM[0][0])*11*11);
    memset(X,0.0,sizeof(X[0])*11);
}

float determinant(float M[14][14],int x){//<<Function for Finding the Determinanat!>>

    int pr,j,p,q,t;
    float c[14],b[14][14],d =0.0;
    if(x==2){
        d=(M[1][1]*M[2][2])-(M[1][2]*M[2][1]);
        return d;
    }else{
        for(j=1;j<=x;j++){
            int r=1,s=1;
            for(p=1;p<=x;p++){
                for(q=1;q<=x;q++){
                    if(p!=1 && q!=j){
                        b[r][s]=M[p][q];
                        s++;
                        if(s>x-1){
                            r++;
                            s=1;
                        }
                    }
                }
            }
            for(t=1,pr=1;t<=1+j;t++){
                pr=(-1)*pr;
            }
            c[j]=pr*determinant(b,x-1);
        }
        for(j=1,d=0;j<=x;j++){
            d=d+(M[1][j]*c[j]);
        }
        return d;
    }
}

void addLinCoeff(int eqnum,int varnum,float val){
    augmentedM[eqnum][varnum+1] += val;
    //printf("eq %d, var %d val %0.2e\n",eqnum,varnum+1,val);
}

void addLinConstTerm(int eqnum,float val){
    augmentedM[eqnum][numVars+1] += val;
    //printf("eq %d, constant val %0.2e\n",eqnum,val);
}

void inputCoeff(){

    int i,j,t;
    float val;
    printf("Enter co-efficients of variables and constant at last Equation By Equation.\n \
    Std.Equations:\n \
    a1x1 + b1x2 +c1x3+...=d1\n \
    a2x1 + b2x2 +c2x3+...=d2\n.\n.\n.\n.\nanx1 + bnx2 +cnx3+...=dn\nEnter the number of variables(Maximum 10): ");
    scanf("%d",&numVars);

    for(i=1;i<=numVars;i++){
        printf("Give coefficients of equation %d\n",i);
        for(j=1;j<=(numVars+1);j++){   
            fflush(stdin);
            j==numVars+1?printf("Constant : "):printf("Coefficient of x%d: ",j-1);
            scanf("%f",&val);
            if(val ==0){val = 1E-7;}
            augmentedM[i][j] = val;
        }
    }
}

Result solveLinear(){
    Result ret;
    int i,j,k;
    float c=0.0,sum = 0.0,res =0.0;
    if(numVars == 1){
        if(augmentedM[1][1] == 0){
            ret.status = MATH_ERROR;
            sprintf(ret.error_info,"Inconsistant or Infinite Solution Equations");
            return ret;
        }
        ret.status = SUCCESS;
        X[1]= augmentedM[1][2]/augmentedM[1][1];
        return ret;
    }
    for(i=1;i<=numVars;i++){
            for(j=1;j<=numVars;j++){
                tempM[i][j]=augmentedM[i][j];
            }
        }
    det = determinant(tempM,numVars);
    if(-1E-36<det && 1E-36>det){
        //printf("NO UNIQUE SOLIUTIONS\n");//for temporary purpose.
        ret.status = MATH_ERROR;
        sprintf(ret.error_info,"Inconsistant or Infinite Solution Equations");
        return ret;
    }
    for(j=1;j<=numVars;j++){
        for(i=1;i<=numVars;i++){
            if(i>j){
                if(augmentedM[j][j] < -1E-36 || augmentedM[j][j] > 1E-36){//<---Check for 0 in Denominator--->
                    c=augmentedM[i][j]/augmentedM[j][j];
                    for(k=1;k<=numVars+1;k++){
                        augmentedM[i][k]=augmentedM[i][k]-(c*augmentedM[j][k]);
                    }
                }else{
                    ret.status = MATH_ERROR;
                    sprintf(ret.error_info,"Inconsistant or Infinite Solution Equations");
                    return ret;
                }
            }
        }
    }
    X[numVars]=augmentedM[numVars][numVars+1]/augmentedM[numVars][numVars];//<<Back Substitution>>
    for(i=numVars-1;i>=1;i--){
        sum=0.0;
        for(j=i+1;j<=numVars;j++){
            sum+=augmentedM[i][j]*X[j];
        }
        X[i]=(augmentedM[i][numVars+1]-sum)/augmentedM[i][i];
    }
    ret.status = SUCCESS;
    return ret;
}



void displayLinearSoln(){

    int i;
    printf("Solution : \n");
    for(i=1;i<=numVars;i++){
        printf("x%d = %f\n",i,X[i]);
    }


}

#endif
