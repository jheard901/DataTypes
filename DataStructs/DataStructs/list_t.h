#pragma once

#include <new>			//std::bad_alloc
#include "utility.h"
#include "obj_t.h"

//unsorted linked list
//information on template specialization of a single method: http://stackoverflow.com/questions/1723537/template-specialization-of-a-single-method-from-a-templated-class
//using class templates as parameters in a class template: http://stackoverflow.com/questions/4189945/templated-class-specialization-where-template-argument-is-a-template
//less relevant (function templates with template arguments):  http://stackoverflow.com/questions/9843671/c-template-function-taking-template-class-as-parameter
//overall explanation of template specialization: http://www.cprogramming.com/tutorial/template_specialization.html
//more on templates from isocpp: https://isocpp.org/wiki/faq/templates#class-templates
//reason for my error initially is because I tried to make a specialization of a single method, which is not possible.
//you need to do a specialization of the entire class to make it work the way you intend when a specific generic type is passed to it.

//possible reason I am having LNK2019 error: http://stackoverflow.com/questions/10271796/c-keep-getting-error-lnk2019-unresolved-external-symbol
//important info on headers: http://stackoverflow.com/questions/20023610/when-to-use-hpp-files


//========================================================//
// LINKEDLIST CLASS
//========================================================//

//made specifically for being used generically with any data type
template <class D> //D stands for data type || ideally, utilize Obj class in it
class LinkedList
{
private:
	struct LinkedNode
	{
		D nData;
		LinkedNode* next = nullptr;	//initialize this so that EmptyList() works properly
	};
	LinkedNode* cursor; //iterator
	LinkedNode* head; //start of list
	LinkedNode* tail; //end of list
	int length;
public:
	LinkedList();
	~LinkedList();
	bool IsFull();
	void InsertObject(D object);	//defaults to add at beginning
	void InsertObject(D object, bool bInsertAtBeg);	//if false, insert a value at the end of list
	void InsertObject(D object, int position, bool bInsertBefore);	//adds data before/after a specific position in list: 0 = head, tail = last element.
	LinkedList* Break(int nElement, bool bKeepValues);	//returns a deep copy of a list starting from nElement to the end of list | optional to delete or keep values from list
	void AddList(LinkedList* nList);
	D GetObject(D object, bool &bFound);
	void DeleteObject(D object);
	LinkedNode* IterateTo(int nPos);	//iterates through list starting from head to specified position
	int GetLength();
	void EmptyList();
	void ResetCursor();
	LinkedNode* GetCursor();
	D GetNextObject();
	bool VerifyNextObject();
};



//========================================================//
// OBJLINKEDLIST CLASS
//========================================================//

//made specifically for being used generically with the container class Obj
template <class GT> //GT stands for generic type
class ObjLinkedList
{
private:
	struct LinkedNode
	{
		Obj<GT> nData; //example of what class would look like if I make it exclusively use the Obj container
		LinkedNode* next;
	};
	LinkedNode* cursor; //iterator
	LinkedNode* head; //start of list
	int length;
public:
	ObjLinkedList();
	~ObjLinkedList();
	bool IsFull();
	void InsertObject(Obj<GT> object);
	Obj<GT> GetObject(Obj<GT> object, bool &bFound);
	void DeleteObject(Obj<GT> object);
	int GetLength();
	void EmptyList();
	void ResetCursor();
	Obj<GT> GetNextObject();
	bool VerifyNextObject();
};

/*
//Specialization removed temporarily

//// syntax example of full class specialization //// untested, but theoretically correct

template <>
class ObjLinkedList<Card>
{
};

//// syntax example of explicit specialization //// tested and works

//declaration
template<>
void ObjLinkedList<long>::InsertObject(Obj<long> object);

//definition
template<>
void ObjLinkedList<long>::InsertObject(Obj<long> object)		//ideally we will specialize Card for the deck of cards linked list
{
}
*/


//========================================================//
// LINKEDLIST TEMPLATE DEFINITIONS
//========================================================//




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
		DP(ba.what());
		return true;
	}
}

template <class D>
void LinkedList<D>::InsertObject(D object)
{
	/*
	//old quick way //this logic can be used for reversing a singly linked list (make head the reverseList's tail, then once finished the last element will be the reverseList's head)
	LinkedNode* temp = new LinkedNode;
	temp->nData = object;
	temp->next = head;
	head = temp;
	length++;

	// EX. if A was the head, and B is being inserted, it works like this:
	// A(head) <- B(temp),  A <- B(head), A <- B(head) <- C(temp), A <- B <- C(head), and etc...
	// 
	// valid to use when list has nullptr for head as well
	*/

	//if list hasn't been initialized yet, add the first value
	if (head == nullptr)
	{
		LinkedNode* temp = new LinkedNode;
		temp->nData = object;
		head = temp;
		length++;
	}
	//if list doesn't have a tail yet, assign it
	else if (tail == nullptr)
	{
		LinkedNode* temp = new LinkedNode;
		temp->nData = object;
		head->next = temp;
		tail = temp;
		length++;
	}
	//else add at object at the end of the list
	else
	{
		LinkedNode* temp = new LinkedNode;
		temp->nData = object;
		tail->next = temp;
		tail = temp;
		length++;
	}
}

template <class D>
void LinkedList<D>::InsertObject(D object, bool bInsertAtBeg)
{
	//insert at beginning
	if (bInsertAtBeg)
	{
		if (head == nullptr)
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			head = temp;
			length++;
		}
		else
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			temp->next = head;
			head = temp;
			length++;
		}
	}
	//insert at end
	else
	{
		if (head == nullptr)
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			head = temp;
			length++;
		}
		else if (tail == nullptr)
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			head->next = temp;
			tail = temp;
			length++;
		}
		else
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			tail->next = temp;
			tail = temp;
			length++;
		}
	}
}

template <class D>
void LinkedList<D>::InsertObject(D object, int position, bool bInsertBefore)
{
	//utilize a local iterator
	LinkedNode* iter = head;

	//confirm if list is initialized
	if (head == nullptr)
	{
		LinkedNode* temp = new LinkedNode;
		temp->nData = object;
		head = temp;
		length++;
		return;
	}

	//then check if position is valid
	if (position >= 0 && position < length)
	{
		//input is okay
		ResetCursor();
		GetNextObject();
		//iterate to position in list
		for (int i = 0; i < position; i++)
		{
			iter = cursor; //iter is the previous node
			GetNextObject();
		}

		//check if we insert before position
		if (bInsertBefore)
		{
			//special case for inserting before head
			if (cursor == head)
			{
				LinkedNode* temp = new LinkedNode;
				temp->nData = object;
				temp->next = head;
				head = temp;
				length++;
			}
			else
			{
				LinkedNode* temp = new LinkedNode;
				temp->nData = object;
				iter->next = temp;		//point the previous node to the new node
				temp->next = cursor;	//point the new node to the current node
				length++;
			}
		}
		//insert after position
		else
		{
			//special case if tail not initialized (i.e. only head in list)
			if (tail == nullptr)
			{
				LinkedNode* temp = new LinkedNode;
				temp->nData = object;
				cursor->next = temp; //cursor should be on the head
				tail = temp;
				length++;
			}
			//special case for inserting after tail
			else if (cursor == tail)
			{
				LinkedNode* temp = new LinkedNode;
				temp->nData = object;
				cursor->next = temp; //cursor should be on the tail
				tail = temp;
				length++;
			}
			else
			{
				LinkedNode* temp = new LinkedNode;
				temp->nData = object;
				temp->next = cursor->next;
				cursor->next = temp;
				length++;
			}
		}
	}
	//invalid position defaults to inserting after the tail
	else
	{
		//invalid input
		DP("Invalid input entered for position, defaulting to insert after last position");
		ResetCursor();
		GetNextObject();
		//iterate to last position in list
		for (int i = 0; i < length-1; i++)
		{
			iter = cursor; //iter is the previous node
			GetNextObject();
		}

		//special case if tail not initialized (i.e. only head in list)
		if (tail == nullptr)
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			cursor->next = temp; //cursor should be on the head
			tail = temp;
			length++;
		}
		//special case for inserting after tail
		else
		{
			LinkedNode* temp = new LinkedNode;
			temp->nData = object;
			cursor->next = temp; //cursor should be on the tail
			tail = temp;
			length++;
		}
	}

}

template<class D>
LinkedList<D>* LinkedList<D>::Break(int nElement, bool bKeepValues)
{
	LinkedNode* iter = nullptr;

	//list must have more than 1 element
	if (length < 2)
	{
		DP("Invalid list length; it must be at least 2 nodes or more to Break() from.");
		return 0;
	}

	//iterate to n element
	ResetCursor();
	GetNextObject();
	for (int i = 0; i < nElement; i++)
	{
		iter = cursor;	//iter is on the previous node
		GetNextObject();
	}

	//list cannot break from the head
	if (cursor == head)
	{
		DP("Cannot Break() from head of list; use the Duplicate() command instead to make a copy of list.");
		return 0;
	}

	//create another list to store these elements
	LinkedList<D>* newList = new LinkedList<D>;
	
	//create deep copies | initialize the newList with a valid head node
	LinkedNode* newNode = new LinkedNode(*cursor);
	newList->head = newNode;
	newList->length++;	//remember to increment newList's length for each added node
	newList->cursor = newList->head;
	//if values WILL NOT BE kept in list
	if (!bKeepValues)
	{
		//special case for deleting tail
		if (length == 2)
		{
			delete cursor;
			cursor = nullptr;
			tail = nullptr;
			length--;
		}
		//set the previous node as the new tail if not keeping values for list Break() is used on
		else
		{
			tail = iter;
			iter = cursor;	//set iter to the node to delete
			cursor = cursor->next;	//set cursor to the next node after the deleted one
			delete iter;
			tail->next = nullptr;
			length--;
		}
		//we start adding nodes to the newList here
		while (cursor != nullptr)
		{
			//add the soon to delete node to the newList
			LinkedNode* nNode = new LinkedNode(*cursor);
			newList->cursor->next = nNode;
			newList->length++;
			newList->cursor = nNode;
			//delete current node, iterate to next one
			iter = cursor;
			cursor = cursor->next;
			delete iter;
			iter = nullptr;
			length--;
		}
	}
	//if values WILL BE kept in list
	else
	{
		while (cursor->next != nullptr)
		{
			cursor = cursor->next;
			LinkedNode* nNode = new LinkedNode(*cursor);
			newList->cursor->next = nNode;
			newList->length++;
			newList->cursor = nNode;
		}
	}
	
	//set the tail for newList | assuming it at least has 2 nodes
	if (newList->length > 1)
	{
		newList->tail = newList->cursor;
	}

	return newList;
}

//for the moment, this only adds a list at the end of a list | nothing about this is type safe yet
template <class D>
void LinkedList<D>::AddList(LinkedList* nList)
{
	//utilize a local iterator
	LinkedNode* iter = head;

	//confirm if list is initialized
	if (head == nullptr)
	{
		nList->ResetCursor();
		nList->GetNextObject();
		LinkedNode* newNode = new LinkedNode(*(nList->cursor));
		head = newNode;
		cursor = newNode;
		length++;

		while (nList->cursor->next != nullptr)
		{
			nList->cursor = nList->cursor->next;
			LinkedNode* nNode = new LinkedNode(*(nList->cursor));
			cursor->next = nNode;
			length++;
			cursor = nNode;
		}
	}
	//when only the head is in list
	else if (tail == nullptr)
	{
		nList->ResetCursor();
		nList->GetNextObject();
		LinkedNode* newNode = new LinkedNode(*(nList->cursor));
		head->next = newNode;
		cursor = newNode;
		length++;

		while (nList->cursor->next != nullptr)
		{
			nList->cursor = nList->cursor->next;
			LinkedNode* nNode = new LinkedNode(*(nList->cursor));
			cursor->next = nNode;
			length++;
			cursor = nNode;
		}
	}
	//all other cases
	else
	{
		nList->ResetCursor();
		nList->GetNextObject();
		LinkedNode* newNode = new LinkedNode(*(nList->cursor));
		tail->next = newNode;
		cursor = newNode;
		length++;

		while (nList->cursor->next != nullptr)
		{
			nList->cursor = nList->cursor->next;
			LinkedNode* nNode = new LinkedNode(*(nList->cursor));
			cursor->next = nNode;
			length++;
			cursor = nNode;
		}
	}

	//set the tail | assuming it has at least 2 nodes
	if (length > 1)
	{
		tail = cursor;
	}
}

//need to specialize non-numeric values such as strings and char
template <class D>
D LinkedList<D>::GetObject(D object, bool &bFound)
{
	cursor = head;
	bFound = false;

	while (cursor != nullptr && !bFound)
	{
		if (cursor->nData == object)
		{
			bFound = true;
			break;
		}
		else if (cursor->nData > object)
		{
			cursor = cursor->next;
			break;
		}
		else //if (cursor->nData < object)
		{
			cursor = cursor->next;
			break;
		}
	}

	return cursor->nData;
}

//this doesn't account for the length of a list being 0 or 1
template <class D>
void LinkedList<D>::DeleteObject(D object)
{
	LinkedNode* tempCursor = nullptr;
	cursor = head;

	//case for deleting object if its head
	if (cursor->nData == object)
	{
		tempCursor = cursor;
		head = cursor->next;
	}
	//case for deleting any other object
	else
	{
		//continue until tempCursor reaches end of list or found the object
		while (cursor != nullptr && !((cursor->next)->nData == object))
		{
			cursor = cursor->next;
		}

		//case for deleting tail
		if (cursor->next == tail)
		{
			tempCursor = cursor->next; //the object to be deleted
			tail = cursor;
			tail->next = nullptr;
		}
		//case for deleting an element between the head and tail of a list
		else
		{
			tempCursor = cursor->next; //the object to be deleted
			cursor->next = (cursor->next)->next; //assign the next node to be the node after the one getting deleted, so the references are not lost
		}
		
	}

	delete tempCursor;
	length--;
}

template <class D>
int LinkedList<D>::GetLength()
{
	return length;
}

//typename required for returning a struct/typedef: http://stackoverflow.com/questions/16131838/error-dependent-name-is-not-a-type-when-use-typedef-type-in-class-as-return
template<class D>
typename LinkedList<D>::LinkedNode* LinkedList<D>::IterateTo(int nPos)
{
	//note this isn't type-safe. Iterate only to a position you know is valid!
	ResetCursor();
	GetNextObject();
	for (int x = 0; x < nPos; x++)
	{
		GetNextObject();
	}
	return cursor;
}

template <class D>
void LinkedList<D>::EmptyList()
{
	while (head != nullptr)
	{
		cursor = head;
		head = head->next;
		delete cursor;
		cursor = nullptr;	//set that pointer to NULL after delete
	}
	tail = nullptr;
	length = 0;
}

//this works in conjunction with GetNextObject()
template <class D>
void LinkedList<D>::ResetCursor()
{
	cursor = nullptr;
}

template<class D>
typename LinkedList<D>::LinkedNode* LinkedList<D>::GetCursor()
{
	return cursor;
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

//true if next object exists
template<class D>
bool LinkedList<D>::VerifyNextObject()
{
	//if cursor is not assigned, then assign it to head
	if (cursor == nullptr)
	{
		cursor = head;
		if (cursor == nullptr)
		{
			ResetCursor();
			return false;
		}
		else
		{
			ResetCursor();
			return true;
		}
	}
	//if cursor already assigned, then check what it points to next
	else
	{
		if (cursor->next == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}







//========================================================//
// OBJLINKEDLIST TEMPLATE DEFINITIONS
//========================================================//




template <class GT>
ObjLinkedList<GT>::ObjLinkedList()
{
	length = 0;
	head = nullptr;
}

template <class GT>
ObjLinkedList<GT>::~ObjLinkedList()
{
	if (length > 0) { EmptyList(); }
}

//checks if can create a new object
template <class GT>
bool ObjLinkedList<GT>::IsFull()
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

template <class GT>
void ObjLinkedList<GT>::InsertObject(Obj<GT> object)
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

template <class GT>
Obj<GT> ObjLinkedList<GT>::GetObject(Obj<GT> object, bool &bFound)
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

template <class GT>
void ObjLinkedList<GT>::DeleteObject(Obj<GT> object)
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

template <class GT>
int ObjLinkedList<GT>::GetLength()
{
	return length;
}

template <class GT>
void ObjLinkedList<GT>::EmptyList()
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
template <class GT>
void ObjLinkedList<GT>::ResetCursor()
{
	cursor = nullptr;
}

template <class GT>
Obj<GT> ObjLinkedList<GT>::GetNextObject()
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

//true if next object exists
template<class GT>
bool ObjLinkedList<GT>::VerifyNextObject()
{
	//if cursor is not assigned, then use a test node
	if (cursor == nullptr)
	{
		cursor = head;
		if (cursor == nullptr)
		{
			ResetCursor();
			return false;
		}
		else
		{
			ResetCursor();
			return true;
		}
	}
	//if cursor already assigned, then check what it points to next
	else
	{
		if (cursor->next == nullptr)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}


