//
//  LinkedList.cpp
//  Poker
//
//  Created by Rogelio Espinoza on 10/16/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
    head = NULL;
    length = 0;
}

LinkedList::~LinkedList()
{
	node* n = head;
	while (n != NULL)
	{
		node* n2 = n;
		n = n->next;
		delete n2;
	}
}

void LinkedList::addFirst(Card data)
{
    node* n = new node;
    n->data = data;
    n->next = head;
	n->prev = NULL;
    head = n;
	if (head->next != NULL)
		head->next->prev = head;

    length++;
}

void LinkedList::addLast(Card data)
{
    if(head == NULL)
    {
        addFirst(data);
        return;
    }
    
    node* last = head;
    while(last->next != NULL)
    {
        last = last->next;
    }
    
    node* n = new node;
    n->data = data;
    n->next = NULL;
	n->prev = last;
    last->next = n;
    tail = n;
}

void LinkedList::printItems(char bullet, string prefix, string suffix)
{
    node* n = head;
    while(n != NULL)
    {
        cout << bullet << prefix << n->data.rank << " of " << n->data.suit << suffix << endl;
        n = n->next;
        bullet++;
    }
}

int LinkedList::countItems()
{
    int counter = 0;
    node* n = head;
    while(n != NULL)
    {
        ++counter;
        n = n->next;
    }
    
    //Update length;
    length = counter;
    
    return counter;
}

Card LinkedList::getItem(int index)
{
    node* n = head;
    while(index > 0)
    {
        n = n->next;
        --index;
    }
    return n->data;
}

Card LinkedList::getItemBy(int suit, int rank)
{
    int counter = 0;
    node* n = head;
    Card c;
    bool foundCard = false;
    while(n !=NULL || foundCard == false)
    {
        counter++;
        c = n->data;
        foundCard = c.suit == suit && c.rank == rank;
        n = n->next;
    }
    
    return c;
    
}

LinkedList::node * LinkedList::getNode(int index)
{
    node* n = head;
    while(index > 0)
    {
        n = n->next;
        --index;
    }
    return n;
}

void LinkedList::removeFirst()
{
    if(head == NULL)
        return;
    
    node* n = head;
    head = n->next;
    delete n;
    length--;
}

void LinkedList::removeItem(int index)
{
    if(index == 0)
    {
        removeFirst();
        return;
    }
    
    node* prev = head;
    while(index > 1)
    {
        prev = prev->next;
        --index;
    }
    
    node* n = prev->next;
    prev->next = n->next;
    delete n;
}


void LinkedList::sort()
{
    for(int c = 0; c < countItems(); c++)
    {
        for(int n = (countItems() - 1); n >= 0; n--)
        {
            node *currentNode = getNode(c);
            node *nextNode = getNode(n);
            
            if((currentNode->data.rank > nextNode->data.rank && c < n) || (currentNode->data.rank < nextNode->data.rank && c > n))
            {
                node *newNode = new node;
                newNode->data = currentNode->data;
                currentNode->data = nextNode->data;
                nextNode->data = newNode->data;
            }
			else if (currentNode->data.rank == nextNode->data.rank)
			{
				if ((currentNode->data.suit > nextNode->data.suit && c < n) || (currentNode->data.suit < nextNode->data.suit && c > n))
				{
					node *newNode = new node;
					newNode->data = currentNode->data;
					currentNode->data = nextNode->data;
					nextNode->data = newNode->data;
				}
			}

        }
    }
}


