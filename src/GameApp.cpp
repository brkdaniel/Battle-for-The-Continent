#include "../headers/GameApp.h"
#include "../headers/GameUtils.h"
#include <iostream>
#include <limits>

GameApp::GameApp() : player("Daniel", "Northern Realms"), isRunning(true) {}

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
    } catch (const std::exception& e) {
        std::cout << "CRITICAL INIT ERROR: " << e.what() << "\n";
        return;
    }

    while (isRunning) {
        displayMenu();
        int command;
        if (!(std::cin >> command)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        if (command == 0) isRunning = false;
        else if (command == 1) runCycle();
        else if (command == 2) {
            player.getDeck().shuffle();
            std::cout << "Deck shuffled.\n";
        }
        else if (command == 3) {
            std::cout << player << "\n";
        }
        else {
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

        player.getMeleeRow().addCard(std::move(card));
        
        std::cout << "Card placed on Melee row successfully.\n";

    } catch (const EmptyDeckException& e) {
        std::cout << "ACTION FAILED: " << e.what() << "\n";
    } catch (const InvalidMoveException& e) {
        std::cout << "ACTION FAILED: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << "\n";
    }
}