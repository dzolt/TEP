#pragma once
#include "CSolution.h"


class CProblem
{
public: 
	virtual bool bConstraintsSatisfied(CSolution& pcSolution) = 0;
	virtual bool bGetQuality(CSolution& pcSolution, double& profit) = 0;
	virtual void vGenerateInstance(int iSeed) = 0;

	virtual bool bWriteProblemToFile(std::string sFileName) = 0;
	virtual bool bReadProblemFromFile(std::string sFileName) = 0;

	virtual double dGetMinValueAt(int iIndex) = 0;
	virtual double dGetMaxValueAt(int iIndex) = 0;

	virtual int iGetSuppliersCount() = 0;
	virtual int iGetFactoriesCount() = 0;
	virtual int iGetWarehousesCount() = 0;
	virtual int iGetSellersCount() = 0;
};