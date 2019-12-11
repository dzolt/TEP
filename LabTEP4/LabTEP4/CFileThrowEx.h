#pragma warning(disable:4996)
#include <string>
#include <vector>
#include <iostream>

#define FILE_AlREADY_OPEN 1;
#define FILE_FAILED_TO_OPEN 2;
#define FILE_ALREADY_CLOSED 3;


class CFileThrowEx
{
public:

	CFileThrowEx();
	CFileThrowEx(std::string sFileName);
	~CFileThrowEx();

	void vOpenFile(std::string sFileName);
	void vOpenTenTimes(std::string sFileName);
	void vCloseFile();
	void vPrintLine(std::string sText);
	void vPrintManyLines(std::vector<std::string> sText);



private:
	FILE *pf_file = NULL;



};//class CFileThrowEx
