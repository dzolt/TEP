#include "CNodeStatic.h"
#include "CNodeDynamic.h"


void v_tree_test()
{
	CTreeStatic c_root;
	c_root.pcGetRoot()->vAddNewChild();
	c_root.pcGetRoot()->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vSetValue(1);
	c_root.pcGetRoot()->pcGetChild(1)->vSetValue(2);

	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(11);
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(12);
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue(13);

	c_root.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(21);
	c_root.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(22);
	std::cout << "Printing c_root tree: " << std::endl;
	c_root.vPrintTree();
	std::cout << "\nPrinting all parents of 3rd child of 1st child of root: " << std::endl;
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vPrintUp();
	CTreeStatic c_root2;
	c_root2.pcGetRoot()->vSetValue(50);
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->vAddNewChild();

	c_root2.pcGetRoot()->pcGetChild(0)->vSetValue(10);
	c_root2.pcGetRoot()->pcGetChild(1)->vSetValue(20);

	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(111);
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(112);
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue(113);

	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(211);
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(212);

	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->pcGetChild(0)->vSetValue(311);
	std::cout << "\nPrinting c_root2 tree: " << std::endl;
	c_root2.vPrintTree();
	std::cout << "\n\n";
	std::cout << "Moving subtrees: " << std::endl;
	c_root.pcGetRoot()->bMoveSubtree(c_root.pcGetRoot(), c_root2.pcGetRoot()->pcGetChild(1));
	std::cout << "\nPrinting c_root tree: " << std::endl;

	c_root.vPrintTree();
	std::cout << "\nPrinting c_root2 tree: " << std::endl;
	c_root2.vPrintTree();
}//void v_tree_test()


void v_dynamic()
{
	CTreeDynamic<int> c_root;
	c_root.pcGetRoot()->vAddNewChild();
	c_root.pcGetRoot()->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vSetValue(60);
	c_root.pcGetRoot()->pcGetChild(1)->vSetValue(20);

	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(11);
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(12);
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue(13);

	c_root.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(21);
	c_root.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(22);

	std::cout << "croot:" << std::endl;
	c_root.vPrintTree();
	std::cout << "\n\n";
	CTreeDynamic<int> c_root2;
	c_root2.pcGetRoot()->vSetValue(50);
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vSetValue(81);
	c_root2.pcGetRoot()->pcGetChild(1)->vSetValue(82);

	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(811);
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(812);
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue(813);

	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(911);
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(912);

	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->pcGetChild(0)->vSetValue(1911);

	std::cout << "croot2" << std::endl;
	c_root2.vPrintTree();
	std::cout << "\n\n";

	c_root.pcGetRoot()->bMoveSubtree(c_root.pcGetRoot(), c_root2.pcGetRoot()->pcGetChild(1));
	std::cout << "croot" << std::endl;

	c_root.vPrintTree();
	std::cout << "\ncroot2" << std::endl;
	c_root2.vPrintTree();
}//void v_dynamic()

void v_dynamic_str()
{
	CTreeDynamic<std::string> c_root;
	c_root.pcGetRoot()->vAddNewChild();
	c_root.pcGetRoot()->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vSetValue("A");
	c_root.pcGetRoot()->pcGetChild(1)->vSetValue("B");

	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue("C");
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue("D");
	c_root.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue("E");

	c_root.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue("F");
	c_root.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue("G");

	std::cout << "croot:" << std::endl;
	c_root.vPrintTree();
	std::cout << "\n\n";
	CTreeDynamic<std::string> c_root2;
	c_root2.pcGetRoot()->vSetValue("R");
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vSetValue("AA");
	c_root2.pcGetRoot()->pcGetChild(1)->vSetValue("BB");

	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue("CC");
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue("DD");
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue("EE");

	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue("FF");
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue("GG");

	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->pcGetChild(0)->vSetValue("HHH");

	std::cout << "croot2" << std::endl;
	c_root2.vPrintTree();
	std::cout << "\n\n";
	std::cout << "croot2 leaves:" << std::endl;
	std::cout << c_root2.pcGetRoot()->iCountLeaves();

	c_root.pcGetRoot()->bMoveSubtree(c_root.pcGetRoot(), c_root2.pcGetRoot()->pcGetChild(1));
	std::cout << "croot" << std::endl;

	c_root.vPrintTree();
	std::cout << "\ncroot2" << std::endl;
	c_root2.vPrintTree();
}//void v_dynamic_str()

void v_live()
{	
	CTreeDynamic<int> c_root2;
	c_root2.pcGetRoot()->vSetValue(50);
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vSetValue(10);
	c_root2.pcGetRoot()->pcGetChild(1)->vSetValue(50);

	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(111);
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(50);
	c_root2.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue(113);

	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(211);
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(212);

	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vAddNewChild();
	c_root2.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->pcGetChild(0)->vSetValue(50);

	std::cout << "\nPrinting Tree: " << std::endl;
	c_root2.vPrintTree();
	std::cout << "\nNumber of 50s in the tree: " << std::endl;
	std::cout<<c_root2.pcGetRoot()->iGetNumberOfAppearances(50);
	std::cout << "\nNumber of 10s in the tree: " << std::endl;
	std::cout<<c_root2.pcGetRoot()->iGetNumberOfAppearances(10)<<std::endl;

}

void v_live2()
{
	CTreeStatic c_root3;
	c_root3.pcGetRoot()->vSetValue(30);
	c_root3.pcGetRoot()->vAddNewChild();
	c_root3.pcGetRoot()->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(0)->vSetValue(100);
	c_root3.pcGetRoot()->pcGetChild(1)->vSetValue(50);

	c_root3.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(0)->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(0)->pcGetChild(0)->vSetValue(111);
	c_root3.pcGetRoot()->pcGetChild(0)->pcGetChild(1)->vSetValue(506);
	c_root3.pcGetRoot()->pcGetChild(0)->pcGetChild(2)->vSetValue(100);

	c_root3.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(1)->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(1)->pcGetChild(0)->vSetValue(21);
	c_root3.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vSetValue(212);

	c_root3.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->vAddNewChild();
	c_root3.pcGetRoot()->pcGetChild(1)->pcGetChild(1)->pcGetChild(0)->vSetValue(100);
	
	std::cout << "\nPrinting Tree: " << std::endl;
	c_root3.vPrintTree();
	std::cout << "\nNumber of 100s in the tree: " << std::endl;
	std::cout << c_root3.pcGetRoot()->iGetNumberOfAppearances(100);
	std::cout << "\nNumber of 10s in the tree: " << std::endl;
	std::cout << c_root3.pcGetRoot()->iGetNumberOfAppearances(10) << std::endl;

}
int main()
{	
	std::cout << "\n------------------------------Tree Static-----------------------" << std::endl;

	//v_tree_test();

	std::cout << "\n\n------------------------------Tree Dynamic-----------------------" << std::endl;

	//v_dynamic();
	v_dynamic_str();

	/*std::cout << "\n\n------------------------------LAB 5 LIVE-----------------------" << std::endl;
	v_live();
	std::cout << "\n\n";
	v_live2();*/
	
	return 0;
};