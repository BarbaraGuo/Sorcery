#include "card.h"
#include "player.h"
#include "minion.h"
#include "board.h"

Card::Card(const std::string name, const std::string description, 
    const std::string type, int cost, int playernum): type{type}, name{name}, 
    description{description}, cost{cost}, playerNum{playernum} {}

Card::~Card(){

}

std::string Card::getType(){
    return type;
}

bool Card::getTargeted(){
    return targeted;
}

void Card::setTargeted(bool b){
    targeted = b;
}

int Card::getCost(){
    return cost;
}

void Card::attack(Player &) {}

void Card::attack(Minion &, Player &) {}

void Card::attack(int, Player&) {}

void Card::getAttackedBy(Minion &, Player &) {}

void Card::use(Player &, Player &) {}

void Card::use(Player &, int) {}

void Card::startTrigger(Player &, Player &) {}

void Card::endTrigger(Player &, Player &) {}

void Card::opponentMinionEnter(Player &, Player &) {}

void Card::minionEnter(Player &, Player &) {}

void Card::minionLeave(Player &, Player &) {}

std::string Card::getName() {
    return name;
}

std::string Card::getDescription() {
    return description;
}
