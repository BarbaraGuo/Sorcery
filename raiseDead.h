#ifndef _RAISEDEAD_H
#define _RAISEDEAD_H
#include "spell.h"
class Player;
class Board;

class RaiseDead : public Spell{
    
    public:
        RaiseDead(int playerNum);
        virtual void attack(Player &) override;
};
#endif
