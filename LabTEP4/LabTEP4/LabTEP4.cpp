#include "CFileLastError.h"
#include "CFileThrowEx.h"
#include "CFileErrCode.h"
#include "Zakres.h"
#include <string>

bool CFileLastError::b_last_error;
int main()
{
	/*
	std::vector<std::string> v_stringVector = { "vector ", "test ","1 ","2 ","3 ","\n" };

	std::cout << "---------------------------CFileLastError-------------------------------" << std::endl;


	CFileLastError c_file("CFileLastError.txt");

	std::cout<<"\n" << c_file.bGetLastError()<<std::endl;
	c_file.vOpenFile("CFileLastError.txt");
	std::cout << "\n" << c_file.bGetLastError();
	c_file.vPrintLine("test 123\n");
	std::cout << "\n" << c_file.bGetLastError();

	c_file.vPrintManyLines(v_stringVector);
	std::cout << "\n" << c_file.bGetLastError();
	c_file.vCloseFile();
	std::cout << "\n" << c_file.bGetLastError();

	std::cout << "\nTEST CLASS" << std::endl;

	c_file.vOpenTenTimes("CFileLastError");



	/*
	std::cout << "\n\n---------------------------CFileThrowEx-------------------------------" << std::endl;

	try
	{
		CFileThrowEx c_file_throw("CFileThrowEx.txt");
		//c_file_throw.vOpenFile("CFileThrowEx.txt");
		c_file_throw.vPrintLine("test 5632\n");
		c_file_throw.vPrintManyLines(v_stringVector);
		c_file_throw.vCloseFile();
		//c_file_throw.vCloseFile();

		std::cout << "\nTEST CLASS" << std::endl;
		c_file_throw.vOpenTenTimes("CFileThrowEx.txt");

	}
	catch (int iException)
	{
		if (iException == 1) std::cout << "Error: " << iException << " File already open" << std::endl;
		else if (iException == 2) std::cout << "Error: " << iException << " File failed to open" << std::endl;
		else if (iException == 3) std::cout << "Error: " << iException << " File already closed" << std::endl;
	}*/


	/*
	std::cout << "\n\n---------------------------CFileErrCode-------------------------------" << std::endl;
	bool b_result = true;
	std::string fileName = "C:\\Users\\Damian\\source\\repos\\Lab4TEP\\Lab4TEP\\CFileErrCode.txt";
	CFileErrCode c_file_ErrCode(fileName, b_result);
	std::cout << std::boolalpha << b_result << std::endl;;
	CFileErrCode c_file_ErrCode1(fileName, b_result);
	std::cout << b_result << std::endl;;
	//c_file_ErrCode.bOpenFile("CFileErrCode.txt");
	c_file_ErrCode.bPrintLine("test 1002\n");
	c_file_ErrCode.bPrintManyLines(v_stringVector);
	c_file_ErrCode.bCloseFile();
	//c_file_ErrCode.bCloseFile();
	std::cout << "\nTEST CLASS" << std::endl;
	c_file_ErrCode.bOpenTenTimes("CFileErrCode.txt");*/



	try
	{
		char* pc_pointer;
		char c_char[] = "149";
		pc_pointer = c_char;
		const char* cpc_string = "124";

		Zakres x("120", 70, 150);
		Zakres z(pc_pointer, 20, 150);
		Zakres a(cpc_string, 20, 150);
		//x = "42a";
		Zakres y = x;
		std::cout << x.iGetValue() << std::endl;
		std::cout << y.iGetValue() << std::endl;
		y = "123";
		std::cout << y.iGetValue() << std::endl;
		std::cout << z.iGetValue() << std::endl;
		std::cout << a.iGetValue() << std::endl;


	}
	catch (int iException)
	{
		if (iException == 1) std::cout << "Cannot convert to nummber NAN" << std::endl;
		else std::cout << "Number out of bounds exception" << std::endl;
	}
	return 0;
}//int main()
