#pragma once
#define INITIAL_MATRIX_VALUE -1
#define DEFAULT_MATRIX_SIZE 1
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
	
	bool bInitializeMatrixWithValue(double** pdMatrix, int iSizeX, int iSizeY, double dValue);
	bool vInitializeMatrixWithInitialValue(double** pdMatrix, int iSizeX, int iSizeY);
	bool vInitializeMatrixWithValue(int iSizeX, int iSizeY, double dValue);

	void operator=(const CMatrix& pcOther);
	void vCopy(const CMatrix& pcOther);

	double dMultiplyMatrixProduct(const CMatrix& cmOtherMatrix);
	double dSumInRowOrColumn(char cFlag, int irowOrColumnIndex);

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
