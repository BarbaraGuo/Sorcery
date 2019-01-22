#ifndef _POTIONSELLER_H
#define _POTIONSELLER_H
#include "minion.h"

class Player;
class Board;

class PotionSeller : public Minion {
    const int powerBolster = 0;
    const int defenceBolster = 1;

    public:
        explicit PotionSeller(int playerNum);
        virtual void endTrigger(Player &, Player &) override;
};
#endif
