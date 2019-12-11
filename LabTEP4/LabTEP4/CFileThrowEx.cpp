#include "CFileThrowEx.h"

CFileThrowEx::CFileThrowEx()
{

}//CFileThrowEx::CFileThrowEx()


CFileThrowEx::CFileThrowEx(std::string sFileName)
{
	vOpenFile(sFileName);
}//CFileThrowEx::CFileThrowEx(std::string sFileName)

CFileThrowEx::~CFileThrowEx()
{
	if (pf_file != NULL) vCloseFile();
}//CFileThrowEx::~CFileThrowEx()


void CFileThrowEx::vOpenFile(std::string sFileName)
{
	if (pf_file != NULL) throw FILE_AlREADY_OPEN;
	pf_file = fopen(sFileName.c_str(), "w+");
	if (pf_file == NULL) throw FILE_FAILED_TO_OPEN;
}//void CFileThrowEx::vOpenFile(std::string sFileName)

void CFileThrowEx::vOpenTenTimes(std::string sFileName)
{
	for (int ii = 0; ii < 10; ii++)
	{
		vOpenFile(sFileName);
	}//	for (int ii = 0; ii < 10; ii++)

}//void CFileThrowEx::vOpenTenTimes(std::string sFileName)



void CFileThrowEx::vCloseFile()
{
	if (pf_file == NULL) throw FILE_ALREADY_CLOSED;
	fclose(pf_file);
	pf_file = NULL;
}//void CFileThrowEx::vCloseFile()


void CFileThrowEx::vPrintLine(std::string sText)
{
	if (pf_file == NULL) throw FILE_FAILED_TO_OPEN;
	fprintf(pf_file, sText.c_str());
}//void CFileThrowEx::vPrintLine(std::string sText)


void CFileThrowEx::vPrintManyLines(std::vector<std::string> sText)
{
	if (pf_file == NULL) throw FILE_FAILED_TO_OPEN;
	for (int ii = 0; ii < sText.size(); ii++)
	{
		vPrintLine(sText[ii]);
	}//	for (int ii = 0 : ii < sText.size(); ii++)
}//void CFileThrowEx::vPrintManyLines(std::vector<std::string> sText)

