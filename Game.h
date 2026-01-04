#ifndef GAME_H
#define GAME_H

#include "Deck.h"
#include "Card.h"
#include <vector>

class Game {
private:
    Deck deck;
    std::vector<Card> playerHand;
    std::vector<Card> dealerHand;
    int playerChips;
    int currentBet;
    
    // Statistics
    int gamesPlayed;
    int gamesWon;
    int gamesLost;
    int biggestWin;
    int currentStreak;
    int longestStreak;
    
    // Game settings
    const int MINIMUM_BET = 10;
    
    // Helper functions
    int calculateHandValue(const std::vector<Card>& hand) const;
    void displayHand(const std::vector<Card>& hand, bool hideFirst = false) const;
    void dealInitialCards();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
    void clearScreen();
    void pause(int milliseconds);
    
    // New features
    bool offerDoubleDown();
    bool offerInsurance();
    void displayStatistics();
    void updateStatistics(bool won, int profit);
    
    // File handling
    void saveData();
    void loadData();
    
public:
    // Constructor
    Game();
    
    // Main game methods
    void play();
    bool playAgain();
};

#endif