#pragma once
#include <vector>
#include <memory>
#include "Card.h"

class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    void addCard(std::unique_ptr<Card> card);
    std::unique_ptr<Card> draw();
    void shuffle();
    void sortByPower();
    bool isEmpty() const;

    /**
     * @brief Template method to filter cards by their specific derived class.
     * @tparam T The derived Card type to search for (e.g., UnitCard, WeatherCard).
     * @return std::vector<const T*> A vector of non-owning pointers to the found cards.
     */

    template <typename T>
    std::vector<const T*> getCardsOfType() const {
        std::vector<const T*> result;
        for (const auto& card : cards) {

            if (const auto* casted = dynamic_cast<const T*>(card.get())) {
                result.push_back(casted);
            }
        }
        return result;
    }
};
