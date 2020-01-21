#include "CRandomSearch.h"

CRandomSearch::CRandomSearch()
{
	pc_current_solution = NULL;
	pc_best_solution = NULL;
}

bool CRandomSearch::bInitialize(CProblem& pcProblem)
{
	pc_problem = &pcProblem;
	return true;
}

bool CRandomSearch::bRunAlgorithm()
{
	if (pc_problem == NULL)
	{
		std::cout << "ALGORITHM UNINITIALIZED! CANNOT PROCEEED!\n" << std::endl;
		return false;
	}
	bool bSuccessfullFind = false;

	pc_best_solution = new CSolution(pc_problem->iGetSuppliersCount(), pc_problem->iGetFactoriesCount(), pc_problem->iGetWarehousesCount(), pc_problem->iGetSellersCount());
	double dCurrentProfit = 0;
	double dBestProfit = 0;

	CTimer time;
	time.vStart();

	while (time.dCurrentTime() < TIMES_TO_RANDOM_ALGORITHM_TIMEOUT)
	{
		pc_current_solution = pcGenerateSolution(*pc_problem);
		if (pc_problem->bConstraintsSatisfied(*pc_current_solution) == true)
		{
			pc_problem->bGetQuality(*pc_current_solution, dCurrentProfit);
			if (dCurrentProfit > dBestProfit)
			{
				delete pc_best_solution;
				dBestProfit = dCurrentProfit;
				pc_best_solution = pc_current_solution;
				bSuccessfullFind = true;
			}
			else
			{
				delete pc_current_solution;
			}
		}
		else
		{
			delete pc_current_solution;
		}
	}
	time.vStop();
	return bSuccessfullFind;
}

CSolution* CRandomSearch::pcGenerateSolution(CProblem& pcProblem)
{
	CRandom cRandom;
	CSolution* pcSolution;
	pcSolution = new CSolution(pcProblem.iGetSuppliersCount(), pcProblem.iGetFactoriesCount(), pcProblem.iGetWarehousesCount(), pcProblem.iGetSellersCount());
	double dRandom = 0;

	for (int i = 0; i < pcSolution->iGetSize(); i++)
	{
		dRandom = cRandom.vSetRange(pcProblem.dGetMinValueAt(i), pcProblem.dGetMaxValueAt(i)).dGenerateNumber();
		pcSolution->pdGetPdSolution()->bSet(dRandom, i);
	}

	pcSolution->vFillMatrixes();
	return pcSolution;
}

CSolution* CRandomSearch::pcGetValidSolution(CProblem& pcProblem)
{
	CSolution* pcValidSolution;
	CTimer time;
	time.vStart();
	//for (int i = 0; i < TIMES_TO_VALIDATE_SOLUTION; i++){
	while(time.dCurrentTime() < VALIDATE_SOLUTION_TIMEOUT)
	{ 
		pcValidSolution = pcGenerateSolution(pcProblem);
		if (pcProblem.bConstraintsSatisfied(*pcValidSolution))
		{	
			time.vStop();
			return pcValidSolution;
		}
		delete pcValidSolution;
	}
	time.vStop();
	return NULL;
}

