//
// Created by atanz on 11/4/2018.
//

#include <string>
#include <iostream>
#include <algorithm>
#include "time.h"
#include "deck.h"
using namespace std;

Deck::Deck() {
    myCards[SIZE];
    myIndex = 0;
    int index = 0;
    Card::Suit suitCard;

    for(int suit = 1; suit <= 4; suit++){
        for(int rank = 1; rank <= 13; rank++){
            if(suit == 1){
                suitCard = Card::spades;
            }
            if(suit == 2){
                suitCard = Card::hearts;
            }
            if(suit == 3){
                suitCard = Card::clubs;
            }
            if(suit == 4){
                suitCard = Card::diamonds;
            }
            myCards[index] = Card(rank, suitCard);
            index++;
        }
    }
}

void Deck::shuffle() {
    int tempIndex = myIndex;
   srand(time(0));
   int random = rand()%51;
    Card tempCard;
    for(int jIndex = 0; jIndex <SIZE; jIndex++) {
        for (int index = 0; index < SIZE; index++) {
            tempCard = myCards[random];
            myCards[random] = myCards[index];
            myCards[index] = tempCard;
            random = rand()%51;
        }
    }
    myIndex = tempIndex;
}

Card Deck::dealCard() {

    if(myIndex==52){
        Card tempCard = Card(14, Card::spades);
        return tempCard;
    }    //fail case
    else{
        Card tempCard = myCards[myIndex];
        myIndex++;
        return tempCard;
    }
}

int Deck::size() const {
    int SizeofCards=SIZE;
    for(int tempSize = 0; tempSize < myIndex; tempSize++){
        SizeofCards--;
    }
    return SizeofCards;
}