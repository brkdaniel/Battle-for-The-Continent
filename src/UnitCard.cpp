#include "../headers/UnitCard.h"

UnitCard::UnitCard(const std::string &n, int p, int id, bool gold, CardType t, bool immune)
    : Card(n), power(p), cardId(id), isGold(gold), type(t), isImmune(immune) {
}

void UnitCard::printDetails(std::ostream &os) const {
    os << "[Unit: " << name << " | ID: " << cardId << " | Pwr: " << power;
    if (isGold) os << " (Gold)";
    if (isImmune) os << " (Immune)";
    os << "]";
}

Card *UnitCard::clone() const {
    return new UnitCard(*this);
}

bool UnitCard::canBePlayedOn(RowType targetRow) const {
    if (isGold) return true;
    return static_cast<RowType>(type) == targetRow;
}

int UnitCard::getCurrentPower() const {
    return power;
}

void UnitCard::setPower(int p) {
    power = p;
}

bool UnitCard::getIsImmune() const {
    return isImmune;
}

bool UnitCard::getIsGold() const {
    return isGold;
}
