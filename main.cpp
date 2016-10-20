//
//  main.cpp
//  Poker
//
//  Created by Rogelio Espinoza on 10/12/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include <iostream>
#include <string>
#include "Card.h"
#include "LinkedList.h"

using namespace std;

bool inputManager(string);
void requestInput();
void buildDeck();
void checkDeckStatus();
void initHand();
void printHand(bool = false);
void sortHand();
void dumpHand();
void startGame();
void startRound();
void initDraw(int);
Card drawCard();
void drawCards(int);
void discardCards(string);
void discardCardAt(int);
void discardAndDrawCardAt(int);
void swapCardAtWith(int, int, int);
void initMoney();
void payFee();
void printMoney();
void awardMoney();
void requestDiscard(string);
bool checkConditions();
string validateLetter(string);
void lostGame();
void exitGame();

LinkedList *deck;
LinkedList *hand;
LinkedList *dump;

Card *handManager;

float money;
float bet;
float award;
int numberOfSuits = 4;
int numberOfRanks = 13;
int cardsInHand = 5;
char bullet = 'A';
string listPrefix = ": ";
bool isFlush = false;
bool isRoyal = false;
int isQuad = 0;
int isTriad = 0;
int isPair = 0;
int isRoyalPair = 0;

string separator = "\n==========================================================\n";
string startGameMessage = "Welcome to CyberPoker 2999!";
string startRoundMessage = "Ready! Go!";
string swapWhichMessage = "Pick which card to swap: ";
string swapWhichRankMessage = "Enter the rank [Ace = 1 and King = 13]: ";
string swapWhichSuitMessage = "Enter the suit [C]lubs, [D]iamonds, [H]earts or [S]pades : ";
string warningMessage = "Sorry, invalid option. Please try again. ";
string discardMessage = "Type the cards you want to discard (e.g. ABC) or just type <Enter> if you don't want to discard any cards:";
string optionsMessage = "OPTIONS... \n- Type the letters for the cards you wish to keep. (i.e., \"acd\") \n- Type \"deck\" to view the cards remaining in the deck. \n- Type \"none\" to keep all cards in your hand. \n- Type \"all\" to discard all cards in your hand. \n- Type \"exit\" to exit the game. \n- Type \"swap\" to CHEAT and swap a card in your hand with one in the deck. \nYOUR CHOICE :";
string winMessage = "You've won! You got ";
string pairMessage = "One Pair (Jacks or higher)";
string twoPairMessage = "Two Pairs";
string triadMessage = "Three of a Kind";
string straightMessage = "Straight";
string flushMessage = "Flush";
string fullhouseMessage = "Full House";
string quadMessage = "Four of a Kind";
string straightFlushMessage = "Straight Flush";
string royalFlushMessage = "Royal Flush";
string lostMessage = "Sorry! No good hands :(";
string lostGameMessage = "Sorry! You're out of money. Game Over!";

int main(int argc, const char * argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	deck = new LinkedList();
	dump = new LinkedList();

	buildDeck();
	//deck->printItems();
	startGame();
}
bool inputManager(string command)
{
	//cout << "MANAGING INPUT!" << endl;
	
	if (command == "deck")
	{
		//print deck;
		deck->printItems();
		return false;
	}
	else if (command == "all")
	{
		//discard everything;
		cout << "That bad, huh?" << endl;
		discardCards("ABCDE");
		drawCards(5);
		printHand();
		return true;
	}
	else if (command == "none")
	{
		//discard none;
		cout << "Awesome! You're keeping all the cards!" << endl;
		printHand();
		return true;
	}
	else if (command == "exit")
	{
		//exit;
		exitGame();
		return true;
	}
	else if(command == "swap")
	{
		//swap cards;
		string option;

		cout << swapWhichMessage << endl;
		getline(cin, option);
		option = toupper(option[0]);
		
		while (option[0] < 'A' || option[0] > 'Z')
		{
			cout << warningMessage << swapWhichMessage << endl;
			getline(cin, option);
			option = toupper(option[0]);
		}


		int index = option[0] - bullet;

		int rank = 0;

		cout << swapWhichRankMessage << endl;
		cin >> rank;
		cin.ignore();
		cin.clear();

		while (!cin || rank > 13 || rank < 1)
		{
			cout << warningMessage << swapWhichRankMessage << endl;
			cin >> rank;
			cin.ignore();
			cin.clear();
		}

		rank = rank - 1;

		option = "";
		cout << swapWhichSuitMessage << endl;
		getline(cin, option);
		option = toupper(option[0]);

		while (option[0] != 'S' && option[0] != 'D' && option[0] != 'H' && option[0] != 'C')
		{
			cout << warningMessage << swapWhichSuitMessage << endl;
			getline(cin, option);
			option = toupper(option[0]);
		}
		int suit;
		switch (option[0])
		{
			case 'C':
				suit = 0;
				break;
			case 'D':
				suit = 1;
				break;
			case 'H':
				suit = 2;
				break;
			case 'S':
				suit = 3;
				break;
			default:
				break;
		}

		swapCardAtWith(index, suit, rank);
		printHand();
		return false;

	}
	else if(command.length() > 0 && command.length() < 4)
	{
		//Check if input is between 1 and 3;
		//Check if they're valid;
		//If not, request input again;
		//If yes, send discard;
		//cout << "GOT INPUT!";
		string validInput = validateLetter(command);

		if (validInput != "")
		{
			command = validInput;
			requestDiscard(command);
		}
		else {
			cout << warningMessage << endl;
			return false;
		}
		return true;
	}
	return false;
}

void requestInput()
{
	string command;
	
	cout << optionsMessage;
	getline(cin, command);

	bool isValidCommand = inputManager(command);

	if (isValidCommand == false)
	{
		requestInput();
	}
}

void buildDeck()
{
	//Loop to add cards to list.
	for (int s = 0; s < numberOfSuits; s++)
	{
		for (int r = 0; r < numberOfRanks; r++)
		{
			Card newCard;
			newCard.rank = r;
			newCard.suit = s;
			newCard.inDeck = true;

			deck->addFirst(newCard);
		}
	}
}

void checkDeckStatus()
{
	cout << separator;
	cout << "Deck has: " << deck->countItems() << endl;
	cout << "Hand has: " << hand->countItems() << endl;
	cout << "Dump has: " << dump->countItems() << endl;
	cout << separator;
}

void startGame()
{
	cout << endl << separator << startGameMessage << separator << endl;

	initMoney();
	startRound();
}

void startRound()
{
	cout << endl << separator << startRoundMessage << separator << endl;

	printMoney();
	payFee();
	initHand();
	initDraw(cardsInHand);
	printHand();
	checkDeckStatus();
	requestInput();

	//If player won, award him money.
	if (checkConditions()) awardMoney();

	//Clean hand.
	dumpHand();

	system("pause");
	
	//Check if player has enough money for next round.
	if(money > 0) startRound();
	else lostGame();
}

void requestDiscard(string input)
{
	int inputMax = 3;
	int inputMin = 1;
	bool isValid = false;
	bool discarding = false;

	//Check for answer;
	//If "No", continue;
	//If "Yes", request which cards;

	//cout << input << ". Length: " << input.length() << " and it's valid: " << isValid << "." << endl;

	//Keep asking until the bastard gives us a valid input.
	/*
	while (!cin || input.length() > inputMax || input.length() < inputMin || isValid == false)
	{
		cout << warningMessage << discardMessage << endl;
		getline(cin, input);

		string validInput = validateLetter(input);
		if (validInput != "" && validInput.length() == input.length())
		{
			input = validInput;
			isValid = true;
		}
	}
	*/

	//Discard cards.
	discardCards(input);
	hand->markKept();
	drawCards(input.length());
	sortHand();
	printHand(true);
}

string validateLetter(string input)
{
	string upperInput;

	//Check each character in input and transform it to uppercase.
	for (char l : input)
	{

		l = toupper(l);
		//Check if it's between the A-Z range.
		if (l < 'A' || l > 'Z')
		{
			upperInput = "";
			return upperInput;
		}
		else
		{
			upperInput += toupper(l);
		}
	}

	return upperInput;
}

void initMoney()
{
	money = 10.0;
	bet = 1.0;
}

void payFee()
{
	money -= bet;
	cout << "You bet $" << bet << " and now you have $" << money << " left!" << endl;
}

void printMoney()
{
	cout << "You have $" << money << "." << endl;
}
void awardMoney()
{
	money += award;
	cout << "You won " << "$" << award << "!" << endl;
}
void initHand()
{
	//handManager = new Card[cardsInHand];
	hand = new LinkedList();
}

void printHand(bool keptTag)
{
	cout << "Your hand has the following cards:" << endl;
	hand->printItems(bullet, listPrefix, "", keptTag);
}

void sortHand()
{
	hand->sort();
}

void dumpHand()
{
	while (hand->countItems() > 0)
	{
		//cout << "Dumping " << hand->countItems() << "." << endl;
		discardCardAt(0);
	}
}

void initDraw(int qt)
{
	for (int q = 0; q < qt; q++)
	{
		hand->addFirst(drawCard());
		//handManager[q] = randomCard;
	}

	hand->sort();
}

void discardCardAt(int index)
{
	Card discardedCard = hand->getItem(index);
	//hand->getNode(index)->data.kept = false;
	dump->addFirst(discardedCard);
	hand->removeItem(index);
}

void discardAndDrawCardAt(int index)
{
	discardCardAt(index);
	hand->addFirst(drawCard());
}

void discardCards(string nums)
{
	string sortedNums = "";
	string unsortedNums = nums;
	int greaterNum = 0;
	while (unsortedNums.length() > 0)
	{
		//Get greater char from options.
		for (int n = 0; n < unsortedNums.length() - 1; n++)
		{
			char currentNum = unsortedNums[n];
			char nextNum = unsortedNums[n + 1];

			int currentGreaterNum = currentNum > nextNum ? n: n + 1;
			
			if (unsortedNums[greaterNum] < unsortedNums[currentGreaterNum])
			{
				greaterNum = currentGreaterNum;
			}
		}

		char greaterLetter = unsortedNums.at(greaterNum);
		int index =  greaterLetter - bullet;
		//cout << "GREATER NUM IS: " << greaterLetter << ", INDEX IS: " << index << "." << endl;

		//sortedNums += unsortedNums[greaterNum];
		unsortedNums.erase(greaterNum, 1);
		greaterNum = 0;
		
		discardCardAt(index);
	}

	//hand->addFirst(drawCard());
}

void swapCardAtWith(int index, int suit, int rank)
{
	/*
	discardCardAt(index);
	//This should be deck;
	
	Card pickedCard = deck->getItemBy(suit, rank);
	if (pickedCard == NULL)
	{
		pickedCard = dump->getItemBy(suit, rank);
	}
	hand->addFirst(pickedCard);
	*/
	LinkedList::node *cardNode = hand->getNode(index);
	string swappingMessage = "You swapped the ";
	swappingMessage.append(hand->getRankName(cardNode->data.rank));
	swappingMessage.append(" of ");
	swappingMessage.append(hand->getSuitName(cardNode->data.suit));

	//Convert to desired card.
	cardNode->data.rank = rank;
	cardNode->data.suit = suit;
	
	cout << swappingMessage << " with a " << hand->getRankName(rank) << " of " << hand->getSuitName(suit) << "." << endl;
}

Card drawCard()
{
	//Get random index between the existing cards range.
	if (deck->countItems() < 1)
	{
		deck = dump;
		dump = new LinkedList();
	}
	int randomIndex = rand() % deck->countItems();
	Card randomCard = deck->getItem(randomIndex);
	//randomCard.kept = true;
	deck->removeItem(randomIndex);

	return randomCard;
}

void drawCards(int draws)
{
	string drawMessage = "You've drawn a ";
	
	for (int d = 0; d < draws; d++)
	{
		Card drawnCard = drawCard();
		hand->addLast(drawnCard);

		//Print drawn message;
		if (d > 0 && d < draws - 1)
		{
			drawMessage += ",";
		}
		else if(d == draws - 1)
		{
			drawMessage += " and ";
		}
		drawMessage += hand->getRankName(drawnCard.rank); 
		drawMessage += " of "; 
		drawMessage += hand->getRankName(drawnCard.suit);
	}

	cout << drawMessage << endl;
}

bool checkConditions()
{
	isFlush = false;
	isQuad = 0;
	isTriad = 0;
	isPair = 0;
	isRoyalPair = 0;
	isRoyal = false;
	//Check if suit's the same;
	for (int s = 0; s < 4; s++)
	{
		Card currentCard = hand->getItem(s);
		Card nextCard = hand->getItem(s + 1);

		isFlush = currentCard.suit == nextCard.suit;
		if (isFlush == false) break;
	}
	//if (isFlush) cout << "isSuit!" << endl;

	//Create ranks array to count cards with same ranks.
	int pairs[13] = { 0 };
	//Count the ranks;
	for (int r = 0; r < 5; r++)
	{
		Card currentCard = hand->getItem(r);
		pairs[currentCard.rank]++;
	}
	//Check for pairs;
	for (int p = 0; p < 13; p++)
	{
		switch (pairs[p])
		{
		case 4:
			isQuad++;
			//cout << "isQuad!" << endl;
			break;
		case 3:
			isTriad++;
			//cout << "isTriad!" << endl;
			break;
		case 2:
			isPair++;
			if (pairs[p] > 9 || pairs[p] == 0) isRoyalPair++;
			//cout << "isPair!" << endl;
			break;
		case 1:
			break;
		default:
			break;
		}
		//cout << p << ": " << pairs[p] << " of " << getNameOfCards(p) << "s." << endl;
	}

	//Check for sequence.
	int counter = 0;
	int firstRank = hand->getItem(0).rank;

	for (int c = 0; c < 4; c++)
	{
		int currentRank = hand->getItem(c).rank;
		int nextRank = hand->getItem(c + 1).rank;

		//Check if current and next ranks are sequential.
		if ((currentRank + 1) == nextRank)
			counter++;

		//Validate aces.
		if (c == 3 && nextRank == 12 && firstRank == 0)
		{
			counter++;
			isRoyal = true;
		}

	}
	//If
	bool isStraight = counter == 4;
	//if (isStraight) cout << "isStraight!" << endl;

	string winningHandMessage;

	if (isStraight)
	{
		if (isFlush)
		{
			if (isRoyal)
			{
				winningHandMessage = royalFlushMessage;
				award = 800;
			}
			else
			{
				winningHandMessage = straightFlushMessage;
				award = 50;
			}
		}
		else
		{
			winningHandMessage = straightMessage;
			award = 4;
		}
	}
	else if (isFlush)
	{
		winningHandMessage = flushMessage;
		award = 6;
	}
	else
	{
		if (isQuad == 1)
		{
			winningHandMessage = quadMessage;
			award = 25;
		}
		else
		{
			if (isTriad == 1)
			{
				if (isPair == 1)
				{
					winningHandMessage = fullhouseMessage;
					award = 9;
				}
				else
				{
					winningHandMessage = triadMessage;
					award = 3;
				}
			}
			else
			{
				if (isPair > 0)
				{
					if (isPair > 1)
					{
						winningHandMessage = twoPairMessage;
						award = 2;
					}
					else
					{
						if (isRoyalPair > 0)
						{
							winningHandMessage = pairMessage;
							award = 1;
						}
					}
				}
				else 
				{
				}
			}
		}
	}

	bool isPoker = isFlush || isStraight || isRoyalPair > 0 || isQuad > 0 || isTriad > 0 || isPair > 1;

	if (isPoker)
	{
		cout << winMessage << winningHandMessage << "!" << endl;

	}
	else
	{
		cout << lostMessage << "!" << endl;
	}
	return isPoker;
}

void lostGame()
{
	cout << lostGameMessage << endl;
	exitGame();
}

void exitGame()
{
	delete deck;
	delete hand;
	delete dump;
	deck = NULL;
	hand = NULL;
	dump = NULL;
	exit(0);
}



