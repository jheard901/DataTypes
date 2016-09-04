#pragma once

//used for comparisons
enum RelationType { EQUAL, GREATER, LESS };

//this is a data class that can be used to represent anything.
class Obj
{
private:
	int t1; //integer data type for example
public:
	Obj();
	~Obj();
	RelationType ComparedTo(Obj other);
	int GetIntData() { return t1; }
	void SetIntData(int val) { t1 = val; }
};