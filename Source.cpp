#include <iostream>
#include "Card.h"
#include "Deck.h"



int aceIndex(std::vector<Card>& hand) {
	int index = -1;
	for (int i = 0; i < hand.size(); i++) {
		if (hand[i].getValue() == 1) {
			index = i;
			return index;
		}
	}
	return index;
}

int getTotal(std::vector<Card>& hand) {
	int total = 0;
	for (int i = 0; i < hand.size(); i++) {
		total += hand[i].getValue();
	}
	return total;
}

void checkBlackJack(std::vector<Card>& hand, bool& game, bool& bj) {
	int total = hand[0].getValue() + hand[1].getValue();
	if (total == 21) {
		game = true;
		bj = true;
	}
	return;
}

void changeAce(std::vector<Card>& hand) {
	int handTotal = getTotal(hand);
	int ace = aceIndex(hand);
	if (ace != -1) {
		hand[ace].changeValue(11);
	}
	
}

void hit(std::vector<Card>& hand, Deck & deck) {
	hand.push_back(deck.draw());
	int handTotal = getTotal(hand);
	int ace = aceIndex(hand);
	
	if (ace != -1 && handTotal > 21) {
		hand[ace].changeValue(1);
	}
	else if (ace != -1 && handTotal + 11 <= 21) {
		hand[ace].changeValue(11);
	}
	

}

void noBust(std::vector<Card> dealers, std::vector<Card> players) {
	int dealerTotal = getTotal(dealers);
	int playerTotal = getTotal(players);

	if (dealerTotal > playerTotal) {
		std::cout << "Dealer has won!" << '\n';
	}
	else if (dealerTotal < playerTotal) {
		std::cout << "You won!!" << '\n';
	}
	else {
		std::cout << "Tied!!!!!" << '\n';
	}
}

void dealersTurn(std::vector<Card> & hand, Deck & deck, bool & game) {
	int total = getTotal(hand);
	if (total < 17) {
		hit(hand, deck);
	}
	else {
		game = true;
	}
}

void checkBust(std::vector<Card> hand, bool playersTurn, bool & game, bool & bust) {
	int total = getTotal(hand);
	if (total > 21) {
		if (playersTurn) {
			std::cout << "You have busted!" << '\n';
			std::cout << "Better luck next time!" << '\n';
			game = true;
			bust = true;
		}

		else {
			std::cout << "Dealer has busted!" << '\n';
			std::cout << "You won!!" << '\n';
			game = true;
			bust = true;
		}
	}
	return;
}

void initialDraw(std::vector<Card>& dealers, std::vector<Card>& players, Deck & deck) {
	for (int i = 0; i < 2; i++) {
		players.push_back(deck.draw());
		dealers.push_back(deck.draw());
	}
}

void emptyHands(std::vector<Card>& dealers, std::vector<Card>& players) {
	dealers.clear();
	players.clear();
}

std::string getDecision() {
	std::string decision;
	bool running = true;
	while (running) {
		std::cout << "Will you 'hit' or 'stay': ";
		std::cin >> decision;
		std::cout << '\n' << '\n';

		if (decision == "hit" || decision == "stay") {
			break;
		}
		std::cout << "That is not a valid decision. Try again." << '\n';
		
	}
	
	std::cout << "You have decided to: " << decision << '\n' << '\n';

	return decision;
}

void printStart() {
	std::cout << "Welcome to Blackjack!" << '\n' << "We will get started right away!";
}

void printNewLines() {
	std::cout << '\n' << '\n' << '\n';
}

void printSituation(std::vector<Card> dealer, std::vector<Card> playerHand, bool playersTurn) {
	if (!playersTurn) {
		std::cout << "Dealer's hand: " << '\n';
		for (int i = 0; i < dealer.size(); i++) {
			dealer[i].printCard();
		}
	}
	
	else {
		std::cout << "Dealer's card: " << '\n';
		dealer[0].printCard();
	}

	std::cout << '\n' << '\n';

	std::cout << "Player's hand: " << '\n';
	for (int k = 0; k < playerHand.size(); k++) {
		playerHand[k].printCard();
	}

	std::cout << '\n' << '\n';

}

Deck noJokerDeck() {
	Deck blackJack(false);
	return blackJack;
}

int main() {
	bool gameOver = false;
	bool playersTurn = true;
	bool busted = false;
	bool bJ = false;

	Deck blackJack = noJokerDeck();
	blackJack.shuffleDeck();

	std::vector<Card> dealersHand;
	std::vector<Card> playersHand;
	

	printStart();
	printNewLines();

	initialDraw(dealersHand, playersHand, blackJack);
	
	changeAce(dealersHand);
	changeAce(playersHand);

	printSituation(dealersHand, playersHand, playersTurn);

	checkBlackJack(dealersHand, gameOver, bJ);
	checkBlackJack(playersHand, gameOver, bJ);

	

	std::string playerDecision;
	
	while (!gameOver) {
		
		if (!playersTurn) {
			dealersTurn(dealersHand, blackJack, gameOver);
			printSituation(dealersHand, playersHand, playersTurn);
			checkBust(dealersHand, playersTurn, gameOver, busted);
		}

		if (playersTurn) {
			playerDecision = getDecision();
		}
		

		if (playerDecision == "hit") {
			hit(playersHand, blackJack);
			printSituation(dealersHand, playersHand, playersTurn);
		}

		if (playersTurn) {
			checkBust(playersHand, playersTurn, gameOver, busted);
		}

		if (playerDecision == "stay") {
			playersTurn = false;
			std::cout << "Dealer's turn." << '\n';
			printNewLines();
			playerDecision = "Done";
		}
		
		

	}
	if (!busted && !bJ) {
		noBust(dealersHand, playersHand);
		std::cout << "Game Over!";
	}
	if (bJ) {
		std::cout << "Black Jack!!!" << '\n';
		std::cout << "Game Over!";
	}
	return 0;
}