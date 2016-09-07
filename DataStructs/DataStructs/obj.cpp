
#include "obj.h"

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


