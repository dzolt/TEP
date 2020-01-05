#include "CMatrix.h"

CMatrix::CMatrix()
{	
	i_size_x = DEFAULT_MATRIX_SIZE;
	i_size_y = DEFAULT_MATRIX_SIZE;
	bCreateMatrix(&pd_matrix, i_size_x, i_size_y);
}//CMatrix::CMatrix()

CMatrix::CMatrix(unsigned int iSizeX, unsigned int iSizeY, bool& bSuccess)
{	
	if (iSizeX < 1 || iSizeY < 1)
	{
		bSuccess = false;
		CMatrix();
	}//if (iSizeX < 0 || iSizeY < 0)
	else
	{
		i_size_x = iSizeX;
		i_size_y = iSizeY;
		bCreateMatrix(&pd_matrix, i_size_x, i_size_y);
	}//else if (iSizeX < 0 || iSizeY < 0)
}//CMatrix::CMatrix(unsigned int iSizeX, unsigned int iSizeY)

bool CMatrix::bCreateMatrix(double*** pdMatrix, int iSizeX, int iSizeY)
{
	if (iSizeX < 1 || iSizeY < 1) return false;
	(*pdMatrix) = new double*[iSizeX];
	for (int i = 0; i < iSizeX; i++)
	{
		for (int j = 0; j < iSizeY; j++)
		{
			(*pdMatrix)[i] = new double[iSizeY];
		}//for (int j = 0; j < iSizeY; j++)
	}//for (int i = 0; i < iSizeX; i++)
	return true;
}//bool CMatrix::bCreateMatrix(double*** pdMatrix, int iSizeX, int iSizeY)

CMatrix::~CMatrix()
{
	vDelete();
}//CMatrix::~CMatrix()

void CMatrix::vDelete()
{
	for (int i = 0; i < i_size_x; i++)
	{
		delete[] pd_matrix[i];
	}//for (int i = 0; i < i_size_x; i++)
	delete[] pd_matrix;
}//void CMatrix::vDelete()

double CMatrix::dGet(int iSizeX, int iSizeY)
{	
	if (iSizeX < 0 || iSizeX >= i_size_x || iSizeY < 0 || iSizeY >= i_size_y) return -1;
	return pd_matrix[iSizeX][iSizeY];
}//double CMatrix::vGet(int iSizeX, int iSizeY)

bool CMatrix::vInitializeMatrixWithInitialValue(double** pdMatrix, int iSizeX, int iSizeY)
{
	if (iSizeX < 1 || iSizeY < 1) return false;
	for (int i = 0; i < iSizeX; i++)
	{
		for (int j = 0; j < iSizeY; j++)
		{
			(pdMatrix)[i][j] = INITIAL_MATRIX_VALUE;
		}//for (int j = 0; j < iSizeY; j++)
	}//for (int i = 0; i < iSizeX; i++)
	return true;
}//bool CMatrix::vInitializeMatrixWithInitialValue(double*** pdMatrix, int iSizeX, int iSizeY)

void CMatrix::operator=(const CMatrix& pcOther)
{	
	vDelete();
	i_size_x = pcOther.i_size_x;
	i_size_y = pcOther.i_size_y;
	bCreateMatrix(&pd_matrix, i_size_x, i_size_y);
	vCopy(pcOther);
}//void CMatrix::operator=(const CMatrix & pcOther)q

void CMatrix::vCopy(const CMatrix& pcOther)
{
	for (int i = 0; i < i_size_x; i++)
	{
		for (int j = 0; j < i_size_y; j++)
		{
			pd_matrix[i][j] = pcOther.pd_matrix[i][j];
		}//for (int j = 0; j < 0; j++)
	}//	for (int i = 0; i < i_size_x; i++)
}//void CMatrix::vCopy(const CMatrix& pcOther)

bool CMatrix::bSet(double dValue, int iSizeX, int iSizeY)
{
	if (dValue < 0 || iSizeX < 0 || iSizeX >= i_size_x || iSizeY < 0 || iSizeY >= i_size_y) return false;
	pd_matrix[iSizeX][iSizeY] = dValue;
	return true;
}//bool CMatrix::bSet(double dValue, int iSizeX, int iSizeY)

bool CMatrix::bSetSize(int iNewSizeX, int iNewSizeY)
{
	if (iNewSizeX < 1 || iNewSizeY < 1 ) return false;
	unsigned int uiTempXSize = (i_size_x < iNewSizeX) ? i_size_x : iNewSizeX;
	unsigned int uiTempYSize = (i_size_y < iNewSizeY) ? i_size_y : iNewSizeY;

	double** newMatrix;
	bCreateMatrix(&newMatrix, iNewSizeX, iNewSizeY);
	vInitializeMatrixWithInitialValue(newMatrix, iNewSizeX, iNewSizeY);

	for (int i = 0; i < uiTempXSize; i++)
	{
		for (int j = 0; j < uiTempYSize; j++)
		{
			newMatrix[i][j] = pd_matrix[i][j];
		}//for (int j = 0; j < uiTempYSize; j++)
	}//for (int i = 0; i < uiTempXSize; i++)

	vDelete();
	pd_matrix = newMatrix;
	i_size_x = iNewSizeX;
	i_size_y = iNewSizeY;
	return true;
}//bool CMatrix::bSetSize(int iNewSizeX, int iNewSizeY)

double CMatrix::dMultiplyMatrixProduct(const CMatrix& cmOtherMatrix) {
	if (i_size_x != cmOtherMatrix.i_size_x || i_size_y != cmOtherMatrix.i_size_y) return -1;
	double dResult = 0;
	for (int i = 0; i < i_size_x; i++)
	{
		for (int j = 0; j < i_size_y; j++)
		{	
			dResult += pd_matrix[i][j] * cmOtherMatrix.pd_matrix[i][j];
		}//for (int j = 0; j < i_size_y; j++)
	}//for (int i = 0; i < i_size_x; i++)
	return dResult;
}//dMultiplyTwoMatrixesProduct(const CMatrix& cmMatrix1 ,const CMatrix& cmMatrix2);

double CMatrix::dSumInRowOrColumn(char cFlag, int iRowOrColumnIndex)
{
	double result = 0;
	if (iRowOrColumnIndex < 0) return -1;

	if (cFlag == 'c')
	{	
		if (iRowOrColumnIndex >= i_size_x) return -1;
		for (int i = 0; i < i_size_x; i++)
		{
			result += pd_matrix[i][iRowOrColumnIndex];
		}//for (int i = 0; i < i_size_x; i++)
		return result;
	}//	if (cFlag == 'c')
	else if (cFlag == 'r')
	{
		if (iRowOrColumnIndex >= i_size_y) return -1;
		for (int i = 0; i < i_size_y; i++)
		{
			result += pd_matrix[iRowOrColumnIndex][i];
		}//for (int i = 0; i < i_size_y; i++)
		return result;
	}//	else if (cFlag == 'r')
	else return -1;
}//double CMatrix::dSumInRowOrColumn(char cFlag, int irowOrColumnIndex)

void CMatrix::vRandomizeValues(CRandom& cRandom)
{
	for (int i = 0; i < i_size_x; i++)
	{
		for (int j = 0; j < i_size_y; j++)
		{
			pd_matrix[i][j] = cRandom.dGenerateNumber();
		}
	}
}//void CMatrix::vRandomizeValues(CRandom& cRandom)
