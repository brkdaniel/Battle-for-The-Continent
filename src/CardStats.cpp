//
// Created by danie on 12/6/2025.
//

#include "../headers/CardStats.h"

CardStats::CardStats(int power, bool immune)
    : current_power(power), is_weather_immune(immune) {
}

int CardStats::getCurrentPower() const {
    return current_power;
}


std::ostream& operator<<(std::ostream& os, const CardStats& stats) {
    os << " POWER: " << stats.current_power;
    if (stats.is_weather_immune) {
        os << " IMMUNE";
    }
    return os;
}