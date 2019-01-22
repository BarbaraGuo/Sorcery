#include "potionSeller.h"
#include "player.h"
#include "board.h"

PotionSeller::PotionSeller(int playerNum): 
	Minion{"Potion Seller", "At the end of your turn, all your minions gain +0/+1.", 
	2, playerNum, 1, 3, 0} {
	setTargeted(false);
}

void PotionSeller::endTrigger(Player &p1, Player &p2) {
    // all your minions gain +0/+1
    std::vector<std::shared_ptr<Minion>> minions = p1.getBoard()->getMinions();
    std::vector<std::shared_ptr<Minion>>::iterator ptr;

    for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
        (*ptr)->alterStats(powerBolster, defenceBolster, p1);
    }
}
