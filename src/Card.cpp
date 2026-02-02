//
// Created by danie on 12/6/2025.
//
#include "../headers/Card.h"

int Card::totalCardsCreated = 0;

Card::Card(const std::string& n) : name(n) {
    totalCardsCreated++;
}

Card::~Card() {
    totalCardsCreated--;
}

int Card::getTotalCards() {
    return totalCardsCreated;
}


const std::string& Card::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    c.printDetails(os);
    return os;
}