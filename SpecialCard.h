//
// Created by danie on 12/7/2025.
//

#pragma once
#include "Card.h"

class SpecialCard : public Card {
private:
    std::string effectDescription;

public:
    SpecialCard(const std::string& n, const std::string& desc);

    void printDetails(std::ostream& os) const override;
    Card* clone() const override;
};

#ifndef OOP_SPECIALCARD_H
#define OOP_SPECIALCARD_H

#endif //OOP_SPECIALCARD_H