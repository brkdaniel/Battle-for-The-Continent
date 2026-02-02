#include "../headers/WeatherCard.h"

WeatherCard::WeatherCard(const std::string &n, RowType r)
    : Card(n), affectedRow(r) {
}

void WeatherCard::printDetails(std::ostream &os) const {
    os << "[Weather: " << name << " | Affects Row: " << (int) affectedRow << "]";
}

Card *WeatherCard::clone() const {
    return new WeatherCard(*this);
}

bool WeatherCard::canBePlayedOn(RowType targetRow) const {
    return affectedRow == targetRow;
}
