#pragma warning(disable:4996)
#include <string>
#include <vector>
#include <iostream>

class CFileLastError
{
public:
	CFileLastError();
	CFileLastError(std::string sFileName);
	~CFileLastError();

	static bool bGetLastError() { return (b_last_error); }
	void vOpenFile(std::string sFileName);
	void vOpenTenTimes(std::string sFileName);
	void vCloseFile();
	void vPrintLine(std::string sText);
	void vPrintManyLines(std::vector<std::string> sText);


private:
	FILE *pf_file = NULL;
	static bool b_last_error;



};//class CFileLastError
