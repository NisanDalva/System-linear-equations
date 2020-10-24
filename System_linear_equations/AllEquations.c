#define _CRT_SECURE_NO_WARNINGS
#include "AllEquations.h"
#include "Equation.h"


int initAllEquations(AllEquations* pAll)
{
	pAll->eqArr = createEquationsArray(&pAll->count);
	Equation* eq;

	if (!pAll->eqArr)
		return 0; //allocation didn't work

	for (int i = 0; i < pAll->count; i++)
	{
		eq = (Equation*)malloc(1 * sizeof(Equation)); //allocates per equation
		if (!eq)
			return 0;//allocation didn't work
		
		eq->count = pAll->count; //number of coefficients equals to number of equations
		pAll->eqArr[i] = eq;
		printf("Enter equation number %d (max 80 letters): ", i + 1);

		while (!initEquation(pAll->eqArr[i])) //check for correct equation
			printf("Wrong input or allocation failed. Enter again equation %d: ", i + 1);
	}
	return 1;
}

Equation** createEquationsArray(int* pCount)
{
	char temp; //temp character to clean the buffer
	Equation** eqArr;

	do
	{
		printf("Number of equations (1-3): ");
		scanf("%d", pCount);
		scanf("%c", &temp); //clean the buffer
	} while (*pCount < 1 || *pCount > 3);

	if (*pCount == 0)
		return NULL;

	eqArr = (Equation**)malloc(*pCount * sizeof(Equation*)); //allocate memory for equations array
	return eqArr; //maybe NULL, check that on initAllEquations method
}

void freeAllEquations(AllEquations* pAll)
{
	for (int i = 0; i < pAll->count; i++)
		freeEquation(pAll->eqArr[i]);
	free(pAll->eqArr);
}