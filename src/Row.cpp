#include "../headers/Row.h"
#include "../headers/UnitCard.h"

Row::Row(RowType t) : type(t) {}

bool Row::canAddCard(const Card* card) const {
    const auto* unit = dynamic_cast<const UnitCard*>(card);
    if (!unit) return false;

    if (unit->getRowType() != type && !unit->isGold()) {
         return false;
    }
    return unit->getRowType() == type;
}

void Row::addCard(std::unique_ptr<Card> card) {
    if (canAddCard(card.get())) {
        cards.push_back(std::move(card));
    } else {
        std::string rowName;
        switch(type) {
            case RowType::MELEE: rowName = "MELEE"; break;
            case RowType::RANGED: rowName = "RANGED"; break;
            case RowType::SIEGE: rowName = "SIEGE"; break;
        }

        std::string cardName = card->getName();
        throw InvalidMoveException(cardName, rowName);
    }
}

int Row::calculatePower() const {
    int total = 0;
    for (const auto& card : cards) {
        if (const auto* unit = dynamic_cast<const UnitCard*>(card.get())) {
            total += unit->getCurrentPower();
        }
    }
    if (hasHorn) total *= 2;
    return total;
}

void Row::applyWeather() {
    for (auto& card : cards) {
        if (auto* unit = dynamic_cast<UnitCard*>(card.get())) {
            if (!unit->isImmune()) {
                unit->setPower(1);
            }
        }
    }
}

void Row::clearWeather() {
}

void Row::setHorn(bool status) {
    hasHorn = status;
}

std::ostream& operator<<(std::ostream& os, const Row& row) {
    std::string typeStr;
    switch(row.type) {
        case RowType::MELEE: typeStr = "Melee"; break;
        case RowType::RANGED: typeStr = "Ranged"; break;
        case RowType::SIEGE: typeStr = "Siege"; break;
    }
    os << typeStr << " Row (" << row.calculatePower() << " pts): ";
    if (row.cards.empty()) {
        os << "[Empty]";
    } else {
        for (const auto& c : row.cards) {
            os << c->getName() << " ";
        }
    }
    if (row.hasHorn) os << " [Commander's Horn Active]";
    return os;
}