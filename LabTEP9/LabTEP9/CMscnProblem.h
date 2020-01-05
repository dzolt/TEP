#pragma warning(disable:4996)
#include "CMatrix.h"
#include "CTable.h"
#include "CSolution.h"
#include "Constants.h"
#include <iostream>


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

	bool bSetDeliveryMatrixValAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetFactoryMatrixValAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetWarehouseMatrixValAt(double dValue, int i_xIndex, int i_yIndex);

	bool bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex);

	bool bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex);

	bool bSetSupplierCapacityAmmount(double dVal, int iIndex);
	bool bSetFactoryCapacityAmmount(double dVal, int iIndex);
	bool bSetWarehouseCapacityAmmount(double dVal, int iIndex);
	bool bSetSellerCapacityAmmount(double dVal, int iIndex);
	bool bSetSellerIncomeValAt(double dVal, int iIndex);

	bool bSetSupplierContractPriceAt(double dVal, int iIndex);
	bool bSetFactoryContractPriceAt(double dVal, int iIndex);
	bool bSetWarehouseContractPriceAt(double dVal, int iIndex);

	bool bGetQuality(CSolution& pcSolution, double& profit);

	bool bConstraintsSatisfied(CSolution& pcSolution);

	double dGetMinValueAt(double* pdSolution, int iIndex);
	double dGetMaxValueAt(double* pdSolution, int iIndex);

	bool bSetMinValueForSupplierItemQuantityAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetMinValueForFactoryItemQuantityAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetMinValueForWarehouseItemQuantityAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetMaxValueForSupplierItemQuantityAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetMaxValueForFactoryItemQuantityAt(double dValue, int i_xIndex, int i_yIndex);
	bool bSetMaxValueForWarehouseItemQuantityAt(double dValue, int i_xIndex, int i_yIndex);

	double dGetMinValueSupplierItemQuantity(int i_xIndex, int i_yIndex);
	double dGetMinValueFactoryItemQuantity(int i_xIndex, int i_yIndex);
	double dGetMinValueWarehouseItemQuantity(int i_xIndex, int i_yIndex);
	double dGetMaxValueSupplierItemQuantity(int i_xIndex, int i_yIndex);
	double dGetMaxValueFactoryItemQuantity(int i_xIndex, int i_yIndex);
	double dGetMaxValueWarehouseItemQuantity(int i_xIndex, int i_yIndex);

	void vSetEveryMaximalCostAtCapacity();

	bool bWriteProblemToFile(std::string sFileName);
	bool bReadProblemFromFile(std::string sFileName);

	void vSetSolution(CSolution* pcSolution) { pc_solution = pcSolution; };
	void vGenerateInstance(CRandom& cRandom);
private:

	inline bool bInitTables();	
	inline bool bInitMatrixes();
	inline bool bInitMinMaxMatrixes();

	inline bool bSetEveryMinimalCostTo(CMatrix** pdMatrix, int iSizex, int iSizeY, double dValue);
	
	inline bool bCheckMinMaxConstraint(CSolution& pcSolution);
	inline bool bCheckSolutionForNegativeNumbers(CSolution& pcSolution);
	inline bool bCheckMaxCapacityOverload(CSolution& pcSolution);
	inline bool bCheckSufficientProductAmmountDelivery(CSolution& pdSolution);

	double dMultiplyDeliveryCostPerItemsOrdered(CSolution& pcSolution);
	double dCalculateTotalContractPrice(CSolution& pcSolution);
	double dCalculateTotalIncomeFromSellers(CSolution& pcSolution);

	bool bReadEntitiesFromProblemFile(FILE* pfFile);
	bool bReadCapacitiesFromProblemFile(FILE* pfFile);
	bool bReadTransportMatrixesFromProblemFile(FILE* pfFile);
	bool bReadContractValuesFromProblemFile(FILE* pfFile);
	bool bReadMinMaxValuesFromProblemFile(FILE* pfFile);
	
	bool bWriteEntitiesToProblemFile(FILE* pfFile);
	bool bWriteCapacitiesToProblemFile(FILE* pfFile);
	bool bWriteTransportMatrixesToProblemFile(FILE* pfFile);
	bool bWriteContractValuesToProblemFile(FILE* pfFile);
	bool bWriteMinMaxValuesToProblemFile(FILE* pfFile);
	bool bWriteMatrixToFile(FILE* pfFile, CMatrix* cmMatrix);

	
	unsigned int i_suppliers_count;
	unsigned int i_factories_count;
	unsigned int i_sellers_count;
	unsigned int i_warehouses_count;

	CTable* ct_suppliers_contract_prices;
	CTable* ct_factories_contract_prices;
	CTable* ct_warehouses_contract_prices;
	
	CTable* ct_sellers_income_value;

	CTable* ct_suppliers_capacity_ammount;
	CTable* ct_factories_capacity_ammount;
	CTable* ct_warehouses_capacity_ammount;
	CTable* ct_sellers_capacity_ammount;

	CMatrix* cm_min_items_sent_from_supplier;
	CMatrix* cm_max_items_sent_from_supplier;

	CMatrix* cm_min_items_sent_from_factory;
	CMatrix* cm_max_items_sent_from_factory;
	
	CMatrix* cm_min_items_sent_from_warehouse;
	CMatrix* cm_max_items_sent_from_warehouse;

	CMatrix* cm_delivery_matrix;
	CMatrix* cm_factory_matrix;
	CMatrix* cm_warehouse_matrix;

	CSolution* pc_solution;

	FILE* pf_file;
};


inline bool CMscnProblem::bSetDeliveryMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_delivery_matrix->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetDeliveryMatrixVal(double dValue, int iSizeX, int iSizeY)

inline bool CMscnProblem::bSetFactoryMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_factory_matrix->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetFactoryMatrixVal(double dValue, int iSizeX, int iSizeY)

inline bool CMscnProblem::bSetWarehouseMatrixValAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_warehouse_matrix->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetWarehouseMatrixVal(double dValue, int iSizeX, int iSizeY)

inline bool CMscnProblem::bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_supplier->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetSupplierMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_factory->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetFactoryMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_warehouse->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetWarehouseMinItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_supplier->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetSupplierMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_factory->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetFactoryMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_warehouse->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetWarehouseMaxItemsSentAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetSupplierCapacityAmmount(double dVal, int iIndex)
{
	return ct_suppliers_capacity_ammount->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetSupplierCapacityAmmount(double dVal, int iIndex)

inline bool CMscnProblem::bSetFactoryCapacityAmmount(double dVal, int iIndex)
{
	return ct_factories_capacity_ammount->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetFactoryCapacityAmmount(double dVal, int iIndex)

inline bool CMscnProblem::bSetWarehouseCapacityAmmount(double dVal, int iIndex)
{
	 return ct_warehouses_capacity_ammount->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetWarehouseCapacityAmmount(double dVal, int iIndex)

inline bool CMscnProblem::bSetSellerCapacityAmmount(double dVal, int iIndex)
{
	return ct_sellers_capacity_ammount->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetSellerCapacityAmmount(double dVal, int iIndex)

inline bool CMscnProblem::bSetSellerIncomeValAt(double dVal, int iIndex)
{
	return ct_sellers_income_value->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetSellerIncomeValAt(double dVal, int iIndex)

inline bool CMscnProblem::bSetSupplierContractPriceAt(double dVal, int iIndex)
{
	return ct_suppliers_contract_prices->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetSupplierContractPriceAt(double dVal, int iIndex)

inline bool CMscnProblem::bSetFactoryContractPriceAt(double dVal, int iIndex)
{
	return ct_factories_contract_prices->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetFactoryContractPriceAt(double dVal, int iIndex)

inline bool CMscnProblem::bSetWarehouseContractPriceAt(double dVal, int iIndex)
{
	return ct_warehouses_contract_prices->bSet(dVal, iIndex);
}//inline bool CMscnProblem::bSetWarehouseContractPriceAt(double dVal, int iIndex)

inline bool CMscnProblem::bSetMinValueForSupplierItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_supplier->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetMinValueForSupplierItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetMinValueForFactoryItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_factory->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetMinValueForFactoryItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetMinValueForWarehouseItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_warehouse->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetMinValueForWarehouseItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetMaxValueForSupplierItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_supplier->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetMaxValueForSupplierItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetMaxValueForFactoryItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_factory->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetMaxValueForFactoryItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)

inline bool CMscnProblem::bSetMaxValueForWarehouseItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_warehouse->bSet(dValue, i_xIndex, i_yIndex);
}//inline bool CMscnProblem::bSetMaxValueForWarehouseItemQuantityAt(double dValue, int i_xIndex, int i_yIndex)

inline double CMscnProblem::dGetMinValueSupplierItemQuantity(int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_supplier->dGet(i_xIndex, i_yIndex);
}//inline double CMscnProblem::dGetMinValueSupplierItemQuantity(int i_xIndex, int i_yIndex)

inline double CMscnProblem::dGetMinValueFactoryItemQuantity(int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_factory->dGet(i_xIndex, i_yIndex);
}//inline double CMscnProblem::dGetMinValueFactoryItemQuantity(int i_xIndex, int i_yIndex)

inline double CMscnProblem::dGetMinValueWarehouseItemQuantity(int i_xIndex, int i_yIndex)
{
	return cm_min_items_sent_from_warehouse->dGet(i_xIndex, i_yIndex);
}//inline double CMscnProblem::dGetMinValueWarehouseItemQuantity(int i_xIndex, int i_yIndex)

inline double CMscnProblem::dGetMaxValueSupplierItemQuantity(int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_supplier->dGet(i_xIndex, i_yIndex);
}//inline double CMscnProblem::dGetMaxValueSupplierItemQuantity(int i_xIndex, int i_yIndex)

inline double CMscnProblem::dGetMaxValueFactoryItemQuantity(int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_factory->dGet(i_xIndex, i_yIndex);
}//inline double CMscnProblem::dGetMaxValueFactoryItemQuantity(int i_xIndex, int i_yIndex)

inline double CMscnProblem::dGetMaxValueWarehouseItemQuantity(int i_xIndex, int i_yIndex)
{
	return cm_max_items_sent_from_warehouse->dGet(i_xIndex, i_yIndex);
}//inline double CMscnProblem::dGetMaxValueWarehouseItemQuantity(int i_xIndex, int i_yIndex)

