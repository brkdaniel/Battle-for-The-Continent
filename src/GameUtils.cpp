#include "../headers/GameUtils.h"
#include "../headers/CardFactory.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

void loadCardsFromFile(const std::string &filename, Deck &deck) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string type, name, desc;
        int val1 = 0, val2 = 0;

        // Format: Type|Name|Val1|Val2|Desc
        // Example: Unit|Soldier|5|0|None

        std::string segment;
        std::vector<std::string> tokens;

        while (std::getline(ss, segment, '|')) {
            tokens.push_back(segment);
        }

        if (tokens.size() >= 2) {
            type = tokens[0];
            name = tokens[1];

            if (tokens.size() > 2) val1 = std::stoi(tokens[2]);
            if (tokens.size() > 3) val2 = std::stoi(tokens[3]);
            if (tokens.size() > 4) desc = tokens[4];

            auto card = CardFactory::createCard(type, name, val1, val2, desc);
            if (card) {
                deck.addCard(std::move(card));
            }
        }
    }
}
