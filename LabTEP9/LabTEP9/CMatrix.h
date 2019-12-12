#pragma once
#define INITIAL_MATRIX_VALUE -1
#define DEFAULT_MATRIX_SIZE 1


class CMatrix
{
public:
	CMatrix();
	CMatrix(unsigned int iSizeX, unsigned int iSizeY, bool& bSuccess);
	~CMatrix();
	void vDelete();

	double vGet(int iSizeX, int iSizeY);
	unsigned int iGetSizeX() { return i_size_x; };
	unsigned int iGetSizeY() { return i_size_y; };

	bool bSet(double dValue, int iSizeX, int iSizeY);
	bool bSetSize(int iNewSizeX, int iNewSizeY);
	
	bool bInitializeMatrixWithValues(double*** pdMatrix, int iSizeX, int iSizeY, double dValue);
	bool vInitializeMatrixWithInitialValue(double*** pdMatrix, int iSizeX, int iSizeY);


private:
	double** pd_matrix;
	unsigned int i_size_x;
	unsigned int i_size_y;
};
