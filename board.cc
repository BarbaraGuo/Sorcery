#include "board.h"
#include "minion.h"
#include "card.h"
#include <string>
#include <iostream>


Board::Board(int playernum) : playernum{playernum} {}

void Board::resetMinionAttacks(){
    for (unsigned int i = 0; i < minions.size(); i++){
        minions.at(i)->resetAttack();
    }
}

void Board::playMinion(std::shared_ptr<Minion> minion) {
    if (minions.size() == 5) {
        throw "Your board is full.";
    } else {
        minion->setPlace(minions.size());
	minions.emplace_back(minion);
    }
}

void Board::playRitual(std::shared_ptr<Ritual> r) {
    ritual.reset();
    ritual = r;
}

// remove a minion from play and add it to the graveyard
void Board::killMinion(int i) {
    minions.at(i - 1)->setDefence(0);
    graveyard.emplace_back(minions.at(i - 1));
    minions.erase(minions.begin() + (i - 1));
}

// return top minion from the graveyard back to the hand
std::shared_ptr<Minion> Board::resurrect(){
    std::shared_ptr<Minion> m = graveyard.back();
    graveyard.pop_back();
    return m;
}

void Board::checkDead(){ // check for dead minions
    std::vector<std::shared_ptr<Minion>>::iterator ptr; 
     
    for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
        if((*ptr)->getDefence() == 0){
            graveyard.emplace_back(*ptr);
            minions.erase(ptr);
        }
    }   
}

void Board::setRitual(std::shared_ptr<Ritual> r){
    ritual = r;
}

std::shared_ptr<Ritual> Board::getRitual(){
    return ritual;
}
	
std::vector<std::shared_ptr<Minion>> & Board::getGraveyard(){
    return graveyard;
}

std::vector<std::shared_ptr<Minion>> & Board::getMinions(){
    return minions;
}
