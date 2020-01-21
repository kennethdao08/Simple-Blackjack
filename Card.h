#include <iostream>

#ifndef CARD
#define CARD

class Card {
	int cardType;
	int value;
	std::string suit;

public:
	Card(int val, int type, std::string pic)
		: value(val), cardType(type), suit(pic)
	{
		
	}

	int getType() {
		return cardType;
	}

	int getValue() {
		return value;
	}

	void changeValue(int val) {
		value = val;
	}

	void resetCard() {
		cardType = -1;
		value = -1;
		suit = "blank";
	}

	void printCard() {
		if (cardType > 10 || cardType == 1) {
			if (cardType == 1) {
				std::cout << "Type: Ace" << std::endl;
			}

			else if (cardType == 11) {
				std::cout << "Type: Jack"  << std::endl;
			}

			else if (cardType == 12) {
				std::cout << "Type: Queen" << std::endl;
			}

			else if (cardType == 13) {
				std::cout << "Type: King" << std::endl;
			}
		}
		else {
			std::cout << "Type: " << cardType << std::endl;
		}
		
		std::cout << "Value: " << value << std::endl;
		std::cout << "Suit: " << suit << std::endl;
	}

	~Card() {
		
	}
};

#endif