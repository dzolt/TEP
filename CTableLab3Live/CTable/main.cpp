#include "CTable.h"
#include <string>
#include <cstring>

using namespace std;

int main()
{


	

	cout << "\n\n---------------------------------------LAB 3---------------------------" << endl;

	CTable c_tab_0;
	CTable c_tab_1;

	c_tab_0.v_set_name("tab0");
	c_tab_1.v_set_name("tab1");


	c_tab_0.b_set_new_size(6);
	c_tab_1.b_set_new_size(4);
	c_tab_0.v_show_table();
	cout << endl << endl;;
	c_tab_1.v_show_table();
	cout << endl << endl;;

	c_tab_0.b_set_value(0, 1);
	c_tab_0.b_set_value(1, 2);
	c_tab_0.b_set_value(2, 3);
	c_tab_0.b_set_value(3, 4);
	c_tab_0.b_set_value(4, 5);
	c_tab_0.b_set_value(5, 6);

	c_tab_1.b_set_value(0, 51);
	c_tab_1.b_set_value(1, 52);
	c_tab_1.b_set_value(2, 53);
	c_tab_1.b_set_value(3, 54);

	cout << "\nc_tab_0 table: " << endl;
	c_tab_0.v_show_table();
	cout << endl << endl;
	cout << "\nc_tab_1 table: " << endl;
	c_tab_1.v_show_table();

	//c_tab_0 = c_tab_1; //this causes error becasue the same table is tried to be deleted twice

	c_tab_1.b_set_value(2, 123);
	cout << endl << endl;;
	cout << "\nc_tab_0 table: " << endl;
	c_tab_0.v_show_table();
	cout << endl << endl;;
	cout << "\nc_tab_1 table: " << endl;
	c_tab_1.v_show_table();
	cout << endl << endl;;

	CTable newt = c_tab_0 + c_tab_1;
	cout << "\nnewt show table: " << endl;
	newt.v_show_table();
	cout << endl << endl;;
	cout << "\nc_tab_0 table: " << endl;
	c_tab_0.v_show_table();
	cout << endl << endl;;
	cout << "\nc_tab_1 table: " << endl;
	c_tab_1.v_show_table();
	cout << endl << endl;;
	cout << "\nnewt table: " << endl;
	newt.v_show_table();
	cout << endl << endl;;

	cout << "\n\n----------LAB3 LIVE-------";
	cout << "\nc_tab_0 table: " << endl;
	c_tab_0.v_show_table();
	c_tab_0 << 2;
	cout << "\nc_tab_0 table after << 2: " << endl;
	c_tab_0.v_show_table();

	
	
	cout << "\n\nnewt show table: " << endl;
	newt.v_show_table();
	newt >> 2;
	cout << "\n\nnewt show table after >> 2: " << endl;
	newt.v_show_table();
	

	
	return 0;
}



