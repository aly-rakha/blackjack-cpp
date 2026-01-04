#include "Deck.h"
#include <algorithm>
#include <random>

Deck::Deck() {
    std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    
    // Create all 52 cards
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards.push_back(Card(suits[i], ranks[j], values[j]));
        }
    }
    
    currentCard = 0;
    shuffle();
}

void Deck::shuffle() {
    std::random_device rd;              // Gets truly random seed from hardware
    std::mt19937 g(rd());              // Mersenne Twister random generator
    std::shuffle(cards.begin(), cards.end(), g);
    currentCard = 0;
}

Card Deck::dealCard() {
    if (currentCard >= cards.size()) {
        shuffle();  // Reshuffle if we run out
    }
    return cards[currentCard++];
}

int Deck::cardsRemaining() const {
    return cards.size() - currentCard;
}