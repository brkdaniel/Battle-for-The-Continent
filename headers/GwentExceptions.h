//
// Created by danie on 12/7/2025.
//
#pragma once
#include <stdexcept>
#include <string>

// clasa de baza
class GwentException : public std::runtime_error {
public:
    // constructoru trimite la std::runtime_error
    explicit GwentException(const std::string& message)
        : std::runtime_error("GWENT ERROR: " + message) {}
};

class EmptyDeckException : public GwentException {
public:
    EmptyDeckException()
        : GwentException("The deck is empty! Cannot draw any more cards.") {}
};

// MUTARE INVALIDA
class InvalidMoveException : public GwentException {
public:
    InvalidMoveException(const std::string& cardName, const std::string& rowName)
        : GwentException("Card [" + cardName + "] cannot be placed on row [" + rowName + "].") {}
};

// FISIERE
class FileReadException : public GwentException {
public:
    explicit FileReadException(const std::string& fileName)
        : GwentException("Critical error: Could not open or read file: " + fileName) {}
};