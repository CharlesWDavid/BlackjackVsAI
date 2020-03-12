#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include "blackjack.h"

using namespace std;

Card::~Card(){}

// Copy Constructor
Card::Card(const Card& pCard)
{
    aRank = pCard.getRank();
    aSuit = pCard.getSuit();
}

Card::Card(Rank pRank, Suit pSuit)
{
    aRank = pRank;
    aSuit = pSuit;
}

// Returns the integer value of the Rank
// If card is JACK, QUEEN, or KING add 10 points
// ONE is worth 1 point but can be worth 11 if advantageous for the player (case taken care in getTotal())
int Card::getValue() const
{ 
    if (aRank >= 11 && aRank <= 13) return 10; 
    return aRank; 
}

// Displays card according to its Rank and Suit (e.g. "THREE of HEARTS" is displayed as "3H")
// Rank is displayed either as an int from 1 to 10 or a char 'J', 'Q', 'K'
// Suit is displayed using its starting character (e.g. 'C' for "CLUBS")
void Card::displayCard()
{
    if (aSuit == CLUBS)
    {
        if (aRank == JACK ) 
            cout << "J" << "C ";
        else if (aRank == QUEEN) 
            cout << "Q" << "C ";
        else if (aRank == KING) 
            cout << "K" << "C ";
        else 
            cout << aRank << "C ";
    }        
    else if (aSuit == DIAMONDS)
    {
        if (aRank == JACK ) 
            cout << "J" << "D ";
        else if (aRank == QUEEN) 
            cout << "Q" << "D ";
        else if (aRank == KING) 
            cout << "K" << "D ";
        else 
            cout << aRank << "D ";
    }   
    else if (aSuit == SPADES)
    {
        if (aRank == JACK ) 
            cout << "J" << "S ";
        else if (aRank == QUEEN) 
            cout << "Q" << "S ";
        else if (aRank == KING) 
            cout << "K" << "S ";
        else 
            cout << aRank << "S ";
    } 
    else if (aSuit == HEARTS)
    {
        if (aRank == JACK ) 
            cout << "J" << "H ";
        else if (aRank == QUEEN) 
            cout << "Q" << "H ";
        else if (aRank == KING) 
            cout << "K" << "H ";
        else 
            cout << aRank << "H ";
    }    
    else
        cout << " (NULL) ";
    
}

Card::Rank Card::getRank() const { return aRank; }

Card::Suit Card::getSuit() const { return aSuit; }

// ####################### HAND ###############################

Hand::Hand(){}

Hand::~Hand(){}

// Adds Card to the Hand by inserting Card at end of vector
void Hand::add(Card& pCard){ aCards.push_back(pCard); }

// Clear the Hand by clearing the vector
void Hand::clear(){ aCards.clear(); }

int Hand::getTotal() const
{
    int handTotal = 0;
    if (aCards.size() == 0) return handTotal; // Return 0 if there are no cards in hand

    int numOfOnes = 0; // Count the number of ONEs that appear to decide after if they are worth 1 or 11
    for (unsigned int i = 0; i < aCards.size(); i++)
    {
        int curVal = aCards[i].getValue();
        if (curVal == 1) numOfOnes++;
        else handTotal += aCards[i].getValue();
    }

    if (numOfOnes > 1) handTotal += numOfOnes; // If there are multiple ONEs then they must be worth 1 or else Bust
    else if (numOfOnes == 1){
        if ((handTotal + 11) <= 21) handTotal += 11; // ONE is worth 11 if there is no Bust
        else handTotal++;  // If adding 11 is a bust then ONE has to be worth 1
    }
        
    return handTotal;
}

// Display the Cards in the Hand to the screen
void Hand::displayHand()
{
    for (unsigned int i = 0; i < aCards.size(); i++)
    {
        aCards[i].displayCard();
    }
}

// ####################### DECK ###############################

Deck::Deck()
{ 
    populate(); 
    shuffle();
}

Deck::~Deck(){}

// Populate the Deck
void Deck::populate()
{
    aCards.clear(); // Ensure Deck is empty before populating it

    // For each Suit create 13 cards (i.e. 13 Ranks)
    for(int suit = 0; suit < 4; suit++)
    {
        for(int rank = 1; rank < 14; rank++)
        {
            aCards.emplace_back((Card::Rank) rank, (Card::Suit) suit);
        }
    }
}

void Deck::shuffle()
{
    if (aCards.empty()) return; // Don't shuffle if deck is empty

    srand(clock());
    int size = aCards.size();
    for (int i = 0; i < size - 1; i++) 
    {
        int j = i + rand() % (size - i);
        swap(aCards[i], aCards[j]);
    }
}

// Deals a Card from the Deck to a Hand
void Deck::deal(Hand& pHand)
{
    if (aCards.empty()) return; // Can't deal a card if deck is empty

    Card cardToAdd = aCards.back();
    aCards.pop_back();
    pHand.add(cardToAdd);
}

int Deck:: getDeckSize(){ return aCards.size(); }

// ####################### ABSTRACT PLAYER ###############################

AbstractPlayer::AbstractPlayer(){}

AbstractPlayer::~AbstractPlayer(){}

// Indicates if Player has busted or not
bool AbstractPlayer::isBusted()
{
    if (aHand.getTotal() > 21) return true;
    return false;
}


// ####################### HUMAN PLAYER ###############################

HumanPlayer::HumanPlayer(){}

HumanPlayer::~HumanPlayer(){}

// Implement inherited method
bool HumanPlayer::isDrawing() const
{
    if (wantDraw == 'y') return true;
    return false;
}

void HumanPlayer::announce(bool playerBusted, bool casinoBusted, int playerScore, int casinoScore)
{
    if (playerBusted) 
        cout << "Player busts." << endl << "Casino wins." << endl << endl;
    else if (casinoBusted || playerScore > casinoScore) 
        cout << "Player wins." << endl << endl;
    else if (playerScore == casinoScore) 
        cout << "Push: No one wins." << endl << endl;
    else 
        cout << "Casino wins." << endl << endl;
}

Hand& HumanPlayer::getHand(){ return aHand; }

void HumanPlayer::setWantDraw(char answer){ wantDraw = answer; } // Determines if player wants to draw or not

// ####################### COMPUTER PLAYER ###############################

ComputerPlayer::ComputerPlayer(){}

ComputerPlayer::~ComputerPlayer(){}

// Implement inherited method
bool ComputerPlayer::isDrawing() const
{
    if (aHand.getTotal() <= 16) return true;
    return false;
}

Hand& ComputerPlayer::getHand(){ return aHand; }

// ####################### BLACKJACK GAME ###############################

BlackJackGame::~BlackJackGame(){}

BlackJackGame::BlackJackGame(){}

void BlackJackGame::play()
{
    // Get new deck if the current one has less than 10 cards remaining at start of new round
    if (m_deck.getDeckSize() < 10){
        m_deck.populate(); 
        m_deck.shuffle();
    }

    // Game starts with Player getting two cards then Dealer reveals their Card
    m_deck.deal(m_player.getHand());
    m_deck.deal(m_player.getHand());
    m_deck.deal(m_casino.getHand());

    // Displays dealer's hand
    cout << "Casino: ";
    m_casino.getHand().displayHand();
    cout << "[" << m_casino.getHand().getTotal() << "]" << endl;

    // Displays the player's hand
    cout << "Player: ";
    m_player.getHand().displayHand();
    cout << "[" << m_player.getHand().getTotal() << "]" << endl;
    
    // Keeping track of which players bust
    bool playerBusted = false; 
    bool casinoBusted = false;

    char answer = 'y';
    cout << "Do you want to draw? (y/n): ";
    cin >> answer;
    m_player.setWantDraw(answer);

    // Player can keep drawing until they want to stop or they bust
    while(m_player.isDrawing()){ 
        
        m_deck.deal(m_player.getHand());

        cout << "Player: ";
        m_player.getHand().displayHand();
        cout << "[" << m_player.getHand().getTotal() << "]" << endl;

        if (!m_player.isBusted()){ // If player hasn't busted they can ask for another card
            cout << "Do you want to draw? (y/n): ";
            cin >> answer;
            m_player.setWantDraw(answer);
        } else { // Exit the loop and end the round if the player has busted
            playerBusted = true;
            break;
        }
    }  

    // Dealer's turn to draw if player doesn't bust
    if (!playerBusted){ 
        do {
            m_deck.deal(m_casino.getHand());

            // Displays the dealer's hand
            cout << "Casino: ";
            m_casino.getHand().displayHand();
            cout << "[" << m_casino.getHand().getTotal() << "]" << endl;

        } while (m_casino.isDrawing()); // Dealer keeps drawing until over 16 or bust
    }

    if (m_casino.isBusted()) casinoBusted = true;

    m_player.announce(playerBusted, casinoBusted, m_player.getHand().getTotal(), m_casino.getHand().getTotal());   

    m_player.getHand().clear(); // Clear both players hand at the end of the round
    m_casino.getHand().clear();
}

