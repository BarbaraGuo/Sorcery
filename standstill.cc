#include "standstill.h"
#include "player.h"
#include "board.h"

using namespace std;

Standstill::Standstill(int playerNum): Ritual{"Standstill", "Whenever a minion enters play, destroy it", 3, playerNum, 2, 4} {}

bool Standstill::activate(Player &p, Minion &m) {
	int charge = getCharge();
	int aCost = getActivationCost();
	if (charge >= aCost) {
		setCharge(charge - aCost);
        	m.alterStats(0, -m.getDefence(), p); 
		return true;
	}
	return true;
}


void Standstill::minionEnter(Player &p, Minion &m) {
    activate(p, m);
}

void Standstill::oppMinionEnter(Player &p, Minion &m) {
    activate(p, m);
}




