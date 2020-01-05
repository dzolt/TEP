#pragma warning(disable:4996)
#include"CMatrix.h"
#include "CTable.h"
#include <iostream>
<<<<<<< HEAD

=======
>>>>>>> bf207b95ddbb7d623144108150addb7e6039bb6e
#define DEFAULT_ENTITY_NUMBER 1
#define MAX_CHARACTER_NUMBER 1000

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

<<<<<<< HEAD
=======
	bool bWriteSolutionMatrixToFile(FILE* pfFile, CMatrix* pcMatrix);
>>>>>>> bf207b95ddbb7d623144108150addb7e6039bb6e
private:
	bool bReadEntitiesFromSolutionFile(FILE* pfFile);
	bool bReadSolutionValuesFromSolutionFile(FILE* pfFile);

	bool bWriteEntitiesToSolutionFile(FILE* pfFile);
	bool bWriteSolutionValuesToSolutionFile(FILE* pfFile);
<<<<<<< HEAD
	bool bWriteSolutionMatrixToFile(FILE* pfFile, CMatrix* pcMatrix);
=======
>>>>>>> bf207b95ddbb7d623144108150addb7e6039bb6e
	void vFillMatrixes();
	void vFillMatrixWithSolutionValues(CMatrix* cmMatrix, int iSolutionStartingIndex);

	unsigned int i_suppliers_count;
	unsigned int i_factories_count;
	unsigned int i_sellers_count;
	unsigned int i_warehouses_count;

<<<<<<< HEAD
	int i_size;
=======
	unsigned int i_size;
>>>>>>> bf207b95ddbb7d623144108150addb7e6039bb6e

	CTable* pd_solution;
	CMatrix* cm_xdMatrix;
	CMatrix* cm_xfMatrix;
	CMatrix* cm_xmMatrix;

	FILE* pf_file;
};