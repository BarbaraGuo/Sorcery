#ifndef _NOVICEPYROMANCER_H
#define _NOVICEPYROMANCER_H
#include "minion.h"

class Player;
class Board;

class NovicePyromancer : public Minion {

    public:
        explicit NovicePyromancer(int playerNum);
        virtual void use(Minion &, Player &);
};
#endif
