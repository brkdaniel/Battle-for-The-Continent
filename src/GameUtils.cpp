#include "../headers/GameUtils.h"
#include <fstream>
#include <iostream>
#include <memory>

#include "../headers/UnitCard.h"
#include "../headers/WeatherCard.h"
#include "../headers/SpecialCard.h"
#include "../headers/TrapCard.h"
#include "../headers/GwentExceptions.h"

void loadCardsFromFile(const std::string& filename, Deck& deck) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileReadException(filename);
    }

    std::cout << ">> Reading cards from file: " << filename << "...\n";

    int type;
    while (file >> type) {
        std::string name;
        file >> name;

        std::unique_ptr<Card> newCard = nullptr;

        if (type == 1) {
            int power, id, rowInt;
            bool isGold, isImmune;
            file >> power >> id >> isGold >> rowInt >> isImmune;
            auto cardType = static_cast<CardType>(rowInt);

            newCard = std::make_unique<UnitCard>(name, power, id, isGold, cardType, isImmune);
        }
        else if (type == 2) {
            int rowInt; file >> rowInt;
            newCard = std::make_unique<WeatherCard>(name, static_cast<RowType>(rowInt));
        }
        else if (type == 3) {
            std::string desc; file >> desc;
            newCard = std::make_unique<SpecialCard>(name, desc);
        }
        else if (type == 4) {
            int rowInt, dmg; file >> rowInt >> dmg;
            newCard = std::make_unique<TrapCard>(name, static_cast<RowType>(rowInt), dmg);
        }

        if (newCard) {
            deck.addCard(std::move(newCard));
        }
    }
    file.close();
    std::cout << ">> File read successfully.\n";
}