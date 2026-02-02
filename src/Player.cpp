//
// Created by danie on 12/6/2025.
//
#include "../headers/Player.h"
#include <utility> // Pentru std::move

Player::Player(std::string n, std::string faction)
    : name(std::move(n)),
      faction_name(std::move(faction)),
      melee_row(RowType::MELEE),
      ranged_row(RowType::RANGED),
      siege_row(RowType::SIEGE)
{}

Deck& Player::getDeck() { return deck; }
Row& Player::getMeleeRow() { return melee_row; }
// Row& Player::getRangedRow() { return ranged_row; }
// Row& Player::getSiegeRow() { return siege_row; }

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "*** PLAYER " << p.name << " HAS A " << p.faction_name << " DECK" << std::endl;
    os << p.deck << std::endl;
    os << p.melee_row << std::endl;
    os << p.ranged_row << std::endl;
    os << p.siege_row << std::endl;
    return os;
}