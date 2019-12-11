#pragma warning(disable:4996)
#include <string>
#include <iostream>

#define NAN_ERROR 1;
#define OUT_OF_RANGE 2;
const int TEN_CONST = 10;

class Zakres
{
public:
	Zakres(std::string sText, int iFrom, int iTo);
	Zakres(char* pcText, int iFrom, int iTo);
	~Zakres() {};
	void operator=(std::string sText);
	void operator=(const Zakres& pcOther);
	void iConvert(std::string sText);
	std::string sConvertChar(char* pc_char);
	int iGetValue() { return i_value; };
	void vCreateNumber(int iNumber);

private:
	int i_from;
	int i_to;
	int i_value;

};//class Zakres