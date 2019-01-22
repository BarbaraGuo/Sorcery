#include "novicePyromancer.h"
#include "player.h"
#include "board.h"

NovicePyromancer::NovicePyromancer(int playerNum): 
	Minion{"Novice Pyromancer", "Deal 1 damage to target minion", 1, 
	playerNum, 0, 1, 1} {
	setTargeted(true);
}

void NovicePyromancer::use(Minion &m, Player &owner) {
    if (silences == 0) {
        m.getUsedBy(*this, owner);
	setActionsLeft(getActionsLeft() - 1);
    } else {
        throw "Cannot use abilities";
    }
}
