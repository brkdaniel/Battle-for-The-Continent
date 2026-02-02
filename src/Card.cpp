#include "../headers/Card.h"

int Card::totalCardsCreated = 0;

Card::Card(const std::string &n) : name(n) {
    totalCardsCreated++;
}

Card::Card(const Card &other) : name(other.name) {
    totalCardsCreated++;
}

Card::~Card() {
    totalCardsCreated--;
}

const std::string &Card::getName() const {
    return name;
}

int Card::getTotalCards() {
    return totalCardsCreated;
}
