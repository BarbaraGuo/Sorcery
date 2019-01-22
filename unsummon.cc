#include "unsummon.h"
#include "player.h"
#include "board.h"
#include "minion.h"
#include <stdexcept>


Unsummon::Unsummon(int playerNum): Spell{"Unsummon", 
	"Return target minion to its owner's hand", 1, playerNum} {
	setTargeted(true);
}

void Unsummon::attack(int i, Player &p) {
    try{
        std::shared_ptr<Minion> m= p.getBoard()->getMinions().at(i - 1);
        p.deathrattle();
        m->clearEnchantments(p);
        p.returnCard(*m);
    } catch (std::out_of_range &e){
        throw "Cannot unsummon minion that does not exist";
    }
}
