#include "CFileLastError.h"


CFileLastError::CFileLastError()
{
	b_last_error = false;

}//CFileLastError::CFileLastError()

CFileLastError::CFileLastError(std::string sFileName)
{
	vOpenFile(sFileName);
}//CFileLastError::CFileLastError(std::string sFileName) 

CFileLastError::~CFileLastError()
{
	if (pf_file != NULL) vCloseFile();

}//CFileLastError::~CFileLastError()


void CFileLastError::vOpenFile(std::string sFileName)
{
	b_last_error = false;

	if (pf_file != NULL)
	{
		std::cout << "File already open" << std::endl;
		b_last_error = true;
		return;
	}//	if (pf_file != NULL)

	pf_file = fopen(sFileName.c_str(), "w+");

	if (pf_file == NULL)
	{
		b_last_error = true;
		std::cout << "Couldn't open file" << std::endl;
	}//	if (pf_file == NULL) 
}//void CFileLastError:: vOpenFile(std::string sFileName)

void CFileLastError::vOpenTenTimes(std::string sFileName)
{

	for (int ii = 0; ii < 10; ii++)
	{
		vOpenFile(sFileName);
		std::cout << b_last_error << std::endl;
	}//for (int ii = 0; ii < 10; ii++)

}//void CFileLastError::vOpenTenTimes()


void CFileLastError::vCloseFile()
{
	b_last_error = false;
	if (pf_file != NULL)
	{
		fclose(pf_file);
		pf_file = NULL;
	}//	if (pf_file != NULL)
	else
	{
		b_last_error = true;
		std::cout << "file already closed" << std::endl;
	}//else	if (pf_file != NULL)

}//void CFileLastError:: vCloseFile(std::string sFileName)

void CFileLastError::vPrintLine(std::string sText)
{
	b_last_error = false;

	if (pf_file == NULL)
	{
		b_last_error = true;
		std::cout << "No open file" << std::endl;
		return;
	}//	if (pf_file != NULL)

	fprintf(pf_file, sText.c_str());


}//void CFileLastError::vPrintLine(std::string sText)

void CFileLastError::vPrintManyLines(std::vector<std::string> sText)
{
	b_last_error = false;

	if (pf_file == NULL)
	{
		b_last_error = true;
		std::cout << "No open file" << std::endl;
		return;
	}//	if (pf_file != NULL)

	for (int ii = 0; ii < sText.size(); ii++)
	{
		vPrintLine(sText[ii]);
		if (b_last_error == true) return;
	}//	for (int ii = 0; ii < sText.size(); ii++)



}//void CFileLastError:: vPrintManyLines(std::vector<std::string> sText)
