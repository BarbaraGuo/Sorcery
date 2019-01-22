#ifndef _DISENCHANT_H_
#define _DISENCHANT_H_
#include "spell.h"
class Minion;
class Player;
class Board;

class Disenchant : public Spell{

    public:
    Disenchant(int playerNum);
    void attack(int i, Player &p);
};
#endif
