#include <string>

class Card
{
private:
    enum Suit
    {
        SPADE,
        HEART,
        CLUB,
        DIAMOND
    };

    enum Value
    {
        ZERO,
        ACE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    };

public:
    Suit cardSuit;
    Value cardValue;

    Card(std::string input)
    {
        parse(input);
    }

    void cardToBinary();

    void parse(std::string input)
    {
        char first = input.at(0);
        char second = input.at(1);

        switch (first)
        {
        case '1':
            this->cardValue = TEN;
            break;
        case '2':
            this->cardValue = TWO;
            break;
        case '3':
            this->cardValue = THREE;
            break;
        case '4':
            this->cardValue = FOUR;
            break;
        case '5':
            this->cardValue = FIVE;
            break;
        case '6':
            this->cardValue = SIX;
            break;
        case '7':
            this->cardValue = SEVEN;
            break;
        case '8':
            this->cardValue = EIGHT;
            break;
        case '9':
            this->cardValue = NINE;
            break;
        case 'A':
            this->cardValue = ACE;
            break;
        case 'a':
            this->cardValue = ACE;
            break;
        case 'J':
            this->cardValue = JACK;
            break;
        case 'j':
            this->cardValue = JACK;
            break;
        case 'Q':
            this->cardValue = QUEEN;
            break;
        case 'q':
            this->cardValue = QUEEN;
            break;
        case 'K':
            this->cardValue = KING;
            break;
        case 'k':
            this->cardValue = KING;
            break;
        }

        switch (second)
        {
        case 's':
            this->cardSuit = SPADE;
            break;
        case 'S':
            this->cardSuit = SPADE;
            break;
        case 'h':
            this->cardSuit = HEART;
            break;
        case 'H':
            this->cardSuit = HEART;
            break;
        case 'd':
            this->cardSuit = DIAMOND;
            break;
        case 'D':
            this->cardSuit = DIAMOND;
            break;
        case 'c':
            this->cardSuit = CLUB;
            break;
        case 'C':
            this->cardSuit = CLUB;
            break;
        }
    }

    std::string cardToString()
    {
        std::string sValue, sSuit;
        switch (this->cardValue)
        {
        case ZERO:
            sValue = "cardToString() Error - ZERO value.\n";
            break;
        case ACE:
            sValue = "A";
            break;
        case JACK:
            sValue = "J";
            break;
        case QUEEN:
            sValue = "Q";
            break;
        case KING:
            sValue = "K";
            break;
        case TWO:
            sValue = "2";
            break;
        case THREE:
            sValue = "3";
            break;
        case FOUR:
            sValue = "4";
            break;
        case FIVE:
            sValue = "5";
            break;
        case SIX:
            sValue = "6";
            break;
        case SEVEN:
            sValue = "7";
            break;
        case EIGHT:
            sValue = "8";
            break;
        case NINE:
            sValue = "9";
            break;
        case TEN:
            sValue = "10";
            break;
        }

        switch (this->cardSuit)
        {
        case SPADE:
            sSuit = "s";
            break;
        case HEART:
            sSuit = "h";
            break;
        case CLUB:
            sSuit = "c";
            break;
        case DIAMOND:
            sSuit = "d";
            break;
        }
        std::string fullCard = sValue + sSuit;
        return fullCard;
    }
};