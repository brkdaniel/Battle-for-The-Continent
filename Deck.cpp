//
// Created by danie on 12/6/2025.
//
#include "Deck.h"
#include <algorithm> // Pentru shuffle
#include <random>    // Pentru random_device
#include <stdexcept> // Pentru runtime_error

#include "GwentExceptions.h"

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
// Funcția swap schimbă pointerii interni între două obiecte Deck
void swap(Deck& first, Deck& second) noexcept {
    using std::swap;
    // Schimbăm vectorii. Pointerii la cărți rămân valizi, doar se mută.
    swap(first.cards, second.cards);
}

// Operatorul de atribuire prin Copy-and-Swap
// Parametrul 'other' este deja o copie (construită cu Copy Constructor)
Deck& Deck::operator=(Deck other) {
    std::cout << "Deck copy assignment (via Copy-and-Swap)\n";

    // Facem schimb între noi ('this') și copia temporară ('other')
    swap(*this, other);

    // Acum 'this' are datele noi, iar 'other' are datele vechi (gunoiul).
    // Când funcția se termină, destructorul lui 'other' va fi apelat automat
    // și va șterge memoria veche. Curat și sigur!

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
        throw EmptyDeckException();
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