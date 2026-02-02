//
// Created by danie on 12/8/2025.
//
#pragma once
#include "Card.h"
#include "Enums.h"

class TrapCard : public Card {
private:
    RowType row = RowType::MELEE;
    int damage = 0; // Cât damage dă când e declanșată

public:
    TrapCard(const std::string& n, RowType r, int dmg);

    void printDetails(std::ostream& os) const override;
    Card* clone() const override;
};