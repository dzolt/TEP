#pragma once
#include "CRandom.h"
#include "Constants.h"
#include "COptimizer.h"


class CRandomSearch : public COptimizer
{
public:
	CRandomSearch();
	bool bInitialize(CProblem& pcProblem);
	bool bRunAlgorithm();
	CSolution* pcGenerateSolution(CProblem& pcProblem);
	CSolution* pcGetValidSolution(CProblem& pcProblem);
private:
	CSolution* pc_current_solution;
};//class CRandomSearch
