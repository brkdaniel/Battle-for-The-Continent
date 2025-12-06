//
// Created by danie on 12/6/2025.
//
#include "Row.h"
#include "UnitCard.h" // <--- OBLIGATORIU: Trebuie să știm de UnitCard pentru dynamic_cast

Row::Row(RowType t) : type(t), has_horn(false) {}

// 1. DESTRUCTORUL (Curăță memoria)
Row::~Row() {
    for (Card* c : cards) {
        delete c; // Ștergem cărțile de pe masă
    }
    cards.clear();
}

int Row::calculateBasePower() const {
    int total = 0;
    for (const auto* card : cards) {
        // CERINȚA: dynamic_cast "cu sens"
        // Încercăm să vedem dacă acest Card* este de fapt un UnitCard*
        if (const auto* unit = dynamic_cast<const UnitCard*>(card)) {
            // Dacă e unitate, îi putem citi puterea
            total += unit->getCurrentPower();
        }
        // Dacă e altceva (ex: WeatherCard), ignorăm puterea (e 0)
    }
    return total;
}

bool Row::canAddCard(Card* card) const {
    // Folosim dynamic_cast pentru a verifica tipul și a accesa getType()
    // (care există doar în UnitCard, nu și în Card abstract)
    auto* unit = dynamic_cast<UnitCard*>(card);

    if (!unit) {
        // Dacă nu e unitate (ex: e vrajă), momentan zicem false
        // (Aici vei putea adăuga logică pt alte tipuri mai târziu)
        return false;
    }

    CardType card_type = unit->getType(); // Acum putem apela getType() sigur

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

void Row::addCard(Card* card) {
    if (canAddCard(card)) {
        cards.push_back(card);
    } else {
        std::cout << "ERROR: Card [" << card->getName()
                  << "] cannot be placed on this row.\n";
        // IMPORTANT: Dacă refuzăm cartea, cineva trebuie să o șteargă!
        // Deoarece Deck-ul a dat-o deja afară (pop_back), ea a rămas în aer.
        // O ștergem aici ca să nu avem memory leak.
        delete card;
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

    for (const auto* card : row.cards) {
        // Dereferențiem pointerul (*card) pentru a apela operator<<
        os << "  " << *card << std::endl;
    }

    os << "TOTAL POWER: " << row.calculatePower() << std::endl;
    return os;
}