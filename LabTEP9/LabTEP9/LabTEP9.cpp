#include <iostream>
#include "CRandom.h"
#include "CRandomSearch.h"

void vTestRandomSearch()
{
	bool bSuccess = true;
	CMscnProblem* problem;
	problem = new CMscnProblem(3, 1, 4, 1, bSuccess);
	if (bSuccess == true) {
		CRandom random;
		double result = 0;
		//problem->vGenerateInstance(200);
		problem->bReadProblemFromFile("Problem.txt");

		CRandomSearch cRandomSearch(problem);
		problem->vSetSolution(cRandomSearch.pcGetBestSolution());//retruns best solution from 100 attempts
		
		problem->pcGetSolution()->bWriteSolutionToFile("Solution.txt");
		problem->bGetQuality(result);
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << problem->bConstraintsSatisfied(*problem->pcGetSolution());
		problem->bWriteProblemToFile("Problem.txt");
	
	}
	else std::cout << "ERROR";
	
}

int main()
{
	/*bool bSuccess = true;
	CMscnProblem problem(3, 1, 4, 1, bSuccess);
	if (bSuccess == true) {
		CSolution* pcSolution;
		CRandom random;
		CRandomSearch cRandomSearch(problem);
		double result = 0;
		pcSolution = new CSolution();
		pcSolution->bReadSolutionFromFile("Solution.txt");
		problem.bReadProblemFromFile("Problem.txt");
		problem.vGenerateInstance(random);
		problem.vSetSolution(pcSolution);

		problem.bGetQuality(*pcSolution, result);
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << problem.bConstraintsSatisfied(*pcSolution);
		problem.bWriteProblemToFile("Problem.txt");
	}
	else std::cout << "ERROR";*/

	vTestRandomSearch();
	return 0;
}
