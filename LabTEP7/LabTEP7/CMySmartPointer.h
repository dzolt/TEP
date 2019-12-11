#pragma once
#include "CRefCounter.h"


template <typename T>
class CMySmartPointer
{
public:
	CMySmartPointer(T* pcPointer)
	{
		pc_pointer = pcPointer; 
		pc_counter = new CRefCounter();
		pc_counter->iAdd();
	}//	CMySmartPointer(T* pcPointer)

	CMySmartPointer(const CMySmartPointer& pcOther)
	{
		vClone(pcOther);
	}//	CMySmartPointer(const CMySmartPointer &pcOther)

	~CMySmartPointer() 
	{
		vDelete();
	}//	~CMySmartPointer() 

	void vDelete();
	void vClone(const CMySmartPointer& pcOther);

	T& operator*() { return *pc_pointer; }
	T* operator->() { return pc_pointer; }
	CMySmartPointer& operator=(const CMySmartPointer& cPointerToCopy);

private:
	T* pc_pointer;
	CRefCounter* pc_counter;
};

template <typename T>
CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer& pcOther)
{	
	//if the pointers differ
	if (pc_pointer != pcOther.pc_pointer)
	{	
		//if the pointer that we work on currently points to some other objects then we decrease the counter 
		if (pc_counter->iGet() > 0) vDelete();
		vClone(pcOther);
	}//	if (pc_pointer != pcOther.pc_pointer)
	return *this;
}//CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer& pcOther)

template <typename T>
void CMySmartPointer<T>::vDelete()
{
	if (pc_counter->iDec() == 1)
	{
		delete pc_pointer;
		delete pc_counter;
	}//if (pc_counter->iDec() == 1)
}//void CMySmartPointer<T>::vDelete()

template <typename T>
void CMySmartPointer<T>::vClone(const CMySmartPointer& pcOther)
{
	pc_pointer = pcOther.pc_pointer;
	pc_counter = pcOther.pc_counter;
	pc_counter->iAdd();
}//void CMySmartPointer<T>::vClone(const CMySmartPointer& pcOther)

