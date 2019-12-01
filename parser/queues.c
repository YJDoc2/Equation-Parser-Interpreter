//========================================================
//==========================Queue=========================

#include<stdio.h>
#include<stdlib.h>
#include "./typedef.c"

#ifndef QUEUE
#define QUEUE

typedef struct varQueue
{
	float var;
	struct varQueue *next;
}gQueue;
gQueue *cfront,*crear,*qTemp;

void enQVal(float variable)
{
	gQueue *newnode = (gQueue *)malloc(sizeof(gQueue));
	newnode->next=NULL;
	newnode->var=variable;
	if (cfront==NULL)
	{
		cfront=newnode;
		crear=newnode;
	}
	else
	{
		crear->next=newnode;
		crear=newnode;
	}
}
Result deQVal()
{
	Result ret;
	if (cfront==NULL)
	{	
		ret.status = ERROR;
		strcpy(ret.error_info,"Empty Queue");
	}
	else
	{
		float a;
		a=cfront->var;
		qTemp=cfront;
		cfront=cfront->next;
		free(qTemp);
		ret.status = SUCCESS;
		ret.data = a;
	}
	return ret;
}
Result flushQVal()								//To Empty the Queue
{
	Result ret;
	if (cfront==NULL)
	{
		ret.status = ERROR;
		strcpy(ret.error_info,"Empty Queue");
	}
	else
	{
		while (cfront!=NULL)
		{
			qTemp=cfront;
			cfront=cfront->next;
			free(qTemp);
		}
		ret.status=SUCCESS;
	}
	return ret;
}


#endif