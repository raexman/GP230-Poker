//
//  LinkedList.hpp
//  Poker
//
//  Created by Rogelio Espinoza on 10/16/16.
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

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>
#include <string>
#include "Card.h"

using namespace std;

class LinkedList
{
public:
    struct node
    {
        Card data;
        node* prev;
        node* next;
    };
    
    node* head;
    node* tail;
    int length;
    
    LinkedList();
	~LinkedList();
	void printItems(char index = 0, string prefix = "", string suffix = "", bool keptTag = false);
    int countItems();
    void addFirst(Card data);
    void addLast(Card data);
    Card getItem(int index);
    Card getItemBy(int suit, int rank);
    node* getNode(int index);
    void removeFirst();
    void removeItem(int index);
	void markKept();
    void sort();
	string getRankName(int rank);
	string getSuitName(int suit);
};

#endif /* LinkedList_hpp */
