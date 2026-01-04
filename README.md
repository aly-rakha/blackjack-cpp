# Blackjack Game in C++

A fully-featured command-line Blackjack game written in C++.

## Features

- 🎲 **Classic Blackjack gameplay** - Play against the dealer
- 💰 **Betting system** - Start with 1000 chips, minimum bet of $10
- 📊 **Statistics tracking** - Win rate, biggest win, win streaks
- 💾 **Save/Load system** - Your progress persists between sessions
- 🎯 **Double Down** - Double your bet and get one more card
- 🛡️ **Insurance** - Protect against dealer blackjack when they show an Ace
- ✨ **Polished UI** - Clean formatting with animations and pauses

## How to Play

### Compile and Run
```bash
g++ -o blackjack main.cpp Card.cpp Deck.cpp Game.cpp
./blackjack
```

### Game Rules

- Get as close to 21 as possible without going over
- Beat the dealer's hand to win
- Aces count as 1 or 11
- Face cards (J, Q, K) count as 10
- Dealer must hit on 16 or less, stands on 17+
- Blackjack (21 with 2 cards) pays 3:2

### Game Options

- **Hit (H)** - Take another card
- **Stand (S)** - Keep your current hand
- **Double Down (D)** - Double your bet, get one card, end turn
- **Insurance (Y/N)** - Bet half your wager that dealer has blackjack (when dealer shows Ace)

## Project Structure
```
.
├── Card.h          # Card class header
├── Card.cpp        # Card class implementation
├── Deck.h          # Deck class header
├── Deck.cpp        # Deck class implementation
├── Game.h          # Game logic header
├── Game.cpp        # Game logic implementation
└── main.cpp        # Entry point
```

## Technical Details

- **Language:** C++
- **Concepts Used:**
  - Object-Oriented Programming (classes, encapsulation)
  - File I/O for save/load functionality
  - STL containers (vectors)
  - Random number generation
  - Multiple file compilation

## Screenshots
```
=====================================
          BLACKJACK
=====================================
Chips: 1000
Minimum bet: $10
=====================================

Your hand: A of Hearts, 10 of Spades (Value: 21)

BLACKJACK!
```

## Future Improvements

- [ ] Split pairs functionality
- [ ] Multiple decks (6-deck shoe)
- [ ] Card counting hints
- [ ] Achievements system
- [ ] Multiplayer mode

## Author

Aly Rakha

## License

Free to use for educational purposes.
```
