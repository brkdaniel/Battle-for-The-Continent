#include <iostream>
#include "Player.h"
#include "Card.h"
// Nu e nevoie sa incluzi Deck.h sau Row.h aici daca le folosesti doar prin Player

int main() {
    std::cout << "*** 1. Loading Player & Cards ***" << std::endl;
    Player playerNo1("Daniel", "Northern Realms");

    Card c1("Knight", 3, 1, false, CardType::MELEE, false);
    Card c2("Archer", 4, 2, true, CardType::RANGED, false);
    Card c3("Ballista", 7, 3, false, CardType::SIEGE, true);
    Card c4("Ram", 2, 4, false, CardType::SIEGE, true);
    Card c5("Geralt", 9, 5, true, CardType::MELEE, true);
    Card c6("Dandelion", 4, 6, false, CardType::MELEE, false);
    Card c7("Yennefer", 7, 7, false, CardType::RANGED, true);

    std::cout << "*** 2. Adding Cards in your Deck ***" << std::endl;
    playerNo1.getDeck().addCard(c1);
    playerNo1.getDeck().addCard(c2);
    playerNo1.getDeck().addCard(c3);
    playerNo1.getDeck().addCard(c4);
    playerNo1.getDeck().addCard(c5);
    playerNo1.getDeck().addCard(c6);
    playerNo1.getDeck().addCard(c7);

    std::cout << playerNo1 << std::endl;

    std::cout << "*** 3. You choose to shuffle your cards ***" << std::endl;
    playerNo1.getDeck().shuffle();
    std::cout << playerNo1 << std::endl;

    std::cout << "*** 4. Testing Deck Copying ***" << std::endl;
    Deck deckCopiat = playerNo1.getDeck();
    Deck deckAtribuit;
    deckAtribuit = playerNo1.getDeck();

    std::cout << "*** 5. You choose to draw some cards ***" << std::endl;
    try {
        Card drawn1 = playerNo1.getDeck().draw();
        std::cout << "You drew " << drawn1.getName() << "\n";
        playerNo1.getMeleeRow().addCard(drawn1);

        Card drawn2 = playerNo1.getDeck().draw();
        std::cout << "You drew " << drawn2.getName() << "\n";
        playerNo1.getSiegeRow().addCard(drawn2);

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "\n*** 6. Final Game State ***\n";
    std::cout << playerNo1;

    return 0;
}