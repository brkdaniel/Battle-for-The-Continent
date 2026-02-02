#pragma once
#include "Player.h"

/**
 * @brief The main application class for the Gwent game.
 * * Implements the Singleton pattern to ensure only one game instance exists.
 * Manages the game loop, user input, and the player state.
 */
class GameApp {
private:
    Player player;
    bool isRunning;

    GameApp();

    void displayMenu() const;

    void runCycle();

    void testGameEngine();

public:
    GameApp(const GameApp &) = delete;

    GameApp &operator=(const GameApp &) = delete;

    static GameApp &getInstance();

    void run();
};
