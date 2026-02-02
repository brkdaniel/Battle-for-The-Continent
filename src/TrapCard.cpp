#include "../headers/TrapCard.h"

TrapCard::TrapCard(const std::string &n, RowType r, int dmg)
    : Card(n), row(r), damage(dmg) {
}

void TrapCard::printDetails(std::ostream &os) const {
    os << "[Trap: " << name << " | Row: " << (int) row << " | Dmg: " << damage << "]";
}

Card *TrapCard::clone() const {
    return new TrapCard(*this);
}

bool TrapCard::canBePlayedOn(RowType targetRow) const {
    return row == targetRow;
}
