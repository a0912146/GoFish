//
// Created by atanz on 11/4/2018.
//

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "time.h"
using namespace std;


void Player::addCard(Card c) {
    myHand.push_back(c);
}

void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}

Card Player::getcard(int CardRank){
    int index = 0;
    for(int size_myHand = myHand.size(); size_myHand != 0 ; size_myHand--){
        int Rank = myHand[index].getRank();
        if(Rank == CardRank){
            return myHand[index];
        }
        index++;
    }
}
bool Player::checkHandForBook(Card &c1, Card &c2) {
    int sizeofMyHand1=myHand.size()-1;
    int sizeofMyHand2;
    int index1 = 0;
    int index2 = 1;
    for(sizeofMyHand2 = myHand.size()-1; sizeofMyHand2!=0; sizeofMyHand2--) {
        c1 = myHand[index1];
        for (index2=index1+1; index2 <= sizeofMyHand1; index2++) {
            c2 = myHand[index2];
            if (c1.getRank() == c2.getRank()) {
                return true;
            }
        }
        index1++;
        index2=index1+1;
    }
    return false;
}

Card Player::chooseCardFromHand() const {
    srand(time(0));

    int CardfromHand = rand()%myHand.size();
    return myHand[CardfromHand];
}

bool Player::cardInHand(Card c) const {
    int index = 0;
    int Cardrank = c.getRank();
    for(int size_myHand = myHand.size(); size_myHand != 0 ; size_myHand--){
        int Rank = myHand[index].getRank();
        if(Rank == Cardrank){
            return true;
        }
        index++;
    }
    return false;
}
Card Player::removeCardFromHand(Card c) {
    int index = 0;
    Card returnvalue;
    for(int size_myHand = myHand.size(); size_myHand != 0; size_myHand--){
        if(myHand[index] == c){
            returnvalue = myHand[index];
            myHand.erase(myHand.begin()+index);
            return returnvalue;
        }
        index++;
    }
    returnvalue = myHand[index];
    myHand.erase(myHand.begin()+index);
    return returnvalue;
}

string Player::showHand() const {
    string tempBuffer = " ";
    Card tempCard;
    int index=0;
    for(int size_myHand = myHand.size(); size_myHand != 0; size_myHand--){
        tempCard = myHand[index];
        tempBuffer = tempBuffer + tempCard.toString();
        tempBuffer = tempBuffer + "   ";    // space between cards
        index++;
    }
    return tempBuffer;
}

string Player::showBooks() const {
    string tempBuffer = " ";
    Card tempBook;
    int index=0;
    if(myBook.size() == 0){
        tempBuffer = "nothing";
    }
    for(int size_myBook = myBook.size(); size_myBook != 0; size_myBook--){
        tempBook = myBook[index];
        tempBuffer = tempBuffer + tempBook.toString();
        tempBuffer = tempBuffer + " ";
        index++;
    }
    return tempBuffer;
}

int Player::getHandSize() const {
    return myHand.size();
}

int Player::getBookSize() const {
    return myBook.size();
}