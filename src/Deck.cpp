#include "../headers/Deck.h"
#include "../headers/UnitCard.h"
#include <algorithm>
#include <random>

Deck::Deck(const Deck& other) {
    for (const auto& cardPtr : other.cards) {
        cards.push_back(std::unique_ptr<Card>(cardPtr->clone()));
    }
}

void swap(Deck& first, Deck& second) noexcept {
    using std::swap;
    swap(first.cards, second.cards);
}

Deck& Deck::operator=(Deck other) {
    swap(*this, other);
    return *this;
}

void Deck::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

std::unique_ptr<Card> Deck::draw() {
    if (cards.empty()) {
        throw EmptyDeckException();
    }
    std::unique_ptr<Card> drawnCard = std::move(cards.back());
    cards.pop_back();
    return drawnCard;
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

void Deck::sortByPower() {
    std::sort(cards.begin(), cards.end(), [](const std::unique_ptr<Card>& a, const std::unique_ptr<Card>& b) {
        auto* unitA = dynamic_cast<UnitCard*>(a.get());
        auto* unitB = dynamic_cast<UnitCard*>(b.get());

        int powerA = unitA ? unitA->getCurrentPower() : 0;
        int powerB = unitB ? unitB->getCurrentPower() : 0;

        return powerA > powerB;
    });
}

std::ostream& operator<<(std::ostream& os, const Deck& deck) {
    if (deck.cards.empty()) {
        os << "  [Empty Deck]\n";
        return os;
    }
    for (const auto& card : deck.cards) {
        card->printDetails(os);
        os << "\n";
    }
    return os;
}