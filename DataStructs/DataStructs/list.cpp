
#include <new>			//std::bad_alloc
#include "utility.h"
#include "list.h"



LinkedList::LinkedList()
{
	length = 0;
	head = nullptr;
}

LinkedList::~LinkedList()
{
	if (length > 0) { EmptyList(); }
}

//checks if can create a new object
bool LinkedList::IsFull()
{
	LinkedNode* temp;
	try
	{
		temp = new LinkedNode;
		delete temp;
		return false;
	}
	catch (std::bad_alloc &ba)
	{
		DP(ba.what()) ;
		return true;
	}
}

void LinkedList::InsertObject(Obj object)
{
	LinkedNode* temp = new LinkedNode;
	temp->nData = object;
	temp->next = head;
	head = temp;
	length++;
	/*
	EX. if A was the head, and B is being inserted, it works like this:
	A (head) <- B (temp),  A <- B(head), and etc...

	valid to use when list has nullptr for head as well
	*/
}

Obj LinkedList::GetObject(Obj object, bool &bFound)
{
	cursor = head;
	bFound = false;

	while (cursor != nullptr && !bFound)
	{
		switch (object.ComparedTo(cursor->nData))
		{
		case EQUAL:
			bFound = true;
			break;
		case GREATER:
			cursor = cursor->next;
			break;
		case LESS:
			cursor = cursor->next;
			break;
		}
	}

	return cursor->nData;
}

void LinkedList::DeleteObject(Obj object)
{
	LinkedNode* tempCursor = nullptr;
	cursor = head;

	//case for deleting object if its head
	if (object.ComparedTo(cursor->nData) == EQUAL)
	{
		head = cursor->next;
	}
	//case for deleting any other object
	else
	{
		while (cursor != nullptr && !(object.ComparedTo((cursor->next)->nData) == EQUAL)) //continue until tempCursor reaches end of list or found the object
		{
			cursor = cursor->next;
		}
		tempCursor = cursor->next; //the object to be deleted
		cursor->next = (cursor->next)->next; //assign the next node to be the node after the one getting deleted, so the references are not lost
	}

	delete tempCursor;
	length--;
}

int LinkedList::GetLength()
{
	return length;
}

void LinkedList::EmptyList()
{
	while (head != nullptr)
	{
		cursor = head;
		head = head->next;
		delete cursor;
	}
	length = 0;
}

//this works in conjunction with GetNextObject()
void LinkedList::ResetCursor()
{
	cursor = nullptr;
}

Obj LinkedList::GetNextObject()
{
	if (cursor == nullptr)
	{
		cursor = head;
	}
	else
	{
		cursor = cursor->next; //if next is null then the return value will be null
	}
	return cursor->nData;
}

