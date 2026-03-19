#include "../headers/Row.h"
#include "../headers/UnitCard.h"
#include <numeric>

Row::Row(RowType t) : type(t) {}

bool Row::canAddCard(const Card* card) const {
    return card->canBePlayedOn(type);
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
    int total = std::accumulate(cards.begin(), cards.end(), 0,
        [](int currentSum, const std::unique_ptr<Card>& card) {
            if (const auto* unit = dynamic_cast<const UnitCard*>(card.get())) {
                return currentSum + unit->getCurrentPower();
            }
            return currentSum;
        });

    return hasHorn ? total * 2 : total;
}

void Row::applyWeather() {
    for (auto& card : cards) {
        if (auto* unit = dynamic_cast<UnitCard*>(card.get())) {
            if (!unit->getIsImmune()) {
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