#ifndef _STANDSTILL_H
#define _STANDSTILL_H
#include <memory>
#include "ritual.h"

class Standstill : public Ritual {

    public:
        explicit Standstill(int playerNum);
        bool activate(Player &p, Minion &m) override;


        void minionEnter(Player &p, Minion &m) override;
        void oppMinionEnter(Player &p, Minion &m) override;


};
#endif
