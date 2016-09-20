
#include "deck.h"
#include "list_t.h"
#include <stdlib.h> //srand(), rand()
#include <time.h> //time()

Deck::Deck()
{
	//initialize the card list
	cardList = new LinkedList<Card>;
}

Deck::~Deck()
{
	delete cardList;
}

void Deck::Generate()
{
	const int NUM_SUITS = 4;
	const int NUM_TYPES = 13;

	for (int x = 0; x < NUM_SUITS; x++) //each suit
	{
		for (int y = 0; y < NUM_TYPES; y++) //each type
		{
			Card* nCard = new Card;
			nCard->Init(Suit(x), y);
			cardList->InsertObject(*nCard);
		}
	}
}

void Deck::Generate(int deckSize, bool bRandomCards)
{

}

void Deck::Shuffle(int nShuffles)
{
	//seed random number generator with a unique number
	srand(unsigned(time(NULL)));

	//I need to make my list class more robust before defining this function
}

void Deck::Shuffle(int nShuffles, int seed)
{

}



