#ifndef _RECHARGE_H
#define _RECHARGE_H
#include "spell.h"
class Player;
class Board;

class Recharge : public Spell{
    const int rechargeAmount = 3;

    public:
        explicit Recharge(int playerNum);
        void attack(Player &) override;
};
#endif
