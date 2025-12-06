//
// Created by danie on 12/6/2025.
//
#include "Card.h"

Card::Card(const std::string& n) : name(n) {}

const std::string& Card::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    // Polimorfism: Apelează funcția specifică tipului real (UnitCard, WeatherCard etc.)
    c.printDetails(os);
    return os;
}