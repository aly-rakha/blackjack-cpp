#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

class Card {
	private:
		std::string suit;
		std::string rank;
		int value;

	public:
		Card(std::string s, std::string r, int v);
		std::string getSuit() const;
		std::string getRank() const;
		int getValue() const;
		void display() const;
		std::vector<std::string> getCardArt() const;
};

#endif
