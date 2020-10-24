#ifndef SOLVER_H_
#define SOLVER_H_

#include "AllEquations.h"

/**
 * Steps to solve:
 * 1. calculate determinant of coefficients matrix
 * 2. inverse the coefficients matrix
 * 3. multiply between coefficients matrix and free numbers matrix
 *
 * result ---> x = A^(-1) * B
 */

typedef struct
{
	int count;
	float** A_Mat;
	float* B_Vec;
	float determinant;
	float* X_Vec;
}Solver;

void initSolver(AllEquations* pAll, Solver* pSolve);
int solve(Solver* pSolve);

float** createMatrixA(AllEquations* pAll, Solver* pSolve);
float* createVectorB(AllEquations* pAll, Solver* pSolve);
float* createVectorX(Solver* pSolve, float** inverse);

void printMatrix(const float** matrix, int size);
void printVectorB(const float* vector, int size);
void printVectorX(const float* vector, int size);
void printDetails(const Solver* pSolve, int hasSolution);

//all math functions to solve the equation system
float getDeterminant(const float** mat, int size);
float** inverseMatrix(const float** mat, int size, int det);
float** transpose(const float** mat, int size);
float* multiplyMatrix(const float** matA, const float* vecB, int size);

void freeSolver(Solver* pSolve);

#endif /* SOLVER_H_ */