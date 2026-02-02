//
// Created by danie on 12/6/2025.
//

#pragma once
#include <string>
#include <iostream>
#include "Deck.h"
#include "Row.h"

class Player {
private:
    std::string name;
    std::string factionName;
    Deck deck;
    Row meleeRow;
    Row rangedRow;
    Row siegeRow;

public:
    Player(std::string n, std::string faction);

    Deck& getDeck();
    Row& getMeleeRow();
    Row& getRangedRow();
    Row& getSiegeRow();

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};