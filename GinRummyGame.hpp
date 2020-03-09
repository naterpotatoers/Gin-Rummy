// #include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <bitset>
#include <string>
#include <stack>
#include <list>
#include "Deck.hpp"

class GinRummyGame
{
private:
    bool winCondition;
    bool playersTurn;
    Card tempCard;
    Deck mainDeck;
    std::string strInput;
    std::stack<Card> discardPile;
    std::list<Card> playerHands[2];

public:
    GinRummyGame();
    void declareCurrPlayer();
    void currPlayerOptions();
    void executeMove();
    void discardCard();
    void checkWinCondition();
    void changePlayers();
    int checkForRuns();
    int checkForMelds();
};