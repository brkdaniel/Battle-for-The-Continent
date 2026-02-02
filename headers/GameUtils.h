#ifndef OOP_GAMEUTILS_H
#define OOP_GAMEUTILS_H
#pragma once
#include <string>
#include "Deck.h"

void loadCardsFromFile(const std::string& filename, Deck& deck);
#endif //OOP_GAMEUTILS_H