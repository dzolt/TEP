#include "CDiffEvol.h"

CDiffEvol::CDiffEvol(int iPopulationSize)
{	
	i_population_size = iPopulationSize;
	d_cross_probability = CROSS_PROBABILIY;
	d_diff_weight = DIFF_WEIGHT;
}

CDiffEvol::~CDiffEvol()
{
	for (int i = 0; i < pv_population.size(); i++)
	{
		delete pv_population.at(i);
	}
	pv_population.clear();

}

bool CDiffEvol::bInitialize(CProblem& pcProblem)
{
	pc_problem = &pcProblem;
	if (!bInitPopulation())
	{
		std::cout << "WARINING! POPULATION INITIALIZATION TIMEOUT!\n" << std::endl;
		return false;
	}
	else
	{
		std::cout << "POPULATION INITLIALIZED!\n" << std::endl;
	}
	return true;
}

void CDiffEvol::vSetConstants(double dCrossProb, double dDiffWeight)
{
	d_cross_probability = dCrossProb;
	d_diff_weight = dDiffWeight;
}

bool CDiffEvol::bInitPopulation()
{
	CRandomSearch cRandomSearch;
	int iIterator = 0;
	CTimer time;
	time.vStart();
	for (int i = 0; i < i_population_size; i++)
	{
		//iIterator++;
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

		if (time.dCurrentTime() >= TIMEOUT_EXEC) return false;
	}
	time.vStop();
	c_random.vSetRange(0, pv_population.size());
	return true;
}

CSolution* CDiffEvol::pcGetRandomInd()
{
	int index = (int)c_random.dGenerateNumber();
	return pv_population.at(index);
}

bool CDiffEvol::bRunAlgorithm()
{	
	if (pc_problem == NULL)
	{
		std::cout << "ALGORITHM UNITIALIZED CANNOT PROCEED!" << std::endl;
		return false;
	}
	CSolution* ind;
	CSolution* baseInd;
	CSolution* addInd0;
	CSolution* addInd1;
	CSolution* indNew;
	double dValue;
	double dTempQuality;
	CTimer time;

	time.vStart();
	while(time.dCurrentTime() < GENOTYPE_CORRECTION_TIMEOUT)
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
				for (int geneOffset = 0; geneOffset < ind->iGetSize(); geneOffset++)
				{
					if (dGetRandomReal(0, 1) < CROSS_PROBABILIY)
					{
						dValue = baseInd->pdGetPdSolution()->dGet(geneOffset) + DIFF_WEIGHT * (addInd0->pdGetPdSolution()->dGet(geneOffset) - addInd1->pdGetPdSolution()->dGet(geneOffset));
						
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
				indNew->vFillMatrixes();
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
	time.vStop();
	return true;
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

CSolution* CDiffEvol::pcGetBestSolution()
{
	int index = 0;
	double dBestValue = 0;
	double dCurrentValue = 0;
	for (int i = 0; i < pv_population.size(); i++)
	{
		pc_problem->bGetQuality(*pv_population.at(i), dCurrentValue);
		if (dCurrentValue > dBestValue)
		{
			dBestValue = dCurrentValue;
			index = i;
		}
	}
	return pv_population.at(index);
}