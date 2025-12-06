//
// Created by danie on 12/6/2025.
//
#include "Card.h"

Card::Card(std::string n, int p, int id, bool gold, CardType t, bool immune)
    : name(n), power(p), card_ID(id), is_gold(gold), stats(p, immune), type(t)
{}

std::string Card::getName() const { return name; }
int Card::getBasePower() const { return power; }
int Card::getID() const { return card_ID; }
bool Card::isGold() const { return is_gold; }
CardType Card::getType() const { return type; }

int Card::getCurrentPower() const { return stats.getCurrentPower(); }
const CardStats& Card::getStats() const { return stats; }

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << "[" << card.name << " | ";
    if (card.is_gold) {
        os << " *(GOLD)* ";
    }
    os << card.stats << "]";
    return os;
}