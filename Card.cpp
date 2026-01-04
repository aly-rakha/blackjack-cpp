#include "Card.h"
#include <iostream>

Card::Card(std::string s, std::string r, int v) {
    suit = s;
    rank = r;
    value = v;
}

std::string Card::getSuit() const {
    return suit;
}

std::string Card::getRank() const {
    return rank;
}

int Card::getValue() const {
    return value;
}

void Card::display() const {
    std::cout << rank << " of " << suit;
}