#pragma warning(disable:4996)
#include"CMatrix.h"
#include "CTable.h"
#include <iostream>
#include "Constants.h"

class CSolution {

public:
	CSolution();
	CSolution(unsigned int uiSuppliersCount, unsigned int uiFactoriesCount, unsigned int uiWarehousesCount, unsigned int uiSellersCount);
	~CSolution();

	unsigned int iGetSize() { return i_size; };
	CTable* pdGetPdSolution() { return pd_solution; };
	CMatrix* pmGetXdMatrix() { return(cm_xdMatrix); };
	CMatrix* pmGetXfMatrix() { return(cm_xfMatrix); };
	CMatrix* pmGetXmMatrix() { return(cm_xmMatrix); };

	bool bWriteSolutionToFile(std::string sFileName);
	bool bReadSolutionFromFile(std::string sFileName);

private:
	bool bReadEntitiesFromSolutionFile(FILE* pfFile);
	bool bReadSolutionValuesFromSolutionFile(FILE* pfFile);

	bool bWriteEntitiesToSolutionFile(FILE* pfFile);
	bool bWriteSolutionValuesToSolutionFile(FILE* pfFile);
	bool bWriteSolutionMatrixToFile(FILE* pfFile, CMatrix* pcMatrix);
	void vFillMatrixes();
	void vFillMatrixWithSolutionValues(CMatrix* cmMatrix, int iSolutionStartingIndex);

	unsigned int i_suppliers_count;
	unsigned int i_factories_count;
	unsigned int i_sellers_count;
	unsigned int i_warehouses_count;

	int i_size;

	CTable* pd_solution;
	CMatrix* cm_xdMatrix;
	CMatrix* cm_xfMatrix;
	CMatrix* cm_xmMatrix;

	FILE* pf_file;
};