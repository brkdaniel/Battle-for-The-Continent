#pragma once
#include "Card.h"
#include "Enums.h"

class TrapCard : public Card {
private:
    RowType row;
    int damage;

public:
    TrapCard(const std::string &n, RowType r, int dmg);

    void printDetails(std::ostream &os) const override;

    Card *clone() const override;

    bool canBePlayedOn(RowType targetRow) const override;
};
