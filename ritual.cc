#include "ritual.h"
#include "player.h"
#include "board.h"
#include "trigger.h"


Ritual::Ritual(std::string name, std::string description, int cost, int playerNum, int activationCost, int charges):
Card{name, description, "ritual", cost, playerNum}, charges{charges}, activationCost{activationCost} {}


Ritual::~Ritual() {
}

void Ritual::setCharge(int c){
	charges = c;
}

int Ritual::getCharge() {
	return charges;
}

void Ritual::setActivationCost(int a) {
	activationCost = a;
}

int Ritual::getActivationCost() {
	return activationCost;
}


std::string Ritual::getType() {
    return type;
}

void Ritual::startTurn(Player &p, Minion &m) {}
void Ritual::minionEnter(Player &p, Minion &m) {}
void Ritual::oppMinionEnter(Player &p, Minion &m) {}



