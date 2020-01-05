#include <iostream>
#include "CMscnProblem.h"
#include "CRandom.h"
#include <random>

void vTest()
{
	/*int iSuppliers = 2;
	int iFactories = 3;
	int iWarehouses = 3;
	int iSellers = 2;
	int iSize = iSuppliers * iFactories + iFactories * iWarehouses + iWarehouses * iSellers;
	bool bsucc = true;
	double* pdSolution = new double[iSize];

	for (int i = 0; i < iSuppliers*iFactories; i++) pdSolution[i] = 3;
	for (int i = iSuppliers * iFactories; i < iSuppliers*iFactories + iFactories * iWarehouses; i++) pdSolution[i] = 2;
	for (int i = iSuppliers * iFactories + iFactories * iWarehouses; i < iSize; i++) pdSolution[i] = 2;

	CMscnProblem problem(iSuppliers,iFactories, iWarehouses,iSellers,bsucc);
	
	if (bsucc == true)
	{
		double result = 0;

		problem.bSetSupplierCapacityAmmount(1000, 0);
		problem.bSetSupplierCapacityAmmount(1000, 1);
		problem.bSetFactoryCapacityAmmount(1000, 0);
		problem.bSetFactoryCapacityAmmount(1000, 1);
		problem.bSetFactoryCapacityAmmount(1000, 2);
		problem.bSetWarehouseCapacityAmmount(1000, 0);
		problem.bSetWarehouseCapacityAmmount(1000, 1);
		problem.bSetWarehouseCapacityAmmount(1000, 2);
		problem.bSetSellerCapacityAmmount(1000, 0);
		problem.bSetSellerCapacityAmmount(1000, 1);
		problem.vSetEveryMaximalCostAtCapacity();


		for (int i = 0; i < iSuppliers; i++) problem.bSetSupplierContractPriceAt(300 + i, i);
		for (int i = 0; i < iFactories; i++) problem.bSetFactoryContractPriceAt(200 + i, i);
		for (int i = 0; i < iWarehouses; i++) problem.bSetWarehouseContractPriceAt(100 + i, i);
		for (int i = 0; i < iSellers; i++) problem.bSetSellerIncomeValAt(100 + 100 * i, i);

		for (int i = 0; i < iSuppliers; i++)
		{
			for (int j = 0; j < iFactories; j++)
			{
				problem.bSetDeliveryMatrixValAt(2, i, j);
			}
		}
		for (int i = 0; i < iFactories; i++)
		{
			for (int j = 0; j < iWarehouses; j++)
			{
				problem.bSetFactoryMatrixValAt(3, i, j);
			}
		}
		for (int i = 0; i < iWarehouses; i++)
		{
			for (int j = 0; j < iSellers; j++)
			{
				problem.bSetWarehouseMatrixValAt(4, i, j);
			}
		}
		problem.bGetQuality(pdSolution, iSize, result);
		std::cout << result << std::endl;
		std::cout << "Satisfied: " << problem.bConstraintsSatisfied(pdSolution, iSize);
		problem.bWriteProblemToFile("Problem.txt");
		problem.bWriteSolutionToFile("Solution.txt", pdSolution);
	}
	else 
	{ 
		std::cout << "error"; 
	}
	*/
}

int main()
{
	int iSuppliers = 2;
	int iFactories = 3;
	int iWarehouses = 3;
	int iSellers = 2;
	bool bsucc = true;

	CMscnProblem problem;
	CSolution* pcSolution;
	
	double result = 0;
	pcSolution = new CSolution();
	pcSolution->bReadSolutionFromFile("Solution.txt");
		
	problem.bReadProblemFromFile("Problem.txt");
	problem.vSetSolution(pcSolution);

	problem.bGetQuality(*pcSolution, result);
	std::cout << "bGetQuality = " << result << std::endl;
	std::cout << "bConstraintsSatisfied: " << std::boolalpha << problem.bConstraintsSatisfied(*pcSolution);
	//delete pcSolution;
	//problem.bWriteProblemToFile("Problem.txt");
	
	//vTest();
	CRandom random;
	std::cout << "\n";
	for (int i = 0; i < 20; i++) {
		std::cout << random.dGenerateNumber() << " ";
	}
	random.vSetRange(-5.0, 30.0);
	for (int i = 0; i < 30; i++) {
		std::cout << random.dGenerateNumber() << " ";
	}
	return 0;
}
