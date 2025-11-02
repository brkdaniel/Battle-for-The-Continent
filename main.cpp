#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

enum class CardType{MELEE, RANGED, SIEGE, SPELL};
enum class RowType{MELEE, RANGED, SIEGE};
class CardStats {
private:
    int current_power;
    bool is_weather_immune;
public:
    //constructor pentru stats pe carti
    CardStats(int power, bool immune) //power(p) -> power = p
        : current_power(power), is_weather_immune(immune) {

    }
    int getCurrentPower() const{return current_power;}
    bool isImmune() const{return is_weather_immune;}
    friend std::ostream& operator<<(std::ostream& os, const CardStats& stats);
};

class Card {
private:
    std::string name;
    int power;
    int card_ID;
    bool is_gold;
    CardStats stats;
    CardType type;

public:
    Card(std::string n, int p, int id, bool gold, CardType t, bool immune) :
    name(n), power(p), card_ID(id), is_gold(gold), stats(p, immune), type(t)
    {}
    friend std::ostream& operator<<(std::ostream& os, const Card& card);

    std::string getName() const{return name;}
    int getBasePower() const{return power;}
    int getID() const{return card_ID;}
    bool isGold() const{return is_gold;}

    int getCurrentPower() const{return stats.getCurrentPower();}
    const CardStats& getStats() const{return stats;}
    CardType getType() const{return type;}

};

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() = default;
    ~Deck() {}
    Deck(const Deck &other) {
        this->cards = other.cards;
        std::cout << "Deck copy constructor" << std::endl;
    }

    void addCard(const Card& card) {
        cards.push_back(card);
    }

    Deck& operator=(const Deck& other) {
        std::cout << "Deck copy assignment" << std::endl;
        if (this != &other) {
            cards = other.cards;
        }
        return *this;
    }

    void shuffle() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
        std::cout << "You shuffled your cards\n";
    }

    Card draw() {
        if (cards.empty()) {
            throw std::runtime_error("You have no cards left to draw.");
        }

        Card drawn_card = cards.back();
        cards.pop_back();
        return drawn_card;
    }

    friend std::ostream& operator<<(std::ostream& os, const Deck& d);

};

class Row {
    private:
    RowType type;
    std::vector<Card> cards;
    bool has_horn; //bonus x2
    int calculateBasePower() const {
        int total = 0;
        for (const auto& card : cards) {
            total += card.getCurrentPower();
        }
        return total;
    }
    bool canAddCard(const Card& card) const {
        CardType card_type = card.getType();
        if (card_type == CardType::SPELL) {
            return false; //inca nu am implementat functionalitatea SPELL
        }
        switch (card_type) {
            case CardType::MELEE:
                return (type == RowType::MELEE);
            case CardType::RANGED:
                return (type == RowType::RANGED);
            case CardType::SIEGE:
                return (type == RowType::SIEGE);
        }
        return false;
    }

public:
    Row(RowType t) : type(t), has_horn(false) {}
    void addCard(const Card& card) {
        if (canAddCard(card)) {
            cards.push_back(card);
        } else {
            std::cout << "ERROR: Card: " << card.getName()
            << " is not the appropriate type" << std::endl;
        }
    }
    int calculatePower() const{
        int basePower = calculateBasePower();

        return has_horn ? (2 * basePower) : basePower;

    }

    friend std::ostream& operator<<(std::ostream& os, const Row& r);

};

class Player {
private:
    std::string name;
    std::string faction_name;
    Deck deck;
    Row melee_row;
    Row ranged_row;
    Row siege_row;

public:
    Player(std::string n, std::string faction) :
        name(n), faction_name(faction),
        melee_row(RowType::MELEE), ranged_row(RowType::RANGED), siege_row(RowType::SIEGE)
    {}
    Deck& getDeck() {
        return deck;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& p);

    Row& getMeleeRow()  {return melee_row;}; //ma adresez direct mesei de joc
    Row& getRangedRow()  {return ranged_row;}; ///apelez sa am control
    Row& getSiegeRow()  {return siege_row;};
};


std::ostream& operator<<(std::ostream& os, const CardStats& stats) {
    os << " POWER: " << stats.getCurrentPower();
    if (stats.isImmune()) {
        os << " IMMUNE";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << "[" << card.getName() << " | ";
    if (card.isGold()) {
        os << " *(GOLD)* ";
    }
    os << card.getStats() << "]" << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Deck &d) {
    os << "DECK SIZE: " << d.cards.size() << std::endl;
    for (const auto& card : d.cards) {
        os << "    " << card << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Row& row) {
    os << "Your ";
    switch (row.type) {
        case RowType::MELEE: os << "MELEE"; break;
        case RowType::RANGED: os << "RANGED"; break;
        case RowType::SIEGE: os << "SIEGE"; break;

    }
    os <<" ROW HAS: "<< std::endl;
    for (const auto& card : row.cards) {
        os <<"  " << card <<"  "<< std::endl;
    }
    os << "TOTAL POWER: " << row.calculatePower() << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    os << "*** PLAYER " << p.name << " HAS A " << p.faction_name << " DECK" << std::endl;
    os << p.deck << std::endl;
    os << p.melee_row << std::endl;
    os << p.ranged_row << std::endl;
    os << p.siege_row << std::endl;

    return os;
}

int main() {
    std::cout << "*** 1. Loading Player & Cards ***"<< std::endl;
    Player playerNo1("Daniel", "Northern Realms");
    Card c1("Knight", 3, 1, false, CardType::MELEE, false);
    Card c2("Archer", 4, 2, true, CardType::RANGED, false);
    Card c3("Ballista", 7, 3, false, CardType::SIEGE, true);
    Card c4("Ram", 2, 4, false, CardType::SIEGE, true);
    Card c5("Geralt", 9, 5, true, CardType::MELEE, true);
    Card c6("Dandelion", 4, 6, false, CardType::MELEE, false);
    Card c7("Yennefer", 7, 7, false, CardType::RANGED, true);

    std::cout << "*** 2. Adding Cards in your Deck ***"<< std::endl;
    playerNo1.getDeck().addCard(c1);
    playerNo1.getDeck().addCard(c2);
    playerNo1.getDeck().addCard(c3);
    playerNo1.getDeck().addCard(c4);
    playerNo1.getDeck().addCard(c5);
    playerNo1.getDeck().addCard(c6);
    playerNo1.getDeck().addCard(c7);

    std::cout << playerNo1 << std::endl;

    std::cout << "*** 3. You choose to shuffle your cards ***"<< std::endl;

    playerNo1.getDeck().shuffle();  //testez shuffle
    std::cout << playerNo1 << std::endl;

    std::cout << "*** 4. Testing Deck Copying ***" << std::endl;
    Deck deckCopiat = playerNo1.getDeck(); // testez constructor de copiere
    Deck deckAtribuit;
    deckAtribuit = playerNo1.getDeck();

    std::cout << "*** 5. You choose to draw some cards ***" << std::endl;
    try {
        Card drawn1 = playerNo1.getDeck().draw(); // testez draw()
        std::cout << "You drew " << drawn1.getName() << "\n";
        playerNo1.getMeleeRow().addCard(drawn1); //
// verifica ultimile 2 carti din deck si incearca sa le bage pe randuri daca se potrivesc, asta ca sa testez corectitudinea functiilor
        Card drawn2 = playerNo1.getDeck().draw();
        std::cout << "You drew " << drawn2.getName() << "\n";
        playerNo1.getSiegeRow().addCard(drawn2);
// sa nu uit sa testez si cand am cards.empty
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "\n*** 6. Final Game State ***\n";
    std::cout << playerNo1;

    return 0;
}
