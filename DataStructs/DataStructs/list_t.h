#pragma once

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
	int GetLength();
	void EmptyList();
	void ResetCursor();
	D GetNextObject();
	bool VerifyNextObject();
};

//explicit specialization declarations (is this partial???)

template<>
void LinkedList<Obj<int>>::InsertObject(Obj<int> object);

template<>
Obj<int> LinkedList<Obj<int>>::GetObject(Obj<int> object, bool & bFound);

template<>
void LinkedList<Obj<int>>::DeleteObject(Obj<int> object);


//Specialization removed temporarily

//this is a specialization of LinkedList when created with the template class Obj
//Obj as the generic type eg "LinkedList<Obj<GT>>" // GT stands for generic type
//essentially, LinkedList<Obj<float>> results in Obj<float> when Obj<T> is its parameter

//template <>
//class LinkedList<Obj<int>> //using int as an example atm; later use Card
//{
//private:
//	struct LinkedNode
//	{
//		Obj<int> nData;
//		LinkedNode* next;
//	};
//	LinkedNode* cursor; //iterator
//	LinkedNode* head; //start of list
//	int length;
//public:
//	LinkedList();
//	~LinkedList();
//	bool IsFull();
//	void InsertObject(Obj<int> object);
//	Obj<int> GetObject(Obj<int> object, bool &bFound);
//	void DeleteObject(Obj<int> object);
//	int GetLength();
//	void EmptyList();
//	void ResetCursor();
//	Obj<int> GetNextObject();
//};



//#include "_list.hpp"




//========================================================//
// TEMPLATE DEFINITIONS
//========================================================//



#include <new>			//std::bad_alloc
#include "utility.h"


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
//	LinkedNode* temp = new LinkedNode;
//	temp->nData = object;
//	temp->next = head;
//	head = temp;
//	length++;
//
//	// EX. if A was the head, and B is being inserted, it works like this:
//	// A (head) <- B (temp),  A <- B(head), and etc...
//	// 
//	// valid to use when list has nullptr for head as well
//
}

//specialization using Obj<int> || ideally we will specialize Obj<Card> for the deck of cards linked list
template<>
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

//need to completely remove the code based around class Obj in this function to use this list generically. Otherwise, I need to tightly couple Obj
//to this class and pretty much use the following class template declaration structure:
//template <class GT>
// template <Obj<GT>>
//
//So, I would pretty much only be able to use type Obj as the container to whatever data I would like, instead of being able to use this list
//generically for simple things like int, float, string, and etc...
template <class D>
D LinkedList<D>::GetObject(D object, bool &bFound)
{
//	cursor = head;
//	bFound = false;
//
//	while (cursor != nullptr && !bFound)
//	{
//		switch (object.ComparedTo(cursor->nData))
//		{
//		case EQUAL:
//			bFound = true;
//			break;
//		case GREATER:
//			cursor = cursor->next;
//			break;
//		case LESS:
//			cursor = cursor->next;
//			break;
//		}
//	}
//
//	return cursor->nData;
}

template<>
Obj<int> LinkedList<Obj<int>>::GetObject(Obj<int> object, bool & bFound)
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

template<>
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

template <class D>
void LinkedList<D>::DeleteObject(D object)
{
//	LinkedNode* tempCursor = nullptr;
//	cursor = head;
//
//	//case for deleting object if its head
//	if (object.ComparedTo(cursor->nData) == EQUAL)
//	{
//		head = cursor->next;
//	}
//	//case for deleting any other object
//	else
//	{
//		while (cursor != nullptr && !(object.ComparedTo((cursor->next)->nData) == EQUAL)) //continue until tempCursor reaches end of list or found the object
//		{
//			cursor = cursor->next;
//		}
//		tempCursor = cursor->next; //the object to be deleted
//		cursor->next = (cursor->next)->next; //assign the next node to be the node after the one getting deleted, so the references are not lost
//	}
//
//	delete tempCursor;
//	length--;
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
			return false;
		}
		else
		{
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


