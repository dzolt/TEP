#include "CMscnProblem.h"
#include <iostream>

CMscnProblem::CMscnProblem()
{
	i_suppliers_count = DEFAULT_TAB_LENGTH;
	i_factories_count = DEFAULT_TAB_LENGTH;
	i_warehouses_count = DEFAULT_TAB_LENGTH;
	i_sellers_count = DEFAULT_TAB_LENGTH;
	pf_file = NULL;
	bInitTables();
	bInitMatrixes();
	bInitMinMaxMatrixes();
}//CMscnProblem::CMscnProblem()

CMscnProblem::CMscnProblem(unsigned int iSuppliersCount, unsigned int iFactoriesCount, unsigned int iWarehousesCount, unsigned int iSellersCount, bool& bSuccess)
{
	if (iSuppliersCount < 1 || iFactoriesCount < 1 || iSellersCount < 1 || iWarehousesCount < 1)
	{
		bSuccess = false;
		CMscnProblem();
	}//if (iSuppliersCount < 1 || iFactoriesCount < 1 || iSellersCount < 1 || iWarehousesCount < 1)
	else
	{
		i_suppliers_count = iSuppliersCount;
		i_factories_count = iFactoriesCount;
		i_sellers_count = iSellersCount;
		i_warehouses_count = iWarehousesCount;
		pf_file = NULL;
		if( bInitTables() == true && bInitMatrixes() == true && bInitMinMaxMatrixes()) bSuccess = true;
		else bSuccess = false;
	}//else if (iSuppliersCount < 1 || iFactoriesCount < 1 || iSellersCount < 1 || iWarehousesCount < 1)
}//CMscnProblem::CMscnProblem(unsigned int iSuppliersCount, unsigned int iFactoriesCount, unsigned int iSellersCount, unsigned int iWarehousesCount, bool bSuccess)

CMscnProblem::~CMscnProblem()
{
	delete ct_suppliers_contract_prices;
	delete ct_factories_contract_prices;
	delete ct_warehouses_contract_prices;

	delete ct_sellers_income_value;

	delete ct_suppliers_capacity_ammount;
	delete ct_factories_capacity_ammount;
	delete ct_warehouses_capacity_ammount;
	delete ct_sellers_capacity_ammount;

	delete cm_min_items_sent_from_supplier;
	delete cm_max_items_sent_from_supplier;

	delete cm_min_items_sent_from_factory;
	delete cm_max_items_sent_from_factory;

	delete cm_min_items_sent_from_warehouse;
	delete cm_max_items_sent_from_warehouse;

	delete cm_delivery_matrix;
	delete cm_factory_matrix;
	delete cm_warehouse_matrix;

	delete pf_file;
}//CMscnProblem::~CMscnProblem()

bool CMscnProblem::bInitTables()
{	
	bool bSuccess = true;
	ct_suppliers_contract_prices =	new CTable(i_suppliers_count, bSuccess);
	ct_warehouses_contract_prices = new CTable(i_warehouses_count, bSuccess);
	ct_factories_contract_prices = new CTable(i_factories_count, bSuccess);

	ct_sellers_income_value = new CTable(i_sellers_count, bSuccess);
	
	ct_suppliers_capacity_ammount = new CTable(i_suppliers_count, bSuccess);
	ct_warehouses_capacity_ammount = new CTable(i_warehouses_count, bSuccess);
	ct_factories_capacity_ammount = new CTable(i_warehouses_count, bSuccess);
	ct_sellers_capacity_ammount = new CTable(i_sellers_count, bSuccess);
	if (bSuccess == false) return false;
	return true;
}//void CMscnProblem::vInitTables()

bool CMscnProblem::bInitMatrixes()
{	
	bool bSuccess = true;

	cm_delivery_matrix = new CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	cm_min_items_sent_from_supplier = new CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	cm_max_items_sent_from_supplier = new CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	
	cm_factory_matrix =  new CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	cm_min_items_sent_from_factory = new CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	cm_max_items_sent_from_factory = new CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	
	cm_warehouse_matrix = new CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	cm_min_items_sent_from_warehouse = new CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	cm_max_items_sent_from_warehouse = new CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	if (bSuccess == true) return true;
	return false;
}//void CMscnProblem::vInitMatrixes()

bool CMscnProblem::bInitMinMaxMatrixes()
{	
	if (
		bSetEveryMinimalCostTo(&cm_min_items_sent_from_supplier, i_suppliers_count, i_factories_count, 0) == false
		|| bSetEveryMinimalCostTo(&cm_min_items_sent_from_factory, i_factories_count, i_warehouses_count, 0) == false
		|| bSetEveryMinimalCostTo(&cm_min_items_sent_from_warehouse, i_warehouses_count, i_sellers_count, 0) == false
		)
		return false;
	else 
	{
		vSetEveryMaximalCostAtCapacity();
		return true;
	}
}//bool CMscnProblem::bInitMinMaxMatrixes()

bool CMscnProblem::bSetEveryMinimalCostTo(CMatrix** pdMatrix, int iSizeX, int iSizeY, double dValue)
{	
	if (iSizeX < 0 || iSizeY < 0 || dValue < 0) return false;
	for (int i = 0; i < iSizeX; i++)
	{
		for (int j = 0; j < iSizeY; j++)
		{
			(*pdMatrix)->bSet(dValue, i, j);
		}//for (int j = 0; j < iSizeY; j++)
	}//for (int i = 0; i < iSizeX; i++)
	return true;
}//bool CMscnProblem::bSetEveryMinimalCostAt(double*** pdMatrix, int iSizeX, int iSizeY, double dValue)

void CMscnProblem::vSetEveryMaximalCostAtCapacity()
{
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			cm_max_items_sent_from_supplier->bSet(ct_suppliers_capacity_ammount->dGet(i), i, j);
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			cm_max_items_sent_from_factory->bSet(ct_factories_capacity_ammount->dGet(i), i, j);
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			cm_max_items_sent_from_warehouse->bSet(ct_warehouses_capacity_ammount->dGet(i), i, j);
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
}//bool CMscnProblem::bSetEveryMaximalCostAtCapacity()

bool CMscnProblem::bSetSuppliersCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;
	
	i_suppliers_count = iNewCount;

	ct_suppliers_contract_prices->bSetSize(i_suppliers_count);
	ct_suppliers_capacity_ammount->bSetSize(i_suppliers_count);

	cm_delivery_matrix->bSetSize(i_suppliers_count, i_factories_count);
	cm_max_items_sent_from_supplier->bSetSize(i_suppliers_count, i_factories_count);
	cm_min_items_sent_from_supplier->bSetSize(i_suppliers_count, i_factories_count);
	return true;
}//void CMscnProblem::vSetSuppliersCount(unsigned int iNewValue)

bool CMscnProblem::bSetFactoriesCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_factories_count = iNewCount;
	
	ct_factories_contract_prices->bSetSize(i_factories_count);
	ct_factories_capacity_ammount->bSetSize(i_factories_count);

	cm_delivery_matrix->bSetSize(i_suppliers_count, i_factories_count);
	cm_min_items_sent_from_supplier->bSetSize(i_suppliers_count, i_factories_count);
	cm_max_items_sent_from_supplier->bSetSize(i_suppliers_count, i_factories_count);
	
	cm_factory_matrix->bSetSize(i_factories_count, i_warehouses_count);
	cm_min_items_sent_from_factory->bSetSize(i_factories_count, i_warehouses_count);
	cm_max_items_sent_from_factory->bSetSize(i_factories_count, i_warehouses_count);
	return true;
}//void CMscnProblem::vSetFactoriesCount(unsigned int iNewValue)

bool CMscnProblem::bSetSellersCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_sellers_count = iNewCount;
	
	ct_sellers_capacity_ammount->bSetSize(i_sellers_count);
	ct_sellers_income_value->bSetSize(i_sellers_count);

	cm_warehouse_matrix->bSetSize(i_warehouses_count, i_sellers_count);
	cm_min_items_sent_from_warehouse->bSetSize(i_warehouses_count, i_sellers_count);
	cm_max_items_sent_from_warehouse->bSetSize(i_warehouses_count, i_sellers_count);
	return true;
}//void CMscnProblem::vSetSellersCount(unsigned int iNewValue)

bool CMscnProblem::bSetWarehousesCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_warehouses_count = iNewCount;
	
	ct_warehouses_capacity_ammount->bSetSize(i_warehouses_count);
	ct_warehouses_contract_prices->bSetSize(i_warehouses_count);

	cm_warehouse_matrix->bSetSize(i_warehouses_count, i_sellers_count);
	cm_min_items_sent_from_warehouse->bSetSize(i_warehouses_count, i_sellers_count);
	cm_max_items_sent_from_warehouse->bSetSize(i_warehouses_count, i_sellers_count);
	
	cm_factory_matrix->bSetSize(i_factories_count, i_warehouses_count);
	cm_min_items_sent_from_factory->bSetSize(i_factories_count, i_warehouses_count);
	cm_max_items_sent_from_factory->bSetSize(i_factories_count, i_warehouses_count);
	return true;
}//void CMscnProblem::vSetWarehousesCount(unsigned int iNewValue)

bool CMscnProblem::bGetQuality(double* pdSolution, int iSize, double& profit)
{	

	//if (bConstraintsSatisfied(pdSolution, iSize) == false) return false;
	double shopIncome = 0;
	double totalDeliveryCost = 0;
	double totalContractPrice = 0;
	double totalProfit = 0;
	
	shopIncome = dCalculateTotalIncomeFromSellers(&pdSolution, iSize);
	totalDeliveryCost = dMultiplyDeliveryCostPerItemsOrdered(&pdSolution);
	totalContractPrice = dCalculateTotalContractPrice(&pdSolution);
	profit = shopIncome - totalDeliveryCost - totalContractPrice;
	
	return true;
}//double CMscnProblem::dGetQuality(double*** pdSolution)

double CMscnProblem::dCalculateTotalIncomeFromSellers(double** pdSolution, int iSize)
{	
	if (iSize < 0 || iSize > i_suppliers_count*i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count) return 0;
	
	double totalShopIncome = 0;
	int iBegginingIndexForWarehouseShop = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count;

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			totalShopIncome += (*pdSolution)[iBegginingIndexForWarehouseShop] * ct_sellers_income_value->dGet(j);
			iBegginingIndexForWarehouseShop++;
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return totalShopIncome;
}//double CMscnProblem::dCalculateTotalIncomeFromSellers(double** pdSolution, int iSize)

double CMscnProblem::dMultiplyDeliveryCostPerItemsOrdered(double** pdSolution)
{	
	int iStartingIndex = 0;
	int iStartingIndexOfFactoryWarehouseMatrix = i_suppliers_count * i_factories_count;
	int iStartingIndexOfWarehouseSellerMatrix = iStartingIndexOfFactoryWarehouseMatrix + i_factories_count * i_warehouses_count;
	double totalDeliveryCost = 0;

	if (
		cm_delivery_matrix->bGetWholeDeliveryCost(*pdSolution, iStartingIndex, totalDeliveryCost) == false
		|| cm_factory_matrix->bGetWholeDeliveryCost(*pdSolution, iStartingIndexOfFactoryWarehouseMatrix, totalDeliveryCost) == false
		|| cm_warehouse_matrix->bGetWholeDeliveryCost(*pdSolution, iStartingIndexOfWarehouseSellerMatrix, totalDeliveryCost) == false
		) return -1;
	return totalDeliveryCost;
}//bool CMscnProblem::bMultiplyDeliveryCostPerItemsOrdered(double** pdSolution)

double CMscnProblem::dCalculateTotalContractPrice(double** pdSolution)
{	
	double totalContractPrice = 0;
	int iCurrentIndex = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{	
			iCurrentIndex = i * i_factories_count + j;
			if ((*pdSolution)[LastIdx + iCurrentIndex] > 0)
			{
				totalContractPrice += ct_suppliers_contract_prices->dGet(i);
				break;
			}//if ((*pdSolution)[LastIdx + iCurrent] > 0)
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrentIndex + 1;
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrentIndex = i * i_warehouses_count + j;
			if ((*pdSolution)[LastIdx + iCurrentIndex] > 0)
			{
				totalContractPrice += ct_factories_contract_prices->dGet(i);
				break;
			}//if ((*pdSolution)[LastIdx + iCurrent] > 0)
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrentIndex + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrentIndex = i * i_sellers_count + j;
			if ((*pdSolution)[LastIdx + iCurrentIndex] > 0)
			{
				totalContractPrice += ct_warehouses_contract_prices->dGet(i);
				break;
			}//if ((*pdSolution)[LastIdx + iCurrent] > 0)
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return totalContractPrice;
}//double CMscnProblem::dCalculateTotalContractPrice()

bool CMscnProblem::bConstraintsSatisfied(double* pdSolution, int iSize)
{
	if (pdSolution == NULL || iSize < 0 || iSize > i_suppliers_count*i_factories_count + i_factories_count*i_warehouses_count + i_warehouses_count*i_sellers_count 
		|| bCheckMinMaxConstraint(pdSolution) == false || bCheckSolutionForNegativeNumbers(pdSolution, iSize) == false
		|| bCheckMaxCapacityOverload(pdSolution) == false || bCheckSufficientProductAmmountDelivery(pdSolution) == false) return false;
	return true;
}//bool CMscnProblem::bConstraintsSatisfied(double * pdSolution, int iSize)

bool CMscnProblem::bCheckMinMaxConstraint(double* pdSolution)
{	
	int iCurrentIndex = 0;
	int LastIdx = 0;

	int iStartingIndex = 0;
	int iStartingIndexOfFactoryWarehouseMatrix = i_suppliers_count * i_factories_count;
	int iStartingIndexOfWarehouseSellerMatrix = iStartingIndexOfFactoryWarehouseMatrix + i_factories_count * i_warehouses_count;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
				iCurrentIndex = i * i_factories_count + j;
			 if( (pdSolution)[LastIdx + iCurrentIndex] < cm_min_items_sent_from_supplier->dGet(i,j) || (pdSolution)[LastIdx + iCurrentIndex] > cm_max_items_sent_from_supplier->dGet(i, j) ) return false;
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)
	LastIdx += iCurrentIndex + 1;

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrentIndex = i * i_warehouses_count + j;
			if ((pdSolution)[LastIdx + iCurrentIndex] < cm_min_items_sent_from_factory->dGet(i, j) || (pdSolution)[LastIdx + iCurrentIndex] > cm_max_items_sent_from_factory->dGet(i, j)) return false;
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrentIndex + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrentIndex = i * i_sellers_count + j;
			if ((pdSolution)[LastIdx + iCurrentIndex] < cm_min_items_sent_from_warehouse->dGet(i, j) || (pdSolution)[LastIdx + iCurrentIndex] > cm_max_items_sent_from_warehouse->dGet(i, j)) return false;
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return true;
}//bool CMscnProblem::bCheckMinMaxConstraint(double * pdSolution)

bool CMscnProblem::bCheckSolutionForNegativeNumbers(double* pdSolution, int iSize)
{	
	if (pdSolution == NULL || iSize < 0 || iSize > i_suppliers_count*i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count ) return false;
	for (int i = 0; i < iSize; i++)
	{
		if (pdSolution[i] < 0) return false;
	}//for (int i = 0; i < iSize; i++)
	return true;
}//bool CMscnProblem::bCheckSolutionForNegativeNumbers(double * pdSolution)

bool CMscnProblem::bCheckMaxCapacityOverload(double * pdSolution)
{
	int iCurrentIndex = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{	
		double orderedAmmount = 0;
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrentIndex = i * i_factories_count + j;
			orderedAmmount += (pdSolution)[LastIdx + iCurrentIndex];
			if (orderedAmmount > ct_suppliers_capacity_ammount->dGet(i)) return false;
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)
	LastIdx += iCurrentIndex + 1;

	for (int i = 0; i < i_factories_count; i++)
	{	
		double orderedAmmount = 0;
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrentIndex = i * i_warehouses_count + j;
			orderedAmmount += (pdSolution)[LastIdx + iCurrentIndex];
			if (orderedAmmount > ct_factories_capacity_ammount->dGet(i)) return false;
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)
	
	LastIdx += iCurrentIndex + 1; 
	for (int i = 0; i < i_warehouses_count; i++)
	{
		double orderedAmmount = 0;
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrentIndex = i * i_sellers_count + j;
			orderedAmmount += (pdSolution)[LastIdx + iCurrentIndex];
			if (orderedAmmount > ct_warehouses_capacity_ammount->dGet(i)) return false;
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)

	//warunek na sumaryczna ilosc przedmiotow do danego sklepu
	for (int j = 0; j < i_sellers_count; j++)
	{	
		double orderedAmmount = 0;
		for (int i = 0; i < i_warehouses_count; i++)
		{
			orderedAmmount += pdSolution[LastIdx + i * i_sellers_count + j];
			if (orderedAmmount > ct_sellers_capacity_ammount->dGet(j)) return false;
		}//for (int i = 0; i < i_warehouses_count; i++)
	}//for (int j = 0; j < i_sellers_count; j++)
	return true;
}//bool CMscnProblem::bCheckMaxCapacityOverload(double * pdSolution)

bool CMscnProblem::bCheckSufficientProductAmmountDelivery(double* pdSolution)
{
	double quantityOfItemsGoingToTheEnitity;
	double quantityOfItemsGoingOutOfTheEnitity;
	int iCurrentIndex = 0;
	int LastIdx = 0;
	//przechodzimy najpierw po danej fabryce i sprawdzamy ile dostala przedmiorow od dostawcow potem przehcodzimy po magazynach i sprawdzamy ile przedmiotow zostalo wyslanych z fabryki j
	for (int j = 0; j < i_factories_count; j++)
	{
		quantityOfItemsGoingToTheEnitity = 0;
		quantityOfItemsGoingOutOfTheEnitity = 0;
		//petla po wszystkich dostawcach dla danej fabryki
		for (int i = 0; i < i_suppliers_count; i++)
		{
			iCurrentIndex = i * i_factories_count + j;
			quantityOfItemsGoingToTheEnitity += (pdSolution)[LastIdx + iCurrentIndex];
		}//for (int j = 0; j < i_factories_count; j++)
		//petla po wszystkich magazynach dla danej fabryki

		int iIndexOfFirstFabric = i_suppliers_count * i_factories_count;
		
		for (int k = 0; k < i_warehouses_count; k++)
		{	
			iCurrentIndex = j * i_warehouses_count + k;
			quantityOfItemsGoingOutOfTheEnitity += pdSolution[iIndexOfFirstFabric + iCurrentIndex];
		}//for (int j = 0; j < i_warehouses_count; i++)
		if (quantityOfItemsGoingOutOfTheEnitity > quantityOfItemsGoingToTheEnitity) return false;
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx = i_suppliers_count * i_factories_count;
	//przechodzimy najpierw po danym magazynie i sprawdzamy ile dostal przedmiotow od fabryki potem przehcodzimy po sklepach i sprawdzamy ile przedmiotow zostalo wyslanych z fabryki j
	for (int j = 0; j < i_warehouses_count; j++)
	{	
		quantityOfItemsGoingToTheEnitity = 0;
		quantityOfItemsGoingOutOfTheEnitity = 0;
		//petla po wszystkich dostawcach dla danego magazynu
		for (int i = 0; i < i_factories_count; i++)
		{
			iCurrentIndex = i * i_warehouses_count + j;
			quantityOfItemsGoingToTheEnitity += (pdSolution)[LastIdx + iCurrentIndex];
		}//for (int j = 0; j < i_factories_count; j++)
		//petla po wszystkich magazynach dla danej fabryki

		int iIndexOfFirstWarehouseSellerMatrix = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count;
		for (int k = 0; k < i_sellers_count; k++)
		{
			iCurrentIndex = j * i_sellers_count + k;
			quantityOfItemsGoingOutOfTheEnitity += pdSolution[iIndexOfFirstWarehouseSellerMatrix + iCurrentIndex];
		}//for (int j = 0; j < i_warehouses_count; i++)
		if (quantityOfItemsGoingOutOfTheEnitity > quantityOfItemsGoingToTheEnitity) return false;
	}//for (int i = 0; i < i_suppliers_count; i++)
	return true;
}//bool CMscnProblem::bCheckSufficientProductAmmountDelivery(double* pdSolution)

double CMscnProblem::dGetMinValueAt(double* pdSolution, int iIndex)
{
	if (iIndex < 0 || iIndex >= i_suppliers_count*i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count) return -1;

	int iCurrentIndex = 0;
	int LastIdx = 0;

	if (iIndex >= i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count)
	{
		LastIdx = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count;
		for (int i = 0; i < i_warehouses_count; i++)
		{
			for (int j = 0; j < i_sellers_count; j++)
			{
				iCurrentIndex = i * i_sellers_count + j;
				if (LastIdx + iCurrentIndex == iIndex) return cm_min_items_sent_from_warehouse->dGet(i, j);
			}//for (int j = 0; j < i_sellers_count; j++)
		}//for (int i = 0; i < i_warehouses_count; i++)
	}//if (iIndex >= i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count)
	else if (iIndex >= i_suppliers_count * i_factories_count)
	{
		LastIdx = i_suppliers_count * i_factories_count;
		for (int i = 0; i < i_factories_count; i++)
		{
			for (int j = 0; j < i_warehouses_count; j++)
			{
				iCurrentIndex = i * i_warehouses_count + j;
				if (LastIdx + iCurrentIndex == iIndex) return cm_min_items_sent_from_factory->dGet(i, j);
			}//for (int j = 0; j < i_warehouses_count; j++)
		}//for (int i = 0; i < i_factories_count; i++)
	}//else if (iIndex >= i_suppliers_count * i_factories_count)
	else
	{
		for (int i = 0; i < i_suppliers_count; i++)
		{
			for (int j = 0; j < i_factories_count; j++)
			{
				iCurrentIndex = i * i_factories_count + j;
				if (LastIdx + iCurrentIndex == iIndex) return cm_min_items_sent_from_supplier->dGet(i, j);
			}//for (int j = 0; j < i_factories_count; j++)
		}//for (int i = 0; i < i_suppliers_count; i++)
	}//else
	
	return -1;
}//double CMscnProblem::dGetMinValueAt(double* pdSolution, int iIndex)

double CMscnProblem::dGetMaxValueAt(double* pdSolution, int iIndex)
{
	if (iIndex < 0 || iIndex >= i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count) return -1;

	int iCurrentIndex = 0;
	int iStartingIndex = 0;
	//if zeby zminimalizowtac przejscia
	if (iIndex >= i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count)
	{
		iStartingIndex = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count;
		for (int i = 0; i < i_warehouses_count; i++)
		{
			for (int j = 0; j < i_sellers_count; j++)
			{
				iCurrentIndex = i * i_sellers_count + j;
				if (iStartingIndex + iCurrentIndex == iIndex) return cm_max_items_sent_from_warehouse->dGet(i, j);
			}//for (int j = 0; j < i_sellers_count; j++)
		}//for (int i = 0; i < i_warehouses_count; i++)
	}//if (iIndex >= i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count)
	else if (iIndex >= i_suppliers_count * i_factories_count)
	{
		iStartingIndex = i_suppliers_count * i_factories_count;
		for (int i = 0; i < i_factories_count; i++)
		{
			for (int j = 0; j < i_warehouses_count; j++)
			{
				iCurrentIndex = i * i_warehouses_count + j;
				if (iStartingIndex + iCurrentIndex == iIndex) return cm_max_items_sent_from_factory->dGet(i, j);
			}//for (int j = 0; j < i_warehouses_count; j++)
		}//for (int i = 0; i < i_factories_count; i++)
	}//else if (iIndex >= i_suppliers_count * i_factories_count)
	else
	{
		for (int i = 0; i < i_suppliers_count; i++)
		{
			for (int j = 0; j < i_factories_count; j++)
			{
				iCurrentIndex = i * i_factories_count + j;
				if (iStartingIndex + iCurrentIndex == iIndex) return cm_max_items_sent_from_supplier->dGet(i, j);
			}//for (int j = 0; j < i_factories_count; j++)
		}//for (int i = 0; i < i_suppliers_count; i++)
	}//else
	return -1;
}//double CMscnProblem::dGetMaxValueAt(double* pdSolution, int iIndex)

bool CMscnProblem::bReadProblemFromFile(std::string sFileName)
{
	if (pf_file != NULL) fclose(pf_file);
	pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;
	if (
		bReadEntitiesFromProblemFile(pf_file) == false
		|| bReadCapacitiesFromProblemFile(pf_file) == false
		|| bReadTransportMatrixesFromProblemFile(pf_file) == false
		|| bReadContractValuesFromProblemFile(pf_file) == false
		)return false;
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_sellers_count; i++)
	{	
		fscanf(pf_file, "%lf", &dTempValue);
		ct_sellers_income_value->bSet(dTempValue, i);
	}

	if (bReadMinMaxValuesFromProblemFile(pf_file) == false) return false;
	
	fclose(pf_file);
	pf_file = NULL;
	if (pf_file != NULL) return false;
	return true;
}//bool CMscnProblem::bReadFromFile(std::string sFileName)

bool CMscnProblem::bReadEntitiesFromProblemFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &i_suppliers_count);
	bSetSuppliersCount(i_suppliers_count);

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &i_factories_count);
	bSetFactoriesCount(i_factories_count);

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &i_warehouses_count);
	bSetWarehousesCount(i_warehouses_count);

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &i_sellers_count);
	bSetSellersCount(i_sellers_count);
	return true;
}//bool CMscnProblem::bReadEntitiesFromFile(FILE* pfFile)

bool CMscnProblem::bReadCapacitiesFromProblemFile(FILE* pfFile)
{	
	if (pf_file == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_suppliers_count; i++)
	{
		fscanf(pf_file, "%lf ", &dTempValue);
		ct_suppliers_capacity_ammount->bSet(dTempValue, i);
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_factories_count; i++)
	{
		fscanf(pf_file, "%lf ", &dTempValue);
		ct_factories_capacity_ammount->bSet(dTempValue, i);
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_warehouses_count; i++)
	{
		fscanf(pf_file, "%lf ", &dTempValue);
		ct_warehouses_capacity_ammount->bSet(dTempValue, i);
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_sellers_count; i++)
	{
		fscanf(pf_file, "%lf ", &dTempValue);
		ct_sellers_capacity_ammount->bSet(dTempValue, i);
	}
	return true;
}//bool CMscnProblem::bReadCapacitiesFromFile(FILE* pfFile, double* pcTempValue)

bool CMscnProblem::bReadTransportMatrixesFromProblemFile(FILE* pfFile)
{	
	if (pf_file == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			fscanf(pf_file, "%lf ", &dTempValue);
			cm_delivery_matrix->bSet(dTempValue, i, j);
		}
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			fscanf(pf_file, "%lf ", &dTempValue);
			cm_factory_matrix->bSet(dTempValue, i, j);
		}
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			fscanf(pf_file, "%lf ", &dTempValue);
			cm_warehouse_matrix->bSet(dTempValue, i, j);
		}
	}
	return true;
}//bool CMscnProblem::bReadTransportMatrixes(FILE* pfFile)

bool CMscnProblem::bReadContractValuesFromProblemFile(FILE * pfFile)
{
	if(pfFile == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_suppliers_count; i++)
	{
		fscanf(pf_file, "%lf", &dTempValue);
		ct_suppliers_contract_prices->bSet(dTempValue, i);
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_factories_count; i++)
	{
		fscanf(pf_file, "%lf", &dTempValue);
		ct_factories_contract_prices->bSet(dTempValue, i);
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_warehouses_count; i++)
	{
		fscanf(pf_file, "%lf", &dTempValue);
		ct_warehouses_contract_prices->bSet(dTempValue, i);
	}
	return true;
}//bool CMscnProblem::bReadContractValuesFromFile(FILE * pfFile)

bool CMscnProblem::bReadMinMaxValuesFromProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			fscanf(pf_file, "%lf", &dTempValue);
			cm_min_items_sent_from_supplier->bSet(dTempValue, i, j);

			fscanf(pf_file, "%lf", &dTempValue);
			cm_max_items_sent_from_supplier->bSet(dTempValue, i, j);
		}
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			fscanf(pf_file, "%lf", &dTempValue);
			cm_min_items_sent_from_factory->bSet(dTempValue, i, j);

			fscanf(pf_file, "%lf", &dTempValue);
			cm_max_items_sent_from_factory->bSet(dTempValue, i, j);
		}
	}

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			fscanf(pf_file, "%lf", &dTempValue);
			cm_min_items_sent_from_warehouse->bSet(dTempValue, i, j);

			fscanf(pf_file, "%lf", &dTempValue);
			cm_max_items_sent_from_warehouse->bSet(dTempValue, i, j);
		}
	}
	return true;
}//bool CMscnProblem::bReamMinMaxValuesFromFile(FILE * pfFile)

bool CMscnProblem::bWriteProblemToFile(std::string sFileName)
{
	if (pf_file != NULL) fclose(pf_file);
	pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) return false;
	if (
		bWriteEntitiesToProblemFile(pf_file) == false
		||bWriteCapacitiesToProblemFile(pf_file) == false
		||bWriteTransportMatrixesToProblemFile(pf_file) == false
		||bWriteContractValuesToProblemFile(pf_file) == false
		) return false;

	fprintf(pf_file, "\np\n");
	for (int i = 0; i < i_sellers_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_sellers_income_value->dGet(i));
	}
	
	if (bWriteMinMaxValuesToProblemFile(pf_file) == false) return false;

	fclose(pf_file);
	pf_file = NULL;
	if (pf_file != NULL) return false;
	return true;
}//bool CMscnProblem::bWriteToFile(std::string sFileName)

bool CMscnProblem::bWriteEntitiesToProblemFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pf_file, "D %d\n", i_suppliers_count);
	fprintf(pf_file, "F %d\n", i_factories_count);
	fprintf(pf_file, "W %d\n", i_warehouses_count);
	fprintf(pf_file, "S %d\n", i_sellers_count);
	return true;
}//bool CMscnProblem::bWriteEntitiesToProblemFile(FILE* pfFile)

bool CMscnProblem::bWriteCapacitiesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pf_file, "sd\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_suppliers_capacity_ammount->dGet(i));
	}

	fprintf(pf_file, "\nsf\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_factories_capacity_ammount->dGet(i));
	}

	fprintf(pf_file, "\nsm\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_warehouses_capacity_ammount->dGet(i));
	}

	fprintf(pf_file, "\nss\n");
	for (int i = 0; i < i_sellers_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_sellers_capacity_ammount->dGet(i));
	}
	return true;
}//bool CMscnProblem::bWriteCapacitiesToProblemFile(FILE * pfFile)

bool CMscnProblem::bWriteTransportMatrixesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pf_file, "\ncd\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			fprintf(pf_file, "%lf ", cm_delivery_matrix->dGet(i, j));
		}
		fprintf(pf_file, "\n");
	}

	fprintf(pf_file, "cf\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			fprintf(pf_file, "%lf ", cm_factory_matrix->dGet(i, j));
		}
		fprintf(pf_file, "\n");
	}

	fprintf(pf_file, "cm\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			fprintf(pf_file, "%lf ", cm_warehouse_matrix->dGet(i, j));
		}
		fprintf(pf_file, "\n");
	}
	return true;
}//bool CMscnProblem::bWriteTransportMatrixesToProblemFile(FILE * pfFile)

bool CMscnProblem::bWriteContractValuesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pf_file, "ud\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_suppliers_contract_prices->dGet(i));
	}

	fprintf(pf_file, "\nuf\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_factories_contract_prices->dGet(i));
	}

	fprintf(pf_file, "\num\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		fprintf(pf_file, "%lf ", ct_warehouses_contract_prices->dGet(i));
	}
	return true;
}//bool CMscnProblem::bWriteContractValuesToProblemFile(FILE * pfFile)

bool CMscnProblem::bWriteMinMaxValuesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pf_file, "\nxdminmax\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			fprintf(pf_file, "%lf ", cm_min_items_sent_from_supplier->dGet(i, j));
			fprintf(pf_file, "%lf ", cm_max_items_sent_from_supplier->dGet(i, j));
		}
		fprintf(pf_file, "\n");
	}

	fprintf(pf_file, "xfminmax\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			fprintf(pf_file, "%lf ", cm_min_items_sent_from_factory->dGet(i, j));
			fprintf(pf_file, "%lf ", cm_max_items_sent_from_factory->dGet(i, j));
		}
		fprintf(pf_file, "\n");
	}

	fprintf(pf_file, "xmminmax\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			fprintf(pf_file, "%lf ", cm_min_items_sent_from_warehouse->dGet(i, j));
			fprintf(pf_file, "%lf ", cm_max_items_sent_from_warehouse->dGet(i, j));
		}
		fprintf(pf_file, "\n");
	}
	return true;
}//bool CMscnProblem::bWriteMinMaxValuesToProblemFile(FILE * pfFile)

bool CMscnProblem::bReadSolutionFromFile(std::string sFileName, double** pdSolution, int& iSize)
{	
	if (pf_file != NULL) fclose(pf_file);
	pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) return false;
	
	bReadEntitiesFromSolutionFile(pf_file, iSize);
	*pdSolution = new double[iSize];
	bReadSolutionValuesFromSolutionFile(pf_file, *pdSolution);

	fclose(pf_file);
	pf_file = NULL;
	if (pf_file != NULL) return false;
	return true;
}//bool CMscnProblem::bReadSolutionToFile(std::string sFileName)

bool CMscnProblem::bReadEntitiesFromSolutionFile(FILE* pfFile, int& iSize)
{
	if (pfFile == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	int iSolutionSuppliers;
	int iSolutionFactories;
	int iSolutionWarehouses;
	int iSolutionSellers;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iSolutionSuppliers);
	
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iSolutionFactories);

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iSolutionWarehouses);

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iSolutionSellers);

	if (iSolutionSuppliers != i_suppliers_count || iSolutionFactories != i_factories_count
		|| iSolutionWarehouses != i_warehouses_count || iSolutionSellers != i_sellers_count) return false;
	iSize = iSolutionSuppliers * iSolutionFactories + iSolutionFactories * iSolutionWarehouses + iSolutionWarehouses * iSolutionSellers;
	return true;
}//bool CMscnProblem::bReadEntitiesFromSolutionFile(FILE* pfFile)

bool CMscnProblem::bReadSolutionValuesFromSolutionFile(FILE* pfFile, double* pdSolution)
{
	if (pfFile == NULL) return false;

	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;
	int iLastIndex = 0;
	int iCurrentIndex = 0;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrentIndex = i * i_factories_count + j;
			fscanf(pf_file, "%lf", &dTempValue);
			pdSolution[iLastIndex + iCurrentIndex] = dTempValue;
		}
	}

	iLastIndex += iCurrentIndex + 1;
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrentIndex = i * i_warehouses_count + j;
			fscanf(pf_file, "%lf", &dTempValue);
			pdSolution[iLastIndex + iCurrentIndex] = dTempValue;
		}
	}

	iLastIndex += iCurrentIndex + 1;
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrentIndex = i * i_sellers_count + j;
			fscanf(pf_file, "%lf", &dTempValue);
			pdSolution[iLastIndex + iCurrentIndex] = dTempValue;
		}
	}
	return true;
}//bool CMscnProblem::bReadSolutionValuesFromSolutionFile(FILE* pfFile, double* pdSolution)

bool CMscnProblem::bWriteSolutionToFile(std::string sFileName, double* pdSolution)
{
	if (pf_file != NULL) fclose(pf_file);
	pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) return false;

	if (
		bWriteEntitiesToSolutionFile(pf_file) == false
	||  bWriteSolutionValuesToSolutionFile(pf_file, pdSolution) == false
		) return false;

	fclose(pf_file);
	pf_file = NULL;
	if (pf_file != NULL) return false;
	return true;
}//bool CMscnProblem::bWriteSolutionToFile(std::string sFileName)

bool CMscnProblem::bWriteEntitiesToSolutionFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pf_file, "D %d\n", i_suppliers_count);
	fprintf(pf_file, "F %d\n", i_factories_count);
	fprintf(pf_file, "M %d\n", i_warehouses_count);
	fprintf(pf_file, "S %d\n", i_sellers_count);
	return true;
}//bool CMscnProblem::bWriteEntitiesToSolutionFile(FILE* pfFile)

bool CMscnProblem::bWriteSolutionValuesToSolutionFile(FILE* pfFile, double* pdSolution)
{
	if (pfFile == NULL) return false;
	int iCurrentIndex = 0;
	int iLastIndex = 0;

	fprintf(pf_file, "xd\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrentIndex = i * i_factories_count + j;
			fprintf(pf_file, "%lf ", pdSolution[iLastIndex + iCurrentIndex]);
		}
	}

	iLastIndex += iCurrentIndex + 1;
	fprintf(pf_file, "xf\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrentIndex = i * i_warehouses_count + j;
			fprintf(pf_file, "%lf ", pdSolution[iLastIndex + iCurrentIndex]);
		}
	}

	iLastIndex += iCurrentIndex + 1;
	fprintf(pf_file, "xm\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrentIndex = i * i_sellers_count + j;
			fprintf(pf_file, "%lf ", pdSolution[iLastIndex + iCurrentIndex]);
		}
	}
	return true;
}//bool CMscnProblem::bWriteSolutionValuesToSolutionFile(FILE* pfFile)

