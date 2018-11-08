//
// Created by atanz on 11/4/2018.
//

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
using namespace std;


void Player::addCard(Card c) {
    myHand.push_back(c);
}

void Player::bookCards(Card c1, Card c2) {
    myBook.push_back(c1);
    myBook.push_back(c2);
}

bool Player::checkHandForBook(Card &c1, Card &c2) {
    int sizeofMyHand1 = myHand.size();
    int sizeofMyHand2 = myHand.size();
    int index1 = 0;
    int index2 = 1;
    for(sizeofMyHand1 = sizeofMyHand1; sizeofMyHand1!=0; sizeofMyHand1--){
        c1 = myHand[index1];
        if((sizeofMyHand1-1)==0){
            return false;
        }

        c2 = myHand[index2];

        if (c1.getRank() == c2.getRank()){
            return true;
        }

        index1++;
        index2++;
    }
}

bool Player::rankInHand(Card c) const {}
Card Player::chooseCardFromHand() const {}
bool Player::cardInHand(Card c) const {}
Card Player::removeCardFromHand(Card c) {}
string Player::showHand() const {}
string Player::showBooks() const {}
int Player::getHandSize() const {}
int Player::getBookSize() const {}
bool Player::checkHandForPair(Card &c1, Card &c2) {}
bool Player::sameRankInHand(Card c) const {}