#pragma once
#include "Card.h"
#include "Enums.h"
#include <string>

class UnitCard : public Card {
private:
    int power;
    int cardId;
    bool isGold;
    CardType type;
    bool isImmune;

public:
    UnitCard(const std::string &n, int p, int id, bool gold, CardType t, bool immune);

    void printDetails(std::ostream &os) const override;

    Card *clone() const override;

    bool canBePlayedOn(RowType row) const override;

    RowType getRowType() const;

    int getCurrentPower() const;

    void setPower(int p);

    bool getIsGold() const;

    bool getIsImmune() const;
};
