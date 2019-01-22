#ifndef _AURAOFPOWER_H_
#define _AURAOFPOWER_H_
#include <memory>
#include "ritual.h"

class Player;
class Board;

class AuraOfPower : public Ritual {
    public:
    explicit AuraOfPower(int playerNum);
    bool activate(Player &p, Minion &m) override;

    void minionEnter(Player &p, Minion &m) override;
};
#endif
