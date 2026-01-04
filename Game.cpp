#include "Game.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <thread>
#include <chrono>

using namespace std;

Game::Game() {
    loadData();
    currentBet = 0;
}

void Game::clearScreen() {
    // Cross-platform clear screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Game::pause(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void Game::saveData() {
    ofstream file("blackjack_save.txt");
    if (file.is_open()) {
        file << playerChips << endl;
        file << gamesPlayed << endl;
        file << gamesWon << endl;
        file << gamesLost << endl;
        file << biggestWin << endl;
        file << longestStreak << endl;
        file.close();
    }
}

void Game::loadData() {
    ifstream file("blackjack_save.txt");
    if (file.is_open()) {
        // Try to read all values
        if (file >> playerChips >> gamesPlayed >> gamesWon >> gamesLost >> biggestWin >> longestStreak) {
            // Successfully read all 6 values
            file.close();
            currentStreak = 0;
            cout << "=====================================" << endl;
            cout << "   WELCOME BACK TO BLACKJACK!" << endl;
            cout << "=====================================" << endl;
            cout << "Your progress has been loaded." << endl;
            pause(1000);
        } else {
            // Old save file format (only had chips)
            file.close();
            // playerChips was already read, just initialize the rest
            gamesPlayed = 0;
            gamesWon = 0;
            gamesLost = 0;
            biggestWin = 0;
            currentStreak = 0;
            longestStreak = 0;
            cout << "=====================================" << endl;
            cout << "   WELCOME BACK TO BLACKJACK!" << endl;
            cout << "=====================================" << endl;
            cout << "Old save file detected. Statistics reset." << endl;
            cout << "Chips: " << playerChips << endl;
            pause(1000);
            saveData();  // Update to new format
        }
    } else {
        // No save file, brand new game
        playerChips = 1000;
        gamesPlayed = 0;
        gamesWon = 0;
        gamesLost = 0;
        biggestWin = 0;
        currentStreak = 0;
        longestStreak = 0;
        cout << "=====================================" << endl;
        cout << "   WELCOME TO BLACKJACK!" << endl;
        cout << "=====================================" << endl;
        cout << "Starting with 1000 chips." << endl;
        pause(1000);
    }
}

void Game::displayStatistics() {
    cout << "\n=====================================" << endl;
    cout << "         YOUR STATISTICS" << endl;
    cout << "=====================================" << endl;
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Games Lost: " << gamesLost << endl;
    if (gamesPlayed > 0) {
        double winRate = (double)gamesWon / gamesPlayed * 100;
        cout << "Win Rate: " << winRate << "%" << endl;
    }
    cout << "Biggest Win: " << biggestWin << " chips" << endl;
    cout << "Longest Win Streak: " << longestStreak << " games" << endl;
    cout << "Current Streak: " << currentStreak << " wins" << endl;
    cout << "=====================================" << endl;
}

void Game::updateStatistics(bool won, int profit) {
    gamesPlayed++;
    
    if (won) {
        gamesWon++;
        currentStreak++;
        
        if (currentStreak > longestStreak) {
            longestStreak = currentStreak;
        }
        
        if (profit > biggestWin) {
            biggestWin = profit;
        }
    } else {
        gamesLost++;
        currentStreak = 0;
    }
}

int Game::calculateHandValue(const vector<Card>& hand) const {
    int value = 0;
    int aces = 0;
    
    for (const Card& card : hand) {
        value += card.getValue();
        if (card.getRank() == "A") {
            aces++;
        }
    }
    
    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }
    
    return value;
}

void Game::displayHand(const vector<Card>& hand, bool hideFirst) const {
    for (size_t i = 0; i < hand.size(); i++) {
        if (hideFirst && i == 0) {
            cout << "[Hidden] ";
        } else {
            hand[i].display();
            if (i < hand.size() - 1) {
                cout << ", ";
            }
        }
    }
}

bool Game::offerInsurance() {
    // Check if dealer's visible card is an Ace
    if (dealerHand[1].getRank() != "A") {
        return false;
    }
    
    cout << "\n=====================================" << endl;
    cout << "Dealer shows an Ace!" << endl;
    cout << "Would you like insurance?" << endl;
    cout << "Insurance costs " << currentBet / 2 << " chips." << endl;
    cout << "Pays 2:1 if dealer has blackjack." << endl;
    cout << "=====================================" << endl;
    cout << "Buy insurance? (Y/N): ";
    
    char choice;
    cin >> choice;
    
    if (choice == 'Y' || choice == 'y') {
        int insuranceCost = currentBet / 2;
        
        if (insuranceCost > playerChips) {
            cout << "Not enough chips for insurance!" << endl;
            return false;
        }
        
        playerChips -= insuranceCost;
        
        // Check if dealer has blackjack
        if (calculateHandValue(dealerHand) == 21) {
            cout << "\nDealer has blackjack!" << endl;
            cout << "Insurance pays out: " << insuranceCost * 2 << " chips!" << endl;
            playerChips += insuranceCost * 3; // Return insurance + 2:1 payout
            pause(1500);
            return true;
        } else {
            cout << "\nDealer doesn't have blackjack." << endl;
            cout << "You lost your insurance bet." << endl;
            pause(1500);
        }
    }
    
    return false;
}

bool Game::offerDoubleDown() {
    // Only offer if player has exactly 2 cards
    if (playerHand.size() != 2) {
        return false;
    }
    
    // Check if player has enough chips
    if (currentBet > playerChips) {
        return false;
    }
    
    cout << "\n=====================================" << endl;
    cout << "Your hand: ";
    displayHand(playerHand);
    cout << " (Value: " << calculateHandValue(playerHand) << ")" << endl;
    
    cout << "\nDealer's hand: ";
    displayHand(dealerHand, true);
    cout << endl;
    cout << "=====================================" << endl;
    
    cout << "\n(D)ouble Down, (H)it, or (S)tand? ";
    
    char choice;
    cin >> choice;
    
    if (choice == 'D' || choice == 'd') {
        playerChips -= currentBet;
        currentBet *= 2;
        
        cout << "\nYou doubled down! Bet is now " << currentBet << " chips." << endl;
        pause(800);
        
        playerHand.push_back(deck.dealCard());
        cout << "You drew: ";
        playerHand.back().display();
        cout << endl;
        
        cout << "Your final hand: ";
        displayHand(playerHand);
        cout << " (Value: " << calculateHandValue(playerHand) << ")" << endl;
        pause(1500);
        
        return true;
    } else if (choice == 'H' || choice == 'h') {
        // Player chose to hit
        playerHand.push_back(deck.dealCard());
        cout << "\nYou drew: ";
        playerHand.back().display();
        cout << endl;
        pause(800);
        return false;  // Continue playing normally
    } else if (choice == 'S' || choice == 's') {
        // Player chose to stand - signal to end turn
        return true;  // Return true to indicate turn is over
    }
    
    return false;
}

void Game::dealInitialCards() {
    playerHand.clear();
    dealerHand.clear();
    
    cout << "\nDealing cards";
    pause(300);
    cout << ".";
    pause(300);
    cout << ".";
    pause(300);
    cout << "." << endl;
    
    playerHand.push_back(deck.dealCard());
    dealerHand.push_back(deck.dealCard());
    playerHand.push_back(deck.dealCard());
    dealerHand.push_back(deck.dealCard());
    
    pause(500);
}

void Game::playerTurn() {
    // Check for double down first (only on first turn with 2 cards)
    if (playerHand.size() == 2) {
        bool turnOver = offerDoubleDown();
        
        if (turnOver) {
            // Either doubled down or chose to stand
            if (calculateHandValue(playerHand) > 21) {
                cout << "\nBust! You went over 21." << endl;
                pause(1000);
            }
            return;
        }
        // If we get here, player chose to hit, so continue with the loop
    }
    
    // Regular hit/stand loop
    while (true) {
        cout << "\n=====================================" << endl;
        cout << "Your hand: ";
        displayHand(playerHand);
        cout << " (Value: " << calculateHandValue(playerHand) << ")" << endl;
        
        cout << "\nDealer's hand: ";
        displayHand(dealerHand, true);
        cout << endl;
        cout << "=====================================" << endl;
        
        if (calculateHandValue(playerHand) > 21) {
            cout << "\nBust! You went over 21." << endl;
            pause(1000);
            return;
        }
        
        cout << "\n(H)it or (S)tand? ";
        char choice;
        cin >> choice;
        
        if (choice == 'H' || choice == 'h') {
            playerHand.push_back(deck.dealCard());
            cout << "\nYou drew: ";
            playerHand.back().display();
            cout << endl;
            pause(800);
        } else if (choice == 'S' || choice == 's') {
            return;
        } else {
            cout << "Invalid choice. Please enter H or S." << endl;
        }
    }
}

void Game::dealerTurn() {
    cout << "\n=====================================" << endl;
    cout << "        DEALER'S TURN" << endl;
    cout << "=====================================" << endl;
    pause(1000);
    
    cout << "Dealer reveals: ";
    displayHand(dealerHand);
    cout << " (Value: " << calculateHandValue(dealerHand) << ")" << endl;
    pause(1500);
    
    while (calculateHandValue(dealerHand) < 17) {
        cout << "\nDealer hits..." << endl;
        pause(1000);
        
        dealerHand.push_back(deck.dealCard());
        cout << "Dealer drew: ";
        dealerHand.back().display();
        cout << endl;
        pause(800);
        
        cout << "Dealer's hand: ";
        displayHand(dealerHand);
        cout << " (Value: " << calculateHandValue(dealerHand) << ")" << endl;
        pause(1500);
    }
    
    if (calculateHandValue(dealerHand) > 21) {
        cout << "\nDealer busts!" << endl;
    } else {
        cout << "\nDealer stands at " << calculateHandValue(dealerHand) << "." << endl;
    }
    pause(1500);
}

void Game::determineWinner() {
    int playerValue = calculateHandValue(playerHand);
    int dealerValue = calculateHandValue(dealerHand);
    
    cout << "\n=====================================" << endl;
    cout << "           RESULTS" << endl;
    cout << "=====================================" << endl;
    cout << "Your hand value: " << playerValue << endl;
    cout << "Dealer's hand value: " << dealerValue << endl;
    cout << "=====================================" << endl;
    
    pause(1000);
    
    int profit = 0;
    bool won = false;
    
    if (playerValue > 21) {
        cout << "\nYou busted! Dealer wins." << endl;
        cout << "Lost: " << currentBet << " chips" << endl;
        profit = -currentBet;
    } else if (dealerValue > 21) {
        cout << "\nDealer busted! YOU WIN!" << endl;
        playerChips += currentBet * 2;
        profit = currentBet;
        cout << "Won: " << profit << " chips" << endl;
        won = true;
    } else if (playerValue > dealerValue) {
        cout << "\nYOU WIN!" << endl;
        playerChips += currentBet * 2;
        profit = currentBet;
        cout << "Won: " << profit << " chips" << endl;
        won = true;
    } else if (dealerValue > playerValue) {
        cout << "\nDealer wins." << endl;
        cout << "Lost: " << currentBet << " chips" << endl;
        profit = -currentBet;
    } else {
        cout << "\nPUSH! It's a tie." << endl;
        playerChips += currentBet;
        cout << "Your bet has been returned." << endl;
    }
    
    updateStatistics(won, profit);
    
    cout << "\n=====================================" << endl;
    cout << "Total chips: " << playerChips << endl;
    cout << "=====================================" << endl;
    
    pause(1500);
    saveData();
}

void Game::play() {
    clearScreen();
    
    cout << "\n=====================================" << endl;
    cout << "          BLACKJACK" << endl;
    cout << "=====================================" << endl;
    cout << "Chips: " << playerChips << endl;
    cout << "Minimum bet: $" << MINIMUM_BET << endl;
    cout << "=====================================" << endl;
    
    // Place bet
    cout << "\nEnter your bet: $";
    while (!(cin >> currentBet) || currentBet < MINIMUM_BET || currentBet > playerChips) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid bet. Enter between $" << MINIMUM_BET << " and $" << playerChips << ": $";
    }
    
    playerChips -= currentBet;
    
    // Deal cards
    dealInitialCards();
    
    cout << "\nYour hand: ";
    displayHand(playerHand);
    cout << " (Value: " << calculateHandValue(playerHand) << ")" << endl;
    
    cout << "Dealer shows: ";
    dealerHand[1].display();
    cout << endl;
    pause(1000);
    
    // Check for insurance
    bool insurancePaid = offerInsurance();
    if (insurancePaid && calculateHandValue(dealerHand) == 21) {
        // Dealer had blackjack and insurance paid out
        saveData();
        return;
    }
    
    // Check for player blackjack
    if (calculateHandValue(playerHand) == 21) {
        cout << "\n=====================================" << endl;
        cout << "       BLACKJACK!" << endl;
        cout << "=====================================" << endl;
        playerChips += currentBet * 2.5;
        int profit = currentBet * 1.5;
        cout << "Blackjack pays 3:2!" << endl;
        cout << "Won: " << profit << " chips" << endl;
        cout << "Total chips: " << playerChips << endl;
        pause(2000);
        updateStatistics(true, profit);
        saveData();
        return;
    }
    
    // Player's turn
    playerTurn();
    
    // Dealer's turn (only if player didn't bust)
    if (calculateHandValue(playerHand) <= 21) {
        dealerTurn();
    }
    
    // Determine winner
    determineWinner();
}

bool Game::playAgain() {
    if (playerChips < MINIMUM_BET) {
        cout << "\n=====================================" << endl;
        cout << "    GAME OVER!" << endl;
        cout << "=====================================" << endl;
        cout << "You don't have enough chips to continue." << endl;
        cout << "Minimum bet is $" << MINIMUM_BET << endl;
        displayStatistics();
        return false;
    }
    
    cout << "\n(P)lay again, (S)tatistics, or (Q)uit? ";
    char choice;
    cin >> choice;
    
    if (choice == 'S' || choice == 's') {
        displayStatistics();
        cout << "\nPress any key to continue...";
        cin.ignore();
        cin.get();
        return playAgain();
    }
    
    return (choice == 'P' || choice == 'p');
}