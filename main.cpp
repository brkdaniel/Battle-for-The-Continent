#include <iostream>
#include <fstream>
#include <string>

#include "Player.h"
#include "UnitCard.h"
#include "WeatherCard.h"
#include "SpecialCard.h"
#include "GwentExceptions.h"

// --- FUNCȚIE FACTORY: Citește fișierul și populează pachetul ---
void loadCardsFromFile(const std::string& filename, Deck& deck) {
    std::ifstream file(filename);

    // Verificăm dacă fișierul s-a deschis
    if (!file.is_open()) {
        throw FileReadException(filename);
    }

    std::cout << ">> Reading cards from file: " << filename << "...\n";

    int type;
    // Citim tipul cărții (primul număr de pe linie)
    while (file >> type) {
        std::string name;
        file >> name; // Citim numele

        Card* newCard = nullptr;

        if (type == 1) {
            // === UNIT CARD ===
            // Format: Putere ID Gold Rand Imun
            int power, id, rowInt;
            bool isGold, isImmune;

            file >> power >> id >> isGold >> rowInt >> isImmune;

            // Cast de la int la Enum
            auto cardType = static_cast<CardType>(rowInt);

            newCard = new UnitCard(name, power, id, isGold, cardType, isImmune);
        }
        else if (type == 2) {
            // === WEATHER CARD ===
            // Format: Rand_Afectat
            int rowInt;
            file >> rowInt;
            auto row = static_cast<RowType>(rowInt);

            newCard = new WeatherCard(name, row);
        }
        else if (type == 3) {
            // === SPECIAL CARD ===
            // Format: Descriere
            std::string desc;
            file >> desc;

            newCard = new SpecialCard(name, desc);
        }

        // Adăugăm cartea creată în pachet
        if (newCard != nullptr) {
            deck.addCard(newCard);
        }
    }

    file.close();
    std::cout << ">> File read successfully.\n";
}

int main() {
    std::cout << "=== MILESTONE 2 DEMO START ===\n\n";

    try {
        // ---------------------------------------------------------
        // ETAPA 1: Instanțierea Jucătorului
        // ---------------------------------------------------------
        std::cout << "*** 1. Loading Player ***" << std::endl;
        Player playerNo1("Daniel", "Northern Realms");

        // ---------------------------------------------------------
        // ETAPA 2: Citirea din Fișier (Factory Pattern)
        // ---------------------------------------------------------
        std::cout << "*** 2. Loading Cards from 'cards.txt' ***" << std::endl;

        // Aici apelăm funcția magică
        loadCardsFromFile("cards.txt", playerNo1.getDeck());

        // Testăm afișarea (Polimorfism: operator<< virtual)
        // Ar trebui să vezi Unități, Vreme și Speciale amestecate
        std::cout << "\n[Initial Deck State]:\n" << playerNo1 << std::endl;

        // Verificăm membrul Static
        std::cout << "-> Total Cards Created (Static): " << Card::getTotalCards() << "\n";

        // ---------------------------------------------------------
        // ETAPA 3: Testăm Shuffle
        // ---------------------------------------------------------
        std::cout << "\n*** 3. Shuffling ***" << std::endl;
        playerNo1.getDeck().shuffle();
        std::cout << "Deck shuffled.\n";

        // ---------------------------------------------------------
        // ETAPA 4: Testăm Copy-and-Swap
        // ---------------------------------------------------------
        std::cout << "\n*** 4. Testing Copy-and-Swap Operator ***" << std::endl;
        {
            Deck deckSursa = playerNo1.getDeck();
            Deck deckDestinatie;
            deckDestinatie.addCard(new UnitCard("Junk", 1, 99, false, CardType::SIEGE, false));

            deckDestinatie = deckSursa; // Assignment

            std::cout << "   [Independence Check] Shuffling Source...\n";
            deckSursa.shuffle(); // Destinatia nu trebuie sa se schimbe
        }
        std::cout << "Copy-and-Swap test finished.\n";

        // ---------------------------------------------------------
        // ETAPA 5: Game Logic & Exceptions (Draw & Play)
        // ---------------------------------------------------------
        std::cout << "\n*** 5. Drawing and Playing (Testing Exceptions) ***" << std::endl;

        // Tragem 3 cărți și încercăm să le jucăm
        for(int i = 0; i < 3; ++i) {
            try {
                Card* drawn = playerNo1.getDeck().draw();
                std::cout << "Draw " << (i+1) << ": " << drawn->getName() << " ... ";

                // Încercăm să le punem pe toate pe MELEE
                // Dacă e Vreme, Specială sau Ranged/Siege, va da eroare
                playerNo1.getMeleeRow().addCard(drawn);
                std::cout << "Placed on Melee.\n";

            } catch (const InvalidMoveException& e) {
                std::cout << "Logic Error: " << e.what() << "\n";
            } catch (const EmptyDeckException& e) {
                std::cout << "Deck Empty: " << e.what() << "\n";
                break;
            }
        }

        // ---------------------------------------------------------
        // ETAPA 6: Starea Finală
        // ---------------------------------------------------------
        std::cout << "\n*** 6. Final Game State ***\n";
        std::cout << playerNo1;
        std::cout << "Final Total Cards: " << Card::getTotalCards() << "\n";

    }
    catch (const FileReadException& e) {
        std::cout << "CRITICAL: " << e.what() << "\n";
        std::cout << "HINT: Make sure 'cards.txt' is in the correct folder!\n";
    }
    catch (const std::exception& e) {
        std::cout << "UNEXPECTED ERROR: " << e.what() << "\n";
    }

    std::cout << "\n=== DEMO END ===\n";
    return 0;
}