
#include <new>			//std::bad_alloc
#include "utility.h"
#include "list.h"


template <class D>
LinkedList<D>::LinkedList()
{
	length = 0;
	head = nullptr;
}

template <class D>
LinkedList<D>::~LinkedList()
{
	if (length > 0) { EmptyList(); }
}

//checks if can create a new object
template <class D>
bool LinkedList<D>::IsFull()
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

//specializations should appear before the generic definition
template<class GT>
void LinkedList<Obj<GT>>::InsertObject(Obj<GT> object)
{
	LinkedNode* temp = new LinkedNode;
	temp->nData = object;
	temp->next = head;
	head = temp;
	length++;
	
	// EX. if A was the head, and B is being inserted, it works like this:
	// A (head) <- B (temp),  A <- B(head), and etc...
	// 
	// valid to use when list has nullptr for head as well
	
}

template <class D>
void LinkedList<D>::InsertObject(D object)
{
	LinkedNode* temp = new LinkedNode;
	temp->nData = object;
	temp->next = head;
	head = temp;
	length++;
	
	// EX. if A was the head, and B is being inserted, it works like this:
	// A (head) <- B (temp),  A <- B(head), and etc...
	// 
	// valid to use when list has nullptr for head as well
	
}

template<class GT>
Obj<GT> LinkedList<Obj<GT>>::GetObject(Obj<GT> object, bool & bFound)
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

template <class D>
D LinkedList<D>::GetObject(D object, bool &bFound)
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

template<class GT>
void LinkedList<Obj<GT>>::DeleteObject(Obj<GT> object)
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

template <class D>
void LinkedList<D>::DeleteObject(D object)
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

template <class D>
int LinkedList<D>::GetLength()
{
	return length;
}

template <class D>
void LinkedList<D>::EmptyList()
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
template <class D>
void LinkedList<D>::ResetCursor()
{
	cursor = nullptr;
}

template <class D>
D LinkedList<D>::GetNextObject()
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





//========================================================//
// TEMPLATE SPECIALIZATION: Obj<int>
//========================================================//





/*

template <class Obj<int>>
LinkedList<Obj<int>>::LinkedList()
{
	length = 0;
	head = nullptr;
}

template <class Obj<int>>
LinkedList<Obj<int>>::~LinkedList()
{
	if (length > 0) { EmptyList(); }
}

//checks if can create a new object
template <class Obj<int>>
bool LinkedList<Obj<int>>::IsFull()
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
		DP(ba.what());
		return true;
	}
}

template <class Obj<int>>
void LinkedList<Obj<int>>::InsertObject(Obj<int> object)
{
	LinkedNode* temp = new LinkedNode;
	temp->nData = object;
	temp->next = head;
	head = temp;
	length++;
	
	// EX. if A was the head, and B is being inserted, it works like this:
	// A (head) <- B (temp),  A <- B(head), and etc...
	// 
	// valid to use when list has nullptr for head as well
	
}

template <class Obj<int>>
Obj<int> LinkedList<Obj<int>>::GetObject(Obj<int> object, bool &bFound)
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

template <class Obj<int>>
void LinkedList<Obj<int>>::DeleteObject(Obj<int> object)
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

template <class Obj<int>>
int LinkedList<Obj<int>>::GetLength()
{
	return length;
}

template <class Obj<int>>
void LinkedList<Obj<int>>::EmptyList()
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
template <class Obj<int>>
void LinkedList<Obj<int>>::ResetCursor()
{
	cursor = nullptr;
}

template <class Obj<int>>
Obj<int> LinkedList<Obj<int>>::GetNextObject()
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

*/


