#include <memory>
#include "auraOfPower.h"
#include "player.h"
#include "board.h"

using namespace std;

AuraOfPower::AuraOfPower(int playerNum): Ritual{"Aura of Power", 
    "Whenever a minion enters play under your control, it gains +1/+1", 1, playerNum, 1, 4} {}

bool AuraOfPower::activate(Player &p, Minion &m) {
    int charge = getCharge();
    int aCost = getActivationCost();
    if (charge >= aCost) {
	setCharge(charge - aCost);
    	m.setAttack(m.getAttack() + 1);
	m.setDefence(m.getDefence() + 1);
	return true;
    }
    return false;
}

void AuraOfPower::minionEnter(Player &p, Minion &m) {
    activate(p, m);
}


