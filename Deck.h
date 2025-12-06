//
// Created by danie on 12/6/2025.
//
#pragma once
#include <vector>
#include <iostream>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() = default;
    ~Deck();

    // Constructor de copiere
    Deck(const Deck& other);

    // Operator de atribuire
    Deck& operator=(const Deck& other);

    void addCard(const Card& card);
    void shuffle();
    Card draw();

    friend std::ostream& operator<<(std::ostream& os, const Deck& d);
};

#ifndef OOP_DECK_H
#define OOP_DECK_H

#endif //OOP_DECK_H