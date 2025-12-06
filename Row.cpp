//
// Created by danie on 12/6/2025.
//
#include "Row.h"

Row::Row(RowType t) : type(t), has_horn(false) {}

int Row::calculateBasePower() const {
    int total = 0;
    for (const auto& card : cards) {
        total += card.getCurrentPower();
    }
    return total;
}

bool Row::canAddCard(const Card& card) const {
    CardType card_type = card.getType();
    if (card_type == CardType::SPELL) {
        return false;
    }
    switch (card_type) {
        case CardType::MELEE:
            return (type == RowType::MELEE);
        case CardType::RANGED:
            return (type == RowType::RANGED);
        case CardType::SIEGE:
            return (type == RowType::SIEGE);
        default:
            return false;
    }
}

void Row::addCard(const Card& card) {
    if (canAddCard(card)) {
        cards.push_back(card);
    } else {
        std::cout << "ERROR: Card: " << card.getName()
                  << " is not the appropriate type" << std::endl;
    }
}

int Row::calculatePower() const {
    int basePower = calculateBasePower();
    return has_horn ? (2 * basePower) : basePower;
}

std::ostream& operator<<(std::ostream& os, const Row& row) {
    os << "Your ";
    switch (row.type) {
        case RowType::MELEE: os << "MELEE"; break;
        case RowType::RANGED: os << "RANGED"; break;
        case RowType::SIEGE: os << "SIEGE"; break;
    }
    os << " ROW HAS: " << std::endl;
    for (const auto& card : row.cards) {
        os << "  " << card << std::endl;
    }
    os << "TOTAL POWER: " << row.calculatePower() << std::endl;
    return os;
}