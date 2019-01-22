#ifndef _AIRELEMENTAL_H_
#define _AIRELEMENTAL_H_
#include "string.h"
#include "minion.h"

class Player;
class Board;

class AirElemental : public Minion {
    public:
    explicit AirElemental(int playerNum);
};
#endif
