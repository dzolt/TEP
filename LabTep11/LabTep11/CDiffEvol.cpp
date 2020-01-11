#include "CDiffEvol.h"

CDiffEvol::CDiffEvol(CMscnProblem& pcProblem, int iPopulationSize)
{
	pc_problem = &pcProblem;
	if (bInitPopulation(iPopulationSize) == false)
	{
		std::cout << "Population TIMEOUT" << std::endl;
	}
}

CDiffEvol::~CDiffEvol()
{
	for (int i = 0; i < pv_population.size(); i++)
	{
		delete pv_population.at(i);
	}
	pv_population.clear();

}

bool CDiffEvol::bInitPopulation(int iPopulationSize)
{
	CRandomSearch cRandomSearch;
	int iIterator = 0;

	for (int i = 0; i < iPopulationSize; i++)
	{
		iIterator++;
		CSolution* pcSolution;
		pcSolution = cRandomSearch.pcGetValidSolution(*pc_problem);
		if (pcSolution != NULL)
		{
			pv_population.push_back(pcSolution);
		}
		else
		{
			delete pcSolution;
			i--;
		}

		if (iIterator == TIMEOUT_EXEC) return false;
	}
	c_random.vSetRange(0, pv_population.size());
	return true;
}

CSolution* CDiffEvol::pcGetRandomInd()
{
	int index = (int)c_random.dGenerateNumber();
	return pv_population.at(index);
}

void CDiffEvol::vCorrectGenotype()
{
	CSolution* ind;
	CSolution* baseInd;
	CSolution* addInd0;
	CSolution* addInd1;
	CSolution* indNew;
	double dValue;
	double dTempQuality;
	for (int j = 0; j < GENOTYPE_CORRECTION_TRIES; j++)
	{
		for (int i = 0; i < pv_population.size(); i++)
		{
			ind = pv_population.at(i);
			baseInd = pcGetRandomInd();
			addInd0 = pcGetRandomInd();
			addInd1 = pcGetRandomInd();
			if (bIndividualsAreDifferent(ind, baseInd, addInd0, addInd1))
			{
				indNew = new CSolution();
				indNew->vCopySizes(*ind);
				for (int geneOffset = 0; geneOffset < ind->iGetSize(); i++)
				{
					if (dGetRandomReal(0, 1) < CROSS_PROBABILIY)
					{
						dValue = baseInd->pdGetPdSolution()->dGet(geneOffset) +
							DIFF_WEIGHT * (addInd0->pdGetPdSolution()->dGet(geneOffset) - addInd1->pdGetPdSolution()->dGet(geneOffset));
						if (dValue < pc_problem->dGetMinValueAt(geneOffset))
						{
							dValue = pc_problem->dGetMinValueAt(geneOffset);
						}
						else if (dValue > pc_problem->dGetMaxValueAt(geneOffset))
						{
							dValue = pc_problem->dGetMaxValueAt(geneOffset);
						}
						indNew->pdGetPdSolution()->bSet(dValue, geneOffset);
					}
					else
					{
						indNew->pdGetPdSolution()->bSet(ind->pdGetPdSolution()->dGet(geneOffset), geneOffset);
					}
				}
				pc_problem->bGetQuality(*indNew, dTempQuality);
				pc_problem->bGetQuality(*ind, dValue);
				if (dTempQuality >= dValue && pc_problem->bConstraintsSatisfied(*indNew))
				{
					delete ind;
					pv_population.erase(pv_population.begin() + i);
					pv_population.insert(pv_population.begin() + i, indNew);
				}
				else
				{
					delete indNew;
				}
			}
		}
	}
}

double CDiffEvol::dGetRandomReal(double dFrom, double dTo)
{
	CRandom cRandom;
	return cRandom.vSetRange(dFrom, dTo).dGenerateNumber();
}

bool CDiffEvol::bIndividualsAreDifferent(CSolution* pcInd, CSolution* pcBaseInd, CSolution* pcAddInd0, CSolution* pcAddInd1)
{
	if (pcInd == pcBaseInd || pcInd == pcAddInd0 || pcInd == pcAddInd1 || pcBaseInd == pcAddInd0 || pcBaseInd == pcAddInd1 || pcAddInd0 == pcAddInd1 ||
		pcInd->bIsIdentical(*pcBaseInd) == true || pcInd->bIsIdentical(*pcAddInd0) == true || pcInd->bIsIdentical(*pcAddInd1) == true ||
		pcBaseInd->bIsIdentical(*pcAddInd0) == true || pcBaseInd->bIsIdentical(*pcAddInd1) == true || pcAddInd0->bIsIdentical(*pcAddInd1) == true)
		return false;

	return true;
}


CSolution* CDiffEvol::pcGetBestSolutionFromPopulation(CMscnProblem& pcProblem)
{
	CSolution* pcBestSolution = pv_population.at(0);
	double dBestValue = 0;
	pcProblem.bGetQuality(*pcBestSolution, dBestValue);
	double dCurrentValue;
	for (int i = 0; i < pv_population.size(); i++)
	{
		pcProblem.bGetQuality(*pv_population.at(i), dCurrentValue);
		if (dCurrentValue > dBestValue)
		{
			dBestValue = dCurrentValue;
			pcBestSolution = pv_population.at(i);
		}
	}
	return pcBestSolution;
}