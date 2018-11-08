//
// Created by atanz on 11/5/2018.
//
#include <string>
#include "card.h"
using namespace std;

// Constructor for Card()
// Default is ace of spades (1 refers to ace)
Card::Card() {
    myRank = 1;
    mySuit = Card::spades;
    }

Card::Card(int rank, Suit s){
    myRank = rank;
    mySuit = s;
}

string Card::toString() const {
    string Rank = "";
    string Suit = "";
    string Card = "";
    Rank = rankString(myRank);
    Suit = suitString(mySuit);
    Card = Rank + Suit;
    return Card;
}

bool Card::sameSuitAs(const Card& c) const {
    if(mySuit == c.mySuit){
        return true;
    }
    else{
        return false;
    }
}  // true if suit same as c

int Card::getRank() const {
    return myRank;
}


string Card::suitString(Card::Suit s) const {
    string newSuit = "";
    if (s == Card::spades){
        newSuit = "s";
        return newSuit;
    }
    if (s == Card::hearts){
        newSuit = "h";
        return newSuit;
    }
    if (s == Card::diamonds){
        newSuit = "d";
        return newSuit;
    }
    if (s == Card::clubs){
        newSuit = "c";
        return newSuit;
    }
}



string Card::rankString(int r) const {
    string newCard = "";
    if (r== 1){
        newCard = "A";
    }
    if (r== 2){
        newCard = "2";
    }
    if (r== 3){
        newCard = "3";
    }
    if (r== 4){
        newCard = "4";
    }
    if (r== 5){
        newCard = "5";
    }
    if (r== 6){
        newCard = "6";
    }
    if (r== 7){
        newCard = "7";
    }
    if (r== 8){
        newCard = "8";
    }
    if (r== 9){
        newCard = "9";
    }
    if (r== 10){
        newCard = "10";
    }
    if (r == 11){
        newCard = "J";
    }
    if (r == 12){
        newCard = "Q";
    }
    if (r == 13){
        newCard = "K";
    }
    return newCard;
}  // return "A", "2", ..."Q"


bool Card::operator==(const Card &rhs) const {
    if (myRank == rhs.myRank){
        return true;
    }
    else{
        return false;
    }
}

bool Card::operator!=(const Card &rhs) const {
    if (myRank != rhs.myRank){
        return true;
    }
    else{
        return false;
    }
}