//
// Created by danie on 12/6/2025.
//
#include "Deck.h"
#include <algorithm> // Pentru shuffle
#include <random>    // Pentru random_device
#include <stdexcept> // Pentru runtime_error

// 1. DESTRUCTORUL - Curăță memoria
Deck::~Deck() {
    for (Card* c : cards) {
        delete c; // Ștergem fiecare carte alocată dinamic
    }
    cards.clear();
}

// 2. CONSTRUCTORUL DE COPIERE (Deep Copy)
Deck::Deck(const Deck& other) {
    std::cout << "Deck copy constructor (Deep Copy)\n";
    for (const auto* c : other.cards) {
        // Aici folosim funcția virtuală CLONE!
        // Nu știm dacă e UnitCard sau altceva, dar clone() știe.
        cards.push_back(c->clone());
    }
}

// 3. OPERATORUL = (Assignment)
Deck& Deck::operator=(const Deck& other) {
    std::cout << "Deck copy assignment\n";
    if (this == &other) {
        return *this; // Auto-atribuire
    }

    // Pasul 1: Curățăm memoria veche (ca în destructor)
    for (Card* c : cards) {
        delete c;
    }
    cards.clear();

    // Pasul 2: Copiem elementele noi (ca în copy constructor)
    for (const auto* c : other.cards) {
        cards.push_back(c->clone());
    }

    return *this;
}

void Deck::addCard(Card* card) {
    cards.push_back(card);
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    // std::shuffle merge perfect și pe vector de pointeri
    std::shuffle(cards.begin(), cards.end(), g);
    std::cout << "You shuffled your cards\n";
}

Card* Deck::draw() {
    if (cards.empty()) {
        throw std::runtime_error("You have no cards left to draw.");
    }

    // Luăm pointerul
    Card* drawn_card = cards.back();
    // Îl scoatem din vector, DAR NU ÎL ȘTERGEM (delete)
    // pentru că vrem să îl returnăm viu.
    cards.pop_back();

    return drawn_card;
}

std::ostream& operator<<(std::ostream& os, const Deck& d) {
    os << "DECK SIZE: " << d.cards.size() << std::endl;
    for (const auto* card : d.cards) {
        // Aici apelăm operator<< pe pointer (*card)
        // Datorită funcțiilor virtuale din Card, se va afișa corect.
        os << "    " << *card << std::endl;
    }
    return os;
}