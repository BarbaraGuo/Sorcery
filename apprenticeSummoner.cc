#include "apprenticeSummoner.h"
#include "player.h"
#include "board.h"
#include "airElemental.h"

ApprenticeSummoner::ApprenticeSummoner(int playerNum): 
    Minion{"Apprentice Summoner", "Summon a 1/1 air elemental", 1, playerNum, 
    1, 1, 1} {
    setTargeted(false);
}

void ApprenticeSummoner::use(Player &p1) {
    if (silences == 0) {
    if(p1.getBoard()->getMinions().size() < 5){
        std::shared_ptr<Minion> c = std::make_shared<AirElemental>(p1.getPlayerNum());
        p1.resurrect(c);
	    setActionsLeft(getActionsLeft() - 1);
    } else { 
	    throw "Not enough space on the board.";
    }
    } else {
        throw "Cannot use abilities";
    }
}

