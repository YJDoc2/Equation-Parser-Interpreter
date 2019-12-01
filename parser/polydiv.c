#include<stdio.h>
#include<stdlib.h>
#include "./linkedlist.c"


#ifndef POLYDIV
#define POLYDIV
// #include "./queues.c"  Later i will try to implement queues instead of arrays
float root1,Remainder;   			//root1= const in (x-r)
float *crrPoly;
float *polyQtnt;
//int degree;

void initPoly(int degree){

	if(crrPoly){free(crrPoly);}
	if(polyQtnt){free(polyQtnt);}
	crrPoly=(float *)malloc((degree+1)*sizeof(float));
	polyQtnt=(float *)malloc(degree*sizeof(float));

}
void getDivisor()
{
	printf("Enter the value or r in (x-r) which is divisor : ");
  	scanf("%f",&root1);
}
float polyDiv(int degree)		//Returns Remainder , input is taken inside this.
{
	int i;
	polyQtnt[0]=crrPoly[0];			//coef of x^n = coef of x^n-1 after division
	for (i = 1; i <= degree; i++)
	{
		polyQtnt[i] = crrPoly[i] + root1 * polyQtnt[i-1];							// polyQtnt[i] is coef of x^(n-i) and same for crrPoly[i]
	}
	Remainder = crrPoly[degree] + root1 * polyQtnt[degree-1];								//Remainder
	for (i=0;i<degree;i++)									//Storing in LinkList
	{
		pushList(polyQtnt[i]);
	}
	//display();
	return Remainder;
}
// void getDivisor()
// {
// 	printf("Enter the value or r in (x-r) which is divisor\n");
//   	scanf("%f",&root1);
// }
int getPoly()
{
	int i,degree;
	printf("Enter the degree of Polynomial Eqn: ");
	scanf("%d",&degree);

	initPoly(degree);

	for (i = 0; i <= degree; i++)
	{
		if(i == degree){
			printf("Enter constant : ");
		}else{
			printf("Enter Coeffecient of x^%d : ", degree-i );
		}
		scanf("%f",&crrPoly[i]);
	}
	return degree;
}
void displayQ(float polyQtnt[99],int degree)		//Pass the degree of eqn
{
	int i;
	for (i = 0; i <= degree; i++)
	{	
		if(i <degree-1){
			printf("(%f x^%d) + ",crrPoly[i],degree-i);		
		}else{
			printf("(%f x^%d)",crrPoly[i],degree-i);		
		}
		
	}
	printf(" / (x - %f) \n",root1);
	// printf("/ (x-%f) \n",root);
	printf("The Quotient is:\n");
	for (i = 0; i < degree; ++i)
	{	
		if(i <degree-1){
			printf("(%f x^%d) +",polyQtnt[i],degree-i-1);
		}else{
			printf("(%f x^%d)",polyQtnt[i],degree-i-1);
		}
	}
	printf("\n");
	printf("Remainder is %f\n",Remainder);
	getchar();
}
#endif