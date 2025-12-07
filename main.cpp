#include <iostream>
#include "Player.h"
#include "UnitCard.h"
#include "WeatherCard.h"
#include "SpecialCard.h"
#include "GwentExceptions.h"

int main() {
    std::cout << "=== MILESTONE 2 DEMO START ===\n\n";

    // ---------------------------------------------------------
    // ETAPA 1: Instanțierea Jucătorului și Crearea Cărților
    // ---------------------------------------------------------
    std::cout << "*** 1. Loading Player & Creating Cards (Dynamic Memory) ***" << std::endl;
    Player playerNo1("Daniel", "Northern Realms");

    // Folosim 'new' și pointeri la clasa de bază (Polimorfism)
    // Cerinta M2: Vector de pointeri la baza abstracta
    Card* c1 = new UnitCard("Knight", 3, 1, false, CardType::MELEE, false);
    Card* c2 = new UnitCard("Archer", 4, 2, true, CardType::RANGED, false);
    Card* c3 = new UnitCard("Ballista", 7, 3, false, CardType::SIEGE, true);
    Card* c4 = new UnitCard("Ram", 2, 4, false, CardType::SIEGE, true);
    Card* c5 = new UnitCard("Geralt", 10, 5, true, CardType::MELEE, true); // Hero
    Card* c6 = new UnitCard("Dandelion", 4, 6, false, CardType::MELEE, false);
    Card* c7 = new UnitCard("Yennefer", 7, 7, false, CardType::RANGED, true);

    // Cerinta M2: Minim 3 clase derivate (Unit, Weather, Special)
    Card* c8 = new WeatherCard("Biting Frost", RowType::MELEE);
    Card* c9 = new SpecialCard("Scorch", "Destroy strongest unit");

    // ---------------------------------------------------------
    // ETAPA 2: Adăugarea în Deck (Ownership Transfer)
    // ---------------------------------------------------------
    std::cout << "*** 2. Adding Cards to Deck ***" << std::endl;
    // Deck-ul preia responsabilitatea pointerilor. Nu mai trebuie să facem noi 'delete'.
    playerNo1.getDeck().addCard(c1);
    playerNo1.getDeck().addCard(c2);
    playerNo1.getDeck().addCard(c3);
    playerNo1.getDeck().addCard(c4);
    playerNo1.getDeck().addCard(c5);
    playerNo1.getDeck().addCard(c6);
    playerNo1.getDeck().addCard(c7);
    playerNo1.getDeck().addCard(c8);
    playerNo1.getDeck().addCard(c9);

    // Testăm afișarea (Polimorfism: operator<< virtual)
    std::cout << playerNo1 << std::endl;

    // Verificăm membrul Static
    std::cout << "-> Total Cards Created (Static): " << Card::getTotalCards() << "\n";

    // ---------------------------------------------------------
    // ETAPA 3: Testăm Shuffle
    // ---------------------------------------------------------
    std::cout << "\n*** 3. Shuffling ***" << std::endl;
    playerNo1.getDeck().shuffle();
    std::cout << "Deck shuffled.\n";

    // ---------------------------------------------------------
    // ETAPA 4: Testăm Copy-and-Swap (Atribuire și Deep Copy)
    // ---------------------------------------------------------
    std::cout << "\n*** 4. Testing Copy-and-Swap Operator ***" << std::endl;
    {
        Deck deckSursa = playerNo1.getDeck(); // Copy Constructor
        Deck deckDestinatie;

        // Adăugăm o carte "gunoi" în destinație ca să vedem că se șterge la atribuire
        deckDestinatie.addCard(new UnitCard("Junk_Card", 1, 99, false, CardType::SIEGE, false));

        std::cout << "   [Before Assignment] Destinatie size: 1 (Junk)\n";

        // TEST CRITIC: Atribuirea
        deckDestinatie = deckSursa;
        std::cout << "   [After Assignment] deckDestinatie = deckSursa executed.\n";

        // Testăm Deep Copy (Independența)
        std::cout << "   [Independence Check] Modifying Source (Shuffle)...\n";
        deckSursa.shuffle();

        std::cout << "   Daca Deep Copy merge, Destinatia NU trebuie sa fie afectata de shuffle-ul sursei.\n";
        // La ieșirea din scope {}, destructorii vor curăța tot.
    }
    std::cout << "Copy-and-Swap test finished (check for crashes/leaks).\n";

    // ---------------------------------------------------------
    // ETAPA 5: Game Logic & Exceptions (Draw & Play)
    // ---------------------------------------------------------
    std::cout << "\n*** 5. Drawing and Playing (Testing Exceptions) ***" << std::endl;
    try {
        // Cazul 1: Succes
        Card* drawn1 = playerNo1.getDeck().draw();
        std::cout << "1. You drew: " << drawn1->getName() << "\n";
        playerNo1.getMeleeRow().addCard(drawn1); // Ar trebui să meargă dacă e Melee sau Hero-Melee
        std::cout << "   -> Placed successfully.\n";

        // Cazul 2: Posibilă Eroare (Invalid Move)
        // Extragem o carte și încercăm să o forțăm pe un rând (demo)
        Card* drawn2 = playerNo1.getDeck().draw();
        std::cout << "2. You drew: " << drawn2->getName() << "\n";

        // Încercăm să o punem tot pe Melee. Dacă e Ranged/Siege/Weather, va arunca excepție.
        std::cout << "   -> Attempting to place on MELEE row...\n";
        playerNo1.getMeleeRow().addCard(drawn2);
        std::cout << "   -> Placed successfully.\n";

    } catch (const EmptyDeckException& e) {
        std::cout << "RESOURCE ERROR: " << e.what() << "\n";
    } catch (const InvalidMoveException& e) {
        std::cout << "LOGIC ERROR: " << e.what() << "\n";
    } catch (const GwentException& e) {
        std::cout << "GWENT ERROR: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "UNKNOWN EXCEPTION: " << e.what() << "\n";
    }

    // ---------------------------------------------------------
    // ETAPA 6: Starea Finală
    // ---------------------------------------------------------
    std::cout << "\n*** 6. Final Game State ***\n";
    std::cout << playerNo1;

    std::cout << "Final Total Cards (Static Check): " << Card::getTotalCards() << "\n";
    std::cout << "\n=== DEMO END ===\n";
    return 0;
}