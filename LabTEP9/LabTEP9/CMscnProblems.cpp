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
	ct_suppliers_contract_prices = CTable(i_suppliers_count, bSuccess);
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
	cm_factory_matrix = CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	cm_warehouse_matrix = CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
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
	return true;
}//void CMscnProblem::vSetSuppliersCount(unsigned int iNewValue)

bool CMscnProblem::bSetFactoriesCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_factories_count = iNewCount;
	
	ct_factories_contract_prices.bSetSize(i_suppliers_count);
	ct_factories_capacity_ammount.bSetSize(i_factories_count);

	cm_delivery_matrix.bSetSize(i_suppliers_count, i_factories_count);
	cm_factory_matrix.bSetSize(i_factories_count, i_warehouses_count);
	return true;
}//void CMscnProblem::vSetFactoriesCount(unsigned int iNewValue)

bool CMscnProblem::bSetSellersCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_sellers_count = iNewCount;
	
	ct_sellers_capacity_ammount.bSetSize(i_sellers_count);
	ct_sellers_income_value.bSetSize(i_sellers_count);

	cm_warehouse_matrix.bSetSize(i_warehouses_count, i_sellers_count);
	return true;
}//void CMscnProblem::vSetSellersCount(unsigned int iNewValue)

bool CMscnProblem::bSetWarehousesCount(unsigned int iNewCount)
{	
	if (iNewCount < 1) return false;

	i_warehouses_count = iNewCount;
	
	ct_warehouses_capacity_ammount.bSetSize(i_warehouses_count);
	ct_warehouses_contract_prices.bSetSize(i_warehouses_count);

	cm_warehouse_matrix.bSetSize(i_warehouses_count, i_sellers_count);
	cm_factory_matrix.bSetSize(i_factories_count, i_warehouses_count);
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

bool CMscnProblem::dGetQuality(double* pdSolution, int iSizeX, int iSizeY, double& profit)
{
	if (pdSolution == NULL || iSizeX < 0 || iSizeY < 0 ) return false;
	double shopIncome = 0;
	double deliveryCost = 0;

	for (int i = 0; i < ct_sellers_income_value.iGetSize(); i++)
	{
		shopIncome += ct_sellers_income_value.dGet(i);
	}

	

	profit = shopIncome - deliveryCost;
	return true;
}//double CMscnProblem::dGetQuality(double*** pdSolution)







