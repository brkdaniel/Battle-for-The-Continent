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
