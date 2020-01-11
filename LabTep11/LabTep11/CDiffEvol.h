#pragma once
#include "Constants.h"
#include "CRandomSearch.h"
class CDiffEvol
{
public:
	CDiffEvol(CMscnProblem& pcProblem, int iPopulationSize);
	~CDiffEvol();
	CSolution* pcGetBestSolutionFromPopulation(CMscnProblem& pcProblem);

	void vPrintPopulation(CMscnProblem& pcProblem)
	{
		double result;
		for (int i = 0; i < pv_population.size(); i++)
		{
			std::cout << "Genotype: " << i << std::endl;
			pcProblem.bGetQuality(*pv_population.at(i), result);
			std::cout << "Quality: " << result << std::endl;
			pcProblem.bConstraintsSatisfied(*pv_population.at(i));
			std::cout << "Constraints satisfied: " << std::boolalpha << pcProblem.bConstraintsSatisfied(*pv_population.at(i)) << std::endl;
		}
	}
private:
	bool bInitPopulation(int iPopulationSize);
	double dGetRandomReal(double dFrom, double dTo);
	bool bIndividualsAreDifferent(CSolution* pcInd, CSolution* pcBaseInd, CSolution* pcAddInd0, CSolution* pcAddInd1);
	CSolution* pcGetRandomInd();
	void vCorrectGenotype();
	std::vector<CSolution*> pv_population;
	CMscnProblem* pc_problem;

	CRandom c_random;
};