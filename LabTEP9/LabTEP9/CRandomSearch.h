#pragma once
#include "CRandom.h"
#include "CMscnProblem.h"
#include "Constants.h"


class CRandomSearch 
{
public:
	CRandomSearch();
	CRandomSearch(CMscnProblem* pcProblem);
	~CRandomSearch();
	CSolution* pcGenerateSolution(CRandom& cRandom);
	CSolution* pcGetBestSolution();
private:
	CSolution* pc_current_solution;
	CSolution* pc_best_solution;
	CMscnProblem* pc_problem;
};//class CRandomSearch
