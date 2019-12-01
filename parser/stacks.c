//========================================================
//=====================PostFix Stack======================

//Suffix / Prefix :-
//Op = Operator
//P = Postfix
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "typedef.c"

#ifndef STACK
#define STACK
typedef struct NodeOp //For Operators Stack
{
	char op;
	struct NodeOp *next;
}NodeO;
typedef struct NodePostfix //For Postfix Expression
{
	float var;
	struct NodePostfix *next;
}NodeP;
//========================================General Stack=====================================================
typedef struct varStack
{
	float var;
	struct varStack *next;
}gStack;
gStack *top,*gTemp;			    //General Stack
NodeO *opTop, *tempOp;			//Global Decalaration for Top and Temp of Operator Link List Stack
NodeP *pTop, *tempP;		//Global Decalaration for Top and Temp of Postfix Link List Stack
void pushOp(char opr)
{
	NodeO *newnodeOp = (NodeO *)malloc(sizeof(NodeO));
	newnodeOp->next=NULL;
	newnodeOp->op=opr;
	if (opTop==NULL)
	{
		opTop=newnodeOp;
	}
	else
	{
		newnodeOp->next=opTop;
		opTop=newnodeOp;					//Attaches NewNode before (on top of) the top node in the stack
	}
}
Result popOp()
{
	char operator;
	Result ret;
	if (opTop==NULL)
	{
		ret.status = ERROR;
		strcpy(ret.error_info,"Operator Stack List Empty");
	}
	else
	{
		operator=opTop->op;
		tempOp=opTop;
		opTop=opTop->next;
		free(tempOp);
		ret.data = operator;
		ret.status = SUCCESS;
	}
	return ret;
}

Result peekOp(){

	char operator;
	Result ret;
	if (opTop==NULL)
	{
		ret.status = ERROR;
		strcpy(ret.error_info,"Operator Stack List Empty");
	}
	else
	{
		ret.data = opTop->op;
		ret.status = SUCCESS;
	}
	return ret;
	
}
//Display Function Only For Debugging
void displayOp()
{
	//int i=2;
	tempOp=opTop;
	if (opTop==NULL)
	{
		printf("opTop is unassigned or the list is empty \n");
	}
	else
	{
		while (tempOp!=NULL)
		{
			printf("%c \n",tempOp->op);			//Display the operators from top -> bottom
			tempOp=tempOp->next;
		}
	}
}
void pushP(float vari)
{
	NodeP *newnodeP =(NodeP *)malloc(sizeof(NodeP));
	newnodeP->next=NULL;
	newnodeP->var=vari;
	if (pTop==NULL)
	{
		pTop=newnodeP;
	}
	else
	{
		newnodeP->next=pTop;
		pTop=newnodeP;					//Attaches NewNode before (on top of) the top node in the stack
	}
}
Result popP()
{
	float variable;
	Result ret;
	if (pTop==NULL)
	{
		strcpy(ret.error_info,"Postfix Stack List Empty");
		ret.status = ERROR;
	}
	else
	{
		variable=pTop->var;
		tempP=pTop;
		pTop=pTop->next;
		free(tempP);
		ret.status = SUCCESS;
		ret.data = variable;
	}
	return ret;
}

//================================Functions of General Stack========================================
void push(float variable)
{
	gStack *newnode =(gStack *)malloc(sizeof(gStack));
	newnode->next=NULL;
	newnode->var=variable;
	if (top==NULL)
	{
		top=newnode;
	}
	else
	{
		newnode->next=top;
		top=newnode;					//Attaches NewNode before (on top of) the top node in the stack
	}
}
Result pop()
{
	float variable;
	Result ret;
	if (top==NULL)
	{	
		ret.status = ERROR;
		strcpy(ret.error_info,"General Stack List Empty");
	}
	else
	{
		variable=top->var;
		gTemp=top;
		top=top->next;
		free(gTemp);
		ret.status= SUCCESS;
		ret.data = variable;
	}
	return ret;
}

gStack *getTop(){
	return top;
}

gStack *setTop(gStack *t){
	gStack *temp;
	while(top!= NULL && top != t){
		temp = top;
		top = top->next;
		free(temp);
	}
}

#endif