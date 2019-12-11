#include "Zakres.h"

Zakres::Zakres(std::string sText, int iFrom, int iTo)
{
	i_from = iFrom;
	i_to = iTo;
	iConvert(sText);
}//Zakres::Zakres(std::string sText, int iFrom, int iTo)

Zakres::Zakres(char* pcText, int iFrom, int iTo)
{
	i_from = iFrom;
	i_to = iTo;
	iConvert(sConvertChar(pcText));
}//Zakres::Zakres(char* pcText, int iFrom, int iTo)

void Zakres::vCreateNumber(int iNumber)
{
	if (iNumber >= i_from && iNumber <= i_to)
	{
		i_value = iNumber;
	}//if (value_to_copy >= i_from && value_to_copy <= i_to)
	else
	{
		throw OUT_OF_RANGE;
	}//else if (iNumber >= i_from && iNumber <= i_to)
}//void Zakres::vCreateNumber(int iNumber)

void Zakres::iConvert(std::string sText)
{
	int i_temp = 0;

	for (int ii = 0; ii < sText.size(); ii++)
	{
		if (sText[ii] < '0' || sText[ii] > '9') throw NAN_ERROR;
		i_temp = i_temp * TEN_CONST;
		i_temp += (int)(sText[ii] - '0');

	}//for (int ii = 0; ii < sText.size(); ii++)

	vCreateNumber(i_temp);

}//int Zakres::iConvert(std::string sText)

std::string Zakres::sConvertChar(char* pc_char)
{
	return pc_char;
}//std::string Zakres::sConvertChar(char* pc_char)

void Zakres::operator=(const Zakres& pcOther)
{
	i_to = pcOther.i_to;
	i_from = pcOther.i_from;
	i_value = pcOther.i_value;
}//Zakres Zakres::operator=(const Zakres& pcOther)//nie musimy tu tworzyc obiektu dlatego, ze nie tworzymy zadnych wskaznikow a tylko kopiujemy pola ktore nie sa od siebie zalezne rownie dobrze mozna by pominac i zostawic shallow coppy

void Zakres::operator=(std::string sText)
{
	iConvert(sText);
}//Zakres operator=(const std::string& sText)