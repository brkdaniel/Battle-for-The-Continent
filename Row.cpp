//
// Created by danie on 12/6/2025.
//
#include "Row.h"
#include "UnitCard.h" // <--- OBLIGATORIU: Trebuie să știm de UnitCard pentru dynamic_cast
#include "GwentExceptions.h"

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
        // Pregătim numele rândului pentru mesajul de eroare
        std::string rowName;
        switch(type) {
            case RowType::MELEE: rowName = "MELEE"; break;
            case RowType::RANGED: rowName = "RANGED"; break;
            case RowType::SIEGE: rowName = "SIEGE"; break;
        }

        // Luăm numele cărții înainte să o ștergem (pentru mesaj)
        std::string cardName = card->getName();

        // IMPORTANT: Ștergem cartea pentru că Deck-ul nu o mai are,
        // iar Row-ul refuză să o ia. Dacă nu dăm delete, rămâne în memorie.
        delete card;

        // ARUNCĂM EXCEPȚIA
        throw InvalidMoveException(cardName, rowName);
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