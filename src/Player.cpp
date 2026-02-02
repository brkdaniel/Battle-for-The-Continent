//
// Created by danie on 12/6/2025.
//
#include "../headers/Player.h"
#include <utility> // Pentru std::move

Player::Player(std::string n, std::string faction)
    : name(std::move(n)),
      factionName(std::move(faction)),
      meleeRow(RowType::MELEE),
      rangedRow(RowType::RANGED),
      siegeRow(RowType::SIEGE)
{}

Deck& Player::getDeck() { return deck; }
Row& Player::getMeleeRow() { return meleeRow; }
Row& Player::getRangedRow() { return rangedRow; }
Row& Player::getSiegeRow() { return siegeRow; }

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "*** PLAYER " << p.name << " HAS A " << p.factionName << " DECK" << std::endl;
    os << p.deck << std::endl;
    os << p.meleeRow << std::endl;
    os << p.rangedRow << std::endl;
    os << p.siegeRow << std::endl;
    return os;
}