#include "banish.h"
#include "player.h"
#include "minion.h"
#include "board.h"

Banish::Banish(int playerNum): Spell{"Banish", "Destroy target minion or ritual", 
    2, playerNum} {
    setTargeted(true);
}

void Banish::attack(int i, Player &owner){
    owner.remove(i);
}
