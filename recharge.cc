#include "recharge.h"
#include "player.h"
#include "board.h"
#include "ritual.h"

Recharge::Recharge(int playerNum): Spell{"Recharge", 
	"Your ritual gains 3 charges", 1, playerNum} {
	setTargeted(false);
}

void Recharge::attack(Player &p) {
    if(p.getBoard()->getRitual()){
        int charge = p.getBoard()->getRitual()->getCharge();
        p.getBoard()->getRitual()->setCharge(charge + rechargeAmount);
    } else {
        throw "You do not have a ritual";
    }
}



