#pragma warning(disable:4996)
#include <string>
#include <vector>
#include <iostream>

class CFileErrCode
{
public:

	CFileErrCode();
	CFileErrCode(std::string sFileName, bool& bResult);
	~CFileErrCode();

	bool bOpenFile(std::string sFileName);
	bool bOpenTenTimes(std::string sFileName);
	bool bCloseFile();
	bool bPrintLine(std::string sText);
	bool bPrintManyLines(std::vector<std::string> sText);


private:
	FILE *pf_file = NULL;



};//class CFileErrCode
