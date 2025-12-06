//
// Created by danie on 12/6/2025.
//

#pragma once
#include <vector>
#include <iostream>
#include "Card.h"
#include "Enums.h"

class Row {
private:
    RowType type;
    std::vector<Card*> cards;
    bool has_horn;

    int calculateBasePower() const;
    bool canAddCard(Card *card) const;

public:
    explicit Row(RowType t);
    void addCard(Card* card);
    int calculatePower() const;
    ~Row();
    friend std::ostream& operator<<(std::ostream& os, const Row& r);
};

#ifndef OOP_ROW_H
#define OOP_ROW_H

#endif //OOP_ROW_H