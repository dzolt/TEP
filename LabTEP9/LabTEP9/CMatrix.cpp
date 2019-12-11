#include "CMatrix.h"




CMatrix::CMatrix()
{
	i_size_x = DEFAULT_MATRIX_SIZE;
	i_size_y = DEFAULT_MATRIX_SIZE;
	bInitializeMatrixWithValues(&pd_matrix, i_size_x, i_size_y, INITIAL_MATRIX_VALUE);
}

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
		bInitializeMatrixWithValues(&pd_matrix, i_size_x, i_size_y, INITIAL_MATRIX_VALUE);
	}//else if (iSizeX < 0 || iSizeY < 0)
}//CMatrix::CMatrix(unsigned int iSizeX, unsigned int iSizeY)

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

double CMatrix::vGet(int iSizeX, int iSizeY)
{	
	if (iSizeX < 0 || iSizeX >= i_size_x || iSizeY < 0 || iSizeY >= i_size_y) return -1;
	return pd_matrix[iSizeX][iSizeY];
}//double CMatrix::vGet(int iSizeX, int iSizeY)

bool CMatrix::bInitializeMatrixWithValues(double*** pdMatrix, int iSizeX, int iSizeY, double dValue)
{	
	if (iSizeX < 1 || iSizeY < 1) return false;
	*pdMatrix = new double*[i_size_x];

	for (int i = 0; i < i_size_x; i++)
	{
		(*pdMatrix)[i] = new double[i_size_y];
		for (int j = 0; j < i_size_y; j++)
		{
			(*pdMatrix)[i][j] = dValue;
		}//for (int j = 0; j < iSizeY; j++)
	}//for (int i = 0; i < iSizeX; i++)
}//void CMatrix::vInitializeMatrix(double dValue)

bool CMatrix::bSet(double dValue, int iSizeX, int iSizeY)
{
	if (dValue < 0 || iSizeX < 0 || iSizeX >= i_size_x || iSizeY < 0 || iSizeY >= i_size_y) return false;
	pd_matrix[iSizeX][iSizeY] = dValue;
	return true;
}//bool CMatrix::bSet(double dValue, int iSizeX, int iSizeY)

bool CMatrix::bSetSize(int iNewSizeX, int iNewSizeY)
{
	if (iNewSizeX < 1 || iNewSizeY < 1) return false;
	unsigned int uiTempXSize = (i_size_x < iNewSizeX) ? i_size_x : iNewSizeX;
	unsigned int uiTempYSize = (i_size_y < iNewSizeY) ? i_size_y : iNewSizeY;

	double** newMatrix;
	bInitializeMatrixWithValues(&newMatrix, iNewSizeX, iNewSizeY, INITIAL_MATRIX_VALUE);

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
}//bool CMatrix::bSetSize(int iNewSizeX, int iNewSizeY)


