#pragma once
#define DEFAULT_TAB_LENGTH 1
#define INITIAL_TAB_VALUE -1

class CTable
{
public:
	CTable();
	CTable(int iSize, bool& bSuccess);
	~CTable();

	int iGetSize() { return i_size; };

	bool bFillTableWithValue(double dValue);
	bool bFillTableWithValue(double** pdTable, double dValue, int iSize);
	bool bSetSize(int iNewSize);
	bool bSet(double dValue, int iIndex);
	
	double dGet(int iIndex);


private:
	double* pd_table;
	int i_size;
};//class CTable