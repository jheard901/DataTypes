#pragma once

#include "obj.h"

//unsorted linked list
//information on template specialization of a single method: http://stackoverflow.com/questions/1723537/template-specialization-of-a-single-method-from-a-templated-class
//using class templates as parameters in a class template: http://stackoverflow.com/questions/4189945/templated-class-specialization-where-template-argument-is-a-template
//less relevant (function templates with template arguments):  http://stackoverflow.com/questions/9843671/c-template-function-taking-template-class-as-parameter
//overall explanation of template specialization: http://www.cprogramming.com/tutorial/template_specialization.html
//reason for my error initially is because I tried to make a specialization of a single method, which is not possible.
//you need to do a specialization of the entire class to make it work the way you intend when a specific generic type is passed to it.
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
};

//this is a specialization of LinkedList when created with Obj as the generic type eg "LinkedList<Obj>"
template <>
template<class GT> //stands for generic type | allows Obj to be used genrically in this case
class LinkedList<Obj<GT>> //error-type issues with using GT here; need to fix that
{
private:
	struct LinkedNode
	{
		Obj<GT> nData;
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
};
