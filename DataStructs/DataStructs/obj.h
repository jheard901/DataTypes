#pragma once

//this is a data class that can be used to represent anything.
class Obj
{
private:
	int t1; //integer data type for example
public:
	Obj();
	~Obj();
	int GetIntData() { return t1; }
};