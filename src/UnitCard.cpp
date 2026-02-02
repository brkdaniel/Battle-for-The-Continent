#include "../headers/UnitCard.h"

UnitCard::UnitCard(const std::string& n, int p, int id, bool gold, CardType t, bool immune)
    : Card(n), power(p), cardID(id), is_gold(gold), type(t), is_immune(immune)
{}

void UnitCard::printDetails(std::ostream& os) const {
    os << "[Unit: " << name << " | Pwr: " << power;
    if (is_gold) os << " (Gold)";
    if (is_immune) os << " (Immune)";
    os << "]";
}

Card* UnitCard::clone() const {
    return new UnitCard(*this);
}

RowType UnitCard::getRowType() const {
    // convertesc CardType in RowType
    return static_cast<RowType>(type);
}

int UnitCard::getCurrentPower() const {
    return power;
}

void UnitCard::setPower(int p) {
    power = p;
}

bool UnitCard::isGold() const {
    return is_gold;
}

bool UnitCard::isImmune() const {
    return is_immune;
}