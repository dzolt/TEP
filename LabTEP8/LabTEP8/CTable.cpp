#include "CTable.h"
int CTable::copiesNum = 0;
int CTable::moveNum = 0;

CTable::CTable()
{
	s_name = S_DEFAULT_NAME;
	cout << "bezp: '" << s_name << "'" << endl;
	i_tab_length = I_DEFAULT_TABLE_LENGTH;
	pi_tab = new int[i_tab_length];
	v_initialize_array(pi_tab, i_tab_length);
}//CTable()

CTable::CTable(string sName, int iTabLength)
{
	s_name = sName;
	cout << "parametr: '" << s_name << "'" << endl;
	if (iTabLength <= 0)
	{
		cout << "size can't be negative. Setting size to default" << endl;
		iTabLength = I_DEFAULT_TABLE_LENGTH;
	}//	if (iTabLength <= 0) 

	i_tab_length = iTabLength;
	pi_tab = new int[i_tab_length];
	v_initialize_array(pi_tab, i_tab_length);
}//CTable:: CTable(string sName, int iTabLength)

CTable::CTable(const CTable& pcCopyOfAnObject)
{	
	vCopy(pcCopyOfAnObject);
}//CTable::CTable(CTable& pcCopyOfAnObject)

CTable::CTable(CTable&& pcOther)
{
	vMove(pcOther);
	std::cout << "move";
}//CTable::CTable(CTable&& pcOther)

void CTable::vMove(CTable& pcOther)
{	
	moveNum++;
	std::cout << "move " << std::endl;
	s_name = pcOther.s_name;
	pi_tab = pcOther.pi_tab;
	i_tab_length = pcOther.i_tab_length;
	pcOther.pi_tab = NULL;
}//void CTable::vMove(CTable&& pcOther)

void CTable::vCopy(const CTable& pcOther)
{	
	copiesNum++;
	std::cout << "copy " << std::endl;
	s_name = pcOther.s_name + "_copy";
	i_tab_length = pcOther.i_tab_length;
	pi_tab = new int[pcOther.i_tab_length];
	for (int i = 0; i < i_tab_length; i++)
	{
		pi_tab[i] = pcOther.pi_tab[i];
	}//	for (int i = 0; i < i_tab_length; i++)
	cout << "kopiuj: '" << s_name << endl;
}//void CTable::pcCopy()

void CTable::v_initialize_array(int* piTable, int iSize)
{
	for (int i = 0; i < iSize; i++)
	{
		piTable[i] = i;
	}//for (int i = 0; i < iSize; i++)
}//void CTable::v_initialize_array(int* piTable, int iSize, int iNumber)

void CTable::v_set_name(string sName)
{
	s_name = sName;
}//void CTable::v_set_name(string sName)

bool CTable::b_set_new_size(int iTabLength)
{
	if (iTabLength <= 0)
	{
		cout << "neg number" << endl;
		return false;
	}//if(iTabLength < 0)
	else
	{
		int* newTable = new int[iTabLength];
		for (int i = 0; (i < i_tab_length && i < iTabLength); i++)
		{
			newTable[i] = this->pi_tab[i];

		}//for(int i = 0; i < this.i_get_tab_length(); i++)
		delete[] pi_tab;
		pi_tab = newTable;
		i_tab_length = iTabLength;
		//cout<<"completed"<<endl;
		return true;
	}//else if(iTabLength < 0)

}//bool CTable:: b_set_new_size(int iTabLength)

void CTable::v_show_table()
{
	for (int i = 0; i < i_tab_length; i++)
	{
		cout << pi_tab[i] << " ";
	}//for (int i = 0; i < this->i_get_tab_length(); i++)
	cout << "\n";
}//void CTable:: v_show_table(int* piTable)

void CTable::v_mod1(CTable* pcTab, int iNewSize) {

	int* pi_new_table = new int[iNewSize];
	for (int i = 0; i < this->i_tab_length; i++)
	{
		pi_new_table[i] = pi_tab[i];

	}//for(int i = 0; i < this.i_get_tab_length(); i++)
	for (int i = i_tab_length; i < iNewSize; i++)
	{
		pi_new_table[i] = 30;

	}//for(int i = 0; i < this.i_get_tab_length(); i++)

	delete[] pi_tab;
	pi_tab = pi_new_table;
	i_tab_length = iNewSize;

}//void CTable:: v_mod1(CTable* pcTab, int iNewSize) {

bool CTable::b_set_value(int iOffset, int iValue)
{
	if (iOffset < 0 || iOffset >= i_tab_length)
	{
		cout << "wrong number";
		return false;
	}//if(iOffset < 0)
	else
	{
		pi_tab[iOffset] = iValue;
		return true;
	}//else if(iOffset < 0)
}// bool b_set_value(int iOffset, int iValue)

void CTable::v_add_table(CTable* pc_table_to_add)
{
	int* newTable = new int[this->i_tab_length + pc_table_to_add->i_tab_length];
	for (int i = 0; i < this->i_tab_length; i++)
	{
		newTable[i] = this->pi_tab[i];
	}//for (int i = 0; i < this->i_get_tab_length; i++)
	int j = 0;
	for (int i = i_tab_length; i < i_tab_length + pc_table_to_add->i_tab_length; i++)
	{
		newTable[i] = pc_table_to_add->pi_tab[j++];
	}//for (int i = 0; i < pc_table_to_add->i_get_tab_length; i++)

	delete[] this->pi_tab;
	pi_tab = newTable;
	i_tab_length = this->i_tab_length + pc_table_to_add->i_tab_length;
}//void v_add_table(CTable* pc_table_to_add)

CTable CTable::operator+(const CTable& pcOther)
{
	CTable c_new_object(s_name + "+" + pcOther.s_name, i_tab_length + pcOther.i_tab_length);
	for (int ii = 0; ii < i_tab_length; ii++)
	{
		c_new_object.pi_tab[ii] = pi_tab[ii];
	}//for (int ii = 0; i < i_tab_length(); ii++)
	int jj = 0;
	for (int ii = i_tab_length; ii < c_new_object.i_tab_length; ii++)
	{
		c_new_object.pi_tab[ii] = pcOther.pi_tab[jj++];
	}
	return (c_new_object);
}//CTable CTable::operator+(CTable &pcOther)

CTable& CTable::operator=(const CTable& pcOther)
{	
	delete[] pi_tab;
	vCopy(pcOther);
	return *this;
}//CTable& CTable::operator=(const CTable& pcOther)


CTable& CTable::operator=(CTable&& pcOther)
{	
	delete[] pi_tab;
	vMove(pcOther);
	return *this;
}//CTable CTable::operator=(const CTable&& pcOther)

void CTable::operator<<(int offset)//[1,2,3,4,5,6,7] (2) [3,4,5,6,7,0,0]
{
	for (int i = 0; i < i_tab_length - offset; i++)
	{
		pi_tab[i] = pi_tab[i + offset];
		pi_tab[i + offset] = 0;
	}//	for (int i = 0; i < i_tab_length; i++)
}//CTable CTable::operator<<(CTable& piTable)

void CTable::operator>>(int offset)//[1,2,3,4,5,6,7] (2) [0,0,1,2,3,4,5]
{
	for (int i = i_tab_length - 1; i >= 0 + offset; i--)
	{
		pi_tab[i] = pi_tab[i - offset];
		pi_tab[i - offset] = 0;
	}//	for (int i = i_tab_length - 1; i >= 0 + offset; i--)
}//CTable CTable::operator>>(CTable& piTable)

CTable:: ~CTable()
{
	cout << "usuwam: '" << s_name << endl;
	delete[] pi_tab;
}//CTable:: ~CTable()