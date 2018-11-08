// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);




int main( )
{
    int numCards = 5;
    int oneCard = 1;

    //Create the players
    Player p1("Joe");
    Player p2("Jane");

    //Create the deck and shuffle it
    Deck d;
    d.shuffle();

    //Deal the cards to make sure both players have 5 cards each
    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);

    cout << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
    cout << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;

    while(d.size() != 0) {

        //check if player 1 and player 2 has any books
       Card pairOne;
       Card pairTwo;
        while(p1.checkHandForBook(pairOne, pairTwo) == true){
            p1.bookCards(pairOne, pairTwo);
            p1.removeCardFromHand(pairOne);
            p1.removeCardFromHand(pairTwo);
            if (d.size() != 0) {
                p1.addCard(d.dealCard());
                p1.addCard(d.dealCard());
            }
            else{
                break;
            }
        }
        while(p2.checkHandForBook(pairOne, pairTwo) == true){
            p2.bookCards(pairOne, pairTwo);
            p2.removeCardFromHand(pairOne);
            p2.removeCardFromHand(pairTwo);
            if (d.size() != 0) {
                p2.addCard(d.dealCard());
                p2.addCard(d.dealCard());
            }
            else{
                break;
            }

        }

        cout << p1.getName() << " has booked: " << p1.showBooks() << endl;
        cout << p2.getName() << " has booked: " << p2.showBooks() << endl;

        //In case the players have made any books, they must return to their original amount
        //(players must have 5 cards at all times). WIll CHECK FOR BOOKS ONLY HERE TO MAKE IT
        // COHESIVE.
        while (p1.getHandSize() != numCards) {
                if(d.size() != 0){
                    dealHand(d, p1, oneCard);
                }
                else{
                    break;
                }
            }
        while(p2.getHandSize() != numCards) {
            if (d.size() != 0) {
                dealHand(d, p2, oneCard);
            }
            else{
                break;
            }
        }

        // Player 1 asks if Player 2 has a card
        Card checkCard1 = p1.chooseCardFromHand();
        int Rank1 = checkCard1.getRank();
        Card checkCard2 = checkCard1;
        cout << p1.getName() << " asks - Do you have a " << Rank1 << endl;
        if(p2.cardInHand(checkCard1) == true){
            cout << p2.getName() << " says - Yes. I have a " << Rank1 << endl;
            p1.addCard(checkCard1);
            int integer = p1.getcard(Rank1);
            p1.bookCards(checkCard1, checkCard2);

            p2.removeCardFromHand(checkCard1);
            cout << p1.getName() << " books the " << Rank1 << endl;
        }
        else{
            Card dealtcard = d.dealCard();
            Rank1 = dealtcard.getRank();
            p1.addCard(dealtcard);
            cout << p2.getName() << " says - Go Fish." << endl;
            cout << p1.getName() << " draws " << Rank1 << endl;
        }

        //Player 2 asks if Player 1 has a card
        Card checkCard3 = p2.chooseCardFromHand();
        int Rank2 = checkCard2.getRank();
        Card checkCard4 = checkCard3;
        cout << p2.getName() << " asks - Do you have a " << Rank2 << endl;
        if(p1.cardInHand(checkCard1) == true){
            cout << p1.getName() << " says - Yes. I have a " << Rank2 << endl;
            p2.addCard(checkCard2);
            checkCard2 = p1.getcard(Rank2);
            p2.bookCards(checkCard3, checkCard4);
            p1.removeCardFromHand(checkCard2);
            cout << p2.getName() << " books the " << Rank2 << endl;
        }
        else{
            Card dealtcard = d.dealCard();
            Rank2 = dealtcard.getRank();
            p2.addCard(dealtcard);
            cout << p1.getName() << " says - Go Fish." << endl;
            cout << p2.getName() << " draws " << Rank1 << endl;
        }

    }
    return EXIT_SUCCESS;  
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}