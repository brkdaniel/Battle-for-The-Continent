#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "Enums.h"
#include "Card.h"
#include "GwentExceptions.h"

class Row {
private:
    RowType type;
    std::vector<std::unique_ptr<Card>> cards;
    bool hasHorn = false;

    bool canAddCard(const Card* card) const;

public:
    explicit Row(RowType t);
    
    Row(const Row&) = delete;
    Row& operator=(const Row&) = delete;
    
    ~Row() = default;

    void addCard(std::unique_ptr<Card> card);

    int calculatePower() const;
    void applyWeather();
    void clearWeather();
    void setHorn(bool status);

    friend std::ostream& operator<<(std::ostream& os, const Row& row);
};