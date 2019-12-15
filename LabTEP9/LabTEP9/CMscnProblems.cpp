#include "CMscnProblem.h"
#include <iostream>

CMscnProblem::CMscnProblem()
{
	i_suppliers_count = DEFAULT_TAB_LENGTH;
	i_factories_count = DEFAULT_TAB_LENGTH;
	i_warehouses_count = DEFAULT_TAB_LENGTH;
	i_sellers_count = DEFAULT_TAB_LENGTH;
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

	//set min for 0 and max for capacity

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
		|| bSetEveryMinimalCostTo(&cm_min_items_sent_from_warehouse, i_warehouses_count, i_sellers_count, 0) == false)
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


bool CMscnProblem::bSetEveryMaximalCostTo(double*** pdMatrix, int iSizeX, int iSizeY, double dValue)
{
	if (iSizeX < 0 || iSizeY < 0 || dValue < 0) return false;
	for (int i = 0; i < iSizeX; i++)
	{
		for (int j = 0; j < iSizeY; j++)
		{
			(*pdMatrix)[i][j] = dValue;
		}//for (int j = 0; j < iSizeY; j++)
	}//for (int i = 0; i < iSizeX; i++)
	return true;
}//bool CMscnProblem::bSetEveryMaximalCostAt(double*** pdMatrix, int iSizeX, int iSizeY, double dValue)

void CMscnProblem::vSetEveryMaximalCostAtCapacity()
{
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			//cm_max_items_sent_from_supplier.bSet(ct_suppliers_capacity_ammount.dGet(i), i, j);
			cm_max_items_sent_from_supplier->bSet(1000, i, j);
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			//cm_max_items_sent_from_factory.bSet(ct_factories_capacity_ammount.dGet(i), i, j);
			cm_max_items_sent_from_factory->bSet(1000, i, j);
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			//cm_max_items_sent_from_warehouse.bSet(ct_warehouses_capacity_ammount.dGet(i), i, j);
			cm_max_items_sent_from_warehouse->bSet(1000, i, j);
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
	
	ct_factories_contract_prices->bSetSize(i_suppliers_count);
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

bool CMscnProblem::bSetDeliveryMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{	
	return cm_delivery_matrix->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetDeliveryMatrixVal(double dValue, int iSizeX, int iSizeY)

bool CMscnProblem::bSetFactoryMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{	
	return cm_factory_matrix->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetFactoryMatrixVal(double dValue, int iSizeX, int iSizeY)

bool CMscnProblem::bSetWarehouseMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_warehouse_matrix->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetWarehouseMatrixVal(double dValue, int iSizeX, int iSizeY)

bool CMscnProblem::bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_supplier->bSet(dValue,i_xIndex,i_yIndex);
}//bool CMscnProblem::bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_factory->bSet(dValue, i_xIndex,i_yIndex);
}//bool CMscnProblem::bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_warehouse->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_supplier->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_factory->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_warehouse->bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetSupplierCapacityAmmount(double dVal, int iIndex)
{
	return ct_suppliers_capacity_ammount->bSet(dVal,iIndex);
}//bool CMscnProblem::bSetSupplierCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetFactoryCapacityAmmount(double dVal, int iIndex)
{
	return ct_factories_capacity_ammount->bSet(dVal, iIndex);
}////bool CMscnProblem::bSetFactoryCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetWarehouseCapacityAmmount(double dVal, int iIndex)
{
	return ct_warehouses_capacity_ammount->bSet(dVal, iIndex);
}////bool CMscnProblem::bSetWarehouseCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetSellerCapacityAmmount(double dVal, int iIndex)
{
	return ct_sellers_capacity_ammount->bSet(dVal, iIndex);
}//bool CMscnProblem::bSetSellerCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetSellerIncomeValAt(double dVal, int iIndex)
{
	return ct_sellers_income_value->bSet(dVal, iIndex);
}//bool CMscnProblem::bSetSellerIncomeValAt(double dVal, int iIndex)

bool CMscnProblem::bSetSupplierContractPriceAt(double dVal, int iIndex)
{
	return ct_suppliers_contract_prices->bSet(dVal, iIndex);
}//bool CMscnProblem::bSetSupplierContractPriceAt(double dVal, int iIndex)

bool CMscnProblem::bSetFactoryContractPriceAt(double dVal, int iIndex)
{
	return ct_factories_contract_prices->bSet(dVal,iIndex);
}//bool CMscnProblem::bSetFactoryContractPriceAt(double dVal, int iIndex)

bool CMscnProblem::bSetWarehouseContractPriceAt(double dVal, int iIndex)
{
	return ct_warehouses_contract_prices->bSet(dVal, iIndex);
}//bool CMscnProblem::bSetWarehouseContractPriceAt(double dVal, int iIndex)

bool CMscnProblem::bGetQuality(double* pdSolution, int iSize, double& profit)
{	

	if (bConstraintsSatisfied(pdSolution, iSize) == false) return false;
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
}

double CMscnProblem::dMultiplyDeliveryCostPerItemsOrdered(double** pdSolution)
{	
	int iCurrent = 0;
	int LastIdx = 0;
	double totalDeliveryCost = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrent = i * i_factories_count + j;
			totalDeliveryCost += cm_delivery_matrix->dGet(i, j) * (*pdSolution)[LastIdx + iCurrent];
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			totalDeliveryCost += cm_factory_matrix->dGet(i, j) * (*pdSolution)[LastIdx + iCurrent];
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			totalDeliveryCost += cm_warehouse_matrix->dGet(i, j) * (*pdSolution)[LastIdx + iCurrent];
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return totalDeliveryCost;
}//bool CMscnProblem::bMultiplyDeliveryCostPerItemsOrdered(double** pdSolution)

double CMscnProblem::dCalculateTotalContractPrice(double** pdSolution)
{	
	double totalContractPrice = 0;

	int iCurrent = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{	
			iCurrent = i * i_factories_count + j;
			if ((*pdSolution)[LastIdx + iCurrent] > 0)
			{
				totalContractPrice += ct_suppliers_contract_prices->dGet(i);
				break;
			}//if ((*pdSolution)[LastIdx + iCurrent] > 0)
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			if ((*pdSolution)[LastIdx + iCurrent] > 0)
			{
				totalContractPrice += ct_factories_contract_prices->dGet(i);
				break;
			}//if ((*pdSolution)[LastIdx + iCurrent] > 0)
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			if ((*pdSolution)[LastIdx + iCurrent] > 0)
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
		||bCheckMaxCapacityOverload(pdSolution) == false || bCheckMinMaxConstraint(pdSolution) == false || bCheckSolutionForNegativeNumbers(pdSolution, iSize) == false
		|| bCheckSufficientProductAmmountDelivery(pdSolution) == false) return false;

	return true;
}//bool CMscnProblem::bConstraintsSatisfied(double * pdSolution, int iSize)

bool CMscnProblem::bCheckMinMaxConstraint(double* pdSolution)
{	
	int iCurrent = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
				iCurrent = i * i_factories_count + j;
			 if( (pdSolution)[LastIdx + iCurrent] < cm_min_items_sent_from_supplier->dGet(i,j) || (pdSolution)[LastIdx + iCurrent] > cm_max_items_sent_from_supplier->dGet(i, j) ) return false;
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)
	LastIdx += iCurrent + 1;

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			if ((pdSolution)[LastIdx + iCurrent] < cm_min_items_sent_from_factory->dGet(i, j) || (pdSolution)[LastIdx + iCurrent] > cm_max_items_sent_from_factory->dGet(i, j)) return false;
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			if ((pdSolution)[LastIdx + iCurrent] < cm_min_items_sent_from_warehouse->dGet(i, j) || (pdSolution)[LastIdx + iCurrent] > cm_max_items_sent_from_warehouse->dGet(i, j)) return false;
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return true;
}//bool CMscnProblem::bCheckMinMaxConstraint(double * pdSolution)

bool CMscnProblem::bCheckSolutionForNegativeNumbers(double * pdSolution, int iSize)
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
	int iCurrent = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{	
		double orderedAmmount = 0;
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrent = i * i_factories_count + j;
			orderedAmmount += (pdSolution)[LastIdx + iCurrent];
			if (orderedAmmount > ct_suppliers_capacity_ammount->dGet(i)) return false;
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)
	LastIdx += iCurrent + 1;

	for (int i = 0; i < i_factories_count; i++)
	{	
		double orderedAmmount = 0;
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			orderedAmmount += (pdSolution)[LastIdx + iCurrent];
			if (orderedAmmount > ct_factories_capacity_ammount->dGet(i)) return false;
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	
	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{	
		double orderedAmmount = 0;
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			orderedAmmount += (pdSolution)[LastIdx + iCurrent];
			if (orderedAmmount > ct_warehouses_capacity_ammount->dGet(i)) return false;
			
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)

	//warunek na sumaryczna ilosc przedmiotow do danego sklepu
	int helperIndex = LastIdx;
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
	//rozwiazanie do dwoch ostatnich p-odpunktow tabeli

	double quantityOfItemsGoingToTheEnitity = 0;
	double quantityOfItemsGoingOutOfTheEnitity = 0;
	int iCurrent = 0;
	int LastIdx = 0;
	//przechodzimy najpierw po danej fabryce i sprawdzamy ile dostala przedmiorow od dostawcow potem przehcodzimy po magazynach i sprawdzamy ile przedmiotow zostalo wyslanych z fabryki j
	for (int j = 0; j < i_factories_count; j++)
	{	
		//petla po wszystkich dostawcach dla danej fabryki
		for (int i = 0; i < i_suppliers_count; i++)
		{
			iCurrent = i * i_factories_count + j;
			quantityOfItemsGoingToTheEnitity += (pdSolution)[LastIdx + iCurrent];
		}//for (int j = 0; j < i_factories_count; j++)
		//petla po wszystkich magazynach dla danej fabryki

		int iIndexOfFirstFabric = i_suppliers_count * i_factories_count;
		//for (int i = 0; i < i_factories_count; i++)
		//{
			for (int z = 0; z < i_warehouses_count; z++)
			{	
				iCurrent = j * i_warehouses_count + z;
				quantityOfItemsGoingOutOfTheEnitity += pdSolution[iIndexOfFirstFabric + iCurrent];
			}//for (int j = 0; j < i_warehouses_count; i++)
		//}//for (int i = 0; i < i_factories_count; i++)
		if (quantityOfItemsGoingOutOfTheEnitity > quantityOfItemsGoingToTheEnitity) return false;
	}//for (int i = 0; i < i_suppliers_count; i++)

	LastIdx = i_suppliers_count * i_factories_count;
	//przechodzimy najpierw po danej fabryce i sprawdzamy ile dostala przedmiorow od dostawcow potem przehcodzimy po magazynach i sprawdzamy ile przedmiotow zostalo wyslanych z fabryki j
	for (int j = 0; j < i_warehouses_count; j++)
	{
		//petla po wszystkich dostawcach dla danego magazynu
		for (int i = 0; i < i_factories_count; i++)
		{
			iCurrent = i * i_warehouses_count + j;
			quantityOfItemsGoingToTheEnitity += (pdSolution)[LastIdx + iCurrent];
		}//for (int j = 0; j < i_factories_count; j++)
		//petla po wszystkich magazynach dla danej fabryki

		int iIndexOfFirstWarehouse = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count;
		//for (int i = 0; i < i_warehouses_count; i++)
		//{
			for (int z = 0; z < i_sellers_count; z++)
			{
				iCurrent = j * i_sellers_count + z;
				quantityOfItemsGoingOutOfTheEnitity += pdSolution[iIndexOfFirstWarehouse + iCurrent];
			}//for (int j = 0; j < i_warehouses_count; i++)
		//}//for (int i = 0; i < i_factories_count; i++)
		if (quantityOfItemsGoingOutOfTheEnitity > quantityOfItemsGoingToTheEnitity) return false;
	}//for (int i = 0; i < i_suppliers_count; i++)
	
	return true;
}//bool CMscnProblem::bCheckSufficientProductAmmountDelivery(double* pdSolution)

double CMscnProblem::dGetMinValueAt(double* pdSolution, int iIndex)
{
	if (iIndex < 0 || iIndex >= i_suppliers_count*i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count) return -1;

	int iCurrent = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrent = i * i_factories_count + j;
			if (LastIdx + iCurrent == iIndex) return cm_min_items_sent_from_supplier->dGet(i, j);
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)
	LastIdx += iCurrent + 1;

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			if (LastIdx + iCurrent == iIndex) return cm_min_items_sent_from_factory->dGet(i, j);
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			if (LastIdx + iCurrent == iIndex) return cm_min_items_sent_from_warehouse->dGet(i, j);
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return -1;
}//double CMscnProblem::dGetMinValueAt(double* pdSolution, int iIndex)

double CMscnProblem::dGetMaxValueAt(double* pdSolution, int iIndex)
{
	if (iIndex < 0 || iIndex >= i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count) return -1;

	int iCurrent = 0;
	int LastIdx = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			iCurrent = i * i_factories_count + j;
			if (LastIdx + iCurrent == iIndex) return cm_max_items_sent_from_supplier->dGet(i, j);
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)
	LastIdx += iCurrent + 1;

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			if (LastIdx + iCurrent == iIndex) return cm_max_items_sent_from_factory->dGet(i, j);
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			if (LastIdx + iCurrent == iIndex) return cm_max_items_sent_from_warehouse->dGet(i, j);
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return -1;
}//double CMscnProblem::dGetMaxValueAt(double* pdSolution, int iIndex)








