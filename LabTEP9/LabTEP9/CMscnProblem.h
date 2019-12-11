#pragma once
#include "CMatrix.h"
#include "CTable.h"

class CMscnProblem
{

public:

	CMscnProblem();
	CMscnProblem(unsigned int iSuppliersCount, unsigned int iFactoriesCount, unsigned int iSellersCount, unsigned int iWarehousesCount, bool& bSuccess);
	
	~CMscnProblem();

	bool bInitTables();	
	bool bInitMatrixes();

	bool bSetSuppliersCount(unsigned int iNewValue);
	bool bSetFactoriesCount(unsigned int iNewValue);
	bool bSetSellersCount(unsigned int iNewValue);
	bool bSetWarehousesCount(unsigned int iNewValue);

	bool bSetShopProfitVal(double dVal, int iIndex);

	bool bSetDeliveryMatrixVal(double dValue, int iSizeX, int iSizeY);//zamien na index
	bool bSetFactoryMatrixVal(double dValue, int iSizeX, int iSizeY);
	bool bSetWarehouseMatrixVal(double dValue, int iSizeX, int iSizeY);

private:

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