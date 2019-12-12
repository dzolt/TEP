#pragma once
#include "CMatrix.h"
#include "CTable.h"

class CMscnProblem
{

public:

	CMscnProblem();
	CMscnProblem(unsigned int iSuppliersCount, unsigned int iFactoriesCount, unsigned int iWarehousesCount, unsigned int iSellersCount, bool& bSuccess);
	~CMscnProblem();
	


	bool bSetSuppliersCount(unsigned int iNewValue);
	bool bSetWarehousesCount(unsigned int iNewValue);
	bool bSetFactoriesCount(unsigned int iNewValue);
	bool bSetSellersCount(unsigned int iNewValue);


	bool bSetDeliveryMatrixValAt(double dValue, int i_xIndex, int i_yIndex);//zamien na index
	bool bSetFactoryMatrixValAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetWarehouseMatrixValAt(double dValue, int i_xIndex, int i_yIndex);

	bool bSetSupplierCapacityAmmount(double dVal, int iIndex);
	bool bSetFactoryCapacityAmmount(double dVal, int iIndex);
	bool bSetWarehouseCapacityAmmount(double dVal, int iIndex);
	bool bSetSellerCapacityAmmount(double dVal, int iIndex);
	bool bSetSellerIncomeValAt(double dVal, int iIndex);

	bool dGetQuality(double* pdSolution, int iSize, double& profit);

	double dMultiplyDeliveryCostPerItemsOrdered(double** pdSolution);
	double dCalculateTotalContractPrice();
	double dCalculateTotalContractPriceForOneEntity(CTable& ctEntity);

private:

	bool bInitTables();	
	bool bInitMatrixes();
	
	unsigned int i_suppliers_count;
	unsigned int i_factories_count;
	unsigned int i_sellers_count;
	unsigned int i_warehouses_count;

	CTable ct_suppliers_contract_prices;
	CTable ct_factories_contract_prices;
	CTable ct_warehouses_contract_prices;
	
	CTable ct_sellers_income_value;

	CTable ct_suppliers_capacity_ammount;
	CTable ct_factories_capacity_ammount;
	CTable ct_warehouses_capacity_ammount;
	CTable ct_sellers_capacity_ammount;

	CMatrix cm_delivery_matrix;
	CMatrix cm_factory_matrix;
	CMatrix cm_warehouse_matrix;
};