#include <iostream>
#include "CMscnProblem.h"
#include <random>

int main()
{
	int iSuppliers = 2;
	int iFactories = 2;
	int iWarehouses = 5;
	int iSellers = 2;
	bool success = true;
	CMscnProblem cNewProblem(iSuppliers, iFactories, iWarehouses, iSellers, success);
	

	int iSize = iSuppliers * iFactories + iFactories * iWarehouses + iWarehouses * iSellers;
	double* pdSolution = new double[iSize];
	
	
	for (int i = 0; i < iSize; i++)
	{	
		double random = ((double)rand() / (double)RAND_MAX);
		pdSolution[i] = random;
	}

	for (int i = 0; i < iSize; i++)
	{
		std::cout << pdSolution[i] << " ";
		if (i % 10 == 0) std::cout << std::endl;
	}
	

	return 0;
}
