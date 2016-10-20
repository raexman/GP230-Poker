//
//  Card.hpp
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

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>

class Card {

public:
    int suit;
    int rank;
    int pos;
    bool inDeck;
    bool inHand;
    bool isDiscarded;
	bool kept;
};

#endif /* Card_hpp */
