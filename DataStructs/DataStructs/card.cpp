
#include "card.h"

Card::Card()
{

}

Card::Card(Suit nSuit, int nType)
{
	Init(nSuit, nType);
}

void Card::Init(Suit iSuit, int iType)
{
	suit = iSuit;
	type = iType;
}

char* Card::GetName()
{

	//this might be relevant later: http://stackoverflow.com/questions/8356223/assign-a-string-literal-to-a-char
	// http://stackoverflow.com/questions/10088661/assigning-a-string-of-characters-to-a-char-array
	// http://stackoverflow.com/questions/5660527/how-do-i-return-a-char-array-from-a-function

	//switch based off type to get the first part of card name
	/*
	switch (type)
	{
	case 0:
		*buffer += "Ace";
		break;
	case 1:
		buffer += "Ace";
		break;
	case 2:
		buffer += "Ace";
		break;
	case 3:
		buffer += "Ace";
		break;
	case 4:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;
	case 0:
		buffer += "Ace";
		break;

	}
	*/
	//append " of " in middle

	//switch based off suit to get last part of card name

	return name;
}

int Card::GetType()
{
	return type;
}

int Card::GetValue()
{
	return faceValue;
}

Suit Card::GetSuit()
{
	return suit;
}


