#pragma once
#include<iostream>
#include"CRandom.h"
#include "Constants.h"

class CTable
{
public:
	CTable();
	CTable(int iSize, bool& bSuccess);
	~CTable();

	int iGetSize() { return i_size; };
	double dGetEX();
	bool bFillTableWithInitialValue(double** pdTable, int iSize);
	bool bFillTableWithValue(double dValue);
	bool bSetSize(int iNewSize);
	bool bSet(double dValue, int iIndex);
	
	double dGet(int iIndex);

	void operator=(const CTable& pcOther);
	void vCopy(const CTable& pcOther);

	void vRandomizeValues(CRandom& cRandom);

	void vPrint() {
		for (int i = 0; i < i_size; i++)
		{
			std::cout << pd_table[i] << " ";
		}
	}
private:
	double* pd_table;
	int i_size;
};//class CTable