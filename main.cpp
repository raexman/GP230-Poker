//
//  main.cpp
//  Poker
//
//  Created by Rogelio Espinoza on 10/12/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include <iostream>
#include <string>
#include "Card.h"
#include "LinkedList.h"

using namespace std;

bool inputManager(string);
void requestInput(string);
void buildDeck();
void checkDeckStatus();
void initHand();
void printHand();
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
void requestDiscard();
bool checkConditions();
string validateLetter(string);
void exit();

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
bool sameSuit = false;
int isQuad = 0;
int isTriad = 0;
int isPair = 0;

string separator = "\n==========================================================\n";
string startGameMessage = "Welcome to CyberPoker 2999!";
string startRoundMessage = "Ready! Go!";
string swapWhichMessage = "Pick which card to swap: ";
string swapWithMessage = "Enter the rank and the suit together (e.g. Ace of Diamonds would be \"AD\"";
string warningMessage = "Invalid option, try again. ";
string discardMessage = "Type the cards you want to discard (e.g. ABC) or just type <Enter> if you don't want to discard any cards:";
string optionsMessage = "OPTIONS... \n- Type the letters for the cards you wish to keep. (i.e., \"acd\") \n- Type \"deck\" to view the cards remaining in the deck. \n- Type \"none\" to discard all cards in your hand. \n- Type \"all\" to keep all cards in your hand. \n- Type \"exit\" to exit the game. \n- Type \"swap\" to CHEAT and swap a card in your hand with one in the deck. \nYOUR CHOICE :";


int main(int argc, const char * argv[]) {
	deck = new LinkedList();
	dump = new LinkedList();

	buildDeck();
	//deck->printItems();
	startGame();
}
bool inputManager(string command)
{
	
	if (command == "deck")
	{
		//print deck;
		deck->printItems();
		return false;
	}
	else if (command == "none")
	{
		//discard everything;
		discardCards("ABCDE");
		drawCards(5);
		return true;
	}
	else if (command == "all")
	{
		//discard none;
		return true;
	}
	else if (command == "exit")
	{
		//exit;
		exit();
		return true;
	}
	else if(command == "swap")
	{
		//swap cards;
		string option;

		cout << swapWhichMessage << endl;
		printHand();
		getline(cin, option);
		option = toupper(option[0]);
		
		while (option[0] < 'A' || option[0] > 'Z')
		{
			cout << warningMessage << swapWhichMessage << endl;
			getline(cin, option);
			option = toupper(option[0]);
		}

		int index = option[0] - bullet;
		Card swapCard = hand->getItem(index);

		//swapCardAtWith()

		return false;

	}
	else if(command.length() > 0 && command.length() < 4)
	{
		//Check if input is between 1 and 3;
		//Check if they're valid;
		//If not, request input again;
		//If yes, send discard;
		string validInput = validateLetter(command);

		if (validInput != "")
		{
			command = validInput;
			requestDiscard();
		}
		else {
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
	getline(cin, command, ' ');

	bool isValidCommand = inputManager(command);

	if (isValidCommand == false)
	{
		requestInput(command);
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

	if (checkConditions())
		awardMoney();
	dumpHand();
	startRound();
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
	drawCards(input.length());
	sortHand();
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
	cout << "You bet $" << bet << "and now you have $" << money << " left!" << endl;
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

void printHand()
{
	cout << "Your hand has the following cards:" << endl;
	hand->printItems(bullet, listPrefix, "");
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
	dump->addFirst(hand->getItem(index));
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
	discardCardAt(index);
	Card pickedCard = hand->getItemBy(suit, rank);
	hand->addFirst(pickedCard);
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
		drawMessage += drawnCard.rank; 
		drawMessage += " of "; 
		drawMessage += drawnCard.suit;
	}

	cout << drawMessage << endl;
}

bool checkConditions()
{
	sameSuit = false;
	isQuad = 0;
	isTriad = 0;
	isPair = 0;

	//Check if suit's the same;
	for (int s = 0; s < 4; s++)
	{
		Card currentCard = hand->getItem(s);
		Card nextCard = hand->getItem(s + 1);

		sameSuit = currentCard.suit == nextCard.suit;
		if (sameSuit == false) break;
	}
	if (sameSuit) cout << "isSuit!" << endl;

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
			counter++;

	}
	//If
	bool isStraight = counter == 4;
	if (isStraight) cout << "isStraight!" << endl;
	return sameSuit || isPair > 0 || isTriad > 0 || isQuad > 0 || isStraight;
}

void exit()
{
	//exit;
	//system("");
}
