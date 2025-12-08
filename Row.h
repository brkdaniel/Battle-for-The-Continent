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
    bool has_horn = false;

    int calculateBasePower() const;
    bool canAddCard(Card *card) const;

public:
    explicit Row(RowType t);
    ~Row();

    // Dezactivăm copierea pentru a preveni erori de memorie accidentale
    Row(const Row&) = delete;
    Row& operator=(const Row&) = delete;

    void addCard(Card* card);
    int calculatePower() const;
    friend std::ostream& operator<<(std::ostream& os, const Row& r);
};

#ifndef OOP_ROW_H
#define OOP_ROW_H

#endif //OOP_ROW_H