#ifndef _UNSUMMON_H
#define _UNSUMMON_H
#include "spell.h"

class Player;
class Board;
class Minion;

class Unsummon : public Spell{
    public:
        explicit Unsummon(int playerNum);
        virtual void attack(int, Player &) override;
};
#endif
