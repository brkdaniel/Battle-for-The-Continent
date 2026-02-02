#include "../headers/CardFactory.h"
#include "../headers/UnitCard.h"
#include "../headers/WeatherCard.h"
#include "../headers/SpecialCard.h"
#include "../headers/TrapCard.h"
#include "../headers/Enums.h"

std::unique_ptr<Card> CardFactory::createCard(const std::string &type,
                                              const std::string &name,
                                              int value1,
                                              int value2,
                                              const std::string &desc) {
    if (type == "Unit") {
        auto row = static_cast<CardType>(value2);
        return std::make_unique<UnitCard>(name, value1, 0, false, row, false);
    }

    if (type == "Hero") {
        auto row = static_cast<CardType>(value2);
        return std::make_unique<UnitCard>(name, value1, 0, true, row, true);
    }

    if (type == "Weather") {
        return std::make_unique<WeatherCard>(name, static_cast<RowType>(value2));
    }

    if (type == "Special") {
        return std::make_unique<SpecialCard>(name, desc);
    }

    if (type == "Trap") {
        return std::make_unique<TrapCard>(name, static_cast<RowType>(value2), value1);
    }

    return nullptr;
}
