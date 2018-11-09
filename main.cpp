// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include <fstream>
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:

//Input Parameter: deck of cards, player, and the number of card
//Output Parameter: None
//Definition: Will deal a card when during GOFISH or during the beginning portion of the game
void dealHand(Deck &d, Player &p, int numCards);

//Input Parameter: player1, player2, and deck of cards
//Output Parameter: The player who won the game
//Definition: Once there are no more cards in the deck, will go to the second scenario to finish
// out game and that scenario comes to this function to find the winner.
Player findWinner(Player &p1, Player &p2, Deck &d);

//Input Parameter: First card to be booked, second card to be booked, and the player booking the card
//Output Parameter: None
//Definition: Will book the card and delete the pair from the players own collection
void Booking(Card pairOne, Card pairTwo, Player &p);

//Input Parameter: First Player and Second Player
//Output Parameter: None
//Definition: Output to the screen what has been booked and what cards the players both have
void outputBeginning(Player &p1, Player &p2);

//Input Parameter: The player out of cards and the total number of cards they need (once out of cards, the player will get seven new cards.
//Output Parameter: None
//Definition: Will output a message stating that the player has no more cards left and needs to draw more cards
void Output1(Player &p, int numCards);

//Input Parameter: Player One, Player Two, the cards that are going to be booked
//Output Parameter: The player who won
//Definition: The player one has no more cards left so they are going to find all the bookings left for
// the second player and then find the winner in this function to return to findWinner() function.
Player Finish1(Player &p1, Player &p2, Card pairOne, Card pairTwo);

//Input Parameter: Player One, Player Two, the cards that are going to be booked
//Output Parameter: The player who won
//Definition: The player two has no more cards left so they are going to find all the bookings left for
// the second player and then find the winner in this function to return to findWinner() function.
Player Finish2(Player &p1, Player &p2, Card pairOne, Card pairTwo);

int main(int argc, char *argv[]) {
    ofstream myfile;
    myfile.open ("gofish_results.txt");
    int numCards = 7;
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

    myfile << p1.getName() << " has these cards in his hand: \n" << p1.showHand() << endl;
    myfile << p2.getName() << " has these cards in her hand: \n" << p2.showHand() << endl;
    myfile << "\n" <<endl;

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

        // Player 1 asks if Player 2 has a card. Will see if there is a booking that occurs or if not, GOFISH.
        // Player will draw card. Only draw card during GOFISH scenario
        Card checkCard1 = p1.chooseCardFromHand();
        int Rank1 = checkCard1.getRank();
        string Rank11 = "";
        Rank11 = checkCard1.rankString(Rank1);
        Card checkCard2;
        myfile << p1.getName() << " asks - Do you have a " << Rank11 << endl;
        if(p2.cardInHand(checkCard1) == true){
            myfile << p2.getName() << " says - Yes. I have a " << Rank11 << endl;
            checkCard2 = p2.getcard(Rank1);
            p1.addCard(checkCard2);
            Booking(checkCard1, checkCard2, p1);
            p2.removeCardFromHand(checkCard2);
            cout << p1.getName() << " books the " << Rank11 << endl;
            cout << "\n" << endl;

            //Checks to see if the player is out of cards so that they can be replenished.
            // If the deck is out of cards though, then function will break
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
            outputBeginning(p1,p2);
        }
        else{
            //Player 2 did not have the card so the player 1 will draw a card.
                Card dealtcard = d.dealCard();
                Rank1 = (dealtcard.getRank());
                Rank11 = dealtcard.rankString(Rank1);
                p1.addCard(dealtcard);
            myfile << p2.getName() << " says - Go Fish." << endl;
            myfile << p1.getName() << " draws " << Rank11 << endl;
            myfile << "\n" << endl;

            //Check to see that if in the process of drawing a card, that card made a booking with a
            //card in the current sample.
            while(p1.checkHandForBook(pairOne, pairTwo) == true) {
                Booking(pairOne, pairTwo, p1);
                myfile << p1.getName() << " has booked: " << p1.showBooks() << " from drawing a card from the pile." << endl;
                //Checks to see if the player is out of cards so that they can be replenished.
                // If the deck is out of cards though, then function will break
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
            outputBeginning(p1,p2);
        }

        //Player 2 asks if Player 1 has a card
        Card checkCard3 = p2.chooseCardFromHand();
        int Rank2 = checkCard3.getRank();
        string Rank22 = "";
        Rank22 = checkCard3.rankString(Rank2);
        Card checkCard4;
        myfile << p2.getName() << " asks - Do you have a " << Rank22 << endl;
        if(p1.cardInHand(checkCard3) == true) {
            myfile << p1.getName() << " says - Yes. I have a " << Rank22 << endl;
            checkCard4 = p1.getcard(Rank2);
            p2.addCard(checkCard4);
            Booking(checkCard3, checkCard4, p2);
            p1.removeCardFromHand(checkCard4);
            myfile << p2.getName() << " books the " << Rank22 << endl;
            myfile << "\n" << endl;
            //Checks to see if the player is out of cards so that they can be replenished.
            // If the deck is out of cards though, then function will break
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
            outputBeginning(p1,p2);
        }
        else{
            //Player 2 did not have the card so the player 1 will draw a card.
            Card dealtcard = d.dealCard();
            Rank2 = dealtcard.getRank();
            p2.addCard(dealtcard);
            Rank22 = dealtcard.rankString(Rank2);
            myfile << p1.getName() << " says - Go Fish." << endl;
            myfile << p2.getName() << " draws " << Rank22 << endl;
            myfile << "\n" << endl;
            while(p2.checkHandForBook(pairOne, pairTwo) == true) {
                Booking(pairOne, pairTwo, p2);
                myfile << p2.getName() << " has booked: " << p2.showBooks() << " from drawing a card from the pile." << endl;
                //Checks to see if the player is out of cards so that they can be replenished.
                // If the deck is out of cards though, then function will break
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
            outputBeginning(p1,p2);
        }
    }

    //finish going through the cards. There are no longer any cards in the deck so will finish the program out.
    while(d.size() == 0){
        if(p1.getHandSize() == 0){
            if(p2.getHandSize() == 0){
                if(p1.getBookSize() == p2.getBookSize()){
                    myfile << "There was a tie. \n" << p1.getName() << " has " << p1.getBookSize() << ". \nThese are the bookings: " << p1.showBooks() << ". \n" << p2.getName() <<
                         " has " << p2.getBookSize() << ". \nThese are the bookings: " << p2.showBooks() << ". " <<endl;
                    myfile.close();
                    return EXIT_SUCCESS;
                }
                if (p1.getBookSize() > p2.getBookSize()){
                    myfile << p1.getName() << " has WON the game with " << p1.getBookSize() << " bookings. \nThese are the bookings: " << p1.showBooks() << endl;
                    myfile << p2.getName() << " has " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << endl;
                    myfile.close();
                    return EXIT_SUCCESS;
                }
                else{
                    myfile << p2.getName() << " has WON the game with " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << endl;
                    myfile << p1.getName() << " has " << p1.getBookSize() << " bookings. \nThese are the bookings: " << p1.showBooks() << endl;
                    myfile.close();
                    return EXIT_SUCCESS;
                }
            }
        }
        Player Winner;

        while(p1.getHandSize() != 0  && p2.getHandSize() != 0) {
            int Player1;
            int Player2;
            Card pairOne;
            Card pairTwo;
            int done = 0;

            if (done == 0) {
                if (p1.getHandSize() == 0) {
                    myfile << p1.getName() << " has no more cards left. This means " << p2.getName()
                           << " has all pairs left. "
                           << p2.getName() << " will now book them." << endl;
                    myfile << "\n" << endl;
                    Winner = Finish2(p1, p2, pairOne, pairTwo);
                    done =1;
                }
            }
            if (done == 0) {
                if (p2.getHandSize() == 0) {
                    myfile << p1.getName() << " has no more cards left. This means " << p2.getName()
                         << " has all pairs left. "
                         << p2.getName() << " will now book them." << endl;
                    myfile << "\n" << endl;
                    Winner = Finish1(p1, p2, pairOne, pairTwo);
                    done =1;
                }
            }

            // Player 1 asks if Player 2 has a card
            if (done == 0) {
                Card checkCard1 = p1.chooseCardFromHand();
                int Rank1 = checkCard1.getRank();
                string Rank11 = "";
                Rank11 = checkCard1.rankString(Rank1);
                Card checkCard2;
                myfile << p1.getName() << " asks - Do you have a " << Rank11 << endl;
                if (p2.cardInHand(checkCard1) == true) {
                    myfile << p2.getName() << " says - Yes. I have a " << Rank11 << endl;
                    checkCard2 = p2.getcard(Rank1);
                    p1.addCard(checkCard2);
                    Booking(checkCard1, checkCard2, p1);
                    p2.removeCardFromHand(checkCard2);
                    myfile << p1.getName() << " books the " << Rank11 << endl;
                    myfile << "\n" << endl;
                } else {
                    myfile << p2.getName() << " says - Go Fish." << endl;
                    myfile << "\n" << endl;
                    while (p1.checkHandForBook(pairOne, pairTwo) == true) {
                        Booking(pairOne, pairTwo, p1);
                        myfile << p1.getName() << " has booked: " << p1.showBooks()
                             << " from drawing a card from the pile."
                             << endl;
                        myfile << "\n" << endl;
                        if (p1.getHandSize() == 0) {
                            Winner = Finish2(p1, p2, pairOne, pairTwo);
                            done =1;
                        }
                    }

                }
            }
            if (done ==0) {
                myfile << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
                myfile << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;
                myfile << "\n" << endl;
                if (p1.getHandSize() == 0) {
                    myfile << p1.getName() << " has no more cards left. This means " << p2.getName()
                         << " has all pairs left. "
                         << p2.getName() << " will now book them." << endl;
                    myfile << "\n" << endl;
                    Winner = Finish2(p1, p2, pairOne, pairTwo);
                    done =1;
                }
                if (p2.getHandSize() == 0) {
                    myfile << p1.getName() << " has no more cards left. This means " << p2.getName()
                         << " has all pairs left. "
                         << p2.getName() << " will now book them." << endl;
                    myfile << "\n" << endl;
                    Winner = Finish1(p1, p2, pairOne, pairTwo);
                    done =1;
                }
            }
            //Player 2 asks if Player 1 has a card
            if(done == 0) {
                Card checkCard3 = p2.chooseCardFromHand();
                int Rank2 = checkCard3.getRank();
                string Rank22 = "";
                Rank22 = checkCard3.rankString(Rank2);
                Card checkCard4;
                myfile << p2.getName() << " asks - Do you have a " << Rank22 << endl;
                if (p1.cardInHand(checkCard3) == true) {
                    myfile << p1.getName() << " says - Yes. I have a " << Rank22 << endl;
                    checkCard4 = p1.getcard(Rank2);
                    p2.addCard(checkCard4);
                    Booking(checkCard3, checkCard4, p2);
                    p1.removeCardFromHand(checkCard4);
                    myfile << p2.getName() << " books the " << Rank22 << endl;
                    myfile << "\n" << endl;
                } else {
                    myfile << p1.getName() << " says - Go Fish." << endl;
                    myfile << "\n" << endl;
                    while (p2.checkHandForBook(pairOne, pairTwo) == true) {
                        Booking(pairOne, pairTwo, p2);
                        myfile << p2.getName() << " has booked: " << p2.showBooks()
                             << " from drawing a card from the pile."
                             << endl;
                        myfile << "\n" << endl;
                        if (p2.getHandSize() == 0) {
                            myfile << p2.getName() << " has no more cards left. This means " << p1.getName()
                                 << " has all pairs left. " << p1.getName() << " will now book them." << endl;
                            myfile << "\n" << endl;
                            Winner = Finish1(p1, p2, pairOne, pairTwo);
                            done =1;
                        }
                    }
                }
            }

            if(done == 0) {
                if (p1.getHandSize() == 0) {
                    cout << p1.getName() << " has no more cards left. This means " << p2.getName()
                         << " has all pairs left. "
                         << p2.getName() << " will now book them." << endl;
                    cout << "\n" << endl;
                    Winner = Finish2(p1, p2, pairOne, pairTwo);
                    done =1;
                }
                if (p2.getHandSize() == 0) {
                    cout << p1.getName() << " has no more cards left. This means " << p2.getName()
                         << " has all pairs left. "
                         << p2.getName() << " will now book them." << endl;
                    cout << "\n" << endl;
                    Winner = Finish1(p1, p2, pairOne, pairTwo);
                    done=1;
                }
            }
        }

        if(Winner.getName() == "tie"){
            myfile << "There was a tie. \n" << p1.getName() << " has " << p1.getBookSize() << ". \nThese are the bookings: " << p1.showBooks() << ". \n" << p2.getName() <<
            " has " << p2.getBookSize() << ". \nThese are the bookings: " << p2.showBooks() << ". " <<endl;
            return EXIT_SUCCESS;
        }
        if (Winner.getName() == p1.getName()){
            myfile << p1.getName() << " has WON the game with " << p1.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << endl;
            myfile << p2.getName() << " has " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << endl;
            return EXIT_SUCCESS;
        }
        else{
            myfile << p2.getName() << " has WON the game with " << p2.getBookSize() << " bookings. \nThese are the bookings: " << p2.showBooks() << endl;
            myfile << p1.getName() << " has " << p1.getBookSize() << " bookings. \nThese are the bookings: " << p1.showBooks() << endl;
            return EXIT_SUCCESS;
        }
    }
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}

void Booking(Card pairOne, Card pairTwo, Player &p){
    p.bookCards(pairOne, pairTwo);
    p.removeCardFromHand(pairOne);
    p.removeCardFromHand(pairTwo);
}

void outputBeginning(Player &p1, Player &p2){
    cout << p1.getName() << " has booked " << p1.showBooks() << " so far. " << endl;
    cout << p2.getName() << " has booked " << p2.showBooks() << " so far. " << endl;
    cout << p1.getName() << " has these cards in his hand: " << p1.showHand() << endl;
    cout << p2.getName() << " has these cards in her hand: " << p2.showHand() << endl;
    cout << "\n" << endl;
}

Player Finish2(Player &p1, Player &p2, Card pairOne, Card pairTwo){
    int Player1;
    int Player2;
    Player tie("tie");
    cout << p1.getName() << " has no more cards left. This means " << p2.getName() << " has all pairs left. " << p2.getName() << " will now book them." << endl;
    cout << "\n" << endl;
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
    cout << p2.getName() << " has no more cards left. This means " << p1.getName() << " has all pairs left. " << p1.getName() << " will now book them." << endl;
    cout << "\n" << endl;
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
    cout << p.getName() << " has no more cards left. \nWill draw " << numCards << " from the deck or whatever else is left if deck get's empty." <<endl;
    cout << p.getName() << " has drawn these cards in the hand: " << p.showHand() << endl;
    cout << "\n" << endl;
}