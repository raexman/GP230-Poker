//
//  Card.hpp
//  Poker
//
//  Created by Rogelio Espinoza on 10/16/16.
//  Copyright © 2016 Rogelio Espinoza. All rights reserved.
//

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
