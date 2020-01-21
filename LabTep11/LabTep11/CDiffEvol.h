#pragma once
#include "Constants.h"
#include "CRandomSearch.h"
#include "COptimizer.h"
class CDiffEvol : public COptimizer
{
public:
	CDiffEvol(int iPopulationSize);
	~CDiffEvol();
	bool bInitialize(CProblem& pcProblem);

	void vSetConstants(double dCrossProb, double dDiffWeight);
	void vSetPopulationSize(int iPopulationSize) { i_population_size = iPopulationSize; };

	void vPrintPopulation(CProblem& pcProblem)
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
	CSolution* pcGetBestSolution();
private:
	bool bInitPopulation();
	double dGetRandomReal(double dFrom, double dTo);
	bool bIndividualsAreDifferent(CSolution* pcInd, CSolution* pcBaseInd, CSolution* pcAddInd0, CSolution* pcAddInd1);
	CSolution* pcGetRandomInd();
	bool bRunAlgorithm();

	std::vector<CSolution*> pv_population;
	//CProblem* pc_problem;
	CRandom c_random;

	int i_population_size;
	double d_cross_probability;
	double d_diff_weight;
};