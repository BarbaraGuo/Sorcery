#include "boneGolem.h"
#include "player.h"
#include "board.h"

BoneGolem::BoneGolem(int playerNum): 
    Minion{"Bone Golem", "Gain +1/+1 whenever a minion leaves play.", 
    2, playerNum, 1, 3, 0} {
    setTargeted(false);
}

void BoneGolem::minionLeave(Player &p1, Player &p2) {
    this->power++;
    this->defence++;
}
