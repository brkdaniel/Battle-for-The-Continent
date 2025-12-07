//
// Created by danie on 12/6/2025.
//
#pragma once
#include <vector>
#include <iostream>
#include "Card.h" // Include baza abstractă

class Deck {
private:
    // SCHIMBARE MAJORĂ: Vector de pointeri, nu de obiecte
    std::vector<Card*> cards;

public:
    Deck() = default;

    // 1. Destructor (Trebuie să șteargă pointerii!)
    ~Deck();

    // 2. Constructor de Copiere (Deep Copy)
    Deck(const Deck& other);

    // // 3. Operator de atribuire (Copy-and-Swap sau clasic)
    // Deck& operator=(const Deck& other);

    // NOU: Primește parametrul prin VALOARE (se face o copie automată)
    Deck& operator=(Deck other);

    // NOU: Funcție prietenă pentru swap eficient
    friend void swap(Deck& first, Deck& second) noexcept;

    // Modificăm addCard să ia pointeri (sau să creeze pointeri)
    // Varianta care ia pointer transferă responsabilitatea
    void addCard(Card* card);

    void shuffle();

    // Returnează pointer, nu obiect
    Card* draw();

    friend std::ostream& operator<<(std::ostream& os, const Deck& d);
};

#ifndef OOP_DECK_H
#define OOP_DECK_H

#endif //OOP_DECK_H