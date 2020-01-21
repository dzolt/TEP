#include <iostream>
#include "CRandom.h"
#include "CDiffEvol.h"
#include "CMscnProblem.h"
#include "CRandomSearch.h"

void vTestRandomSearch()
{
	bool bSuccess = true;
	CProblem* pc_problem = new CMscnProblem(3, 2, 4, 2, bSuccess);
	if (bSuccess == true) {
		CSolution* pcSolution;
		double result = 0;

		pc_problem->vGenerateInstance(200);

		COptimizer* pc_optimizer = new CRandomSearch();
		pc_optimizer->bInitialize(*pc_problem);
		pc_optimizer->bRunAlgorithm();

		pcSolution = pc_optimizer->pcGetBestSolution();

		pc_problem->bGetQuality(*pcSolution, result);
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << pc_problem->bConstraintsSatisfied(*pcSolution);
		delete pc_optimizer;
	}
	else std::cout << "ERROR";
	delete pc_problem;
}

void vDiffTest()
{
	bool bSuccess = true;
	CProblem* pc_problem = new CMscnProblem(3, 2, 4, 2, bSuccess);
	if (bSuccess == true)
	{	
		CDiffEvol diffEvol(10);
		CSolution* pcSolution;
		double result = 0;
		pc_problem->vGenerateInstance(200);

		COptimizer* pc_optimizer = &diffEvol;
		pc_optimizer->bInitialize(*pc_problem);
		pcSolution = pc_optimizer->pcGetBestSolution();
		pc_problem->bGetQuality(*pcSolution, result);
		std::cout << "BEFORE OPTIMALIZATION: \n" << std::endl;
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << pc_problem->bConstraintsSatisfied(*pcSolution);
		std::cout << "\n\n\n";
		diffEvol.vPrintPopulation(*pc_problem);
		pc_optimizer->bRunAlgorithm();
		pcSolution = pc_optimizer->pcGetBestSolution();
		pc_problem->bGetQuality(*pcSolution, result);
		std::cout << "AFTER OPTIMALIZATION: \n" << std::endl;
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << pc_problem->bConstraintsSatisfied(*pcSolution);
		std::cout << "\n\n\n";
		diffEvol.vPrintPopulation(*pc_problem);

	}
	else std::cout << "ERROR";
	delete pc_problem;
}

int main()
{
	//vTestRandomSearch();
	vDiffTest();
	return 0;
}
