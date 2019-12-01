#include<stdio.h>
void showHelp()
{
	printf("\n\n");

	printf(" ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ ______ \n");
	printf("|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|\n");
	printf(" \t\t  ______                  _   _               _____                       			\n");
	printf(" \t\t |  ____|                | | (_)             |  __ \\                       		\n");
	printf(" \t\t | |__   __ _ _   _  __ _| |_ _  ___  _ __   | |__) |_ _ _ __ ___  ___ _ __  		\n");
	printf(" \t\t |  __| / _` | | | |/ _` | __| |/ _ \\| '_ \\  |  ___/ _` | '__/ __|/ _ \\ '__| 	\n");
	printf(" \t\t | |___| (_| | |_| | (_| | |_| | (_) | | | | | |  | (_| | |  \\__ \\  __/ |    	\n");
	printf(" \t\t |______\\__, |\\__,_|\\__,_|\\__|_|\\___/|_| |_| |_|   \\__,_|_|  |___/\\___|_|  	\n");
	printf(" \t\t           | |                                                           			\n");
	printf(" \t\t           |_|                                                           	 		\n");
    printf("========================================================================================================================\n");
    printf("                                             		    HELP                                                                                            \n");
    printf("========================================================================================================================\n");
    printf("\n");
    printf("This is Version 'Mark II' developed by Vatsal Soni,Yashodhan Joshi,Yatharth Vyas.\n\n");
    printf(">>>>>>GENERAL PARSER:\n\n");
    printf("----->Initial Screen is General Parser.\nIt can parse normal algebric equations.It supports some constants and default and named variables.\n");
    printf("----->Default Variables are defined as $0 to $9.Default Named Variable is Ans,which stores the answer of last operation.\n");
    printf("----->To store a value in variable just use variableName = equation. Variable name can be user defined or $0 to $9.\n");
    printf("----->To use value of variables or constants in equation, use their name or $0 to $9 for default variable.\n");
    printf("----->Supported Operations Are :\n\t- for Unary negation\n\t+ for addition\n\t- for subtraction\n\t* for multiplication\n\t/ for division\n\t%% for modulus or remainder\n\t^ for exponentiation.(NOTE :only positive values are supported as base of fractional powers)\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
    printf(">>>>>>Inbuilt functions :\n\n");
    printf("----->NOTE: All functions are case sensitive.\n");
    printf("----->Help : Shows help,i.e. this page\n");
    printf("----->showvars : Shows variables and their values\n");
    printf("----->showconst : Shows constants and their values\n");
    printf("----->vardump : Saves values of variables in a file named vardump.log,Overwrites if existing.Does not Store Ans variable.\n\tShows Error if user does not have permission to write in folder this programm is running in.\n");
    printf("----->varload: Reads the file vardump.log and loads values of variables in it.Overwrites existing variables of same name.\n\tShows Error if vardump.log Does not exist in same file as this programm.\n");
    printf("----->varclear : deletes all userdefined named variables, and Ans, sets $0 to $9 values to 0.\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
    printf(">>>>>>LINEAR EQUATION SYSTEM SOLVING :\n\n");
    printf("----->Use linsolve in general parser to use this.\nThis has two modes - Equation parsing and Coefficient Read.\n\n");
    printf("Enter coeff to Use Coefficient read:\n");
    printf("----->Standerd Form: a1x1 + a2x2 + a3x3 + a4x4+... = b\n----->Enter co-efficients first and constant at the last equation by equation.\n\n");
    printf("Use solve to parse equations and  solve them.\n");
    printf("----->If determinant is zero 0 then linear system of equations is not consistent, therefore solutions will not exits or will have infinite no. of solutions.\n");
    printf("----->If determinant is not zero then linear system of equations is consistent and equations can have unique solution.\n");
    printf("----->Method used for solving the linear equations is Gauss-Elimination Method.\n");
    printf("\n----->Type quit to return back to General Parser\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
    printf(">>>>>>PLOYNOMIAL EQUATION SOLVING: \n\n");
    printf("----->Use polysolve in general parser to use this.\nThis has three modes - Equation parsing,Coefficient Read and Linear Division.\n\n");
    printf("Enter coeff to Use Coefficient read:\n");
    printf("----->Enter the degree of Polynomial first\n");
    printf("Standerd form of a1x^n+a2x^n-1+......anx^1+constant.\n\n");
    printf("Enter the equation with powers of x or X to parse equation and find its roots.\n");
    printf("----->Now the program will use Newton-Raphson and Repeated Polynomial Division to find roots of your equation\n");
    printf("----->The All Real Roots will be displayed, upto accuracy of approximately 0.0001.\n\n");
    printf("Use div Divide a polynomial by a linear factor.\n");
    printf("----->This will divide a Polynomial Equation by a Linear of the form (x-r)\n");
    printf("----->User will have to input the value of r in (x-r) first\n");
    printf("----->Then User will be asked to input the degree of Polynomial\n");
    printf("----->Finally, User will have to input the equation in a similar fashion as in Polynomial Equation\n");
    printf("----->The output will be displayed on the screen\n");
    printf("\n----->Type quit to return back to General Parser\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n\n");
    printf("----->Type quit to close Equation Parser\n\n");
    printf("\n\t\t\t\t\tThank You for using Equation Parser.\n\n");


	 printf("__   __                                        ______           _                                        __   __ \n");
	 printf("\\ \\ / /                                       |  ____|         | |                                       \\ \\ / / \n");
	 printf(" \\ V /_____ ______ ______ ______ ______ ______| |__   _ __   __| |______ ______ ______ ______ ______ _____\\ V /  \n");
	 printf("  > <______|______|______|______|______|______|  __| | '_ \\ / _` |______|______|______|______|______|______> <   \n");
	 printf(" / . \\                                        | |____| | | | (_| |                                        / . \\  \n");
	 printf("/_/ \\_\\                                       |______|_| |_|\\__,_|                                       /_/ \\_\\ \n");
     printf("\n");
                                                                                                                 
                                                                                                                 


}
