//
// Created by danie on 12/6/2025.
//
#pragma once
#include <string>
#include <iostream>
#include "Enums.h"
#include "CardStats.h"

class Card {
private:
    std::string name;
    int power;
    int card_ID;
    bool is_gold;
    CardStats stats;
    CardType type;

public:
    Card(std::string n, int p, int id, bool gold, CardType t, bool immune);

    std::string getName() const;
    int getBasePower() const;
    int getID() const;
    bool isGold() const;
    CardType getType() const;

    // Delegare către stats
    int getCurrentPower() const;
    const CardStats& getStats() const;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

#ifndef OOP_CARD_H
#define OOP_CARD_H

#endif //OOP_CARD_H