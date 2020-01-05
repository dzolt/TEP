#include "CSolution.h"


CSolution::CSolution()
{
	i_suppliers_count = DEFAULT_ENTITY_NUMBER;
	i_factories_count = DEFAULT_ENTITY_NUMBER;
	i_warehouses_count = DEFAULT_ENTITY_NUMBER;
	i_sellers_count = DEFAULT_ENTITY_NUMBER;
	i_size = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count;
	bool bSuccess = true;
	pd_solution = new CTable(i_size, bSuccess);
	cm_xdMatrix = new CMatrix();
	cm_xfMatrix = new CMatrix();
	cm_xmMatrix = new CMatrix();
}//CSolution::CSolution()

CSolution::CSolution(unsigned int uiSuppliersCount, unsigned int uiFactoriesCount, unsigned int uiWarehousesCount, unsigned int uiSellersCount)
{
	bool bSuccess = true;
	i_suppliers_count = uiSuppliersCount;
	i_factories_count = uiFactoriesCount;
	i_warehouses_count = uiWarehousesCount;
	i_sellers_count = uiSellersCount;

	i_size = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count;
	pd_solution = new CTable(i_size, bSuccess);

	cm_xdMatrix = new CMatrix(i_suppliers_count, i_factories_count, bSuccess);
	cm_xfMatrix = new CMatrix(i_factories_count, i_warehouses_count, bSuccess);
	cm_xmMatrix = new CMatrix(i_warehouses_count, i_sellers_count, bSuccess);
	if (bSuccess == false) CSolution();
}//CSolution::CSolution(unsigned int uiSuppliersCount, unsigned int uiFactoriesCount, unsigned int uiWarehousesCount, unsigned int uiSellersCount)

CSolution::~CSolution()
{
	delete pd_solution;

	delete cm_xdMatrix;
	delete cm_xfMatrix;
	delete cm_xmMatrix;

	delete pf_file;
}//CSolution::~CSolution()

void CSolution::vFillMatrixWithSolutionValues(CMatrix* cmMatrix, int iSolutionStartingIndex)
{
	for (int i = 0; i < cmMatrix->iGetSizeX(); i++)
	{
		for (int j = 0; j < cmMatrix->iGetSizeY(); j++)
		{
			cmMatrix->bSet(pd_solution->dGet(iSolutionStartingIndex++), i, j);
		}//		for (int j = 0; j < cmMatrix->iGetSizeY(); j++)
	}//	for (int i = 0; i < cmMatrix->iGetSizeX(); i++)
}//void CSolution::vFillMatrixWithSolutionValues(CMatrix* cmMatrix, int iSolutionStartingIndex)

void CSolution::vFillMatrixes()
{	
	int iStartingIndexOfFactoryMatrix = i_suppliers_count * i_factories_count;
	int iStartingIndexOfWarehouseMatrix = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count;
	vFillMatrixWithSolutionValues(cm_xdMatrix, 0);
	vFillMatrixWithSolutionValues(cm_xfMatrix, iStartingIndexOfFactoryMatrix);
	vFillMatrixWithSolutionValues(cm_xmMatrix, iStartingIndexOfWarehouseMatrix);
}//void CSolution::vFillMatrixes()
bool CSolution::bReadSolutionFromFile(std::string sFileName)
{
	if (pf_file != NULL) fclose(pf_file);
	pf_file = fopen(sFileName.c_str(), "r");
	if (pf_file == NULL) return false;

	bReadEntitiesFromSolutionFile(pf_file);

	pd_solution->bSetSize(i_size);

	bReadSolutionValuesFromSolutionFile(pf_file);

	fclose(pf_file);
	pf_file = NULL;
	if (pf_file != NULL) return false;
	return true;
}//bool CMscnProblem::bReadSolutionToFile(std::string sFileName)

bool CSolution::bReadEntitiesFromSolutionFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;
	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	int iTempValue;
	
	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iTempValue);
	i_suppliers_count = iTempValue;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iTempValue);
	i_factories_count = iTempValue;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iTempValue);
	i_warehouses_count = iTempValue;

	fscanf(pf_file, "%s", cCurrentLineLoaded);
	fscanf(pf_file, "%i", &iTempValue);
	i_sellers_count = iTempValue;
	
	i_size = i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count;
	cm_xdMatrix->bSetSize(i_suppliers_count, i_factories_count);
	cm_xfMatrix->bSetSize(i_factories_count, i_warehouses_count);
	cm_xmMatrix->bSetSize(i_warehouses_count, i_sellers_count);
	return true;
}//bool CMscnProblem::bReadEntitiesFromSolutionFile(FILE* pfFile)

bool CSolution::bReadSolutionValuesFromSolutionFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;

	char cCurrentLineLoaded[MAX_CHARACTER_NUMBER];
	double dTempValue;

	for (int i = 0; i < i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count + i_warehouses_count * i_sellers_count; i++)
	{
		if (i == 0 || i == i_suppliers_count * i_factories_count || i == i_suppliers_count * i_factories_count + i_factories_count * i_warehouses_count)
		{
			fscanf(pf_file, "%s", cCurrentLineLoaded);
		}
		fscanf(pfFile, "%lf", &dTempValue);
		pd_solution->bSet(dTempValue, i);
	}
	vFillMatrixes();
	return true;
}//bool CSolution::bReadSolutionValuesFromSolutionFile(FILE* pfFile)

bool CSolution::bWriteSolutionToFile(std::string sFileName)
{
	if (pf_file != NULL) fclose(pf_file);
	pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) return false;

	if (
		bWriteEntitiesToSolutionFile(pf_file) == false
		|| bWriteSolutionValuesToSolutionFile(pf_file) == false
		) return false;

	fclose(pf_file);
	pf_file = NULL;
	if (pf_file != NULL) return false;
	return true;
}//bool CMscnProblem::bWriteSolutionToFile(std::string sFileName)

bool CSolution::bWriteEntitiesToSolutionFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;
	fprintf(pfFile, "D %d\n", i_suppliers_count);
	fprintf(pfFile, "F %d\n", i_factories_count);
	fprintf(pfFile, "M %d\n", i_warehouses_count);
	fprintf(pfFile, "S %d\n", i_sellers_count);
	return true;
}//bool CMscnProblem::bWriteEntitiesToSolutionFile(FILE* pfFile)

bool CSolution::bWriteSolutionValuesToSolutionFile(FILE* pfFile)
{
	if (pfFile == NULL) return false;
	int iCurrentIndex = 0;
	int iLastIndex = 0;

	fprintf(pfFile, "xd\n");
	bWriteSolutionMatrixToFile(pfFile, cm_xdMatrix);
	
	fprintf(pfFile, "xf\n");
	bWriteSolutionMatrixToFile(pfFile, cm_xfMatrix);

	fprintf(pfFile, "xm\n");
	bWriteSolutionMatrixToFile(pfFile, cm_xmMatrix);

	return true;
}//bool CMscnProblem::bWriteSolutionValuesToSolutionFile(FILE* pfFile)

bool CSolution::bWriteSolutionMatrixToFile(FILE* pfFile, CMatrix* pcMatrix)
{
	if (pfFile == NULL) return false;
	for (int i = 0; i < pcMatrix->iGetSizeX(); i++)
	{
		for (int j = 0; j < pcMatrix->iGetSizeY(); j++)
		{
			fprintf(pfFile, "%lf ", pcMatrix->dGet(i,j));
		}
		fprintf(pfFile, "\n");
	}
	return true;
}//bool CSolution::bWriteMatrixToFile(FILE* pfFile, CMatrix* pcMatrix)

