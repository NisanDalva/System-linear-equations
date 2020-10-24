#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "Equation.h"
#define MAX_LEN 80

int initEquation(Equation* pE)
{
	pE->A = (float*)malloc(pE->count * sizeof(float)); //allocate memory for each coefficients equation
	if (!pE->A)
		return 0; //allocation didn't work

	char* theEquation = createDynamicEquation();
	if (!theEquation)
		return 0; //allocation didn't work

	if (!getCoefficients(pE, theEquation))
		return 0; //wrong input

	free(theEquation); //the full equation (for example: 5x+3y-7z=10) should no longer to be used
	return 1;
}

char* createDynamicEquation()
{
	char temp[MAX_LEN];
	char* theEquation;
	fgets(temp, MAX_LEN, stdin); //input from user

	theEquation = (char*)malloc(strlen(temp) * sizeof(char));
	if (!theEquation)
		return NULL; //allocation didn't work

	strcpy(theEquation, temp); // copy from temp to theEquation
	return theEquation;
}

int getCoefficients(Equation* pE, const char* theEquation)
{
	int sign = 1, power = 1;
	int hasDot = 0, number = 0;
	double subNumber = 0; //number after the point
	char c;
	// flags to check if the equation is valid
	int flagX, flagY, flagZ, flagEqual;
	flagX = flagY = flagZ = flagEqual = 0;

	for (int i = 0; i < strlen(theEquation); i++) // run all over theEquation string
	{
		c = theEquation[i];

		if (c == '*' || c == ' ' || c == '+')
			continue; // skip those characters, doesn't need to check them

		if (c != 'x' && c != 'y' && c != 'z' && c != '=') //convert from string to float
		{
			if (c == '-')
				sign = -sign;

			else if (isdigit(c) && !hasDot)
			{
				number *= 10;
				number += c - '0';
			}
			else if (isdigit(c) && hasDot)
				subNumber += (c - '0') * pow(10, -(power++)); //example: 0.23 --> 2*10^(-1) + 3*10^(-2)

			else if (c == '.')
				hasDot = 1;
		}
		else //put the number that found before in a correct variable
		{
			if (c == 'x')
			{
				flagX = 1;
				pE->A[0] = sign * (number + subNumber);
			}
			else if (c == 'y')
			{
				flagY = 1;
				pE->A[1] = sign * (number + subNumber);
			}
			else if (c == 'z')
			{
				flagZ = 1;
				pE->A[2] = sign * (number + subNumber);
			}
			else if (c == '=')
				flagEqual = 1;

			//initialize values to next number
			number = hasDot = 0;
			subNumber = 0.0;
			sign = abs(sign);
			power = 1;
		}
	}
	pE->B = sign * (number + subNumber); //last number

	if ((flagX == 0 && flagY == 0 && flagZ == 0)
		|| flagEqual == 0) //none of the variables were initialized, or there is no equation at all - wrong input
		return 0;
	else
		return 1;
}

void freeEquation(Equation* pE)
{
	free(pE->A);
}