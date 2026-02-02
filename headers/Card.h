#pragma once
#include <string>
#include <iostream>
#include "Enums.h"

class Card {
protected:
    std::string name;
    static int totalCardsCreated;

public:
    Card(const std::string &n);

    Card(const Card &other);

    virtual ~Card();

    virtual void printDetails(std::ostream &os) const = 0;

    virtual Card *clone() const = 0;

    virtual bool canBePlayedOn(RowType row) const = 0;

    std::string getName() const;

    static int getTotalCards();
};
