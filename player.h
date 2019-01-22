#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <vector>
#include <memory>
#include "board.h"
#include "deck.h"
#include "minion.h"


class Player {
    std::string name;
        int playernum;
        int life;
        int magic;
        bool testing;

    std::unique_ptr<Deck> deck;
    std::shared_ptr<Board> board = std::make_shared<Board>(playernum);
    std::vector<std::shared_ptr<Card>> hand;
    std::vector<std::shared_ptr<Card>> graveyard;
    std::shared_ptr<Minion> lastMinion;

    Player *opponent;

        public:
        Player(std::string name, int n,bool testing, std::vector<std::string> deckName); //ctor
        ~Player(); //dtor

        // getters and setters
        std::string getName();
        int getPlayerNum();
        int getMagic();
        void setMagic(int m);
        int getLife();
        Player *getOpponent();
        void setOpponent(Player *opp);
        void setLife(int l);
    std::shared_ptr<Minion> getLastMinionPlayed();
    std::shared_ptr<Board> getBoard();
        void setBoard(std::shared_ptr<Board> b);
    std::vector<std::shared_ptr<Card>> getHand();
        void setHand(std::vector<std::shared_ptr<Card>>);
    std::vector<std::shared_ptr<Card>> getGraveyard();
        void setGraveyard(std::vector<std::unique_ptr<Card>>);
        void shuffleDeck();

        bool draw(); // draws card
        void discard(unsigned int i); // discards ith card in hand
        void returnCard(Minion &m); // Returns a card back to the players hand
        bool resurrect(std::shared_ptr<Minion> c); // Returns a card back to the players hand from graveyard
        void oneMagic(); // gains a magic

        void attack(unsigned int i); // orders ith minion to attack opposing player
        void attack(unsigned int i, unsigned int j); // orders active player's ith minion
                                // to attack inactive player's jth minion
        void takeDamage(int d); // take specified amount of damage

        void play(unsigned int i); // play ith card in hand
        void play(unsigned int i, int p, unsigned int t); // play ith card in hand on minion
                                        // at index t of player p
        void use(unsigned int i); // use ith minion's activated ability
        void use(unsigned int i, int p, unsigned int t); // use ith minion's activated ability
                                        // on minion at index t of player p

        void remove(unsigned int i); // Removes the ith card from play

        void startTurn(); // trigger beginning of turn triggers
        void endTurn(); // trigger end of turn triggers
        void opponentBattlecry(); // trigger minion play triggers
        void battlecry(); // trigger minion play triggers
        void deathrattle(); // trigger minion death triggers
};

#endif
