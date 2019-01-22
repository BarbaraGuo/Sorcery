#ifndef _EARTHELEMENTAL_H_
#define _EARTHELEMENTAL_H_
#include "minion.h"

class Player;
class Board;

class EarthElemental : public Minion {
    public:
    explicit EarthElemental(int playerNum);
};
#endif
