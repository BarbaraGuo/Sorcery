#ifndef _BONEGOLEM_H_
#define _BONEGOLEM_H_
#include "minion.h"

class Player;
class Board;

class BoneGolem : public Minion {

    public:
    explicit BoneGolem(int playerNum);
    virtual void minionLeave(Player &, Player &) override;

};
#endif
