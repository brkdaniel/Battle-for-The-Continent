#pragma once
#include "Card.h"
#include "Enums.h"
#include <string>

class UnitCard : public Card {
private:
    int power = 0;
    int cardId = 0;
    bool isGold = false;
    CardType type = CardType::MELEE;
    bool isImmune = false;

public:
    UnitCard(const std::string &n, int p, int id, bool gold, CardType t, bool immune);

    void printDetails(std::ostream &os) const override;

    Card *clone() const override;

    bool canBePlayedOn(RowType row) const override;

    int getCurrentPower() const;

    void setPower(int p);

    bool getIsImmune() const;
    bool getIsGold() const;
};
