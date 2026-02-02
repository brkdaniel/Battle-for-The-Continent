//
// Created by danie on 12/6/2025.
//
#pragma once
#include <string>
#include <iostream>

class Card {
protected:
    std::string name;
    static int totalCardsCreated;

public:
    Card(const std::string& n);
    //functie pt a citi contorul
    static int getTotalCards();

    virtual ~Card();

    virtual void printDetails(std::ostream& os) const = 0;

    virtual Card* clone() const = 0;

    const std::string& getName() const;

    friend std::ostream& operator<<(std::ostream& os, const Card& c);
};