#include "CNodeStatic.h"

CTreeStatic::CNodeStatic::CNodeStatic()
{
	//std::cout << "create node: " <<x++<< std::endl;
	i_val = 0;
	pc_parent_node = NULL;
}//CNodeStatic::CNodeStatic() 

void CTreeStatic::CNodeStatic::vAddNewChild()
{
	v_children.push_back(CNodeStatic());
	v_children.back().pc_parent_node = this;
}//void CNodeStatic::vAddNewChild()

bool CTreeStatic::CNodeStatic::vAddExistingChild(CNodeStatic& cNewChild)
{
	//nie musimy sprawdzic czy new child jest nullem bo referencja nie moze byc na null
	v_children.push_back(cNewChild);
	v_children.back().pc_parent_node = this;
	return true;
}//bool CTreeStatic::CNodeStatic::vAddExistingChild(CNodeStatic& cNewChild)

int CTreeStatic::CNodeStatic::iGetChildOffset(CNodeStatic& pcChildToFind)
{
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		if (&(v_children[ii]) == &pcChildToFind) { return ii; }
	}//	for (int ii = 0; ii < v_children.size(); ii++)
	return NULL;
}//int CTreeStatic::CNodeStatic::iGetChildOffset(CNodeStatic& pcChildToFind)

bool CTreeStatic::CNodeStatic::bRemoveChild(int iChildOffset)
{
	if (iChildOffset < 0 || iChildOffset >= v_children.size()) return false;
	v_children.erase(v_children.begin() + iChildOffset);
	return true;
}//bool CTreeStatic::CNodeStatic::bRemoveChild(int iChildOffset)

bool CTreeStatic::CNodeStatic::bRemoveChildFromParent()
{
	int i_child_offset = pc_parent_node->iGetChildOffset(*this);
	if (i_child_offset == NULL || !(pc_parent_node->bRemoveChild(i_child_offset))) return false;
	return true;
}//bool CTreeStatic::CNodeStatic::bRemoveChildFromParent()

CTreeStatic::CNodeStatic* CTreeStatic::CNodeStatic::pcGetChild(int iChildOffset)
{
	if (iChildOffset < 0 || iChildOffset >= v_children.size()) return NULL;
	return &v_children.at(iChildOffset);
}//CNodeStatic* CNodeStatic::pcGetChild(int iChildOffset)

void CTreeStatic::CNodeStatic::vPrintAllBelow()
{
	vPrint();
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		v_children[ii].vPrintAllBelow();
	}//for (int i = 0; i < v_children.size(); i++)
}//void CNodeStatic::vPrintAllBelow()

void CTreeStatic::CNodeStatic::vPrintUp()
{
	vPrint();
	if (pc_parent_node != NULL) pc_parent_node->vPrintUp();
}//void CNodeStatic::vPrintUp()

bool CTreeStatic::CNodeStatic::bMoveSubtree(CNodeStatic* pcParentNode, CNodeStatic* pcNewChildNode)
{
	if (pcParentNode == NULL || pcNewChildNode == NULL || pcNewChildNode->pc_parent_node == NULL ||
		pcParentNode->pcGetNodeRoot() == pcNewChildNode->pcGetNodeRoot() || this->pcGetNodeRoot() != pcParentNode->pcGetNodeRoot()) return false;//if either of nodes is non-existent or new child is the root
	pcParentNode->vAddExistingChild(*pcNewChildNode);
	if (!(pcNewChildNode->bRemoveChildFromParent())) return false;
	return true;
}//bool bMoveSubtree(CNodeStatic* pcParentNode, CNodeStatic* pcNewChildNode)

CTreeStatic::CNodeStatic* CTreeStatic::CNodeStatic::pcGetNodeRoot()
{
	if (pc_parent_node == NULL) return this;
	pc_parent_node->pcGetNodeRoot();
}//CTreeDynamic::CNodeDynamic* CTreeDynamic::CNodeDynamic::pcGetNodeRoot()

int CTreeStatic::CNodeStatic::iGetNumberOfAppearances(int iNumber)
{	
	int i_count_value = 0;
	if (i_val == iNumber) i_count_value = 1;
	iCount(iNumber, i_count_value);
	return i_count_value;
}//int CTreeStatic::CNodeStatic::iGetNumberOfAppearances(int iNumber)

void CTreeStatic::CNodeStatic::iCount(int iNumber, int& iNumberOfCounts)
{
	for (int ii = 0; ii < v_children.size(); ii++)
	{
		if (v_children[ii].i_val == iNumber)
		{
			iNumberOfCounts += 1;
		}//if (v_children[ii].i_val == iNumber)
		v_children[ii].iCount(iNumber, iNumberOfCounts);
	}//for (int ii = 0; ii < v_children.size(); ii++)
}//int CTreeStatic::CNodeStatic::iCount(int iNumber)


CTreeStatic::CNodeStatic::~CNodeStatic() //nothing is created dynamically therefore the destructor doesn't have to contain any delte fields
{
	//std::cout << "usuwan node: " << i_val << "  " << std::endl;
}//CNodeStatic::~CNodeStatic() 


//-------------------------------------------------------------------------CTreeStatic-------------------------------------------------------------------------
CTreeStatic::CTreeStatic()
{

}//CTreeStatic::CTreeStatic()

CTreeStatic::~CTreeStatic()
{
	//std::cout << "usuwan tree: " << std::endl;
}//CTreeStatic::~CTreeStatic()

void CTreeStatic::vPrintTree()
{
	c_root.vPrintAllBelow();
}//void CTreeStatic::vPrintTree()
