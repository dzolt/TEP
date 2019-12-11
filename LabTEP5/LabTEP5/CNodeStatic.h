#pragma once
#include<vector>
#include<iostream>


class CTreeStatic
{
private:
	class CNodeStatic
	{
	public:
		CNodeStatic();
		~CNodeStatic();

		void vSetValue(int iNewVal) { i_val = iNewVal; };

		int iGetChildrenNumber() { return(v_children.size()); };
		void vAddNewChild();
		bool vAddExistingChild(CNodeStatic& cNewChild);
		bool bRemoveChildFromParent();
		bool bRemoveChild(int iChildOffset);
		CNodeStatic* pcGetChild(int iChildOffset);
		int iGetChildOffset(CNodeStatic& pcChildToFind);

		void vPrint() { std::cout << " " << i_val; };
		void vPrintAllBelow();
		void vPrintUp();

		bool bMoveSubtree(CNodeStatic* pcParentNode, CNodeStatic* pcNewChildNode);
		CNodeStatic* pcGetNodeRoot();

		int iGetNumberOfAppearances(int iNumber);
		void iCount(int iNumber, int& iCountValue);
	private:
		std::vector<CNodeStatic> v_children;
		CNodeStatic* pc_parent_node;
		int i_val;
	};//class CNodeStatic
public:
	CTreeStatic();
	~CTreeStatic();
	CNodeStatic* pcGetRoot() { return(&c_root); }
	void vPrintTree();
private:
	CNodeStatic c_root;
};//class CTreeStatic
