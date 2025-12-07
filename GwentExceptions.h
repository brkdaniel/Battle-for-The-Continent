//
// Created by danie on 12/7/2025.
//
#pragma once
#include <stdexcept>
#include <string>

// 1. CLASA DE BAZĂ PROPRIE
class GwentException : public std::runtime_error {
public:
    // Constructorul preia mesajul și îl trimite la std::runtime_error
    explicit GwentException(const std::string& message)
        : std::runtime_error("GWENT ERROR: " + message) {}
};

// 2. EXCEPȚIE PENTRU PACHET GOL (Resurse)
class EmptyDeckException : public GwentException {
public:
    EmptyDeckException()
        : GwentException("The deck is empty! Cannot draw any more cards.") {}
};

// 3. EXCEPȚIE PENTRU MUTARE INVALIDĂ (Logică joc)
class InvalidMoveException : public GwentException {
public:
    InvalidMoveException(const std::string& cardName, const std::string& rowName)
        : GwentException("Card [" + cardName + "] cannot be placed on row [" + rowName + "].") {}
};

// 4. EXCEPȚIE PENTRU FIȘIERE (Input/Output - o folosim mai târziu)
class FileReadException : public GwentException {
public:
    explicit FileReadException(const std::string& fileName)
        : GwentException("Critical error: Could not open or read file: " + fileName) {}
};

#ifndef OOP_GWENTEXCEPTION_H
#define OOP_GWENTEXCEPTION_H

#endif //OOP_GWENTEXCEPTION_H