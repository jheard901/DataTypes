#pragma once

//Goals:
//Create a deck of 52 playing cards (13 cards, 4 suits)
//Create Generate() and Shuffle() functions for the deck

//The idea for this comes from the challenge of making a representation of a deck of
//playing cards. No specifics need to be accounted for such as usage of cards in Blackjack,
//Poker, or other card games.


enum Suit { SPADE, HEART, CLUB, DIAMOND };

class Card
{
private:
	int faceValue; //the numeric value of the card (ranges from 2-11)
	int type; //represents the card type ranging from "two" to "ace" (ranges from 0-12)
	Suit suit; //the suit of the card
	char name[24]; //this size should be large enough for any name possibility
public:
	Card(); //by default, card not given a suit or type until Init() called
	Card(Suit nSuit, int nType); //overloaded constructor for creating a card of specific suit and type
	//void Init(); //ideally want this for randomly initializing a card
	void Init(Suit iSuit, int iType);
	char* GetName(); //returns a string based off type & suit. eg type = 3, suit = diamond -> "four of diamonds"
	int GetType();
	int GetValue();
	Suit GetSuit();

};