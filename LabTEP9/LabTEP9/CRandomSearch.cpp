#include "CRandomSearch.h"

CRandomSearch::CRandomSearch()
{
	pc_problem = NULL;
	pc_current_solution = NULL;
	pc_best_solution = NULL;
}

CRandomSearch::CRandomSearch(CMscnProblem* pcProblem)
{
	pc_problem = pcProblem;
	pc_current_solution = NULL;
	pc_best_solution = NULL;
}

CRandomSearch::~CRandomSearch()
{
	delete pc_problem;
	delete pc_current_solution;
}

CSolution* CRandomSearch::pcGenerateSolution(CRandom& cRandom)
{
	CSolution* pcSolution;
	pcSolution = new CSolution(pc_problem->iGetSuppliersCount(), pc_problem->iGetFactoriesCount(), pc_problem->iGetWarehousesCount(),
		pc_problem->iGetSellersCount());
	double dRandom = 0;
	//double currentAmmountSent = 0; // dodalem current ammount sent mozne zle??
	for (int i = 0; i < pcSolution->iGetSize(); i++)
	{	
		//if (i == pcSolution->iGetXfMatrixFirstIndex() || i == pcSolution->iGetXmMatrixFirstIndex()) currentAmmountSent = 0;

		if (i < pcSolution->iGetXfMatrixFirstIndex())
		{	
			dRandom = cRandom.vSetRange(pc_problem->dGetMinValueAt(*pcSolution, i), pc_problem->dGetMaxValueAt(*pcSolution, i)).dGenerateNumber();
			pcSolution->pdGetPdSolution()->bSet(dRandom,i);
			//currentAmmountSent += pcSolution->pdGetPdSolution()->dGet(i);
		}
		else if (i < pcSolution->iGetXmMatrixFirstIndex())
		{
			dRandom = cRandom.vSetRange(pc_problem->dGetMinValueAt(*pcSolution, i), pc_problem->dGetMaxValueAt(*pcSolution, i)).dGenerateNumber();
			pcSolution->pdGetPdSolution()->bSet(dRandom, i);
			//currentAmmountSent += pcSolution->pdGetPdSolution()->dGet(i);
		}
		else
		{
			dRandom = cRandom.vSetRange(pc_problem->dGetMinValueAt(*pcSolution, i), pc_problem->dGetMaxValueAt(*pcSolution, i)).dGenerateNumber();
			pcSolution->pdGetPdSolution()->bSet(dRandom, i);
			//currentAmmountSent += pcSolution->pdGetPdSolution()->dGet(i) -20;
		}
	}

	pcSolution->vFillMatrixes();
	return pcSolution;
}

CSolution* CRandomSearch::pcGetBestSolution()
{
	CRandom random;
	double dCurrentProfit = 0;
	double dBestProfit = 0;
	for (int i = 0; i < TIMES_TO_RUN_ALGORITHM; i++)
	{
		 pc_current_solution = pcGenerateSolution(random);
		 if (i == 0)
		 {
			 pc_best_solution = pc_current_solution;
			 pc_problem->vSetSolution(pc_best_solution);
		 }
		 // czy nie trzeba pc_problem.pc_solution zamienic na current
		 pc_problem->bGetQuality(*pc_current_solution, dCurrentProfit);
		 
		 if (pc_problem->bConstraintsSatisfied(*pc_current_solution) == true)
		 {	
			 if (pc_best_solution == NULL)
			 {
				 pc_best_solution = pc_current_solution;
				 dBestProfit = dCurrentProfit;
			 }
			 else if (dCurrentProfit > dBestProfit)
			 {
				 delete pc_best_solution;
				 dBestProfit = dCurrentProfit;
				 pc_best_solution = pc_current_solution;
			 }
		 }
		//i warunek na sprawdzenie ktore jest lepsze
	}
	return pc_best_solution;
}