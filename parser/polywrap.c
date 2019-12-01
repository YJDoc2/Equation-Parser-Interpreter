#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "./typedef.c"
#include "./preparser.c"
#include "./parser.c"
#include "./linkedlist.c"
#include "./poly.c"
#include "./util.c"

#ifndef POLYWRAP
#define POLYWRAP

char *nextStart;

void pushPolyConstTerm(float val){
    //printf("Constant Value %f\n",val);
    pushPolyTerm(0,val);
    //addPolyConstTerm(val);
}
void pushPolyCoeff(int power,float val){
    //printf("Power : %d coeff %f\n",power,val);
    pushPolyTerm(power,val);
    //addPolyCoeff(power,val);
}

void setPolyTerms(int degree){
    
    initPoly(degree);
    memset(crrPoly,0,(degree+1)*sizeof(float));
	memset(polyQtnt,0,degree*sizeof(float));
    Polyterm *temp = pstart;
    while(temp != NULL){
        crrPoly[degree-temp->pow] += temp->coeff;
        temp = temp->next;
    }
}

Result getPower(char *in){
    Result ret;
    int brack=0;
    char *temp,*end;
    if( *(in+1) == '+' || *(in+1) == '-' || *(in+1) == '=' || *(in+1) == '\0'){
        ret.status = SUCCESS;
        ret.data = 1;
        nextStart = in;
        return ret;
    }
    if(*(in+1)!= '^'){
        ret.status =ERROR;
        sprintf(ret.error_info,"Incorrect Format please use x^ or X^");
        return ret;
    }
    temp = in+1;
    while(*temp != '\0'){
        if(*temp =='(' || *temp =='[' || *temp =='{'){
            brack++;
        }
        if(*temp ==')' || *temp ==']' || *temp =='}'){
            brack--;
        }
        if(brack ==0 && (*(temp+1) == '+' || *(temp+1)=='-' || *(temp+1) == '\0')){
            break;
        }
        temp++;
    }
    ret = parse(in+2,temp+1);
    CHECK(ret,in,3);
    if(ret.data <0 || ret.data-(int)ret.data >1E-36){
        ret.status = ERROR;
        sprintf(ret.error_info,"Cannot solve polynomials with fractional powers");
        return ret;
    }else{
        ret.data = (int)ret.data;
    }
    nextStart = temp;
    return ret;
}

Result parsePoly(char in[]){
    char *start,*end,*eq,*xpos;
    char eqn[50];
    memset(eqn,'\0',50);
    int power;
    Result temp;

    int degree =0;
    removeSpaces(in);
    temp = bracketCheck(in,in+strlen(in));
    CHECK(temp,in,1);
    if(strchr(in,'=') != strrchr(in,'=')){
        temp.status = ERROR;
        sprintf(temp.error_info,"Cannot Have multiple assignment Signs in An Equation");
        return temp;
    }
    eq = strchr(in,'=');
    if(eq == NULL){
        pushPolyConstTerm(0);
        strncpy(eqn,in,strlen(in)+1);
        end = eqn+strlen(eqn)-1;
    }else{
        end = eq-1;
        temp = parse(eq+1,in+strlen(in));
        CHECK(temp,in,eq+1);
        strncpy(eqn,in,eq-in);
        eqn[strlen(eqn)] ='\0';
        pushPolyConstTerm(-temp.data);//const Term should be on left of equal sign
    }
    start = eqn;
    xpos = getCharPos(eqn,end,'x');
    if(xpos == NULL){
        temp.status = ERROR;
        sprintf(temp.error_info,"No X or x found in given polynomial equation");
        return temp;
    }
    while(xpos != NULL){
        temp = getPower(xpos);
        CHECK(temp,in,xpos-in+1);
        power = (int)temp.data;
        if(degree<power){degree = power;}//From polydiv.c
        if(start == xpos || *start == '\0'){
            temp.status = SUCCESS;
            temp.data = 1;
        }else if(*start=='-' && start+1 ==xpos){
            temp.status = SUCCESS;
            temp.data = -1;
        }else{
            temp = parse(start,xpos);
            CHECK(temp,in,xpos-in);
        }
        pushPolyCoeff(power,temp.data);
        if(*(nextStart+1) == '+'){
            start = nextStart+2;
        }else{
            start = nextStart+1;
        }
        xpos = getCharPos(xpos+1,xpos+strlen(xpos),'x');
    }
    if(start != eqn+strlen(eqn)){
        temp = parse(start,eqn+strlen(eqn));
        CHECK(temp,in,xpos-in);
        pushPolyConstTerm(temp.data);
    }
    setPolyTerms(degree);
    temp.status = SUCCESS;
    temp.data = degree;
    return temp;
}

Result solvePoly(char in[]){
    poly = 1; // from parser
    Result ret;
    flushRootList();
    ret = parsePoly(in);
    if(ret.status != SUCCESS){poly =0;flushRootList();return ret;}
    evalPoly((int)ret.data);
    flushTermList();
    poly =0;
    ret.status = SUCCESS;
    return ret;
    //displayRoot();
}

#endif