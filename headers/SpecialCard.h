#pragma once
#include "Card.h"
#include <string>

class SpecialCard : public Card {
private:
    std::string effectDescription;

public:
    SpecialCard(const std::string &n, const std::string &desc);

    void printDetails(std::ostream &os) const override;

    Card *clone() const override;

    bool canBePlayedOn(RowType row) const override;
};
