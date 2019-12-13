#include <iostream>
#include "CMscnProblem.h"
#include <random>

int main()
{
	int iSuppliers = 2;
	int iFactories = 3;
	int iWarehouses = 2;
	int iSellers = 3;
	int iSize = iSuppliers * iFactories + iFactories * iWarehouses + iWarehouses * iSellers;
	bool bsucc = true;
	double** deliveryMatrix = new double*[iSuppliers];
	double** factoryMatrix = new double*[iFactories];
	double** warehouseMatrix = new double*[iWarehouses];
	double* pdSolution = new double[iSize];

	for (int i = 0; i < iSize; i++) pdSolution[i] = i;

	CMscnProblem problem = CMscnProblem();
	
	//                                          initialize
	/*for (int i = 0; i < iSuppliers; i++)
	{
		
		for (int j = 0; j < iFactories; j++)
		{
			deliveryMatrix[i] = new double[iFactories];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)


	for (int i = 0; i < iFactories; i++)
	{

		for (int j = 0; j < iWarehouses; j++)
		{
			factoryMatrix[i] = new double[iWarehouses];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < iWarehouses; i++)
	{

		for (int j = 0; j < iSellers; j++)
		{
			warehouseMatrix[i] = new double[iSellers];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)



	//										Fill
	int iCurrent = 0;
	int LastIdx = 0;


	for (int i = 0; i < iSuppliers; i++)
	{

		for (int j = 0; j < iFactories; j++)
		{	
			iCurrent = i * iFactories + j;
			deliveryMatrix[i][j] = pdSolution[LastIdx + iCurrent];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < iFactories; i++)
	{

		for (int j = 0; j < iWarehouses; j++)
		{
			iCurrent = i * iWarehouses + j;
			factoryMatrix[i][j] = pdSolution[LastIdx + iCurrent];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < iWarehouses; i++)
	{

		for (int j = 0; j < iSellers; j++)
		{
			iCurrent = i * iSellers + j;
			warehouseMatrix[i][j] = pdSolution[LastIdx + iCurrent];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)


	//              print

	 iCurrent = 0;
	 LastIdx = 0;


	for (int i = 0; i < iSuppliers; i++)
	{

		for (int j = 0; j < iFactories; j++)
		{
			std::cout << deliveryMatrix[i][j] << " ";
		}//for (int j = 0; j < i_factories_count; j++)
		std::cout << std::endl;
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < iFactories; i++)
	{

		for (int j = 0; j < iWarehouses; j++)
		{
			std::cout << factoryMatrix[i][j] << " ";
		}//for (int j = 0; j < i_factories_count; j++)
		std::cout << std::endl;

	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < iWarehouses; i++)
	{

		for (int j = 0; j < iSellers; j++)
		{
			std::cout << warehouseMatrix[i][j] << " ";
		}//for (int j = 0; j < i_factories_count; j++)
		std::cout << std::endl;

	}//for (int i = 0; i < i_suppliers_count; i++)*/
	




	return 0;
}
