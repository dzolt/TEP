#include <iostream>
#include "CRandom.h"
#include "CRandomSearch.h"
#include "CDiffEvol.h"

void vTestRandomSearch()
{
	bool bSuccess = true;
	CMscnProblem problem(3, 2, 4, 2, bSuccess);
	if (bSuccess == true) {
		CSolution* pcSolution;
		double result = 0;
		problem.vGenerateInstance(200);
		//problem->bReadProblemFromFile("Problem.txt");

		CRandomSearch cRandomSearch;
		pcSolution = cRandomSearch.pcGetBestSolution(problem);

		problem.bGetQuality(*pcSolution, result);
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << problem.bConstraintsSatisfied(*pcSolution);
		problem.bWriteProblemToFile("Problem.txt");

	}
	else std::cout << "ERROR";

}

void vDiffTest()
{
	bool bSuccess = true;
	CMscnProblem problem(3, 2, 4, 2, bSuccess);
	if (bSuccess == true)
	{
		double result = 0;
		problem.vGenerateInstance(200);
		CDiffEvol evolutionProblem(problem, 20);
		CSolution* pcSolution;
		pcSolution = evolutionProblem.pcGetBestSolutionFromPopulation(problem);
		problem.bGetQuality(*pcSolution, result);
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << problem.bConstraintsSatisfied(*pcSolution);
		std::cout << "\n\n\n";
		evolutionProblem.vPrintPopulation(problem);
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

	//vTestRandomSearch();
	vDiffTest();
	return 0;
}
