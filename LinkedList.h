//
//  LinkedList.hpp
//  Poker
//
//  Created by Rogelio Espinoza on 10/16/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

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
	void printItems(char index = 0, string prefix = "", string suffix = "");
    int countItems();
    void addFirst(Card data);
    void addLast(Card data);
    Card getItem(int index);
    Card getItemBy(int suit, int rank);
    node* getNode(int index);
    void removeFirst();
    void removeItem(int index);
    void deleteLinkedList();
    void sort();
};

#endif /* LinkedList_hpp */
