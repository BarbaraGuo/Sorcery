#include "masterSummoner.h"
#include "player.h"
#include "board.h"
#include "airElemental.h"

MasterSummoner::MasterSummoner(int playerNum): 
	Minion{"Master Summoner", "Summon up to 3 1/1 air elementals", 3, playerNum, 
	2, 3, 2} {
	setTargeted(false);
}

void MasterSummoner::use(Player &p1) {
    if (silences == 0) {
    if(p1.getBoard()->getMinions().size() < 5){
        for(int i = 0; i < 3; i++){
            std::shared_ptr<Minion> c = std::make_shared<AirElemental>(p1.getPlayerNum());
            c->setPlace(p1.getBoard()->getMinions().size());
            if (!p1.resurrect(c)){
                break;
            }
        }
	setActionsLeft(getActionsLeft() - 1);
    } else { 
	    throw "Not enough space on the board.";
    }
    } else {
        throw "Cannot use abilities.";
    }
}     
