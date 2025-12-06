//
// Created by danie on 12/7/2025.
//
#pragma once
#include "Card.h"
#include "CardStats.h"
#include "Enums.h"

// CLASA DERIVATĂ (Is-A Card)
class UnitCard : public Card {
private:
    int power;
    int card_ID;
    bool is_gold;
    CardStats stats;
    CardType type;

public:
    // Constructor
    UnitCard(std::string n, int p, int id, bool gold, CardType t, bool immune);

    // Suprascrierea funcțiilor virtuale (Override)
    void printDetails(std::ostream& os) const override;

    // Implementarea Clone (returnează o copie a sinelui)
    Card* clone() const override;

    // Getters vechi (mutati aici)
    int getCurrentPower() const;
    CardType getType() const;
    bool isGold() const;
};
#ifndef OOP_UNITCARD_H
#define OOP_UNITCARD_H

#endif //OOP_UNITCARD_H