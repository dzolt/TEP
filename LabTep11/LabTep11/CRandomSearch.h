#pragma once
#include "CRandom.h"
#include "CMscnProblem.h"
#include "Constants.h"


class CRandomSearch
{
public:
	CRandomSearch();
	~CRandomSearch();
	CSolution* pcGenerateSolution(CMscnProblem& cProblem);
	CSolution* pcGetBestSolution(CMscnProblem& cProblem);
	CSolution* pcGetValidSolution(CMscnProblem& cProblem);
	bool bGetSolutionQualityToFile(std::string sFileName, double dProfit);
private:
	double dCalculateRangePercentage(double dValue, double dMinRange, double dMaxRange);
	CSolution* pc_current_solution;
	CSolution* pc_best_solution;
};//class CRandomSearch
