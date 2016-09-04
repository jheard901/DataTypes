#pragma once

#include "obj.h"

//unsorted linked list
class LinkedList
{
private:
	struct LinkedNode
	{
		Obj nData;
		LinkedNode* next;
	};
	LinkedNode* cursor; //iterator
	LinkedNode* head; //start of list
	int length;
public:
	LinkedList();
	~LinkedList();
	bool IsFull();
	void InsertObject(Obj object);
	Obj GetObject(Obj object, bool &bFound);
	void DeleteObject(Obj object);
	int GetLength();
	void EmptyList();
	void ResetCursor();
	Obj GetNextObject();
};
