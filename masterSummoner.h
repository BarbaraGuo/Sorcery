#ifndef _MASTERSUMMONER_H
#define _MASTERSUMMONER_H
#include "minion.h"
class AirElemental;
class Player;
class Board;

class MasterSummoner : public Minion {
    public:
        explicit MasterSummoner(int playerNum);
        virtual void use(Player &) override;       

};
#endif
