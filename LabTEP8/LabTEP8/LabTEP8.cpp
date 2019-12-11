#include "CTable.h"
#include <string>
#include <cstring>

using namespace std;

void test()
{
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

	cout << "\nc_tab_1 table: " << endl;
	c_tab_1.v_show_table();

	c_tab_1.b_set_value(2, 123);
	
	cout << "\nc_tab_0 table: " << endl;
	c_tab_0.v_show_table();
	
	cout << "\nc_tab_1 table: " << endl;
	c_tab_1.v_show_table();


	CTable ex;
	ex = std::move(c_tab_1);
	ex = c_tab_0;
	std::cout << "\n\n";
	c_tab_0.v_show_table();
	ex.v_show_table();
	CTable add;

	add = ex + c_tab_0;
	cout << endl;
	add.v_show_table();

	CTable::getCopies();
	CTable::getMoves();

	


}


int main()
{

	test();

	
	
	return 0;
}



