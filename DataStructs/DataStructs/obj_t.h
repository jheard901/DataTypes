#pragma once

//The purpose of this class is to be a container (similar to the vector class)
//clearly this is not as powerful as std::vector<T> but in time, we can get there...


//used for comparisons
enum RelationType { EQUAL, GREATER, LESS };

//this is a data class that can be used to represent anything.
//basis for templates: http://www.cplusplus.com/doc/oldtutorial/templates/
//how to setup templates: http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file



//lets try making this a template now

template <class G>	//G stands for generic data type
class Obj
{
private:
	G t1; //assume integer data type for example
public:
	Obj();
	~Obj();
	RelationType ComparedTo(Obj other);
	G GetData() { return t1; }
	void SetData(G val) { t1 = val; }
};

//optional to specialize this template's ComparedTo() function to make it work different ways depending on the data type
//e.g.
//
//template <>
//RelationType Obj<long>::ComparedTo(Obj other);
//
//however, this means that if you use classes such as Card, then you need to include it into this class, which is not good
//since it is adding dependencies between classes. I think its better to encapsulate features such as comparison of a data
//type within that class itself, and to only use this class as the bridge that connects the two.




template <class G>
Obj<G>::Obj()
{
	//t1 = 0;
}

template <class G>
Obj<G>::~Obj()
{

}

//this is used for comparing Obj to each other based off a key (int in this case); ideally, this should be flexible enough to be able to compare any type of data within Obj
template <class G>
RelationType Obj<G>::ComparedTo(Obj other)
{
	if (GetData() == other.GetData())
	{
		return EQUAL;
	}
	else if (GetData() > other.GetData())
	{
		return GREATER;
	}
	else
	{
		return LESS;
	}
}



/*

//non-template for simplicity and to accomplish something | this compiles and works
class Obj
{
private:
	int t1; //assume integer data type for example
public:
	Obj();
	~Obj();
	RelationType ComparedTo(Obj other);
	int GetData() { return t1; }
	void SetData(int val) { t1 = val; }
};


Obj::Obj()
{
	//t1 = 0;
}

Obj::~Obj()
{

}

RelationType Obj::ComparedTo(Obj other)
{
	if (GetData() == other.GetData())
	{
		return EQUAL;
	}
	else if (GetData() > other.GetData())
	{
		return GREATER;
	}
	else
	{
		return LESS;
	}
}


*/


