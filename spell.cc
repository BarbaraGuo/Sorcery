#include "spell.h"
#include "player.h"
#include "board.h"
#include "minion.h"

Spell::Spell(std::string name, std::string description, int cost, int playerNum): 
Card{name, description, "spell", cost, playerNum} {}

Spell::~Spell(){

}

std::string Spell::getType() {
    return type;
}

void Spell::attack(Player &p){

}

void Spell::attack(Minion &m, Player &){

}

void Spell::attack(int, Player &){

}





