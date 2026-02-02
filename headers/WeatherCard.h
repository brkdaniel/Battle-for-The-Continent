//
// Created by danie on 12/7/2025.
//
#pragma once
#include "Card.h"
#include "Enums.h"

class WeatherCard : public Card {
private:
    RowType affectedRow; // Ce rând îngheță/afectează

public:
    WeatherCard(const std::string& n, RowType row);

    // Suprascriem metodele obligatorii
    void printDetails(std::ostream& os) const override;
    Card* clone() const override;

};