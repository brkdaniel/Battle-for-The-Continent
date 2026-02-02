//
// Created by danie on 12/6/2025.
//
#pragma once
#include <iostream>

class CardStats {
private:
    int current_power;
    bool is_weather_immune;

public:

    //constructor pentru stats pe carti
    CardStats(int power, bool immune);//power(p) - liste de initializare -> power = p

    int getCurrentPower() const;

    friend std::ostream& operator<<(std::ostream& os, const CardStats& stats);
};

#ifndef OOP_CARDSTATS_H
#define OOP_CARDSTATS_H

#endif //OOP_CARDSTATS_H