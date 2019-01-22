#ifndef _FIREELEMENTAL_H
#define _FIREELEMENTAL_H
#include "minion.h"
class Player;
class Board;

class FireElemental : public Minion{
    const int damage = 1;

    public:
        explicit FireElemental(int playerNumber);  
        virtual void opponentMinionEnter(Player &, Player &) override;
};
#endif
