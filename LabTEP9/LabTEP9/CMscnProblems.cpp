#include "CMscnProblem.h"
#include <iostream>

CMscnProblem::CMscnProblem()
{
	i_suppliers_count = DEFAULT_TAB_LENGTH;
	i_factories_count = DEFAULT_TAB_LENGTH;
	i_warehouses_count = DEFAULT_TAB_LENGTH;
	i_sellers_count = DEFAULT_TAB_LENGTH;
	pf_file = NULL;
	pc_solution = NULL;
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
		pc_solution = NULL;
		if (bInitTables() == true && bInitMatrixes() == true && bInitMinMaxMatrixes()) bSuccess = true;
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
	delete pc_solution;
}//CMscnProblem::~CMscnProblem()

bool CMscnProblem::bInitTables()
{
	bool bSuccess = true;
	ct_suppliers_contract_prices = new CTable(i_suppliers_count, bSuccess);
	ct_warehouses_contract_prices = new CTable(i_warehouses_count, bSuccess);
	ct_factories_contract_prices = new CTable(i_factories_count, bSuccess);

	ct_sellers_income_value = new CTable(i_sellers_count, bSuccess);

	ct_suppliers_capacity_ammount = new CTable(i_suppliers_count, bSuccess);
	ct_warehouses_capacity_ammount = new CTable(i_warehouses_count, bSuccess);
	ct_factories_capacity_ammount = new CTable(i_factories_count, bSuccess);
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

	cm_factory_matrix = new CMatrix(i_factories_count, i_warehouses_count, bSuccess);
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
		|| bSetEveryMinimalCostTo(&cm_min_items_sent_from_warehouse, i_warehouses_count, i_sellers_count, MINIMAL_XM_VALUE) == false
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
	double dMaxItemsSentFromSupplier = ct_suppliers_capacity_ammount->dGetEX() + MAXIMAL_SUPPLIER_CAPACITY_AMMOUNT / 10;
	double dMaxItemsSentFromFactory = ct_factories_capacity_ammount->dGetEX() + MAXIMAL_FACTORY_CAPACITY_AMMOUNT / 10;
	double dMaxItemsSentFromWarehouse = ct_suppliers_capacity_ammount->dGetEX() + MAXIMAL_WAREHOUSE_CAPACITY_AMMOUNT / 10;
	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			cm_max_items_sent_from_supplier->bSet(dMaxItemsSentFromSupplier, i, j);
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			cm_max_items_sent_from_factory->bSet(dMaxItemsSentFromFactory, i, j);
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			cm_max_items_sent_from_warehouse->bSet(dMaxItemsSentFromWarehouse, i, j);
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

bool CMscnProblem::bGetQuality(CSolution& pcSolution, double& profit)
{
	//if (bConstraintsSatisfied(pdSolution, iSize) == false) return false;
	double shopIncome = 0;
	double totalDeliveryCost = 0;
	double totalContractPrice = 0;
	double totalProfit = 0;

	shopIncome = dCalculateTotalIncomeFromSellers(pcSolution);
	totalDeliveryCost = dMultiplyDeliveryCostPerItemsOrdered(pcSolution);
	totalContractPrice = dCalculateTotalContractPrice(pcSolution);
	profit = shopIncome - totalDeliveryCost - totalContractPrice;

	return true;
}//double CMscnProblem::dGetQuality(double*** pdSolution)

double CMscnProblem::dCalculateTotalIncomeFromSellers(CSolution& pcSolution)
{
	double totalShopIncome = 0;

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			totalShopIncome += pcSolution.pmGetXmMatrix()->dGet(i, j) * ct_sellers_income_value->dGet(j);
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return totalShopIncome;
}//double CMscnProblem::dCalculateTotalIncomeFromSellers(double** pdSolution, int iSize)

double CMscnProblem::dMultiplyDeliveryCostPerItemsOrdered(CSolution& pcSolution)
{
	double totalDeliveryCost = 0;
	totalDeliveryCost += cm_delivery_matrix->dMultiplyMatrixProduct(*pcSolution.pmGetXdMatrix());
	totalDeliveryCost += cm_factory_matrix->dMultiplyMatrixProduct(*pcSolution.pmGetXfMatrix());
	totalDeliveryCost += cm_warehouse_matrix->dMultiplyMatrixProduct(*pcSolution.pmGetXmMatrix());
	return totalDeliveryCost;
}//bool CMscnProblem::bMultiplyDeliveryCostPerItemsOrdered(double** pdSolution)

double CMscnProblem::dCalculateTotalContractPrice(CSolution& pcSolution)
{
	double totalContractPrice = 0;

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			if (pcSolution.pmGetXdMatrix()->dGet(i, j) > 0)
			{
				totalContractPrice += ct_suppliers_contract_prices->dGet(i);
				break;
			}
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			if (pcSolution.pmGetXfMatrix()->dGet(i, j) > 0)
			{
				totalContractPrice += ct_factories_contract_prices->dGet(i);
				break;
			}
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			if (pcSolution.pmGetXmMatrix()->dGet(i, j) > 0)
			{
				totalContractPrice += ct_warehouses_contract_prices->dGet(i);
				break;
			}
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return totalContractPrice;
}//double CMscnProblem::dCalculateTotalContractPrice()

bool CMscnProblem::bConstraintsSatisfied(CSolution& pcSolution)
{
	if (pcSolution.pdGetPdSolution() == NULL|| pcSolution.iGetSize() != i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count
		|| bCheckMaxCapacityOverload(pcSolution) == false || bCheckSufficientProductAmmountDelivery(pcSolution) == false
		|| bCheckMinMaxConstraint(pcSolution) == false || bCheckSolutionForNegativeNumbers(pcSolution) == false) return false;
	return true;
}//bool CMscnProblem::bConstraintsSatisfied(double * pdSolution, int iSize)

bool CMscnProblem::bCheckMinMaxConstraint(CSolution& pcSolution)
{

	for (int i = 0; i < i_suppliers_count; i++)
	{
		for (int j = 0; j < i_factories_count; j++)
		{
			if (pcSolution.pmGetXdMatrix()->dGet(i, j) < cm_min_items_sent_from_supplier->dGet(i, j) || pcSolution.pmGetXdMatrix()->dGet(i, j) > cm_max_items_sent_from_supplier->dGet(i, j)) return false;
		}//for (int j = 0; j < i_factories_count; j++)
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < i_factories_count; i++)
	{
		for (int j = 0; j < i_warehouses_count; j++)
		{
			if (pcSolution.pmGetXfMatrix()->dGet(i, j) < cm_min_items_sent_from_factory->dGet(i, j) || pcSolution.pmGetXfMatrix()->dGet(i, j) > cm_max_items_sent_from_factory->dGet(i, j)) return false;
		}//for (int j = 0; j < i_warehouses_count; j++)
	}//for (int i = 0; i < i_factories_count; i++)

	for (int i = 0; i < i_warehouses_count; i++)
	{
		for (int j = 0; j < i_sellers_count; j++)
		{
			if (pcSolution.pmGetXmMatrix()->dGet(i, j) < cm_min_items_sent_from_warehouse->dGet(i, j) || pcSolution.pmGetXmMatrix()->dGet(i, j) > cm_max_items_sent_from_warehouse->dGet(i, j)) return false;
		}//for (int j = 0; j < i_sellers_count; j++)
	}//for (int i = 0; i < i_warehouses_count; i++)
	return true;
}//bool CMscnProblem::bCheckMinMaxConstraint(double * pdSolution)

bool CMscnProblem::bCheckSolutionForNegativeNumbers(CSolution& pcSolution)
{
	if (pcSolution.iGetSize() != i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count) return false;
	for (int i = 0; i < pcSolution.iGetSize(); i++)
	{
		if (pcSolution.pdGetPdSolution()->dGet(i) < 0) return false;
	}//for (int i = 0; i < iSize; i++)
	return true;
}//bool CMscnProblem::bCheckSolutionForNegativeNumbers(double * pdSolution)

bool CMscnProblem::bCheckMaxCapacityOverload(CSolution& pcSolution)
{	
	double orderedAmmount = 0;
	for (int i = 0; i < i_suppliers_count; i++)
	{
		orderedAmmount = pcSolution.pmGetXdMatrix()->dSumInRowOrColumn('r', i);
		if (orderedAmmount > ct_suppliers_capacity_ammount->dGet(i)) return false;
	}//for (int i = 0; i < i_suppliers_count; i++)

	for (int i = 0; i < i_factories_count; i++)
	{
		orderedAmmount = pcSolution.pmGetXfMatrix()->dSumInRowOrColumn('r', i);
		if (orderedAmmount > ct_factories_capacity_ammount->dGet(i)) return false;
	}//for (int i = 0; i < i_factories_count; i++)

	for (int i = 0; i < i_warehouses_count; i++)
	{
		orderedAmmount = pcSolution.pmGetXmMatrix()->dSumInRowOrColumn('r', i);
		if (orderedAmmount > ct_warehouses_capacity_ammount->dGet(i)) return false;
	}//for (int i = 0; i < i_warehouses_count; i++)

	//warunek na sumaryczna ilosc przedmiotow do danego sklepu
	for (int i = 0; i < i_sellers_count; i++)
	{
		orderedAmmount = pcSolution.pmGetXmMatrix()->dSumInRowOrColumn('c', i);
		if (orderedAmmount > ct_sellers_capacity_ammount->dGet(i)) return false;
	}//for (int j = 0; j < i_sellers_count; j++)
	return true;
}//bool CMscnProblem::bCheckMaxCapacityOverload(double * pdSolution)

bool CMscnProblem::bCheckSufficientProductAmmountDelivery(CSolution& pcSolution)
{
	double quantityOfItemsGoingToTheEnitity = 0;
	double quantityOfItemsGoingOutOfTheEnitity = 0;

	//przechodzimy najpierw po danej fabryce i sprawdzamy ile dostala przedmiorow od dostawcow potem przehcodzimy po magazynach i sprawdzamy ile przedmiotow zostalo wyslanych z fabryki j
	for (int j = 0; j < i_factories_count; j++)
	{
		quantityOfItemsGoingToTheEnitity = pcSolution.pmGetXdMatrix()->dSumInRowOrColumn('c', j);
		quantityOfItemsGoingOutOfTheEnitity = pcSolution.pmGetXfMatrix()->dSumInRowOrColumn('r', j);
		if (quantityOfItemsGoingOutOfTheEnitity > quantityOfItemsGoingToTheEnitity) return false;
	}//for (int i = 0; i < i_factories_count; i++)

	//przechodzimy najpierw po danym magazynie i sprawdzamy ile dostal przedmiotow od fabryki potem przehcodzimy po sklepach i sprawdzamy ile przedmiotow zostalo wyslanych z fabryki j
	for (int j = 0; j < i_warehouses_count; j++)
	{
		quantityOfItemsGoingToTheEnitity = pcSolution.pmGetXfMatrix()->dSumInRowOrColumn('c', j);
		quantityOfItemsGoingOutOfTheEnitity = pcSolution.pmGetXmMatrix()->dSumInRowOrColumn('r', j);
		if (quantityOfItemsGoingOutOfTheEnitity > quantityOfItemsGoingToTheEnitity) return false;
	}//for (int i = 0; i < i_suppliers_count; i++)
	return true;
}//bool CMscnProblem::bCheckSufficientProductAmmountDelivery(double* pdSolution)

 //USUNAC TO?????? poprawic jak u raszczuka? 

double CMscnProblem::dGetMinValueAt(CSolution& pcSolution, int iIndex)
{
	if (iIndex < 0 || iIndex >= pcSolution.iGetSize()) return -1;

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

double CMscnProblem::dGetMaxValueAt(CSolution& pcSolution, int iIndex)
{
	if (iIndex < 0 || iIndex >= pcSolution.iGetSize()) return -1;

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
	if (pfFile == NULL) return false;
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
		|| bWriteCapacitiesToProblemFile(pf_file) == false
		|| bWriteTransportMatrixesToProblemFile(pf_file) == false
		|| bWriteContractValuesToProblemFile(pf_file) == false
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
	fprintf(pfFile, "D %d\n", i_suppliers_count);
	fprintf(pfFile, "F %d\n", i_factories_count);
	fprintf(pfFile, "W %d\n", i_warehouses_count);
	fprintf(pfFile, "S %d\n", i_sellers_count);
	return true;
}//bool CMscnProblem::bWriteEntitiesToProblemFile(FILE* pfFile)

bool CMscnProblem::bWriteCapacitiesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pfFile, "sd\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_suppliers_capacity_ammount->dGet(i));
	}

	fprintf(pfFile, "\nsf\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_factories_capacity_ammount->dGet(i));
	}

	fprintf(pfFile, "\nsm\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_warehouses_capacity_ammount->dGet(i));
	}

	fprintf(pfFile, "\nss\n");
	for (int i = 0; i < i_sellers_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_sellers_capacity_ammount->dGet(i));
	}
	return true;
}//bool CMscnProblem::bWriteCapacitiesToProblemFile(FILE * pfFile)

bool CMscnProblem::bWriteTransportMatrixesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pfFile, "\ncd\n");
	bWriteMatrixToFile(pfFile, cm_delivery_matrix);

	fprintf(pfFile, "cf\n");
	bWriteMatrixToFile(pfFile, cm_factory_matrix);

	fprintf(pfFile, "cm\n");
	bWriteMatrixToFile(pfFile, cm_warehouse_matrix);
	
	return true;

}//bool CMscnProblem::bWriteTransportMatrixesToProblemFile(FILE * pfFile)

bool CMscnProblem::bWriteContractValuesToProblemFile(FILE * pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pfFile, "ud\n");
	for (int i = 0; i < i_suppliers_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_suppliers_contract_prices->dGet(i));
	}

	fprintf(pfFile, "\nuf\n");
	for (int i = 0; i < i_factories_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_factories_contract_prices->dGet(i));
	}

	fprintf(pfFile, "\num\n");
	for (int i = 0; i < i_warehouses_count; i++)
	{
		fprintf(pfFile, "%lf ", ct_warehouses_contract_prices->dGet(i));
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

bool CMscnProblem::bWriteMatrixToFile(FILE* pfFile, CMatrix* pcMatrix)
{
	if (pfFile == NULL) return false;
	for (int i = 0; i < pcMatrix->iGetSizeX(); i++)
	{
		for (int j = 0; j < pcMatrix->iGetSizeY(); j++)
		{
			fprintf(pfFile, "%lf ", pcMatrix->dGet(i, j));
		}
		fprintf(pfFile, "\n");
	}
	return true;
}//bool CSolution::bWriteMatrixToFile(FILE* pfFile, CMatrix* pcMatrix)

void CMscnProblem::vGenerateInstance(int iSeed)
{	
	CRandom cRandom(iSeed);
	vRandomize(cRandom);
}//void CMscnProblem::vGenerateInstance(int iInstanceSeed)

void CMscnProblem::vRandomize(CRandom& cRandom)
{
	ct_suppliers_capacity_ammount->vRandomizeValues(cRandom.vSetRange(MINIMAL_CAPACITY_AMMOUNT, MAXIMAL_SUPPLIER_CAPACITY_AMMOUNT));
	ct_factories_capacity_ammount->vRandomizeValues(cRandom.vSetRange(MINIMAL_CAPACITY_AMMOUNT, MAXIMAL_FACTORY_CAPACITY_AMMOUNT));
	ct_warehouses_capacity_ammount->vRandomizeValues(cRandom.vSetRange(MINIMAL_CAPACITY_AMMOUNT,MAXIMAL_WAREHOUSE_CAPACITY_AMMOUNT));
	ct_sellers_capacity_ammount->vRandomizeValues(cRandom.vSetRange(MINIMAL_CAPACITY_AMMOUNT, MAXIMAL_SELLER_CAPACITY_AMMOUNT));

	ct_suppliers_contract_prices->vRandomizeValues(cRandom.vSetRange(MINIMAL_SUPPLIER_CONTRACT_PRICE_VALUE, MAXIMAL_SUPPLIER_CONTRACT_PRICE_VALUE));
	ct_factories_contract_prices->vRandomizeValues(cRandom.vSetRange(MINIMAL_FACTORY_CONTRACT_PRICE_VALUE, MAXIMAL_FACTORY_CONTRACT_PRICE_VALUE));
	ct_warehouses_contract_prices->vRandomizeValues(cRandom.vSetRange(MINIMAL_WAREHOUSE_CONTRACT_PRICE_VALUE, MAXIMAL_WAREHOUSE_CONTRACT_PRICE_VALUE));
	ct_sellers_income_value->vRandomizeValues(cRandom.vSetRange(MINIMAL_SELLER_INCOME_VALUE, MAXIMAL_SELLER_INCOME_VALUE));

	cm_delivery_matrix->vRandomizeValues(cRandom.vSetRange(MINIMAL_CD_VALUE, MAXIMAL_CD_VALUE));
	cm_factory_matrix->vRandomizeValues(cRandom.vSetRange(MINIMAL_CF_VALUE, MAXIMAL_CF_VALUE));
	cm_warehouse_matrix->vRandomizeValues(cRandom.vSetRange(MINIMAL_CM_VALUE, MAXIMAL_CM_VALUE));

	/*cm_min_items_sent_from_supplier->vRandomizeValues(cRandom.vSetRange(MINIMAL_XD_VALUE, MAXIMAL_XD_VALUE / 2));
	cm_max_items_sent_from_supplier->vRandomizeValues(cRandom.vSetRange(MAXIMAL_XD_VALUE / 2, MAXIMAL_XD_VALUE));

	cm_min_items_sent_from_factory->vRandomizeValues(cRandom.vSetRange(MINIMAL_XF_VALUE, MAXIMAL_XF_VALUE / 2));
	cm_max_items_sent_from_factory->vRandomizeValues(cRandom.vSetRange(MAXIMAL_XF_VALUE / 2, MAXIMAL_XF_VALUE));

	cm_min_items_sent_from_warehouse->vRandomizeValues(cRandom.vSetRange(MINIMAL_XM_VALUE, MAXIMAL_XM_VALUE / 2));
	cm_max_items_sent_from_warehouse->vRandomizeValues(cRandom.vSetRange(MAXIMAL_XM_VALUE / 2, MAXIMAL_XM_VALUE));*/


	cm_min_items_sent_from_supplier->bInitializeMatrixWithValue(MINIMAL_XD_VALUE);
	cm_max_items_sent_from_supplier->vRandomizeValues(cRandom.vSetRange(MAXIMAL_XD_VALUE / 2, MAXIMAL_XD_VALUE));

	cm_min_items_sent_from_factory->bInitializeMatrixWithValue(MINIMAL_XF_VALUE);
	cm_max_items_sent_from_factory->vRandomizeValues(cRandom.vSetRange(MAXIMAL_XF_VALUE / 2, MAXIMAL_XF_VALUE));

	cm_min_items_sent_from_warehouse->bInitializeMatrixWithValue(MINIMAL_XM_VALUE);
	cm_max_items_sent_from_warehouse->vRandomizeValues(cRandom.vSetRange(MAXIMAL_XM_VALUE / 2, MAXIMAL_XM_VALUE));
}

bool CMscnProblem::bGetQuality(double& dResult)
{
	return bGetQuality(*pc_solution, dResult);
}
