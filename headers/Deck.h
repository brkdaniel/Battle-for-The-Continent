#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"
#include "GwentExceptions.h"

class Deck {
private:
    std::vector<std::unique_ptr<Card> > cards;

public:
    Deck() = default;

    Deck(const Deck &other);

    Deck &operator=(Deck other);

    friend void swap(Deck &first, Deck &second) noexcept;

    ~Deck() = default;

    void addCard(std::unique_ptr<Card> card);

    std::unique_ptr<Card> draw();

    void shuffle();

    void sortByPower();

    friend std::ostream &operator<<(std::ostream &os, const Deck &deck);

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
