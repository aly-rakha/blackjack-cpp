#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
private:
    std::vector<Card> cards;
    int currentCard;  // Index of next card to deal

public:
    // Constructor
    Deck();
    
    // Methods
    void shuffle();
    Card dealCard();
    int cardsRemaining() const;
};

#endif