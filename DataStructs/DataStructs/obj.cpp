
#include "obj.h"

Obj::Obj()
{
	t1 = 0;
}

Obj::~Obj()
{

}

//this is used for comparing Obj to each other based off a key (int in this case); ideally, this should be flexible enough to be able to compare any type of data within Obj
RelationType Obj::ComparedTo(Obj other)
{
	if (GetIntData() == other.GetIntData())
	{
		return EQUAL;
	}
	else if (GetIntData() > other.GetIntData())
	{
		return GREATER;
	}
	else
	{
		return LESS;
	}
}


