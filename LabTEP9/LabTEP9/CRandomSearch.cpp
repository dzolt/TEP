#include "CRandomSearch.h"

CRandomSearch::CRandomSearch()
{
	pc_problem = NULL;
	pc_current_solution = NULL;
	pc_best_solution = pc_current_solution;
}

CRandomSearch::CRandomSearch(CMscnProblem* pcProblem)
{
	pc_problem = pcProblem;
	pc_current_solution = NULL;
	pc_best_solution = pc_current_solution;
}

CRandomSearch::~CRandomSearch()
{
	delete pc_problem;
	delete pc_best_solution;
	delete pc_current_solution;
}

CSolution* CRandomSearch::pcGenerateSolution(CRandom& cRandom)
{
	CSolution* pcSolution;
	pcSolution = new CSolution(pc_problem->iGetSuppliersCount(), pc_problem->iGetFactoriesCount(), pc_problem->iGetWarehousesCount(),
		pc_problem->iGetSellersCount());
	double dRandom = 0;
	for (int i = 0; i < pcSolution->iGetSize(); i++)
	{	
		if (i < pcSolution->iGetXfMatrixFirstIndex())
		{	
			dRandom = cRandom.vSetRange(MINIMAL_XD_VALUE, pc_problem->dGetMaxValueAt(*pcSolution, i)).dGenerateNumber();
			pcSolution->pdGetPdSolution()->bSet(dRandom,i);
		}
		if (i < pcSolution->iGetXmMatrixFirstIndex())
		{
			dRandom = cRandom.vSetRange(MINIMAL_XF_VALUE, pc_problem->dGetMaxValueAt(*pcSolution, i)).dGenerateNumber();
			pcSolution->pdGetPdSolution()->bSet(dRandom, i);
		}
		else
		{
			dRandom = cRandom.vSetRange(MINIMAL_XM_VALUE, pc_problem->dGetMaxValueAt(*pcSolution, i)).dGenerateNumber();
			pcSolution->pdGetPdSolution()->bSet(dRandom, i);
		}
	}
	//moze zrobic metode randomize values with problem i w niej zrobic ze kazda wartosc w matrixie jest z przedzialu wartosci odpowiadajacej
	//minmax matrix [i][j]
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
		 
		 pc_problem->bGetQuality(*pc_current_solution, dCurrentProfit);
		 if (dCurrentProfit > dBestProfit)
		 {	
			 delete pc_best_solution;
			 dBestProfit = dCurrentProfit;
			 pc_best_solution = pc_current_solution;
		 }
		//i warunek na sprawdzenie ktore jest lepsze
	}
	return pc_best_solution;
}