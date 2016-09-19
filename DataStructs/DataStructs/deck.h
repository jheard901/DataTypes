#pragma once

#include "card.h"
//#include "list_t.h"

//using forward declarations: http://stackoverflow.com/questions/553682/when-can-i-use-a-forward-declaration
template <class D>
class LinkedList;


class Deck : public Card
{
private:
	LinkedList<Card>* cardList;
public:
	Deck();
	~Deck();
	void Generate();
	void Generate(int deckSize, bool bRandomCards);
	void Shuffle(int nShuffles); //defaults to use true random shuffling
	void Shuffle(int nShuffles, int seed); //uses a psuedo random seed to base the shuffling off of (using the same seed will give repeat results)
};

