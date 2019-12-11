#include "CMySmartPointer.h"
#include <iostream>




void func()
{	
	int i_number = 7;
	int* x = new int[5];
	x[0] = 1;
	int* y = new int[5];
	y[0] = 2;
	CMySmartPointer<int> c_point(x);
	CMySmartPointer<int> c_point2(x);
	CMySmartPointer<int> c_point3(c_point);
	
	c_point = c_point2;
}



int main()
{
	func();
	return 0;
}
