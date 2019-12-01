#include<stdio.h>
#include<stdlib.h>

#ifndef LINKEDLIST
#define LINKEDLIST
typedef struct LinkList //For Polynomial
{
	float coef;
	struct LinkList *next;
}Quotient;
typedef struct polyterm{
	int pow;
	float coeff;
	struct polyterm *next;
}Polyterm;
Quotient *newnode,*qstart,*rootstart,*flushtemp,*qlast;			//start= to store quotient list  			start2= to store roots list
Polyterm *newnodeP,*pstart,*last;
void pushList(float v)
{
	Quotient *newnode =(Quotient *)malloc(sizeof(Quotient));
	newnode->next=NULL;
	newnode->coef=v;
	if (qstart==NULL)
	{
		qstart=newnode;
		qlast = newnode;
	}
	else
	{
		newnode->coef=v;
		
		qlast->next=newnode;
		qlast = newnode;
	}
}
void displayList()
{
	Quotient *temp;
	temp=qstart;
	if (qstart==NULL)
	{
		printf("list is empty \n");
	}
	else
	{
		while (temp!=NULL)
		{
			printf("%f \n",temp->coef);			//Display the variables from top -> bottom
			temp=temp->next;
		}
	}
}
void pushRoot(float v)
{
	Quotient *temp;
	Quotient *newnode =(Quotient *)malloc(sizeof(Quotient));
	newnode->next=NULL;
	newnode->coef=v;
	if (rootstart==NULL)
	{
		rootstart=newnode;
	}
	else
	{
		temp=rootstart;
		newnode->coef=v;
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=newnode;
	}
}

void pushPolyTerm(int pow,float coeff)
{
	Polyterm *temp;
	Polyterm *newnode =(Polyterm *)malloc(sizeof(Polyterm));
	newnode->next=NULL;
	newnode->pow = pow;
	newnode->coeff=coeff;
	if (pstart==NULL)
	{
		pstart=newnode;
		last = newnode;
	}
	else
	{
		last->next = newnode;
		last=newnode;
	}
}

void flushTermList(){
	Polyterm *temp;
	while (pstart!=NULL){
		temp = pstart;
		pstart=pstart->next;
		free(temp);
	}
}

void flushRootList(){
	while (rootstart!=NULL){
		flushtemp = rootstart;
		rootstart=rootstart->next;
		free(flushtemp);
	}
}
void displayRoot()
{
	Quotient *temp;
	temp=rootstart;
	if (temp==NULL)
	{
		printf("No Real root Found for this Equation \n");
	}
	else
	{
		while (temp!=NULL)
		{
			printf("Root= %f \n",temp->coef);			//Display the variables from top -> bottom
			temp=temp->next;
		}
	}
}
#endif
