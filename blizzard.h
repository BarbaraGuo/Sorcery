#ifndef _BLIZZARD_H_
#define _BLIZZARD_H_
#include "spell.h"
class Player;
class Board;

class Blizzard : public Spell{
    const int damage = -2;

    public:
    explicit Blizzard(int playerNum);
    virtual void attack(Player &) override;

};
#endif

