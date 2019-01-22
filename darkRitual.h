#ifndef _DARKRITUAL_H_
#define _DARKRITUAL_H_
#include <memory>
#include "ritual.h"

class Player;
class Board;

class DarkRitual : public Ritual {

    public:
    explicit DarkRitual(int playerNum);
    bool activate(Player &p, Minion &m) override;
    
    void startTurn(Player &p, Minion &m) override;

};
#endif
