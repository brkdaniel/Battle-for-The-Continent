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
    std::string faction_name;
    Deck deck;
    Row melee_row;
    Row ranged_row;
    Row siege_row;

public:
    Player(std::string n, std::string faction);

    Deck& getDeck();
    Row& getMeleeRow();
    Row& getRangedRow();
    Row& getSiegeRow();

    friend std::ostream& operator<<(std::ostream& os, const Player& p);
};

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#endif //OOP_PLAYER_H