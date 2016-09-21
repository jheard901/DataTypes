
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

	//stores merged values, and replaces cardList with them || cleared after each shuffle
	LinkedList<Card>* tempList = nullptr; 

	for (int i = 0; i < nShuffles; i++)
	{
		//break the cardList at a random point near the middle || temporarily just use a default for midpoint
		int midpoint = cardList->GetLength() / 2;
		LinkedList<Card>* splitList = cardList->Break(midpoint, false);
		int shortLength = 0;

		//use the shortest length list to decide how many times to iterate adding
		if (cardList->GetLength() < splitList->GetLength())
		{
			shortLength = cardList->GetLength();
		}
		else if (cardList->GetLength() > splitList->GetLength())
		{
			shortLength = splitList->GetLength();
		}
		//both lists are equal | we could use either's length
		else
		{
			shortLength = cardList->GetLength();
		}

		//iterate until adding every card from a single list into tempList
		for (int x = 0; x < shortLength; x++)
		{
			//add 1 from card list, then 1 from spilt list, and repeat (it models how cards are traditionally shuffled)
			tempList->InsertObject(cardList->IterateTo(x)->nData);
			tempList->InsertObject(splitList->IterateTo(x)->nData);
		}
		//check which list is the short one, if not both
		if (cardList->GetLength() == shortLength && splitList->GetLength() == shortLength)
		{
			//requires no additional action since we added both of all elements
		}
		else if (cardList->GetLength() == shortLength)
		{
			//add only the remaining elements from the longer list: splitList in this case
		}
		else if (splitList->GetLength() == shortLength)
		{
			//add only the remaining elements from the longer list: cardList in this case
		}
	}
}

void Deck::Shuffle(int nShuffles, int seed)
{

}



