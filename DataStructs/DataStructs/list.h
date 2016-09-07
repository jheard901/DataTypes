#pragma once

#include "obj.h"

//unsorted linked list
//information on template specialization of a single method: http://stackoverflow.com/questions/1723537/template-specialization-of-a-single-method-from-a-templated-class
template <class D> //D stands for data type || ideally, utilize Obj class in it
class LinkedList
{
private:
	struct LinkedNode
	{
		D nData;
		LinkedNode* next;
	};
	LinkedNode* cursor; //iterator
	LinkedNode* head; //start of list
	int length;
public:
	LinkedList();
	~LinkedList();
	bool IsFull();
	void InsertObject(D object);
	D GetObject(D object, bool &bFound);
	void DeleteObject(D object);
	template <> //template specialization for a single method
	void DeleteObject(Obj object);
	int GetLength();
	void EmptyList();
	void ResetCursor();
	D GetNextObject();
};


