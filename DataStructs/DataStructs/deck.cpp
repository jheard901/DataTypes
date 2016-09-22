
#include "deck.h"
#include "list_t.h"
#include "math.h"
#include <vector>

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
	SeedGenerator();

	//stores merged values, and replaces cardList with them || cleared after each shuffle
	LinkedList<Card>* tempList = new LinkedList<Card>; 

	for (int i = 0; i < nShuffles; i++)
	{
		////// SPLIT DECK INTO SMALLER DECKS THEN RANDOMLY MERGE THEM BACK TOGETEHR //////	This can be its own function

		//split deck into 4, 5, or 6 pieces
		const int MIN_SPLITS = 3;
		const int MAX_SPLITS = 5;
		int nDeckSplits = GetRandomInt(MIN_SPLITS, MAX_SPLITS);
		int numDecks = nDeckSplits + 1;
		int splitLength = cardList->GetLength() / numDecks;
		//stores each split deck	//temporarily using vector here, until I update class Obj to fulfill a similar role
		std::vector<LinkedList<Card>*> splitDeckList;
		for (int i = 0; i < nDeckSplits; i++)
		{
			splitDeckList.push_back(cardList->Break(cardList->GetLength() - splitLength, false));
		}
		//now we need to put every deck being used into a single list
		LinkedList<LinkedList<Card>*> listOfLists;
		listOfLists.InsertObject(cardList);
		for (int x = 0; x < nDeckSplits; x++)
		{
			listOfLists.InsertObject(splitDeckList[x]);
		}
		while (listOfLists.GetLength() > 0)
		{
			LinkedList<Card>* refList = (listOfLists.IterateTo(GetRandomInt(0, listOfLists.GetLength()))->nData);
			tempList->AddList(refList);
			listOfLists.DeleteObject(refList);
		}

		//clean the cardList then add the tempList to it
		cardList->EmptyList();
		cardList->AddList(tempList);

		//cleanup temp list for reuse
		tempList->EmptyList();

		////// START OF SHUFFLING CARDS TOGETHER //////	This can also be its own function

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



