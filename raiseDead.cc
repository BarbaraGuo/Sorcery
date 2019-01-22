#include "raiseDead.h"
#include "player.h"
#include "board.h"

RaiseDead::RaiseDead(int playerNum): Spell{"Raise Dead", 
	"Resurrect the top minion in your graveyard and set it's defence to 1", 
	3, playerNum} {
	setTargeted(false);
}

void RaiseDead::attack(Player &p) {
    if(p.getBoard()->getGraveyard().size() > 0) {
        std::shared_ptr<Minion> m = p.getBoard()->resurrect();
        m->setDefence(1);
        p.resurrect(m);
    } else {
        throw "Graveyard is empty";
    }
}
