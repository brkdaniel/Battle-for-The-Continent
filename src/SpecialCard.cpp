#include "../headers/SpecialCard.h"

SpecialCard::SpecialCard(const std::string& n, const std::string& desc)
    : Card(n), effectDescription(desc)
{}

void SpecialCard::printDetails(std::ostream& os) const {
    os << "[Special: " << name << " | " << effectDescription << "]";
}

Card* SpecialCard::clone() const {
    return new SpecialCard(*this);
}

bool SpecialCard::canBePlayedOn(RowType /*targetRow*/) const {
    return true;
}