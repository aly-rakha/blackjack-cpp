#include "Game.h"
#include <iostream>

using namespace std;

int main() {
    Game game;
    
    do {
        game.play();
    } while (game.playAgain());
    
    cout << "\nThanks for playing!" << endl;
    
    return 0;
}