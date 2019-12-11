#include "CTable.h"


CTable::CTable()
{
	s_name = S_DEFAULT_NAME;
	cout << "bezp: '" << s_name << "'" << endl;
	i_tab_length = I_DEFAULT_TABLE_LENGTH;
	pi_tab = new int[i_tab_length];
	s_password = S_DEFAULT_PASSWORD;
	v_initialize_array(pi_tab, i_tab_length, I_DEFAULT_NUMBER);
}//CTable()

CTable::CTable(string sName, int iTabLength, string sPassword)
{
	s_name = sName;
	cout << "parametr: '" << s_name << "'" << endl;
	if (iTabLength <= 0)
	{
		cout << "size can't be negative. Setting size to default" << endl;
		iTabLength = I_DEFAULT_TABLE_LENGTH;
	}//	if (iTabLength <= 0) 

	if (sPassword == "")
	{
		s_password = S_DEFAULT_PASSWORD;
	}//if (sPassword == "")
	else if (b_set_new_password(sPassword))
	{
		cout << "Password: " << s_password << endl;
	}//else if (b_set_new_password(sPassword))
	else
	{
		s_password = S_DEFAULT_PASSWORD;
		cout << "Password failed to change setting DEFAULT PASSWORD: " << s_password << endl;
	}//else else if (b_set_new_password(sPassword))

	i_tab_length = iTabLength;
	pi_tab = new int[i_tab_length];
	v_initialize_array(pi_tab, i_tab_length, I_DEFAULT_NUMBER);


}//CTable:: CTable(string sName, int iTabLength)

CTable::CTable(const CTable& pcCopyOfAnObject)
{

	s_name = pcCopyOfAnObject.s_name + "_copy";
	i_tab_length = pcCopyOfAnObject.i_tab_length;
	pi_tab = new int[pcCopyOfAnObject.i_tab_length];
	s_password = pcCopyOfAnObject.s_password;
	for (int i = 0; i < i_tab_length; i++)
	{

		pi_tab[i] = pcCopyOfAnObject.pi_tab[i];

	}//	for (int i = 0; i < i_tab_length; i++)



	cout << "kopiuj: '" << s_name << endl;


}//CTable::CTable(CTable& pcCopyOfAnObject)

void CTable::v_initialize_array(int* piTable, int iSize, int iNumber)
{
	for (int i = 0; i < iSize; i++)
	{
		piTable[i] = iNumber;
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

CTable* CTable::pc_clone()
{

	return new CTable(*this);


}//CTable* CTable:: pc_clone()

void CTable::v_show_table()
{

	for (int i = 0; i < i_tab_length; i++)
	{
		cout << pi_tab[i] << " ";
	}//for (int i = 0; i < this->i_get_tab_length(); i++)

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

void CTable::v_mod2(CTable pcTab, int iNewSize) {

	int* pi_new_table = new int[iNewSize];


	for (int i = 0; i < i_tab_length; i++)
	{
		pi_new_table[i] = pi_tab[i];

	}//for(int i = 0; i < this.i_get_tab_length(); i++)

	for (int i = i_tab_length; i < iNewSize; i++)
	{
		pi_new_table[i] = 30;

	}//for(int i = 0; i < this.i_get_tab_length(); i++)

	delete[] pi_tab;
	pi_tab = pi_new_table;


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
	for (int i = this->i_tab_length; i < this->i_tab_length + pc_table_to_add->i_tab_length; i++)
	{
		newTable[i] = pc_table_to_add->pi_tab[j++];
	}//for (int i = 0; i < pc_table_to_add->i_get_tab_length; i++)

	delete[] this->pi_tab;
	pi_tab = newTable;
	i_tab_length = this->i_tab_length + pc_table_to_add->i_tab_length;

}//void v_add_table(CTable* pc_table_to_add)

bool CTable::b_set_new_password(string sNewPassword)
{
	if (sNewPassword.length() < 5)
	{
		cout << "Password too short. Stayed unchanged. ";

		return false;

	}//if (sNewPassword.length() < 5)
	else
	{
		bool b_is_small_letter = false;
		bool b_is_capital_letter = false;
		bool b_is_digit = false;

		for (int ii = 0; ii < sNewPassword.length(); ii++)
		{

			if (b_is_small_letter == false)
			{
				if (sNewPassword[ii] >= 'a' && sNewPassword[ii] <= 'z')
				{
					b_is_small_letter = true;
				}//if (sNewPassword[ii] >= 'a' && sNewPassword[ii] <= "z")

			}//if (b_is_small_letter == false)

			if (b_is_capital_letter == false)
			{
				if (sNewPassword[ii] >= 'A' && sNewPassword[ii] <= 'Z')
				{
					b_is_capital_letter = true;
				}//if (sNewPassword[ii] >= 'A' && sNewPassword[ii] <= 'Z')

			}//if (b_is_capital_letter == false)

			if (b_is_digit == false)
			{

				if (isdigit(sNewPassword[ii]))//sNewPassword[ii] >= 0 && sNewPassword[ii] <= 9
				{
					b_is_digit = true;
				}//if (sNewPassword[ii] >= 0 && sNewPassword[ii] <= 9)

			}//if (b_is_digit == false)

			if (b_is_digit && b_is_capital_letter && b_is_small_letter)
			{
				cout << "Password change succesfully to: " << sNewPassword << endl;
				s_password = sNewPassword;
				return true;

			}//if (b_is_digit && b_is_capital_letter && b_is_small_letter)

		}//for (int ii = 0; ii < sNewPassword.length(); ii++)

		if (b_is_digit == false)
		{
			cout << "New password requires a number" << endl;
		}//if (b_is_digit == false)
		if (b_is_small_letter == false)
		{
			cout << "New password requires a lower case letter " << endl;
		}//if (b_is_small_letter == false)
		if (b_is_capital_letter == false)
		{
			cout << "New password requires a capital letter" << endl;
		}//if (b_is_capital_letter == false)

		return false;

	}//else if (sNewPassword.length() < 5)



}//bool CTable::b_set_new_password(string sNewPassword)

bool CTable::b_change_password(string sNewPassword)
{
	if (b_is_different(sNewPassword))
	{
		if (b_set_new_password(sNewPassword))
		{
			return true;

		}//if (b_set_new_password(sNewPassword))
		else
		{
			cout << "Failed to change password" << endl;
			return false;
		}//else if (b_set_new_password(sNewPassword))
	}//if (is_different(string sNewPassword))
	else
	{
		cout << "Password doesn't differ from the old one" << endl;
		return false;
	}//else if (is_different(string sNewPassword))
}//bool CTable::b_change_password(string sNewPassword)

bool CTable::b_is_different(string sNewPassword)
{
	int i_count_different_characters = 0;

	for (int ii = 0; ii < sNewPassword.length(); ii++)
	{
		if (s_password[ii] != sNewPassword[ii])
		{
			i_count_different_characters++;
		}//if (s_password[ii] == sNewPassword[ii])
		if (i_count_different_characters >= 2)
		{
			return true;
		}
	}//for (int ii = 0; ii < sNewPassword.length(); ii++

	return false;
}//bool CTable::b_is_different(string sNewPassword)


CTable CTable::operator+(const CTable& pcOther)
{
	CTable c_new_object(this->s_name + "+" + pcOther.s_name, i_tab_length + pcOther.i_tab_length, "");
	for (int ii = 0; ii < i_tab_length; ii++)
	{
		c_new_object.pi_tab[ii] = pi_tab[ii];
	}//for (int ii = 0; i < i_tab_length(); ii++)
	int jj = 0;
	for (int ii = i_tab_length; ii < c_new_object.i_tab_length; ii++)
	{
		c_new_object.pi_tab[ii] = pcOther.pi_tab[jj++];
	}
	return c_new_object;
}//CTable CTable::operator+(CTable &pcOther)

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

string CTable::s_get_password()
{
	return s_password;
}//string CTable::s_get_password()


CTable:: ~CTable()
{

	cout << "usuwam: '" << s_name << endl;
	delete [] pi_tab;


}//CTable:: ~CTable()
