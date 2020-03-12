#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

using namespace std;

class Card
{
    public:
    enum Rank 
	{ 
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX,
		SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
	};

    enum Suit
	{
		CLUBS, DIAMONDS, SPADES, HEARTS
	};

    ~Card();
    Card(const Card& pCard);
    Card(Rank pRank, Suit pSuit);

    int getValue() const;
 
    void displayCard();

    Rank getRank() const;

    Suit getSuit() const;

    private:
    Rank aRank;
    Suit aSuit;

};

class Hand
{
    public:
    Hand();
    ~Hand();

    void add(Card& pCard);

    void clear();
    
    int getTotal() const;

    void displayHand();

    private:
    vector<Card> aCards; // Using vector to represent Cards contained in Hand
};

class Deck
{
    public:
    Deck();
    ~Deck();

    void populate();

    void shuffle();

    void deal(Hand& pHand);

    int getDeckSize();

    void displayDeck();

    private:
    vector<Card> aCards; // Using vector to represent Cards contained in Deck
};

class AbstractPlayer
{
    public:
    AbstractPlayer();
    ~AbstractPlayer();

    virtual bool isDrawing() const = 0; 

    bool isBusted();

    protected:
    Hand aHand; // Player's Hand

};

class HumanPlayer: public AbstractPlayer
{
    public:
    HumanPlayer();
    ~HumanPlayer();

    // Implement inherited method
    bool isDrawing() const;

    void announce(bool playerBusted, bool casinoBusted, int playerScore, int casinoScore);

    Hand& getHand();

    // void updateScore();
    
    // int getScore();

    void setWantDraw(char answer);

    private:
    // int aScore;
    char wantDraw; // Char indicating if player wants to draw or not
};

class ComputerPlayer: public AbstractPlayer
{
    public:
    ComputerPlayer();
    ~ComputerPlayer();

    // Implement inherited method
    bool isDrawing() const;

    Hand& getHand();

    // void updateScore();

    // int getScore();

    // private:
    // int aScore;
};

class BlackJackGame
{
    public:
    BlackJackGame();
    ~BlackJackGame();

    void play();

    private:
    Deck m_deck;
    ComputerPlayer m_casino;
    HumanPlayer m_player;
};



#endif