//
// Created by danie on 12/6/2025.
//
#pragma once
#include <iostream>

class CardStats {
private:
    int currentPower;
    bool isWeatherImmune;

public:

    //constructor pentru stats pe carti
    CardStats(int power, bool immune);//power(p) - liste de initializare -> power = p

    int getCurrentPower() const;

    friend std::ostream& operator<<(std::ostream& os, const CardStats& stats);
};
