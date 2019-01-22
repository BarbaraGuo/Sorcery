#ifndef _APPRENTICESUMMONER_H
#define _APPRENTICESUMMONER_H
#include "minion.h"

class Player;
class Board;

class ApprenticeSummoner : public Minion {
    public:
    explicit ApprenticeSummoner(int playerNum);
    virtual void use(Player &) override;
};

#endif
