#pragma once

//used for comparisons
enum RelationType { EQUAL, GREATER, LESS };

//this is a data class that can be used to represent anything.
//basis for templates: http://www.cplusplus.com/doc/oldtutorial/templates/
//how to setup templates: http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
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