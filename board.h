#ifndef _BOARD_H_
#define _BOARD_H_
#include <string>
#include <vector>
#include <memory>

class Card;
class Minion;
class Ritual;

class Board {
    int playernum; // owner of board
    std::vector<std::shared_ptr<Minion>> minions;
    std::vector<std::shared_ptr<Minion>> graveyard;
    std::shared_ptr<Ritual> ritual;

    public:
    Board(int playernum); //ctor
    void resetMinionAttacks();
    void playMinion(std::shared_ptr<Minion> m); // play a minion
    void playRitual(std::shared_ptr<Ritual> r); // play a ritual
    void killMinion(int i); // remove a minion from play and
                                                // add it to the graveyard
    std::shared_ptr<Minion> resurrect(); // reeturn top minion from the graveyard
                                        // back to the board
    bool isFull(); // checks if board has max number of minions
    void checkDead(); // check for dead minions
    void addCharges(); // add charges to current ritual on board

    void setRitual(std::shared_ptr<Ritual> r);
    std::shared_ptr<Ritual> getRitual();

    std::vector<std::shared_ptr<Minion>> &getGraveyard();
    std::vector<std::shared_ptr<Minion>> &getMinions();

    void printCard(Card &);
};

#endif


