#pragma once
#define DEFAULT_TAB_LENGTH 1
#define INITIAL_TAB_VALUE -1

class CTable
{
public:
	CTable();
	CTable(int iSize, bool& bSuccess);
	~CTable();

	bool bFillTableWithValue(double dValue);
	bool bFillTableWithValue(double** pdTable, double dValue, int iSize);
	bool bSetSize(int iNewSize);


private:
	double* pd_table;
	int i_size;
};//class CTable