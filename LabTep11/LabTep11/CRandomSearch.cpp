#include "CRandomSearch.h"

CRandomSearch::CRandomSearch()
{
	pc_current_solution = NULL;
	pc_best_solution = NULL;
}

CRandomSearch::~CRandomSearch()
{
}

CSolution* CRandomSearch::pcGenerateSolution(CMscnProblem& cProblem)
{
	CRandom cRandom;
	CSolution* pcSolution;
	pcSolution = new CSolution(cProblem.iGetSuppliersCount(), cProblem.iGetFactoriesCount(), cProblem.iGetWarehousesCount(), cProblem.iGetSellersCount());
	double dRandom = 0;
	for (int i = 0; i < pcSolution->iGetSize(); i++)
	{
		dRandom = cRandom.vSetRange(cProblem.dGetMinValueAt(i), cProblem.dGetMaxValueAt(i)).dGenerateNumber();
		pcSolution->pdGetPdSolution()->bSet(dRandom, i);
	}

	pcSolution->vFillMatrixes();
	return pcSolution;
}

CSolution* CRandomSearch::pcGetValidSolution(CMscnProblem& cProblem)
{
	CSolution* pcValidSolution;
	for (int i = 0; i < TIMES_TO_VALIDATE_SOLUTION; i++)
	{
		pcValidSolution = pcGenerateSolution(cProblem);
		if (cProblem.bConstraintsSatisfied(*pcValidSolution))
		{
			return pcValidSolution;
		}
		delete pcValidSolution;
	}
	return NULL;
}

CSolution* CRandomSearch::pcGetBestSolution(CMscnProblem& cProblem)
{
	int dupa = 0;
	double dCurrentProfit = 0;
	double dBestProfit = 0;
	pc_best_solution = new CSolution(cProblem.iGetSuppliersCount(), cProblem.iGetFactoriesCount(), cProblem.iGetWarehousesCount(), cProblem.iGetSellersCount());

	for (int i = 0; i < TIMES_TO_RUN_ALGORITHM; i++)
	{
		pc_current_solution = pcGenerateSolution(cProblem);
		// bGetSolutionQualityToFile("SolutionsQuality.txt", dCurrentProfit);
		if (cProblem.bConstraintsSatisfied(*pc_current_solution) == true)
		{
			cProblem.bGetQuality(*pc_current_solution, dCurrentProfit);
			if (dCurrentProfit > dBestProfit)
			{
				dupa++;
				delete pc_best_solution;
				dBestProfit = dCurrentProfit;
				pc_best_solution = pc_current_solution;
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
	std::cout << "Ilosc rozwiazan dobrych: " << dupa << std::endl;
	return pc_best_solution;
}
/*
bool CRandomSearch::bGetSolutionQualityToFile(std::string sFileName, double dProfit)
{
	FILE* pfFile;
	pfFile = fopen(sFileName.c_str(), "a");
	if (pfFile == NULL) return false;
	fprintf(pfFile, "\nxd\n");
	for (int i = 0; i < pc_current_solution->pmGetXdMatrix()->iGetSizeX(); i++)
	{
		for (int j = 0; j < pc_current_solution->pmGetXdMatrix()->iGetSizeY(); j++)
		{
			double dMinRange = pc_problem->pmGetMinItemsSupplierMatrix()->dGet(i, j);
			double dMaxRange = pc_problem->pmGetMaxItemsSupplierMatrix()->dGet(i, j);
			double percantage = dCalculateRangePercentage(pc_current_solution->pmGetXdMatrix()->dGet(i, j), dMinRange, dMaxRange);
			fprintf(pfFile, "%lf%% ", percantage);
		}
		fprintf(pfFile, "\n");
	}

	fprintf(pfFile, "\nxf\n");
	for (int i = 0; i < pc_current_solution->pmGetXfMatrix()->iGetSizeX(); i++)
	{
		for (int j = 0; j < pc_current_solution->pmGetXfMatrix()->iGetSizeY(); j++)
		{
			double dMinRange = pc_problem->pmGetMinItemsFactoryMatrix()->dGet(i, j);
			double dMaxRange = pc_problem->pmGetMaxItemsFactoryMatrix()->dGet(i, j);
			double percantage = dCalculateRangePercentage(pc_current_solution->pmGetXfMatrix()->dGet(i, j), dMinRange, dMaxRange);
			fprintf(pfFile, "%lf%% ", percantage);
		}
		fprintf(pfFile, "\n");
	}

	fprintf(pfFile, "\nxm\n");
	for (int i = 0; i < pc_current_solution->pmGetXmMatrix()->iGetSizeX(); i++)
	{
		for (int j = 0; j < pc_current_solution->pmGetXmMatrix()->iGetSizeY(); j++)
		{
			double dMinRange = pc_problem->pmGetMinItemsWarehouseMatrix()->dGet(i, j);
			double dMaxRange = pc_problem->pmGetMaxItemsWarehouseMatrix()->dGet(i, j);
			double percantage = dCalculateRangePercentage(pc_current_solution->pmGetXmMatrix()->dGet(i, j), dMinRange, dMaxRange);
			fprintf(pfFile, "%lf%% ", percantage);
		}
		fprintf(pfFile, "\n");
	}
	fprintf(pfFile, "\nprofit: ");
	fprintf(pfFile, "%lf", dProfit);
	return true;
}

double CRandomSearch::dCalculateRangePercentage(double dValue, double dMinRange, double dMaxRange)
{
	double range = dMaxRange - dMinRange;
	return ((dValue - dMinRange) / range) * 100;
}*/