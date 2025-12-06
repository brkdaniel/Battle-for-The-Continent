#include <iostream>
#include "Player.h"
#include "UnitCard.h" // Trebuie să includem clasa concretă pentru a face 'new'
// Nu includem "Card.h" direct pentru că UnitCard îl include deja

int main() {
    std::cout << "=== MILESTONE 2 DEMO START ===\n\n";

    // 1. Instanțierea Jucătorului
    std::cout << "*** 1. Loading Player & Creating Cards (Dynamic Memory) ***" << std::endl;
    Player playerNo1("Daniel", "Northern Realms");

    // SCHIMBARE M2: Folosim 'new' și pointeri la clasa de bază (Polimorfism)
    // Deși variabila e de tip Card* (Baza), obiectul real e UnitCard (Derivata)
    Card* c1 = new UnitCard("Knight", 3, 1, false, CardType::MELEE, false);
    Card* c2 = new UnitCard("Archer", 4, 2, true, CardType::RANGED, false);
    Card* c3 = new UnitCard("Ballista", 7, 3, false, CardType::SIEGE, true);
    Card* c4 = new UnitCard("Ram", 2, 4, false, CardType::SIEGE, true);
    Card* c5 = new UnitCard("Geralt", 10, 5, true, CardType::MELEE, true); // Gold Hero
    Card* c6 = new UnitCard("Dandelion", 4, 6, false, CardType::MELEE, false);
    Card* c7 = new UnitCard("Yennefer", 7, 7, false, CardType::RANGED, true);

    // 2. Adăugarea în Deck
    // Deck-ul preia responsabilitatea pointerilor (Ownership transfer)
    std::cout << "*** 2. Adding Cards to Deck ***" << std::endl;
    playerNo1.getDeck().addCard(c1);
    playerNo1.getDeck().addCard(c2);
    playerNo1.getDeck().addCard(c3);
    playerNo1.getDeck().addCard(c4);
    playerNo1.getDeck().addCard(c5);
    playerNo1.getDeck().addCard(c6);
    playerNo1.getDeck().addCard(c7);

    // Testăm afișarea (Polimorfism: operator<< virtual)
    std::cout << playerNo1 << std::endl;

    // 3. Testăm Shuffle
    std::cout << "*** 3. Shuffling ***" << std::endl;
    playerNo1.getDeck().shuffle();
    std::cout << playerNo1 << std::endl;

    // 4. Testăm Deep Copy (Rule of Three cu pointeri)
    // Asta verifică dacă funcția virtuală clone() merge corect
    std::cout << "*** 4. Testing Deep Copy (Virtual Clone) ***" << std::endl;
    {
        Deck deckCopiat = playerNo1.getDeck();
        std::cout << "Deck Copiat (Temporar): \n" << deckCopiat << "\n";
        // Când ieșim din acest bloc {}, destructorul lui deckCopiat
        // va șterge copiile cărților, dar deck-ul original rămâne intact.
    }
    std::cout << "Deck-ul original a ramas intact (Speram):\n" << playerNo1.getDeck() << "\n";

    // 5. Testăm Draw și Play (Dynamic Cast în Row)
    std::cout << "*** 5. Drawing and Playing ***" << std::endl;
    try {
        // Extragem prima carte
        Card* drawn1 = playerNo1.getDeck().draw();
        std::cout << "You drew: " << drawn1->getName() << "\n"; // -> în loc de .

        // O jucăm pe rândul Melee
        // Aici Row::addCard face dynamic_cast să vadă dacă e UnitCard și dacă e Melee
        playerNo1.getMeleeRow().addCard(drawn1);

        // Extragem a doua carte
        Card* drawn2 = playerNo1.getDeck().draw();
        std::cout << "You drew: " << drawn2->getName() << "\n";

        // Încercăm să o punem tot pe Melee (dacă e Ranged/Siege va da eroare și o va șterge)
        playerNo1.getMeleeRow().addCard(drawn2);

    } catch (const std::exception& e) {
        std::cout << "EXCEPTION: " << e.what() << "\n";
    }

    // 6. Starea Finală
    std::cout << "\n*** 6. Final Game State ***\n";
    std::cout << playerNo1;

    // Nu trebuie să facem delete manual la c1...c7 aici,
    // deoarece Deck-ul (sau Row-ul) le deține și le va șterge în destructorii lor.

    std::cout << "\n=== DEMO END ===\n";
    return 0;
}