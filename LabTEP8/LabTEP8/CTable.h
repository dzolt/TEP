#pragma once
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const string S_DEFAULT_NAME = "DEFAULT_NAME";
const int I_DEFAULT_TABLE_LENGTH = 5;


class CTable
{
public:
	CTable();
	CTable(string sName, int iTabLength);
	CTable(const CTable& pcCopyOfAnObject);
	CTable(CTable&& pcOther);
	~CTable(); // destruktor

	CTable operator+(const CTable& pcOther);
	void operator<<(int offset);
	void operator>>(int offset);
	CTable& operator=(CTable&& pcOther);
	CTable& operator=(const CTable& pcOther);
	static void getCopies() { cout << "copies-: " << copiesNum; };
	static void getMoves() { cout << "moves-: " << moveNum; };

	void v_set_name(string sName);
	bool b_set_new_size(int iTabLength);
	void vCopy(const CTable& pcOther);
	void vMove(CTable& pcOther);

	void v_show_table();
	void v_initialize_array(int* piTab, int iLength);
	void v_mod1(CTable* pcTab, int iNewSize);
	bool b_set_value(int iOffset, int iValue);
	void v_add_table(CTable* pc_table_to_add);
private:
	string s_name;
	int i_tab_length;
	int* pi_tab;
	static int copiesNum;
	static int moveNum;
};// class CTable
