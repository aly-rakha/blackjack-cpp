#include <iostream>
#include <vector>
#include "Card.h"

using namespace std;

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
	cout << rank << " of " << suit;
}

std::vector<std::string> Card::getCardArt() const {
    std::vector<std::string> art(5);
    
    std::string suitSymbol;
    if (suit == "Hearts") suitSymbol = "♥";
    else if (suit == "Diamonds") suitSymbol = "♦";
    else if (suit == "Clubs") suitSymbol = "♣";
    else if (suit == "Spades") suitSymbol = "♠";
    
    std::string displayRank = rank;
    if (rank.length() == 1) displayRank = rank + " ";
    
    art[0] = " ┌─────┐";
    art[1] = " │" + displayRank + "   │";
    art[2] = " │  " + suitSymbol + "  │";
    art[3] = " │   " + displayRank + "│";
    art[4] = " └─────┘";
    
    return art;
}
