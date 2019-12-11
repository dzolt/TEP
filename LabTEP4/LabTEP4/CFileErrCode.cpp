#include "CFileErrCode.h"

CFileErrCode::CFileErrCode()
{

}//CFileErrCode::CFileErrCode()

CFileErrCode::CFileErrCode(std::string sFileName, bool& bResult)
{
	bResult = bOpenFile(sFileName);
}//CFileErrCode::CFileErrCode(std::string sFileName)

CFileErrCode::~CFileErrCode()
{
	if (pf_file != NULL) bCloseFile();
}//CFileErrCode::~CFileErrCode()

bool CFileErrCode::bOpenFile(std::string sFileName)
{
	if (pf_file != NULL)
	{
		std::cout << "File already opened." << std::endl;//mozna tu jeszcze zamknac plik
		return false;
	}//	if (pf_file != NULL)

	pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL)
	{
		std::cout << "Failed to open file" << std::endl;
		return false;
	}//	if (pf_file == NULL)
	return true;

}//void CFileErrCode::vOpenFile(std::string sFileName)

bool CFileErrCode::bOpenTenTimes(std::string sFileName)
{

	for (int ii = 0; ii < 10; ii++)
	{
		std::cout << bOpenFile(sFileName) << std::endl;

	}//	for (int ii = 0; ii < 10; ii++)
	return true;

}//bool CFileErrCode::bOpenTenTimes()


bool CFileErrCode::bCloseFile()
{
	if (pf_file == NULL)
	{
		std::cout << "File already closed" << std::endl;
		return false;
	}//	if (pf_file == NULL)
	fclose(pf_file);
	pf_file = NULL;
	return true;
}//void CFileErrCode::vCloseFile()

bool CFileErrCode::bPrintLine(std::string sText)
{
	if (pf_file == NULL)
	{
		std::cout << "No file to write to" << std::endl;
		return false;
	}//	if (pf_file == NULL)
	fprintf(pf_file, sText.c_str());
	return true;
}//void CFileErrCode::vPrintLine(std::string sText)

bool CFileErrCode::bPrintManyLines(std::vector<std::string> sText)
{
	if (pf_file == NULL)
	{
		std::cout << "No file to write to" << std::endl;
		return false;
	}//	if (pf_file == NULL)
	for (int ii = 0; ii < sText.size(); ii++)
	{
		bPrintLine(sText[ii]);
	}//	for (int ii = 0 : ii < sText.size(); ii++)
	return true;
}//void CFileErrCode::vPrintManyLines(std::vector<std::string> sText)