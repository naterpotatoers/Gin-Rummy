#include <algorithm>
#include <vector>
#include <queue>
#include "Card.hpp"

class Deck
{
private:
	std::vector<std::string> deckOfCards = {
		"As", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "10s", "Js", "Qs", "Ks",
		"Ah", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "10h", "Jh", "Qh", "Kh",
		"Ac", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "10c", "Jc", "Qc", "Kc",
		"Ad", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "10d", "Jd", "Qd", "Kd"};
	std::queue<Card> deck;

public:
	Deck()
	{
		shuffleDeck();
		for (std::string s : deckOfCards)
		{
			Card temp(s);
			deck.push(temp);
		}
	}
	
	void shuffleDeck()
	{
		random_shuffle(deckOfCards.begin(), deckOfCards.end());
	}
};
