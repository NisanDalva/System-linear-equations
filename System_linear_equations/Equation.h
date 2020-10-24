#ifndef EQUATION_H_
#define EQUATION_H_

#define MAX_LEN 80

typedef struct
{
	int count; //number of coefficients
	float* A; //coefficients of x,y,z (in that order)
	float B; //the free number on the right side
}Equation;

int initEquation(Equation* pE);
char* createDynamicEquation();

/**
 * convert from full equation to only coefficients for x,y,z and store them in array
 * also method stores the free number into variable B
 * 5x+3y-7z=10 ---> [5, 3, -7] , B=10
 */
int getCoefficients(Equation* pE, const char* theEquation);
void freeEquation(Equation* pE);

#endif /* EQUATION_H_ */