
#ifndef OOP_GAMEAPP_H
#define OOP_GAMEAPP_H
#pragma once
#include "Player.h"

class GameApp {
private:
    Player player;
    bool isRunning;

    void displayMenu() const;
    void runCycle();

public:
    GameApp();
    void run();
};

#endif //OOP_GAMEAPP_H