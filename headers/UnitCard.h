#pragma once
#include "Card.h"
#include "Enums.h"
#include <string>

class UnitCard : public Card {
private:
    int power;
    int cardID;
    bool is_gold;
    CardType type;
    bool is_immune;

public:
    UnitCard(const std::string& n, int p, int id, bool gold, CardType t, bool immune);

    void printDetails(std::ostream& os) const override;
    Card* clone() const override;

    // Getters si Setters necesari pentru logica din Row
    RowType getRowType() const;
    int getCurrentPower() const;
    void setPower(int p);
    bool isGold() const;
    bool isImmune() const;
};