//
// Created by danie on 12/6/2025.
//
#include "Deck.h"
#include <algorithm> // Pentru shuffle
#include <random>    // Pentru random_device
#include <stdexcept> // Pentru runtime_error

Deck::~Deck() {}

Deck::Deck(const Deck& other) : cards(other.cards) {
    std::cout << "Deck copy constructor" << std::endl;
}

Deck& Deck::operator=(const Deck& other) {
    std::cout << "Deck copy assignment" << std::endl;
    if (this != &other) {
        cards = other.cards;
    }
    return *this;
}

void Deck::addCard(const Card& card) {
    cards.push_back(card);
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    std::cout << "You shuffled your cards\n";
}

Card Deck::draw() {
    if (cards.empty()) {
        throw std::runtime_error("You have no cards left to draw.");
    }
    Card drawn_card = cards.back();
    cards.pop_back();
    return drawn_card;
}

std::ostream& operator<<(std::ostream& os, const Deck& d) {
    os << "DECK SIZE: " << d.cards.size() << std::endl;
    for (const auto& card : d.cards) {
        os << "    " << card << std::endl;
    }
    return os;
}