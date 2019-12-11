#pragma once
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int I_DEFAULT_NUMBER = 5;
const string S_DEFAULT_NAME = "DEFAULT_NAME";
const int I_DEFAULT_TABLE_LENGTH = 5;
const string S_DEFAULT_PASSWORD = "Pass123";

class CTable
{
public:
	CTable();
	CTable(string sName, int iTabLength, string sPassword);
	CTable(const CTable& pcCopyOfAnObject);
	~CTable(); // destruktor

	CTable operator+(const CTable& pcOther);
	void operator<<(int offset);
	void operator>>(int offset);
	CTable* pc_clone();

	void v_set_name(string sName);
	bool b_set_new_size(int iTabLength);

	string s_get_password();

	void v_show_table();//was (int* piTable)
	void v_initialize_array(int* piTab, int iLength, int iNumber);
	void v_mod1(CTable* pcTab, int iNewSize);
	void v_mod2(CTable pcTab, int iNewSize);
	bool b_set_value(int iOffset, int iValue);
	void v_add_table(CTable* pc_table_to_add);
	bool b_set_new_password(string sNewPassword);
	bool b_change_password(string sNewPassword);
	bool b_is_different(string sNewPassword);
private:
	string s_name;
	int i_tab_length;
	int* pi_tab;
	string s_password;



};// class CTable
