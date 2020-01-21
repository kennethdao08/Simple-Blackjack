#include <vector>
#include "Card.h"
#include <algorithm>
#include <random>
#include <chrono>

class Deck {

	std::vector<Card> deckOfCards;
	bool includesJoker;
	int deckSize;

private:
	void createDeck(bool joker) {
		if (joker) {
			deckOfCards.push_back(Card(0, 0, "Joker"));
		}
		addSpades();
		addDiamonds();
		addClubs();
		addHearts();

		deckSize = deckOfCards.size();
	}

	void addSpades() {
		for (int i = 1; i <= 13; i++) {
			if (i > 10) {
				deckOfCards.push_back(Card(10, i, "Spades"));
			}
			else {
				deckOfCards.push_back(Card(i, i, "Spades"));
			}
			
		}
	}

	void addDiamonds() {
		for (int i = 1; i <= 13; i++) {
			if (i > 10) {
				deckOfCards.push_back(Card(10, i, "Diamonds"));
			}
			else {
				deckOfCards.push_back(Card(i, i, "Diamonds"));
			}
		}
	}

	void addClubs() {
		for (int i = 1; i <= 13; i++) {
			if (i > 10) {
				deckOfCards.push_back(Card(10, i, "Clubs"));
			}
			else {
				deckOfCards.push_back(Card(i, i, "Clubs"));
			}
		}
	}

	void addHearts() {
		for (int i = 1; i <= 13; i++) {
			if (i > 10) {
				deckOfCards.push_back(Card(10, i, "Hearts"));
			}
			else {
				deckOfCards.push_back(Card(i, i, "Hearts"));
			}
		}
	}

public:
	Deck(bool joker){
		includesJoker = joker;
		createDeck(includesJoker);

	}

	// Returns the card on top of the deck/stack
	Card draw() {
		Card drawnCard = deckOfCards[deckSize-1];
		deckOfCards.pop_back();
		deckSize -= 1;
		return drawnCard;
	}

	int currentDeckSize() {
		return deckSize;
	}

	// Only shuffles the current deck, doesn't shuffle the deck if it is empty.
	void shuffleDeck() {
		if (isEmpty()) {
			std::cout << "The deck is empty." << '\n';
			return;
		}
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(std::begin(deckOfCards), std::end(deckOfCards), std::default_random_engine(seed));
	}

	// Resets the deck and shuffles the deck.
	void reshuffleDeck() {
		emptyDeck();
		createDeck(includesJoker);
		shuffleDeck();
	}

	// Empties out the deck to contain nothing.
	void emptyDeck() {
		if (isEmpty()) {
			std::cout << "The deck is empty already." << '\n';
			return;
		}
		deckOfCards.clear();
	}

	// Make this function private?
	// Returns true if the deck is empty, otherwise false.
	bool isEmpty() {
		if (deckOfCards.size() == 0) {
			return true;
		}
		return false;
	}

	// Prints out the contents of the deck.
	void printDeck() {
		if (isEmpty()) {
			std::cout << "The deck is empty." << '\n';
			return;
		}
		for (int i = 0; i < deckOfCards.size(); i++) {
			deckOfCards[i].printCard();
		}
	}

	~Deck() {

	}
};