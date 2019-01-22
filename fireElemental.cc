#include "fireElemental.h"
#include "player.h"
#include "board.h"

FireElemental::FireElemental(int playerNum): 
	Minion{"Fire Elemental", 
	"Whenever an opponent's minion enters play, deal 1 damange to it", 2, 
	playerNum, 2, 2, 0} {
	setTargeted(false);
}

void FireElemental::opponentMinionEnter(Player &p1, Player &p2) {
    p2.getLastMinionPlayed()->alterStats(0, damage, p2);
}
