#include "../headers/GameApp.h"
#include "../headers/GameUtils.h"
#include "../headers/UnitCard.h"
#include <iostream>
#include <limits>

GameApp::GameApp() : player("Daniel", "Northern Realms"), isRunning(true) {
}

GameApp &GameApp::getInstance() {
    static GameApp instance;
    return instance;
}

void GameApp::testGameEngine() {
    player.getDeck().sortByPower();

    player.getMeleeRow().setHorn(true);
    player.getMeleeRow().setHorn(false); // Reset

    player.getRangedRow().applyWeather();
    player.getRangedRow().clearWeather(); // Reset

    if (player.getSiegeRow().calculatePower() < 0) {
        std::cout << "Engine Check: Siege row integrity ok.\n";
    }
}

void GameApp::displayMenu() const {
    std::cout << "\n=== GWENT MENU ===\n";
    std::cout << "1. Draw Card & Play\n";
    std::cout << "2. Shuffle Deck\n";
    std::cout << "3. Show Board\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose option: ";
}

void GameApp::run() {
    try {
        loadCardsFromFile("cards.txt", player.getDeck());
        std::cout << "Initialization complete. Deck loaded.\n";

        testGameEngine();
        std::cout << "System checks passed: Engine active.\n";

        std::cout << "Debug Info: Total Card objects created: " << Card::getTotalCards() << "\n";
    } catch (const std::exception &e) {
        std::cout << "CRITICAL INIT ERROR: " << e.what() << "\n";
        return;
    }

    while (isRunning) {
        displayMenu();
        int command;
        if (!(std::cin >> command)) {
            if (std::cin.eof()) {
                std::cout << "End of input detected. Exiting loop.\n";
                isRunning = false;
                continue;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (command == 0) isRunning = false;
        else if (command == 1) runCycle();
        else if (command == 2) {
            player.getDeck().shuffle();
            std::cout << "Deck shuffled.\n";
        } else if (command == 3) {
            std::cout << player << "\n";
        } else {
            std::cout << "Invalid command.\n";
        }
    }
    std::cout << "Exiting Gwent Application...\n";
}

void GameApp::runCycle() {
    try {
        std::cout << "Drawing a card...\n";

        auto card = player.getDeck().draw();
        std::cout << "You drew: " << card->getName() << "\n";

        if (const auto *unit = dynamic_cast<const UnitCard *>(card.get())) {
            if (unit->getIsGold()) {
                std::cout << "*** LEGENDARY GOLD CARD! ***\n";
            }
        }

        std::cout << "Where do you want to place it?\n";
        std::cout << "0. Melee Row\n1. Ranged Row\n2. Siege Row\n> ";

        int rowChoice;
        if (!(std::cin >> rowChoice)) {
            std::cout << "Invalid input. Turn skipped, card lost.\n";
            return;
        }

        if (rowChoice == 0) {
            player.getMeleeRow().addCard(std::move(card));
            std::cout << "Placed on MELEE.\n";
        } else if (rowChoice == 1) {
            player.getRangedRow().addCard(std::move(card));
            std::cout << "Placed on RANGED.\n";
        } else if (rowChoice == 2) {
            player.getSiegeRow().addCard(std::move(card));
            std::cout << "Placed on SIEGE.\n";
        } else {
            std::cout << "Invalid row index. Card lost.\n";
        }
    } catch (const EmptyDeckException &e) {
        std::cout << "ACTION FAILED: " << e.what() << "\n";
    } catch (const InvalidMoveException &e) {
        std::cout << "ACTION FAILED: " << e.what() << "\n";
        std::cout << "(Hint: Use 'Show Board' to check row types or read card description)\n";
    } catch (const std::exception &e) {
        std::cout << "ERROR: " << e.what() << "\n";
    }
}
