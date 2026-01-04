#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    std::string suit;   // Hearts, Diamonds, Clubs, Spades
    std::string rank;   // A, 2-10, J, Q, K
    int value;          // Numeric value for blackjack

public:
    // Constructor
    Card(std::string s, std::string r, int v);
    
    // Getters
    std::string getSuit() const;
    std::string getRank() const;
    int getValue() const;
    
    // Display card
    void display() const;
};

#endif