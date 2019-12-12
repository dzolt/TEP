#include "CTable.h"

CTable::CTable()
{
	pd_table = new double[DEFAULT_TAB_LENGTH];
	i_size = DEFAULT_TAB_LENGTH;
	bFillTableWithValue(INITIAL_TAB_VALUE);
}//CTable::CTable()

CTable::CTable(int iSize, bool& bSuccess)
{	
	if (iSize < 1)
	{
		bSuccess = false;
		CTable();
	}//if (iSize < 1)
	else
	{
		pd_table = new double[iSize];
		i_size = iSize;
		bFillTableWithValue(INITIAL_TAB_VALUE);
	}//else if (iSize < 1)
}//CTable::CTable(int iSize, bool& bSuccess)


CTable::~CTable()
{
	delete pd_table;
}//CTable::~CTable()

bool CTable::bFillTableWithValue(double dValue)
{
	if (dValue < 0) return false;
	for (int i = 0; i < i_size; i++)
	{
		pd_table[i] = dValue;
	}//	for (int i = 0; i < i_size; i++)
	return true;
}//bool CTable::vFillTableWithValue(double dValue)

bool CTable::bFillTableWithValue(double** pdTable, double dValue, int iSize)
{
	if (iSize < 1) return false;
	for (int i = 0; i < iSize; i++)
	{
		(*pdTable)[i] = INITIAL_TAB_VALUE;
	}
	return true;
}//bool CTable::bFillTableWithValue(double** pdTable, double dValue)


bool CTable::bSetSize(int iNewSize)
{
	if (iNewSize < 1) return false;

	double* newTable = new double[iNewSize];
	bFillTableWithValue(&newTable, INITIAL_TAB_VALUE, iNewSize);
	
	unsigned int uiTempValue = (i_size < iNewSize) ? i_size : iNewSize;
	
	for (int i = 0; i < uiTempValue; i++)
	{
		newTable[i] = pd_table[i];
	}
	delete[] pd_table;
	pd_table = newTable;
	i_size = iNewSize;
	return true;
}//bool CTable::bSetSize(int iNewSize)

bool CTable::bSet(double dValue, int iIndex)
{	
	if (dValue < 0 || iIndex < 0 || iIndex >= i_size) return false;
	pd_table[iIndex] = dValue;
	return true;
}//bool CTable::bSet(double dValue, int iIndex)

double CTable::dGet(int iIndex)
{
	if (iIndex < 0 || iIndex >= i_size) return - 1;
	return pd_table[iIndex];
}//double CTable::dGet(int iIndex)

