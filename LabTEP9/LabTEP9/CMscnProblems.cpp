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
		if( bInitTables() == true && bInitMatrixes() == true) bSuccess = true;
		else bSuccess = false;
	}//else if (iSuppliersCount < 1 || iFactoriesCount < 1 || iSellersCount < 1 || iWarehousesCount < 1)
}//CMscnProblem::CMscnProblem(unsigned int iSuppliersCount, unsigned int iFactoriesCount, unsigned int iSellersCount, unsigned int iWarehousesCount, bool bSuccess)

CMscnProblem::~CMscnProblem(){}//CMscnProblem::~CMscnProblem()

bool CMscnProblem::bInitTables()
{	
	bool bSuccess = true;
	ct_suppliers_contract_prices =	CTable(i_suppliers_count, bSuccess);
	ct_warehouses_contract_prices = CTable(i_warehouses_count, bSuccess);
	ct_factories_contract_prices = CTable(i_factories_count, bSuccess);

	ct_sellers_income_value = CTable(i_sellers_count, bSuccess);
	
	ct_suppliers_capacity_ammount = CTable(i_suppliers_count, bSuccess);
	ct_warehouses_capacity_ammount = CTable(i_warehouses_count, bSuccess);
	ct_factories_capacity_ammount = CTable(i_warehouses_count, bSuccess);
	if (bSuccess == false) return false;
	return true;
}//void CMscnProblem::vInitTables()

bool CMscnProblem::bInitMatrixes()
{	
	bool bSuccess = true;
	cm_delivery_matrix = CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	cm_min_items_sent_from_supplier = CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	cm_max_items_sent_from_supplier = CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	
	cm_factory_matrix =  CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	cm_min_items_sent_from_factory = CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	cm_max_items_sent_from_factory = CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	
	cm_warehouse_matrix = CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	cm_min_items_sent_from_warehouse = CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	cm_max_items_sent_from_warehouse = CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	if (bSuccess == true) return true;
	return false;
}//void CMscnProblem::vInitMatrixes()


bool CMscnProblem::bSetSuppliersCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;
	
	i_suppliers_count = iNewCount;

	ct_suppliers_contract_prices.bSetSize(i_suppliers_count);
	ct_suppliers_capacity_ammount.bSetSize(i_suppliers_count);

	cm_delivery_matrix.bSetSize(i_suppliers_count, i_factories_count);
	cm_max_items_sent_from_supplier.bSetSize(i_suppliers_count, i_factories_count);
	cm_min_items_sent_from_supplier.bSetSize(i_suppliers_count, i_factories_count);
	return true;
}//void CMscnProblem::vSetSuppliersCount(unsigned int iNewValue)

bool CMscnProblem::bSetFactoriesCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_factories_count = iNewCount;
	
	ct_factories_contract_prices.bSetSize(i_suppliers_count);
	ct_factories_capacity_ammount.bSetSize(i_factories_count);

	cm_delivery_matrix.bSetSize(i_suppliers_count, i_factories_count);
	cm_min_items_sent_from_supplier.bSetSize(i_suppliers_count, i_factories_count);
	cm_max_items_sent_from_supplier.bSetSize(i_suppliers_count, i_factories_count);
	
	cm_factory_matrix.bSetSize(i_factories_count, i_warehouses_count);
	cm_min_items_sent_from_factory.bSetSize(i_factories_count, i_warehouses_count);
	cm_max_items_sent_from_factory.bSetSize(i_factories_count, i_warehouses_count);
	return true;
}//void CMscnProblem::vSetFactoriesCount(unsigned int iNewValue)

bool CMscnProblem::bSetSellersCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_sellers_count = iNewCount;
	
	ct_sellers_capacity_ammount.bSetSize(i_sellers_count);
	ct_sellers_income_value.bSetSize(i_sellers_count);

	cm_warehouse_matrix.bSetSize(i_warehouses_count, i_sellers_count);
	cm_min_items_sent_from_warehouse.bSetSize(i_warehouses_count, i_sellers_count);
	cm_max_items_sent_from_warehouse.bSetSize(i_warehouses_count, i_sellers_count);
	return true;
}//void CMscnProblem::vSetSellersCount(unsigned int iNewValue)

bool CMscnProblem::bSetWarehousesCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_warehouses_count = iNewCount;
	
	ct_warehouses_capacity_ammount.bSetSize(i_warehouses_count);
	ct_warehouses_contract_prices.bSetSize(i_warehouses_count);

	cm_warehouse_matrix.bSetSize(i_warehouses_count, i_sellers_count);
	cm_min_items_sent_from_warehouse.bSetSize(i_warehouses_count, i_sellers_count);
	cm_max_items_sent_from_warehouse.bSetSize(i_warehouses_count, i_sellers_count);
	
	cm_factory_matrix.bSetSize(i_factories_count, i_warehouses_count);
	cm_min_items_sent_from_factory.bSetSize(i_factories_count, i_warehouses_count);
	cm_max_items_sent_from_factory.bSetSize(i_factories_count, i_warehouses_count);
	return true;
}//void CMscnProblem::vSetWarehousesCount(unsigned int iNewValue)

bool CMscnProblem::bSetDeliveryMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{	
	return cm_delivery_matrix.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetDeliveryMatrixVal(double dValue, int iSizeX, int iSizeY)

bool CMscnProblem::bSetFactoryMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{	
	return cm_factory_matrix.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetFactoryMatrixVal(double dValue, int iSizeX, int iSizeY)

bool CMscnProblem::bSetWarehouseMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_warehouse_matrix.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetWarehouseMatrixVal(double dValue, int iSizeX, int iSizeY)

bool CMscnProblem::bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_supplier.bSet(dValue,i_xIndex,i_yIndex);
}//bool CMscnProblem::bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_factory.bSet(dValue, i_xIndex,i_yIndex);
}//bool CMscnProblem::bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_warehouse.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_supplier.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_factory.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_warehouse.bSet(dValue, i_xIndex, i_yIndex);
}//bool CMscnProblem::bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

bool CMscnProblem::bSetSupplierCapacityAmmount(double dVal, int iIndex)
{
	return ct_suppliers_capacity_ammount.bSet(dVal,iIndex);
}//bool CMscnProblem::bSetSupplierCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetFactoryCapacityAmmount(double dVal, int iIndex)
{
	return ct_factories_capacity_ammount.bSet(dVal, iIndex);
}////bool CMscnProblem::bSetFactoryCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetWarehouseCapacityAmmount(double dVal, int iIndex)
{
	return ct_warehouses_capacity_ammount.bSet(dVal, iIndex);
}////bool CMscnProblem::bSetWarehouseCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetSellerCapacityAmmount(double dVal, int iIndex)
{
	return ct_sellers_capacity_ammount.bSet(dVal, iIndex);
}//bool CMscnProblem::bSetSellerCapacityAmmount(double dVal, int iIndex)

bool CMscnProblem::bSetSellerIncomeValAt(double dVal, int iIndex)
{
	return ct_sellers_income_value.bSet(dVal, iIndex);
}//bool CMscnProblem::bSetSellerIncomeValAt(double dVal, int iIndex)

bool CMscnProblem::bSetSupplierContractPriceAt(double dVal, int iIndex)
{
	return ct_suppliers_contract_prices.bSet(dVal, iIndex);
}//bool CMscnProblem::bSetSupplierContractPriceAt(double dVal, int iIndex)

bool CMscnProblem::bSetFactoryContractPriceAt(double dVal, int iIndex)
{
	return ct_factories_contract_prices.bSet(dVal,iIndex);
}//bool CMscnProblem::bSetFactoryContractPriceAt(double dVal, int iIndex)

bool CMscnProblem::bSetWarehouseContractPriceAt(double dVal, int iIndex)
{
	return ct_warehouses_contract_prices.bSet(dVal, iIndex);
}//bool CMscnProblem::bSetWarehouseContractPriceAt(double dVal, int iIndex)

bool CMscnProblem::bGetQuality(double* pdSolution, int iSize, double& profit)
{	

	if (pdSolution == NULL || iSize <= 0 || bConstraintsSatisfied(pdSolution, iSize) == false) return false;
	double shopIncome = 0;
	double totalDeliveryCost = 0;
	double totalContractPrice = 0;

	for (int i = 0; i < ct_sellers_income_value.iGetSize(); i++)
	{
		shopIncome += ct_sellers_income_value.dGet(i);
	}

	totalDeliveryCost = dMultiplyDeliveryCostPerItemsOrdered(&pdSolution);
	totalContractPrice = dCalculateTotalContractPrice();
	profit = shopIncome - totalDeliveryCost - totalContractPrice;
	
	return true;
}//double CMscnProblem::dGetQuality(double*** pdSolution)

bool CMscnProblem::bConstraintsSatisfied(double* pdSolution, int iSize)
{
	
	return false;
}//bool CMscnProblem::bConstraintsSatisfied(double * pdSolution, int iSize)

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
			totalDeliveryCost += cm_delivery_matrix.vGet(i, j) * (*pdSolution)[LastIdx + iCurrent];
		}
	}
	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			iCurrent = i * i_warehouses_count + j;
			totalDeliveryCost += cm_factory_matrix.vGet(i, j) * (*pdSolution)[LastIdx + iCurrent];
		}
	}
	LastIdx += iCurrent + 1;
	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			iCurrent = i * i_sellers_count + j;
			totalDeliveryCost += cm_warehouse_matrix.vGet(i, j) * (*pdSolution)[LastIdx + iCurrent];
		}
	}
	return totalDeliveryCost;
}//bool CMscnProblem::bMultiplyDeliveryCostPerItemsOrdered(double** pdSolution)

double CMscnProblem::dCalculateTotalContractPrice()
{
	double totalContractPrice = 0;

	totalContractPrice += dCalculateTotalContractPriceForOneEntity(ct_suppliers_contract_prices);
	totalContractPrice += dCalculateTotalContractPriceForOneEntity(ct_factories_contract_prices);
	totalContractPrice += dCalculateTotalContractPriceForOneEntity(ct_warehouses_contract_prices);

	return totalContractPrice;
}//double CMscnProblem::dCalculateTotalContractPrice()

double CMscnProblem::dCalculateTotalContractPriceForOneEntity(CTable& ctEntity)
{	
	double totalContractPrice = 0;

	for (int i = 0; i < ctEntity.iGetSize(); i++)
	{
		totalContractPrice += ctEntity.dGet(i);
	}
	return totalContractPrice;
}//double CMscnProblem::dCalculateTotalContractPriceForOneEntity(CTable& Entity)








