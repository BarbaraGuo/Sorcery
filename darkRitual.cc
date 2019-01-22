#include "darkRitual.h"
#include "player.h"
#include "board.h"

using namespace std;

DarkRitual::DarkRitual(int playerNum): Ritual{"Dark Ritual", 
    "At the start of your turn, gain 1 magic", 0, playerNum, 1, 5} {}

bool DarkRitual::activate(Player &p, Minion &m) {
    int charge = getCharge();
    int aCost = getActivationCost();
    if (charge >= aCost) {
	setCharge(charge - aCost);
	p.oneMagic();
	return true;
    }
	return false;
}

void DarkRitual::startTurn(Player &p, Minion &m) {
    activate(p, m);
}
