
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
	LinkedList<Card>* tempList = new LinkedList<Card>; 

	for (int i = 0; i < nShuffles; i++)
	{
		////// SPLIT DECK INTO SMALLER DECKS THEN RANDOMLY MERGE THEM BACK TOGETEHR //////

		//for this, split deck into 4-6 smaller pieces, then randomly decide which piece to merge back into main deck until all are back in


		////// START OF SHUFFLING CARDS TOGETHER //////

		//break the cardList at a random point near the middle || temporarily just use a default for midpoint
		int midpoint = cardList->GetLength() / 2;
		LinkedList<Card>* splitList = cardList->Break(midpoint, false);
		int shortLength = 0;	//the length of the shortest list
		LinkedList<Card>* longestList = nullptr;	//points to the longest length list

		//use the shortest length list to decide how many times to iterate adding
		if (cardList->GetLength() < splitList->GetLength())
		{
			shortLength = cardList->GetLength();
			longestList = splitList;
		}
		else if (cardList->GetLength() > splitList->GetLength())
		{
			shortLength = splitList->GetLength();
			longestList = cardList;
		}
		//both lists are equal | we could use either's length
		else
		{
			shortLength = cardList->GetLength();
			longestList = cardList;
		}

		//iterate until adding every card from a single list into tempList
		for (int x = 0; x < shortLength; x++)
		{
			//add 1 from card list, then 1 from spilt list, and repeat (it models how cards are traditionally shuffled)
			tempList->InsertObject(cardList->IterateTo(x)->nData);
			tempList->InsertObject(splitList->IterateTo(x)->nData);
		}

		//if lists are not same length then add remaining elements from the longer list into the tempList
		if (cardList->GetLength() != splitList->GetLength())
		{
			tempList->InsertObject(longestList->IterateTo(shortLength + 1)->nData);
			while (longestList->GetCursor()->next != nullptr)
			{
				tempList->InsertObject(longestList->GetNextObject());
			}
		}

		//clear the cardList, then add the tempList to cardList
		cardList->EmptyList();
		cardList->AddList(tempList); //need to make method for adding deep copy of another list | base it off InsertObject() for the positioning, and Break() for copying the nodes

		//now cleanup other lists for reuse
		tempList->EmptyList();
		splitList->EmptyList();

		//check which list is the short one, if not both
		//if (cardList->GetLength() == shortLength && splitList->GetLength() == shortLength)
		//{
		//	//requires no additional action since we added both of all elements
		//}
		//else if (cardList->GetLength() == shortLength)
		//{
		//	//add only the remaining elements from the longer list: splitList in this case
		//}
		//else if (splitList->GetLength() == shortLength)
		//{
		//	//add only the remaining elements from the longer list: cardList in this case
		//}
	}

	//clean up memory
	delete tempList;
}

void Deck::Shuffle(int nShuffles, int seed)
{

}



