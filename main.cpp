#include <iostream>
#include "blackjack.h"

using namespace std;

int main()
{
    cout << "\nWelcome to the Comp322 BlackJack game!" << endl << endl;

    BlackJackGame game;

    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
    {
        game.play();

        // Check whether the player would like to play another round 
        cout << "Would you like another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);
    }
    
    cout << "Game Over!" << endl << endl;
    return 0;
}
