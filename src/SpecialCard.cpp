//
// Created by danie on 12/7/2025.
//
#include "../headers/SpecialCard.h"

SpecialCard::SpecialCard(const std::string& n, const std::string& desc)
    : Card(n), effectDescription(desc)
{}

void SpecialCard::printDetails(std::ostream& os) const {
    os << "[Special: " << name << " | Effect: " << effectDescription << "]";
}

Card* SpecialCard::clone() const {
    return new SpecialCard(*this);
}