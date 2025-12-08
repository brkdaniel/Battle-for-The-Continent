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
    int card_ID = 0;
    bool is_gold = false;
    CardStats stats;
    CardType type;

public:
    // Constructor
    UnitCard(const std::string& n, int p, int id, bool gold, CardType t, bool immune);

    // Suprascrierea funcțiilor virtuale (Override)
    void printDetails(std::ostream& os) const override;

    // Implementarea Clone (returnează o copie a sinelui)
    Card* clone() const override;

    // Getters vechi (mutati aici)
    int getCurrentPower() const;
    int getID() const;
    CardType getType() const;
    bool isGold() const;
};
#ifndef OOP_UNITCARD_H
#define OOP_UNITCARD_H

#endif //OOP_UNITCARD_H