#pragma once
#include<iostream>
#include<vector>
#include <string>

//-------------------------------------------------------------------------CTreeDynamic-------------------------------------------------------------------------
template<typename T> class CTreeDynamic
{
private:
	class CNodeDynamic
	{
	public:
		CNodeDynamic();
		~CNodeDynamic();
		void vSetValue(T iNewValue) { t_value = iNewValue; };

		int iGetChildrenNumber() { return v_children.size(); };
		int iGetChildOffset(CNodeDynamic* pcChildToFind);
		void vAddNewChild();
		CNodeDynamic* pcGetChild(int iChildOffset);
		bool vRemoveChild(int iOffset);
		bool vRemoveChildFromItsParent();
		bool vAddNewExistingChild(CNodeDynamic* pcNewChild);

		void vPrint() { std::cout << " " << t_value; };
		void vPrintAllBelow();

		bool bMoveSubtree(CNodeDynamic* pcParentNode, CNodeDynamic* pcNewChildNode);
		CNodeDynamic* pcGetNodeRoot();
		
		int iGetNumberOfAppearances(T iNumber);
		void iCount(T iNumber, int& iCountNumber);
		int iCountLeaves();
	private:
		T t_value;
		std::vector<CNodeDynamic*> v_children;
		CNodeDynamic* pc_parent_node;


	};//class CNodeDynamic
public:
	CTreeDynamic();
	~CTreeDynamic();

	CNodeDynamic* pcGetRoot() { return pc_root; };
	void vPrintTree();
	
private:
	CNodeDynamic* pc_root;
};//template<typename T> class CTreeDynamic



template<typename T>
int CTreeDynamic<T>::CNodeDynamic::iCountLeaves()
{
	if (v_children.empty()) return 1;
	else
	{
		int leaves = 0;
		for (int ii = 0; ii < v_children.size(); ii++)
		{
			leaves += v_children[ii]->iCountLeaves();
		}
		return leaves;
	}
}//int CTreeDynamic<T>::CNodeDynamic::iCountLeaves()




template<typename T>
CTreeDynamic<T>::CNodeDynamic::CNodeDynamic()
{
	//std::cout << "create node: " << x++ << std::endl;
	//na co ustawic i_value?
	pc_parent_node = NULL;

}//CNodeDynamic::CNodeDynamic()

template<typename T>
CTreeDynamic<T>::CNodeDynamic::~CNodeDynamic()
{
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		//std::cout << "usuwan node: " << v_children[ii]->i_value << std::endl;
		delete v_children[ii];
	}
}//CNodeDynamic::~CNodeDynamic()

template<typename T>
void CTreeDynamic<T>::CNodeDynamic::vAddNewChild()
{
	v_children.push_back(new CNodeDynamic());
	v_children.back()->pc_parent_node = this;
}//void CNodeDynamic::vAddNewChild()

template<typename T>
bool CTreeDynamic<T>::CNodeDynamic::vAddNewExistingChild(CNodeDynamic* pcNewChild)
{
	if (pcNewChild == NULL) return false;
	v_children.push_back(pcNewChild);
	v_children.back()->pc_parent_node = this;
	return true;
}//void CNodeDynamic::vAddNewExistingChild(CNodeDynamic* pcNewChild)

template<typename T>
typename CTreeDynamic<T>::CNodeDynamic* CTreeDynamic<T>::CNodeDynamic::pcGetChild(int iChildOffset)
{
	if (iChildOffset < 0 || iChildOffset >= v_children.size()) return NULL;
	return v_children[iChildOffset];
}//CTreeDynamic* CNodeDynamic::pcGetChild(int iChildOffset)

template<typename T>
int CTreeDynamic<T>::CNodeDynamic::iGetChildOffset(CNodeDynamic* pcChildToFind)
{
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		if (v_children[ii] == pcChildToFind) return ii;
	}//for (int ii = 0; ii < v_children.size(); ii++)
	return NULL;
}//int CNodeDynamic::iGetChildOffset(CNodeDynamic* pcChildToFind)

template<typename T>
void CTreeDynamic<T>::CNodeDynamic::vPrintAllBelow()
{
	vPrint();
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		v_children[ii]->vPrintAllBelow();
	}//	for (int ii = 0; ii < v_children.size(); ii++)
}//void CNodeDynamic::vPrintAllBelow()

template<typename T>
bool CTreeDynamic<T>::CNodeDynamic::vRemoveChild(int iOffset)
{
	if (iOffset < 0 || iOffset >= v_children.size()) return false;
	v_children.erase(v_children.begin() + iOffset);
	return true;
}//void CNodeDynamic::vRemoveChild(int iOffset)

template<typename T>
bool CTreeDynamic<T>::CNodeDynamic::vRemoveChildFromItsParent()
{
	int iOffsetOfTheChildToBeRemoved = pc_parent_node->iGetChildOffset(this);
	if (iOffsetOfTheChildToBeRemoved == NULL || !(pc_parent_node->vRemoveChild(iOffsetOfTheChildToBeRemoved))) return false;
	return true;
}//void CNodeDynamic::vRemoveChild(int iOffset)

template<typename T>
bool CTreeDynamic<T>::CNodeDynamic::bMoveSubtree(CNodeDynamic* pcParentNode, CNodeDynamic* pcNewChildNode)
{
	//jesli nowy rodzic albo nowe dziecko nie istnieje albo nowe dziecko jest rootem(nie rzutuje tree na roota) jesli chcemy przenisc subtree
	// z tego samego drzewa lub jesli pcParentNode nie jest z drzewa dla torego wywolujemy metode to false
	if (pcParentNode == NULL || pcNewChildNode == NULL || pcNewChildNode->pc_parent_node == NULL ||
		pcParentNode->pcGetNodeRoot() == pcNewChildNode->pcGetNodeRoot() || this->pcGetNodeRoot() != pcParentNode->pcGetNodeRoot()) return false;
	if (!(pcNewChildNode->vRemoveChildFromItsParent())) return false;;//if it fails to remove child because it wasn't found or failed to remove it return false
	pcParentNode->vAddNewExistingChild(pcNewChildNode);
	return true;
}//bool bMoveSubtree(CNodeDynamic* pcParentNode, CNodeDynamic* pcNewChildNode)

template<typename T>
typename CTreeDynamic<T>::CNodeDynamic* CTreeDynamic<T>::CNodeDynamic::pcGetNodeRoot()
{
	if (pc_parent_node == NULL) return this;
	pc_parent_node->pcGetNodeRoot();
}//CTreeDynamic::CNodeDynamic* CTreeDynamic::CNodeDynamic::pcGetNodeRoot()

template<typename T>
int CTreeDynamic<T>::CNodeDynamic::iGetNumberOfAppearances(T iNumber)
{
	int i_count_value = 0;
	if (t_value == iNumber) i_count_value = 1;
	iCount(iNumber, i_count_value);
	return i_count_value;
}//int CTreeDynamic::CNodeDynamic::iGetNumberOfAppearances(int iNumber)

template<typename T>
void CTreeDynamic<T>::CNodeDynamic::iCount(T iNumber, int& iCountNumber)
{
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		if (v_children[ii]->t_value == iNumber)
		{
			iCountNumber += 1;
		}
		v_children[ii]->iCount(iNumber, iCountNumber);
	}
}//int CTreeDynamic::CNodeDynamic::iCount(int iNumber)




//-------------------------------------------------------------------------CTreeDynamic-------------------------------------------------------------------------
template<typename T>
CTreeDynamic<T>::CTreeDynamic()
{
	//std::cout << "create tree: " << std::endl;
	pc_root = new CNodeDynamic();
}//CTreeDynamic::CTreeDynamic()

template<typename T>
CTreeDynamic<T>::~CTreeDynamic()
{
	//std::cout << "usuwam tree : ";
	//pc_root->vPrint();
	std::cout << std::endl;
	delete pc_root;
}//CTreeDynamic::~CTreeDynamic()

template<typename T>
void CTreeDynamic<T>::vPrintTree()
{
	pc_root->vPrintAllBelow();
}//void CTreeDynamic::vPrintTree()
