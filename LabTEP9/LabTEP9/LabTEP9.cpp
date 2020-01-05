#include <iostream>
#include "CMscnProblem.h"
#include "CRandom.h"
#include <random>


int main()
{
	bool bSuccess = true;
	CMscnProblem problem(3,1,4,1,bSuccess);
	if (bSuccess == true) {
		CSolution* pcSolution;
		CRandom random;
		double result = 0;
		pcSolution = new CSolution();
		pcSolution->bReadSolutionFromFile("Solution.txt");
		//problem.bReadProblemFromFile("Problem.txt");
		problem.vGenerateInstance(random);
		problem.vSetSolution(pcSolution);

		problem.bGetQuality(*pcSolution, result);
		std::cout << "bGetQuality = " << result << std::endl;
		std::cout << "bConstraintsSatisfied: " << std::boolalpha << problem.bConstraintsSatisfied(*pcSolution);
		problem.bWriteProblemToFile("Problem.txt");
	}
	else std::cout << "ERRORR";
	return 0;
}
