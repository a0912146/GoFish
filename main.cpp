// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include "fstream"
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
Player findWinner(Player &p1, Player &p2, Deck &d);
void Booking(Card pairOne, Card pairTwo, Player &p);
void outputBeginning(Player &p1, Player &p2);
void Output1(Player &p, int numCards);
Player Finish1(Player &p1, Player &p2, Card pairOne, Card pairTwo);
Player Finish2(Player &p1, Player &p2, Card pairOne, Card pairTwo);

ofstream myfile ("gofish_results.txt");

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

    myfile << p1.getName() << " has these cards in his hand: " << p1.showHand() << "\n";
    myfile << p2.getName() << " has these cards in her hand: " << p2.showHand() << "\n";
    myfile << "\n";

    while(d.size() != 0) {

        //check if player 1 and player 2 has any books
        Card pairOne;
        Card pairTwo;
        while(p1.checkHandForBook(pairOne, pairTwo) == true){
            Booking(pairOne, pairTwo, p1);
        }
        while(p2.checkHandForBook(pairOne, pairTwo) == true){
            Booking(pairOne, pairTwo, p2);
        }
        outputBeginning(p1,p2);

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
            Output1(p1, numCards);
        }
        if(p2.getHandSize() == 0) {
            while (p2.getHandSize() != numCards) {
                if (d.size() != 0) {
                    dealHand(d, p2, oneCard);
                } else {
                    break;
                }
            }
            Output1(p2, numCards);
        }

        // Player 1 asks if Player 2 has a card
        Card checkCard1 = p1.chooseCardFromHand();
        int Rank1 = checkCard1.getRank();
        string Rank11 = "";
        Rank11 = checkCard1.rankString(Rank1);
        Card checkCard2;
        myfile << p1.getName() << " asks - Do you have a " << Rank11 << "\n";
        if(p2.cardInHand(checkCard1) == true){
            myfile << p2.getName() << " says - Yes. I have a " << Rank11 << "\n";
            checkCard2 = p2.getcard(Rank1);
            p1.addCard(checkCard2);
            Booking(checkCard1, checkCard2, p1);
            p2.removeCardFromHand(checkCard2);
            myfile << p1.getName() << " books the " << Rank11 << "\n";
            myfile << "\n";
            if(p1.getHandSize() == 0) {
                while (p1.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p1, oneCard);
                    } else {
                        break;
                    }
                }
                Output1(p1, numCards);
            }
            if(p2.getHandSize() == 0) {
                while (p2.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p2, oneCard);
                    } else {
                        break;
                    }
                }
                Output1(p2, numCards);
            }
        }
        else{
            Card dealtcard = d.dealCard();
            Rank1 = (dealtcard.getRank());
            Rank11 = dealtcard.rankString(Rank1);
            p1.addCard(dealtcard);
            myfile << p2.getName() << " says - Go Fish." << "\n";
            myfile << p1.getName() << " draws " << Rank11 << "\n";
            myfile << "\n";
            while(p1.checkHandForBook(pairOne, pairTwo) == true) {
                Booking(pairOne, pairTwo, p1);
                myfile << p1.getName() << " has booked: " << p1.showBooks() << " from drawing a card from the pile." << "\n";
                if (p1.getHandSize() == 0) {
                    while (p1.getHandSize() != numCards) {
                        if (d.size() != 0) {
                            dealHand(d, p1, oneCard);
                        } else {
                            break;
                        }
                    }
                    Output1(p1, numCards);
                }
            }

        }

        //Player 2 asks if Player 1 has a card
        Card checkCard3 = p2.chooseCardFromHand();
        int Rank2 = checkCard3.getRank();
        string Rank22 = "";
        Rank22 = checkCard3.rankString(Rank2);
        Card checkCard4;
        myfile << p2.getName() << " asks - Do you have a " << Rank22 << "\n";
        if(p1.cardInHand(checkCard3) == true) {
            myfile << p1.getName() << " says - Yes. I have a " << Rank22 << "\n";
            checkCard4 = p1.getcard(Rank2);
            p2.addCard(checkCard4);
            Booking(checkCard3, checkCard4, p2);
            p1.removeCardFromHand(checkCard4);
            myfile << p2.getName() << " books the " << Rank22 << "\n";
            myfile << "\n" << "\n";
            if (p1.getHandSize() == 0) {
                while (p1.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p1, oneCard);
                    } else {
                        break;
                    }
                }
                Output1(p1, numCards);
            }
            if (p2.getHandSize() == 0) {
                while (p2.getHandSize() != numCards) {
                    if (d.size() != 0) {
                        dealHand(d, p2, oneCard);
                    } else {
                        break;
                    }
                }
                Output1(p2, numCards);
            }
        }
        else{
            Card dealtcard = d.dealCard();
            Rank2 = dealtcard.getRank();
            p2.addCard(dealtcard);
            Rank22 = dealtcard.rankString(Rank2);
            myfile << p1.getName() << " says - Go Fish." << "\n";
            myfile << p2.getName() << " draws " << Rank22 << "\n";
            myfile << "\n";
            while(p2.checkHandForBook(pairOne, pairTwo) == true) {
                Booking(pairOne, pairTwo, p2);
                myfile << p2.getName() << " has booked: " << p2.showBooks() << " from drawing a card from the pile." << "\n";
                if (p2.getHandSize() == 0) {
                    while (p2.getHandSize() != numCards) {
                        if (d.size() != 0) {
                            dealHand(d, p2, oneCard);
                        } else {
                            break;
                        }
                    }
                    Output1(p2, numCards);
                }
            }
        }
    }

    //finish going through the cards
    while(d.size() == 0){
        if(p1.getHandSize() == 0){
            if(p2.getHandSize() == 0){
                if(p1.getBookSize() == p2.getBookSize()){
                    myfile << "There was a tie. \n" << p1.getName() << " has " << p1.getBookSize() << ". \nThese are the bookings: " << p1.showBooks() << ". \n" << p2.getName() <<
                         " has " << p2.getBookSize() << ". \n These are the bookings: " << p2.showBooks() << ". " <<"\n";
                    myfile.close();
                    return EXIT_SUCCESS;
                }
                if (p1.getBookSize() > p2.getBookSize()){
                    myfile << p1.getName() << " has WON the game with " << p1.getBookSize() << " bookings. \nThese are the bookings: " << p1.showBooks() << "\n";
                    myfile << p2.getName() << " has " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << "\n";
                    myfile.close();
                    return EXIT_SUCCESS;
                }
                else{
                    myfile << p2.getName() << " has WON the game with " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << "\n";
                    myfile << p1.getName() << " has " << p1.getBookSize() << " bookings. \n These are the bookings: " << p1.showBooks() << "\n";
                    myfile.close();
                    return EXIT_SUCCESS;
                }
            }
        }
        Player Winner= findWinner(p1, p2, d);
        if(Winner.getName() == "tie"){
            myfile << "There was a tie. \n" << p1.getName() << " has " << p1.getBookSize() << ". \nThese are the bookings: " << p1.showBooks() << ". \n" << p2.getName() <<
                 " has " << p2.getBookSize() << ". These are the bookings: " << p2.showBooks() << ". " <<"\n";
            myfile.close();
            return EXIT_SUCCESS;
        }
        if (Winner.getName() == p1.getName()){
            myfile << p1.getName() << " has WON the game with " << p1.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << "\n";
            myfile << p2.getName() << " has " << p2.getBookSize() << " bookings. These are the bookings: " << p2.showBooks() << "\n";
            myfile.close();
            return EXIT_SUCCESS;
        }
        else{
            myfile << p2.getName() << " has WON the game with " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << "\n";
            myfile << p1.getName() << " has " << p1.getBookSize() << " bookings. \n These are the bookings: " << p1.showBooks() << "\n";
            myfile.close();
            return EXIT_SUCCESS;
        }
    }
}



void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

Player findWinner (Player &p1, Player &p2, Deck &d){
    while(p1.getHandSize() != 0  && p2.getHandSize() != 0) {
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
        myfile << p1.getName() << " asks - Do you have a " << Rank11 << "\n";
        if (p2.cardInHand(checkCard1) == true) {
            myfile << p2.getName() << " says - Yes. I have a " << Rank11 << "\n";
            checkCard2 = p2.getcard(Rank1);
            p1.addCard(checkCard2);
            Booking(checkCard1, checkCard2, p1);
            p2.removeCardFromHand(checkCard2);
            myfile << p1.getName() << " books the " << Rank11 << "\n";
            myfile << "\n";
        } else {
            Card dealtcard = d.dealCard();
            Rank1 = (dealtcard.getRank());
            Rank11 = dealtcard.rankString(Rank1);
            p1.addCard(dealtcard);
            myfile << p2.getName() << " says - Go Fish." << "\n";
            myfile << p1.getName() << " draws " << Rank11 << "\n";
            myfile << "\n";
            while (p1.checkHandForBook(pairOne, pairTwo) == true) {
                Booking(pairOne, pairTwo, p1);
                myfile << p1.getName() << " has booked: " << p1.showBooks() << " from drawing a card from the pile."
                     << "\n";
                myfile << "\n";
                if (p1.getHandSize() == 0) {
                    return Finish2(p1, p2, pairOne, pairTwo);
                }
            }

        }

        myfile << p1.getName() << " has these cards in his hand: " << p1.showHand() << "\n";
        myfile << p2.getName() << " has these cards in her hand: " << p2.showHand() << "\n";
        myfile << "\n";
        if (p1.getHandSize() == 0) {
            myfile << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. "
                 << p2.getName() << " will now book them." << "\n";
            myfile << "\n";
            return Finish2(p1, p2, pairOne, pairTwo);
        }
        if (p2.getHandSize() == 0) {
            myfile << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. "
                 << p2.getName() << " will now book them." << "\n";
            myfile << "\n";
            return Finish1(p1, p2, pairOne, pairTwo);
        }
        //Player 2 asks if Player 1 has a card
        Card checkCard3 = p2.chooseCardFromHand();
        int Rank2 = checkCard3.getRank();
        string Rank22 = "";
        Rank22 = checkCard3.rankString(Rank2);
        Card checkCard4;
        myfile << p2.getName() << " asks - Do you have a " << Rank22 << "\n";
        if (p1.cardInHand(checkCard3) == true) {
            myfile << p1.getName() << " says - Yes. I have a " << Rank22 << "\n";
            checkCard4 = p1.getcard(Rank2);
            p2.addCard(checkCard4);
            Booking(checkCard3, checkCard4, p2);
            p1.removeCardFromHand(checkCard4);
            myfile << p2.getName() << " books the " << Rank22 << "\n";
            myfile << "\n";
        } else {
            Card dealtcard = d.dealCard();
            Rank2 = dealtcard.getRank();
            p2.addCard(dealtcard);
            Rank22 = dealtcard.rankString(Rank2);
            myfile << p1.getName() << " says - Go Fish." << "\n";
            myfile << p2.getName() << " draws " << Rank22 << "\n";
            myfile << "\n";
            while (p2.checkHandForBook(pairOne, pairTwo) == true) {
                Booking(pairOne, pairTwo, p2);
                myfile << p2.getName() << " has booked: " << p2.showBooks() << " from drawing a card from the pile."
                     << "\n";
                myfile << "\n";
                if (p2.getHandSize() == 0) {
                    myfile << p2.getName() << " has no more cards left. This means " << p1.getName()
                         << " has all pairs left. " << p1.getName() << " will now book them." << "\n";
                    myfile << "\n";
                    return Finish1(p1, p2, pairOne, pairTwo);
                }
            }
        }

        if (p1.getHandSize() == 0) {
            myfile << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. "
                 << p2.getName() << " will now book them." << "\n";
            myfile << "\n";
            return Finish2(p1, p2, pairOne, pairTwo);
        }
        if (p2.getHandSize() == 0) {
            myfile << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. "
                 << p2.getName() << " will now book them." << "\n";
            myfile << "\n";
            return Finish1(p1, p2, pairOne, pairTwo);
        }
    }
}

void Booking(Card pairOne, Card pairTwo, Player &p){
    p.bookCards(pairOne, pairTwo);
    p.removeCardFromHand(pairOne);
    p.removeCardFromHand(pairTwo);
}

void outputBeginning(Player &p1, Player &p2){
    myfile << p1.getName() << " has booked " << p1.showBooks() << " so far. " << "\n";
    myfile << p2.getName() << " has booked " << p2.showBooks() << " so far. " << "\n";
    myfile << p1.getName() << " has these cards in his hand: " << p1.showHand() << "\n";
    myfile << p2.getName() << " has these cards in her hand: " << p2.showHand() << "\n";
    myfile << "\n";
}

Player Finish2(Player &p1, Player &p2, Card pairOne, Card pairTwo){
    int Player1;
    int Player2;
    Player tie("tie");
    myfile << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. " << p2.getName() << " will now book them." << "\n";
    myfile << "\n";
    while(p2.getHandSize() != 0) {
        Booking(pairOne, pairTwo, p2);
    }
    Player1 = p1.getBookSize();
    Player2 = p2.getBookSize();
    if(Player1 > Player2){
        return p1.getName();
    }
    if(Player1 == Player2){
        return tie;
    }
    else{
        return p2.getName();
    }
}

Player Finish1(Player &p1, Player &p2, Card pairOne, Card pairTwo){
    int Player1;
    int Player2;
    Player tie("tie");
    myfile << p2.getName() << " has no more cards left. This means " << p1.getName() << " has all pairs left. " << p1.getName() << " will now book them." << "\n";
    myfile << "\n";
    while(p1.getHandSize() != 0) {
        Booking(pairOne, pairTwo, p1);
    }
    Player1 = p1.getBookSize();
    Player2 = p2.getBookSize();
    if(Player1 > Player2){
        return p1.getName();
    }
    if(Player1 == Player2){
        return tie;
    }
    else{
        return p2.getName();
    }
}

void Output1(Player &p, int numCards){
    myfile << p.getName() << " has no more cards left. \nWill draw " << numCards << " from the deck or whatever else is left if deck get's empty." << "\n";
    myfile << p.getName() << " has drawn these cards in his hand: " << p.showHand() << "\n";
    myfile << "\n";
}