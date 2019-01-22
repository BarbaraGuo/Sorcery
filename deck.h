#ifndef _DECK_H_
#define _DECK_H_
#include <string>
#include <vector>
#include <memory>

class Card;

class Deck {
    int playernum; // owner of deck
    std::vector<std::shared_ptr<Card>> cards;

    public:
    Deck (int playernum, std::vector<std::string> c); // ctor
    std::vector<std::shared_ptr<Card>> getCards();
    void shuffle(); // shuffles deck
    bool isEmpty(); // checks if deck is empty
    std::shared_ptr<Card> draw(); // draws a card and returns the card drawn
};

#endif
