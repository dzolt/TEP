#pragma once
#include "CProblem.h"
#include "CTimer.h"
class COptimizer
{
public:
	
	virtual bool bInitialize(CProblem& pcProblem) = 0;
	virtual bool bRunAlgorithm() = 0;
	virtual CSolution* pcGetBestSolution() {return pc_best_solution;};
protected:
	CProblem* pc_problem;
	CSolution* pc_best_solution;
};