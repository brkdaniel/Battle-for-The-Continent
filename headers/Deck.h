#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"
#include "GwentExceptions.h"

class Deck {
private:
    std::vector<std::unique_ptr<Card> > cards;

public:
    Deck() = default;

    Deck(const Deck &other);

    Deck &operator=(Deck other);

    friend void swap(Deck &first, Deck &second) noexcept;

    ~Deck() = default;

    void addCard(std::unique_ptr<Card> card);

    std::unique_ptr<Card> draw();

    void shuffle();

    void sortByPower();

    friend std::ostream &operator<<(std::ostream &os, const Deck &deck);
};
