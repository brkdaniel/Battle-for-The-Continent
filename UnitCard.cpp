//
// Created by danie on 12/7/2025.
//
#include "UnitCard.h"

// Apelăm constructorul bazei (: Card(n))
UnitCard::UnitCard(std::string n, int p, int id, bool gold, CardType t, bool immune)
    : Card(n), // Inițializăm numele în clasa de bază
      power(p), card_ID(id), is_gold(gold), stats(p, immune), type(t)
{}

void UnitCard::printDetails(std::ostream& os) const {
    os << "[Unit: " << name << " | ";
    if (is_gold) os << "*(GOLD)* ";
    os << stats << " | Type: " << (int)type << "]";
}

// Funcția critică pentru copierea Deck-ului mai târziu
Card* UnitCard::clone() const {
    return new UnitCard(*this); // Returnează un pointer nou
}

int UnitCard::getCurrentPower() const { return stats.getCurrentPower(); }
CardType UnitCard::getType() const { return type; }
bool UnitCard::isGold() const { return is_gold; }