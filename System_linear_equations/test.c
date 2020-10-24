#include <stdio.h>
#include "AllEquations.h"
#include "Equation.h"
#include "Solver.h"

void freeSystem(AllEquations* pAll, Solver* pSolve);

int main()
{
	AllEquations allEq;
	Solver solver;
	int hasSolution, isAllCorrect;

	isAllCorrect = initAllEquations(&allEq);
	printf("-------------------------------\n");

	if (isAllCorrect)
	{
		initSolver(&allEq, &solver);
		hasSolution = solve(&solver); //try to solve the system

		printDetails(&solver, hasSolution);
		freeSystem(&allEq, &solver);
	}
	else
		printf("One of the allocations didn't work.");

	return 1;
}

void freeSystem(AllEquations* pAll, Solver* pSolve)
{
	freeAllEquations(pAll);
	freeSolver(pSolve);
}