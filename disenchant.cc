#include "disenchant.h"
#include "minion.h"
#include "player.h"
#include "board.h"

Disenchant::Disenchant(int playerNum): Spell{"Disenchant", 
    "Destroy the top enchantment on target minion", 1, playerNum} {
    setTargeted(true);
}
    
void Disenchant::attack(int i, Player &p) {
    try {
        std::shared_ptr<Minion> m= p.getBoard()->getMinions().at(i - 1);
        m->removeTopEnchant(p);
    } catch (std::out_of_range &e){
        std::cerr << i << std::endl;
    }
}
