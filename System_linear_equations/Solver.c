#include <stdio.h>
#include <string.h>
#include "Solver.h"
#include "AllEquations.h"


void initSolver(AllEquations* pAll, Solver* pSolve)
{
	pSolve->count = pAll->count;
	pSolve->A_Mat = createMatrixA(pAll, pSolve);
	pSolve->B_Vec = createVectorB(pAll, pSolve);

	if (!pSolve->A_Mat || !pSolve->B_Vec)
	{
		printf("Allocation failed for A_Mat or B_Vec");
		return;
	}
	pSolve->determinant = getDeterminant(pSolve->A_Mat, pSolve->count);
}

int solve(Solver* pSolve)
{
	float** tempInverseMatrix;

	if (pSolve->determinant == 0)
		return 0; //no solution

	tempInverseMatrix = inverseMatrix(pSolve->A_Mat, pSolve->count, pSolve->determinant);
	pSolve->X_Vec = createVectorX(pSolve, tempInverseMatrix);

	//free tempInverseMatrix
	for (int i = 0; i < pSolve->count; i++)
		free(tempInverseMatrix[i]);
	free(tempInverseMatrix);

	if (!pSolve->X_Vec)
	{
		printf("Allocation failed for X_Vec");
		return 0;
	}
	return 1;
}

float** createMatrixA(AllEquations* pAll, Solver* pSolve)
{
	float** mat = (float**)malloc(pSolve->count * sizeof(float*));
	if (!mat)
		return NULL; //allocation didn't work

	for (int i = 0; i < pSolve->count; i++)
		mat[i] = pAll->eqArr[i]->A;

	return mat;
}

float* createVectorB(AllEquations* pAll, Solver* pSolve)
{
	float* vector = (float*)malloc(pSolve->count * sizeof(float));
	if (!vector)
		return NULL;//allocation didn't work

	for (int i = 0; i < pSolve->count; i++)
		vector[i] = pAll->eqArr[i]->B;

	return vector;
}

float* createVectorX(Solver* pSolve, float** inverse)
{
	float* vector;
	vector = multiplyMatrix(inverse, pSolve->B_Vec, pSolve->count);

	return vector;
}

void printMatrix(const float** matrix, int size)
{
	printf("Matrix A =\n");
	for (int i = 0; i < size; i++)
	{
		printf("\t");
		for (int j = 0; j < size; j++)
			printf("%.3f   ", matrix[i][j]);

		printf("\n");
	}
	printf("\n");
}

void printVectorB(const float* vector, int size)
{
	printf("Vector B =\n");
	for (int i = 0; i < size; i++)
	{
		printf("\t");
		printf("%.3f\n", vector[i]);
	}
	printf("\n");
}

void printVectorX(const float* vector, int size)
{
	char ch[3] = { 'x', 'y', 'z' };
	printf("Vector X =\n");
	for (int i = 0; i < size; i++)
	{
		printf("\t");
		printf("%c = %.3f\n", ch[i], vector[i]);
	}
	printf("\n");
}

void printDetails(const Solver* pSolve, int hasSolution)
{
	printMatrix(pSolve->A_Mat, pSolve->count);
	printf("Matrix A determinant = %.3f\n\n", pSolve->determinant);
	printVectorB(pSolve->B_Vec, pSolve->count);
	if (hasSolution)
		printVectorX(pSolve->X_Vec, pSolve->count);
	else
		printf("There is no single solution for that system of equations.\n");
}

float getDeterminant(const float** mat, int size)
{
	if (size == 3)
		return  mat[0][0] * ((mat[1][1] * mat[2][2]) - (mat[1][2] * mat[2][1])) -
		mat[0][1] * ((mat[1][0] * mat[2][2]) - (mat[1][2] * mat[2][0])) +
		mat[0][2] * ((mat[1][0] * mat[2][1]) - (mat[1][1] * mat[2][0]));

	else if (size == 2)
		return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);

	else
		return mat[0][0];
}

float** transpose(const float** mat, int size)
{
	// allocates a temp matrix
	float** transposed = (float**)malloc(size * sizeof(float*));
	for (int i = 0; i < size; i++)
		transposed[i] = (float*)malloc(size * sizeof(float));

	if (!transposed)
		return NULL; //allocation didn't work

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			transposed[j][i] = mat[i][j];
	}

	//free the mat, should not be used any more
	for (int i = 0; i < size; i++)
		free(mat[i]);
	free(mat);

	return transposed;
}

float** inverseMatrix(const float** mat, int size, int det)
{
	// allocates a temp matrix
	float** temp = (float**)malloc(size * sizeof(float*));
	for (int i = 0; i < size; i++)
		temp[i] = (float*)malloc(size * sizeof(float));

	if (!temp)
		return NULL; //allocation didn't work

	if (size == 1)
		temp[0][0] = 1 / mat[0][0];
	else if (size == 2)
	{
		temp[0][0] = mat[1][1] / det;
		temp[0][1] = -mat[0][1] / det;
		temp[1][0] = -mat[1][0] / det;
		temp[1][1] = mat[0][0] / det;
	}
	else if (size == 3)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				temp[i][j] = (((mat[(i + 1) % 3][(j + 1) % 3] * mat[(i + 2) % 3][(j + 2) % 3]) -
					(mat[(i + 1) % 3][(j + 2) % 3] * mat[(i + 2) % 3][(j + 1) % 3])) / det);
		}
		temp = transpose(temp, size);
	}
	return temp;
}

float* multiplyMatrix(const float** matA, const float* vecB, int size)
{
	float* vector = (float*)malloc(size * sizeof(float));
	memset(vector, 0, size * sizeof(float));

	if (!vector)
		return NULL; //allocation didn't work

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < size; k++)
				vector[i] += matA[i][k] * vecB[k];
		}
	}
	return vector;
}

void freeSolver(Solver* pSolve)
{
	//free coefficients matrix
	for (int i = 0; i < pSolve->count; i++)
		free(pSolve->A_Mat[i]);
	free(pSolve->A_Mat);

	//free B array
	free(pSolve->B_Vec);

	//free X array
	free(pSolve->X_Vec);

}