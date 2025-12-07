//
// Created by danie on 12/6/2025.
//
#pragma once
#include <string>
#include <iostream>

// CLASA ABSTRACTĂ (Base Class)
class Card {
protected:
    std::string name; // Singurul atribut comun tuturor
    static int totalCardsCreated;

public:
    Card(const std::string& n);
    //functie pt a citi contorul
    static int getTotalCards();
    // 1. Destructor Virtual (CRITIC pentru vector<Card*>)
    virtual ~Card();

    // 2. Funcție Virtuală Pură (Interfața de afișare)
    virtual void printDetails(std::ostream& os) const = 0;

    // 3. Constructor Virtual (Clone)
    // Ne ajută să facem copii corecte (Deep Copy) fără să știm tipul exact
    virtual Card* clone() const = 0;

    const std::string& getName() const;

    // Operator << care apelează funcția virtuală
    friend std::ostream& operator<<(std::ostream& os, const Card& c);
};
#ifndef OOP_CARD_H
#define OOP_CARD_H

#endif //OOP_CARD_H