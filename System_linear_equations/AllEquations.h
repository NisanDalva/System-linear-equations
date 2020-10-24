#ifndef ALLEQUATIONS_H_
#define ALLEQUATIONS_H_

#include <stdio.h>
#include <stdlib.h>

#include "Equation.h"

typedef struct
{
	int count; //number of coefficients
	Equation** eqArr; //all equations
}AllEquations;

/**
 * method creates an array of pointers to equation
 */
Equation** createEquationsArray(int* pCount);
int initAllEquations(AllEquations* pAll);
void freeAllEquations(AllEquations* pAll);

#endif /* ALLEQUATIONS_H_ */