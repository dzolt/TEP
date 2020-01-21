#pragma once
#include "Constants.h"
#include "CRandom.h"
#include <iostream>

class CMatrix
{
public:
	CMatrix();
	CMatrix(unsigned int iSizeX, unsigned int iSizeY, bool& bSuccess);
	~CMatrix();
	void vDelete();

	bool bCreateMatrix(double*** pdMatrix, int iSizeX, int iSizeY);

	double dGet(int i_xIndex, int i_yIndex);
	unsigned int iGetSizeX() { return i_size_x; };
	unsigned int iGetSizeY() { return i_size_y; };

	bool bSet(double dValue, int i_xIndex, int i_yIndex);
	bool bSetSize(int iNewSizeX, int iNewSizeY);

	bool vInitializeMatrixWithInitialValue(double** pdMatrix, int iSizeX, int iSizeY);
	bool bInitializeMatrixWithValue(double dValue);
	void vRandomizeValues(CRandom& cRandom);
	void operator=(const CMatrix& pcOther);
	void vCopy(const CMatrix& pcOther);

	double dMultiplyMatrixProduct(const CMatrix& cmOtherMatrix);
	double dSumInRowOrColumn(char cFlag, int irowOrColumnIndex);
	bool bSubtractFromRow(int iRowNumber, double dValueToSubtract);
	bool bSubtractFromColumn(int iColumnNumber, double dValueToSubtract);

	void vPrint()
	{
		for (int i = 0; i < i_size_x; i++)
		{
			for (int j = 0; j < i_size_y; j++)
			{
				std::cout << pd_matrix[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
private:
	double** pd_matrix;
	unsigned int i_size_x;
	unsigned int i_size_y;
};
