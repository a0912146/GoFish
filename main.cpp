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
        }
        while(p2.checkHandForBook(pairOne, pairTwo) == true){
            p2.bookCards(pairOne, pairTwo);
            p2.removeCardFromHand(pairOne);
            p2.removeCardFromHand(pairTwo);
        }

        cout << p1.getName() << " has booked " << p1.showBooks() << " so far. " << endl;
        cout << p2.getName() << " has booked " << p2.showBooks() << " so far. " << endl;
        cout << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
        cout << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;

        //In case the players have made any books and lost all card, will go back to original amount of cards.
        // WIll CHECK FOR BOOKS ONLY HERE TO MAKE IT
        // COHESIVE.
        if(p1.getHandSize() == 0) {
            while (p1.getHandSize() != numCards) {
                if (d.size() != 0) {
                    dealHand(d, p1, oneCard);
                } else {
                    break;
                }
            }
            cout << p1.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
            cout << p1.getName() << " has drawn these cards in his hand: " << p1.showHand() << endl;
        }
        if(p2.getHandSize() == 0) {
            while (p2.getHandSize() != numCards) {
                if (d.size() != 0) {
                    dealHand(d, p2, oneCard);
                } else {
                    break;
                }
            }
            cout << p2.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
            cout << p2.getName() << " has drawn these cards in his hand: " << p2.showHand() << endl;
        }

        // Player 1 asks if Player 2 has a card
        Card checkCard1 = p1.chooseCardFromHand();
        int Rank1 = checkCard1.getRank();
        string Rank11 = "";
        Rank11 = checkCard1.rankString(Rank1);
        Card checkCard2;
        cout << p1.getName() << " asks - Do you have a " << Rank11 << endl;
        if(p2.cardInHand(checkCard1) == true){
            cout << p2.getName() << " says - Yes. I have a " << Rank11 << endl;
            checkCard2 = p2.getcard(Rank1);
            p1.addCard(checkCard2);
            p1.bookCards(checkCard1, checkCard2);
            p1.removeCardFromHand(checkCard1);
            p1.removeCardFromHand(checkCard2);
            p2.removeCardFromHand(checkCard2);
            cout << p1.getName() << " books the " << Rank11 << endl;
            if(p1.getHandSize() == 0) {
                while (p1.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p1, oneCard);
                    } else {
                        break;
                    }
                }
                cout << p1.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
                cout << p1.getName() << " has drawn these cards in his hand: " << p1.showHand() << endl;
            }
            if(p2.getHandSize() == 0) {
                while (p2.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p2, oneCard);
                    } else {
                        break;
                    }
                }
                cout << p2.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
                cout << p2.getName() << " has drawn these cards in his hand: " << p2.showHand() << endl;
            }
        }
        else{
                Card dealtcard = d.dealCard();
                Rank1 = (dealtcard.getRank());
                Rank11 = dealtcard.rankString(Rank1);
                p1.addCard(dealtcard);
            cout << p2.getName() << " says - Go Fish." << endl;
            cout << p1.getName() << " draws " << Rank11 << endl;
            while(p1.checkHandForBook(pairOne, pairTwo) == true) {
                p1.bookCards(pairOne, pairTwo);
                p1.removeCardFromHand(pairOne);
                p1.removeCardFromHand(pairTwo);
                cout << p1.getName() << " has booked: " << p1.showBooks() << " from drawing a card from the pile." << endl;
                if (p1.getHandSize() == 0) {
                    while (p1.getHandSize() != numCards) {
                        if (d.size() != 0) {
                            dealHand(d, p1, oneCard);
                        } else {
                            break;
                        }
                    }
                    cout << p1.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
                    cout << p1.getName() << " has drawn these cards in his hand: " << p1.showHand() << endl;
                }
            }

        }

        cout << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
        cout << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;

        //Player 2 asks if Player 1 has a card
        Card checkCard3 = p2.chooseCardFromHand();
        int Rank2 = checkCard3.getRank();
        string Rank22 = "";
        Rank22 = checkCard3.rankString(Rank2);
        Card checkCard4;
        cout << p2.getName() << " asks - Do you have a " << Rank22 << endl;
        if(p1.cardInHand(checkCard3) == true) {
            cout << p1.getName() << " says - Yes. I have a " << Rank22 << endl;
            checkCard4 = p1.getcard(Rank2);
            p2.addCard(checkCard4);
            p2.bookCards(checkCard3, checkCard4);
            p2.removeCardFromHand(checkCard3);
            p2.removeCardFromHand(checkCard4);
            p1.removeCardFromHand(checkCard4);
            cout << p2.getName() << " books the " << Rank22 << endl;
            if (p1.getHandSize() == 0) {
                while (p1.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p1, oneCard);
                    } else {
                        break;
                    }
                }
                cout << p1.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." << endl;
                cout << p1.getName() << " has drawn these cards in his hand: " << p1.showHand() << endl;
            }
            if (p2.getHandSize() == 0) {
                while (p2.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p2, oneCard);
                    } else {
                        break;
                    }
                }
                cout << p2.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
                cout << p2.getName() << " has drawn these cards in his hand: " << p2.showHand() << endl;
            }
        }
        else{
            Card dealtcard = d.dealCard();
            Rank2 = dealtcard.getRank();
            p2.addCard(dealtcard);
            Rank22 = dealtcard.rankString(Rank2);
            cout << p1.getName() << " says - Go Fish." << endl;
            cout << p2.getName() << " draws " << Rank22 << endl;
            while(p2.checkHandForBook(pairOne, pairTwo) == true) {
                p2.bookCards(pairOne, pairTwo);
                p2.removeCardFromHand(pairOne);
                p2.removeCardFromHand(pairTwo);
                cout << p2.getName() << " has booked: " << p2.showBooks() << " from drawing a card from the pile." << endl;
                if (p2.getHandSize() == 0) {
                    while (p2.getHandSize() != numCards) {
                        if (d.size() != 0) {
                            dealHand(d, p2, oneCard);
                        } else {
                            break;
                        }
                    }
                    cout << p2.getName() << " has no more cards left. Will draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
                    cout << p2.getName() << " has drawn these cards in his hand: " << p2.showHand() << endl;
                }
            }
        }
        cout << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
        cout << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;
    }

    //finish going through the cards
    while(d.size() == 0){
        int Player1;
        int Player2;
        Card pairOne;
        Card pairTwo;

        // Player 1 asks if Player 2 has a card
        Card checkCard1 = p1.chooseCardFromHand();
        int Rank1 = checkCard1.getRank();
        string Rank11 = "";
        Rank11 = checkCard1.rankString(Rank1);
        Card checkCard2;
        cout << p1.getName() << " asks - Do you have a " << Rank11 << endl;
        if(p2.cardInHand(checkCard1) == true){
            cout << p2.getName() << " says - Yes. I have a " << Rank11 << endl;
            checkCard2 = p2.getcard(Rank1);
            p1.addCard(checkCard2);
            p1.bookCards(checkCard1, checkCard2);
            p1.removeCardFromHand(checkCard1);
            p1.removeCardFromHand(checkCard2);
            p2.removeCardFromHand(checkCard2);
            cout << p1.getName() << " books the " << Rank11 << endl;
            if(p1.getHandSize() == 0) {
                cout << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. " << p2.getName() << " will now book them." << endl;
                while(p2.getHandSize() != 0) {
                    p2.bookCards(pairOne, pairTwo);
                    p2.removeCardFromHand(pairOne);
                    p2.removeCardFromHand(pairTwo);
                }
                Player1 = p1.getBookSize();
                Player2 = p2.getBookSize();
                if(Player1 > Player2){
                    cout << p1.getName() << " has won the game with " << Player1 << " bookings. There are the bookings: " << p1.showBooks() << endl;
                    cout << "These are " << p2.getName() << "bookings:" << p2.showBooks() << endl;
                    break;
                }
                else{
                    cout << p2.getName() << " has won the game with " << Player2 << " bookings. There are the bookings: " << p2.showBooks() << endl;
                    cout << "These are " << p1.getName() << "bookings:" << p1.showBooks() << endl;
                    break;
                }
            }

        }
        else{
            Card dealtcard = d.dealCard();
            Rank1 = (dealtcard.getRank());
            Rank11 = dealtcard.rankString(Rank1);
            p1.addCard(dealtcard);
            cout << p2.getName() << " says - Go Fish." << endl;
            cout << p1.getName() << " draws " << Rank11 << endl;
            while(p1.checkHandForBook(pairOne, pairTwo) == true) {
                p1.bookCards(pairOne, pairTwo);
                p1.removeCardFromHand(pairOne);
                p1.removeCardFromHand(pairTwo);
                cout << p1.getName() << " has booked: " << p1.showBooks() << " from drawing a card from the pile." << endl;
                if (p1.getHandSize() == 0) {
                    cout << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. " << p2.getName() << " will now book them." << endl;
                    while(p2.getHandSize() != 0) {
                        p2.bookCards(pairOne, pairTwo);
                        p2.removeCardFromHand(pairOne);
                        p2.removeCardFromHand(pairTwo);
                    }
                    Player1 = p1.getBookSize();
                    Player2 = p2.getBookSize();
                    if(Player1 > Player2){
                        cout << p1.getName() << " has won the game with " << Player1 << " bookings. There are the bookings: " << p1.showBooks() << endl;
                        cout << "These are " << p2.getName() << "bookings:" << p2.showBooks() << endl;
                        break;
                    }
                    else{
                        cout << p2.getName() << " has won the game with " << Player2 << " bookings. There are the bookings: " << p2.showBooks() << endl;
                        cout << "These are " << p1.getName() << "bookings:" << p1.showBooks() << endl;
                        break;
                    }
                }
            }

        }

        cout << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
        cout << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;

        //Player 2 asks if Player 1 has a card
        Card checkCard3 = p2.chooseCardFromHand();
        int Rank2 = checkCard3.getRank();
        string Rank22 = "";
        Rank22 = checkCard3.rankString(Rank2);
        Card checkCard4;
        cout << p2.getName() << " asks - Do you have a " << Rank22 << endl;
        if(p1.cardInHand(checkCard3) == true) {
            cout << p1.getName() << " says - Yes. I have a " << Rank22 << endl;
            checkCard4 = p1.getcard(Rank2);
            p2.addCard(checkCard4);
            p2.bookCards(checkCard3, checkCard4);
            p2.removeCardFromHand(checkCard3);
            p2.removeCardFromHand(checkCard4);
            p1.removeCardFromHand(checkCard4);
            cout << p2.getName() << " books the " << Rank22 << endl;
            if (p1.getHandSize() == 0) {
                 cout << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. " << p2.getName() << " will now book them." << endl;
                 while(p2.getHandSize() != 0) {
                     p2.bookCards(pairOne, pairTwo);
                     p2.removeCardFromHand(pairOne);
                     p2.removeCardFromHand(pairTwo);
                 }
                Player1 = p1.getBookSize();
                Player2 = p2.getBookSize();
                if(Player1 > Player2){
                    cout << p1.getName() << " has won the game with " << Player1 << " bookings. There are the bookings: " << p1.showBooks() << endl;
                    cout << "These are " << p2.getName() << "bookings:" << p2.showBooks() << endl;
                    break;
                }
                else{
                    cout << p2.getName() << " has won the game with " << Player2 << " bookings. There are the bookings: " << p2.showBooks() << endl;
                    cout << "These are " << p1.getName() << "bookings:" << p1.showBooks() << endl;
                    break;
                }
            }
            if (p2.getHandSize() == 0) {
                cout << p2.getName() << " has no more cards left. This means " << p1.getName() << " has all pairs left. " << p1.getName() << " will now book them." << endl;
                while(p1.getHandSize() != 0) {
                    p1.bookCards(pairOne, pairTwo);
                    p1.removeCardFromHand(pairOne);
                    p1.removeCardFromHand(pairTwo);
                }
                Player1 = p1.getBookSize();
                Player2 = p2.getBookSize();
                if(Player1 > Player2){
                    cout << p1.getName() << " has won the game with " << Player1 << " bookings. There are the bookings: " << p1.showBooks() << endl;
                    cout << "These are " << p2.getName() << "bookings:" << p2.showBooks() << endl;
                    break;
                }
                else{
                    cout << p2.getName() << " has won the game with " << Player2 << " bookings. There are the bookings: " << p2.showBooks() << endl;
                    cout << "These are " << p1.getName() << "bookings:" << p1.showBooks() << endl;
                    break;
                }
            }
        }
        else{
            Card dealtcard = d.dealCard();
            Rank2 = dealtcard.getRank();
            p2.addCard(dealtcard);
            Rank22 = dealtcard.rankString(Rank2);
            cout << p1.getName() << " says - Go Fish." << endl;
            cout << p2.getName() << " draws " << Rank22 << endl;
            while(p2.checkHandForBook(pairOne, pairTwo) == true) {
                p2.bookCards(pairOne, pairTwo);
                p2.removeCardFromHand(pairOne);
                p2.removeCardFromHand(pairTwo);
                cout << p2.getName() << " has booked: " << p2.showBooks() << " from drawing a card from the pile." << endl;
                if (p2.getHandSize() == 0) {
                    cout << p2.getName() << " has no more cards left. This means " << p1.getName() << " has all pairs left. " << p1.getName() << " will now book them." << endl;
                    while(p1.getHandSize() != 0) {
                        p1.bookCards(pairOne, pairTwo);
                        p1.removeCardFromHand(pairOne);
                        p1.removeCardFromHand(pairTwo);
                    }
                    Player1 = p1.getBookSize();
                    Player2 = p2.getBookSize();
                    if(Player1 > Player2){
                        cout << p1.getName() << " has won the game with " << Player1 << " bookings. There are the bookings: " << p1.showBooks() << endl;
                        cout << "These are " << p2.getName() << "bookings:" << p2.showBooks() << endl;
                        break;
                    }
                    else{
                        cout << p2.getName() << " has won the game with " << Player2 << " bookings. There are the bookings: " << p2.showBooks() << endl;
                        cout << "These are " << p1.getName() << "bookings:" << p1.showBooks() << endl;
                        break;
                    }
                }
            }
        }
    }
    return EXIT_SUCCESS;  
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}