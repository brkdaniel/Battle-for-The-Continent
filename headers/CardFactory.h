#pragma once
#include <memory>
#include <string>
#include "Card.h"

/**
 * @brief Static factory class for creating Card instances.
 * Implements the Factory Design Pattern to centralize object creation.
 */
class CardFactory {
public:
    /**
     * @brief Creates a specific card type based on the provided identifier.
     * @param type The category of the card (e.g., "Unit", "Hero", "Weather", "Special").
     * @param name The name of the card.
     * @param value1 Primary numeric value (Power for units, Damage for traps).
     * @param value2 Secondary numeric value (Row index for units).
     * @param desc Text description (for Special/Weather cards).
     * @return std::unique_ptr<Card> Pointer to the created card, or nullptr if type is invalid.
     */
    static std::unique_ptr<Card> createCard(const std::string &type,
                                            const std::string &name,
                                            int value1,
                                            int value2,
                                            const std::string &desc);
};
