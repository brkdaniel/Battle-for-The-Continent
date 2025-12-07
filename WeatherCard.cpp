//
// Created by danie on 12/7/2025.
//
#include "WeatherCard.h"

WeatherCard::WeatherCard(const std::string& n, RowType row)
    : Card(n), affectedRow(row)
{}

void WeatherCard::printDetails(std::ostream& os) const {
    os << "[Weather: " << name << " | Affects Row: " << (int)affectedRow << "]";
}

Card* WeatherCard::clone() const {
    return new WeatherCard(*this);
}

RowType WeatherCard::getAffectedRow() const {
    return affectedRow;
}