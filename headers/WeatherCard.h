#pragma once
#include "Card.h"
#include "Enums.h"

class WeatherCard : public Card {
private:
    RowType affectedRow;

public:
    WeatherCard(const std::string &n, RowType r);

    void printDetails(std::ostream &os) const override;

    Card *clone() const override;

    bool canBePlayedOn(RowType row) const override;
};
