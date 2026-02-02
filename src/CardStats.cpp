//
// Created by danie on 12/6/2025.
//

#include "../headers/CardStats.h"

CardStats::CardStats(int power, bool immune)
    : currentPower(power), isWeatherImmune(immune) {
}

int CardStats::getCurrentPower() const {
    return currentPower;
}


std::ostream& operator<<(std::ostream& os, const CardStats& stats) {
    os << " POWER: " << stats.currentPower;
    if (stats.isWeatherImmune) {
        os << " IMMUNE";
    }
    return os;
}