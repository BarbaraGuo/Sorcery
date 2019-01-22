#include <iterator>
#include "blizzard.h"
#include "player.h"

Blizzard::Blizzard(int playerNum): Spell{"Blizzard", 
    "Deal 2 damage to all minions", 1, playerNum} {
    setTargeted(false);
}

void Blizzard::attack(Player &p){
    // opponent's board
    std::vector<std::shared_ptr<Minion>> minions = p.getOpponent()->getBoard()->getMinions();
    if(minions.size() > 0){
        std::vector<std::shared_ptr<Minion>>::iterator ptr;  
        for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
            (*ptr)->alterStats(0, damage, *(p.getOpponent()));
        } 
    }  
    // active player's board
    std::vector<std::shared_ptr<Minion>> minions2 = p.getBoard()->getMinions();
    if(minions2.size() > 0){
        std::vector<std::shared_ptr<Minion>>::iterator ptr; 
        for (ptr = minions2.begin(); ptr < minions2.end(); ptr++) {
            (*ptr)->alterStats(0, damage, p);
        } 
    }  
}



