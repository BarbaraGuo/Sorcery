#ifndef _BANISH_H_
#define _BANISH_H_
#include "spell.h"
class Player;
class Minion;
class Board;

class Banish : public Spell{
    public:
    explicit Banish(int playerNum);
    virtual void attack(int, Player &) override;
};
#endif
