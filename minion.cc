#include "minion.h"
#include "player.h"
#include "spell.h"
#include "enchantment.h"
#include "novicePyromancer.h"
#include "apprenticeSummoner.h"
#include "masterSummoner.h"

Minion::Minion(std::string name, std::string description, int cost, int playerNum, int attack, int defence, int activecost):
Card{name, description, "minion", cost, playerNum}, placeOnBoard{-1}, power{attack}, defence{defence}, activeCost{activecost} 
{actionsLeft = 0;}

void Minion::setAttack(int a) {
        power = a;
}

int Minion::getAttack() {
        return power;
}

void Minion::setDefence(int d) {
        defence = d;
}

int Minion::getDefence() {
	return defence;
}

std::string Minion::getType() {
        return type;
}

int Minion::getActiveCost() {
        return activeCost;
}

void Minion::setActiveCost(int a) {
        activeCost = a;
}

std::vector<std::shared_ptr<Enchantment>> &Minion::getEnchants() {
	return enchantments;
}

void Minion::setEnchants(std::vector<std::shared_ptr<Enchantment>> e) {
	enchantments = e;
}

void Minion::addSilence() {
	++silences;
}


void Minion::setMaxActions(int m) {
	maxActions = m;
}

int Minion::getMaxActions() {
	return maxActions;
}

void Minion::setActionsLeft(int l) {
	actionsLeft = l;
}

int Minion::getActionsLeft() {
	return actionsLeft;
}

void Minion::attack(Player &p){
    if(actionsLeft > 0){
        p.takeDamage(power);
        --actionsLeft;
    }
}

void Minion::attack(Minion &m, Player &p){
    if(actionsLeft > 0){
        m.alterStats(0, (-1 * power), p);
        --actionsLeft;
    }
}

void Minion::attack(int, Player &){

}

void Minion::getAttackedBy(Minion &m, Player &p){
    if(m.getActionsLeft()>0){
        m.attack(*this, p);
        attack(m, *(p.getOpponent()));
	setActionsLeft(getActionsLeft() + 1);
    }
}

void Minion::use(Player &owner){
    
}

void Minion::use(Minion &m, Player &owner){ //minion and player themselves
    
}

void Minion::getUsedBy(NovicePyromancer &np, Player &p){
    	alterStats(0, -1, p);
	--actionsLeft;    
}

void Minion::getUsedBy(ApprenticeSummoner &, Player &p){

}

void Minion::getUsedBy(MasterSummoner &, Player &p){

}

void Minion::startTrigger(Player &p1, Player &p2){

}

void Minion::endTrigger(Player &p1, Player &p2){

}

void Minion::opponentMinionEnter(Player &, Player &){

}

void Minion::minionEnter(Player &p1, Player &p2){

}
void Minion::minionLeave(Player &p1, Player &p2){

}

void Minion::enchant(){

}

void Minion::removeTopEnchant(Player &p) {
    if(enchantments.size() > 0){
        if (enchantments.back()->getName() == "Silence") {
            --silences;
        } else if (enchantments.back()->getName() == "Haste") {
            --maxActions;
        } else if (enchantments.back()->getName() == "Magic Fatigue") {
            activeCost -= 2;
        } else if (enchantments.back()->getName() == "Giant Strength") {
            if (defence > 0) {
                alterStats(-2, -2, p);
            }
        } else if (enchantments.back()->getName() == "Enrage") {
            if (defence > 0) {
                alterStats(-(power/2), -(defence/2), p);
            }
        }
        enchantments.erase(enchantments.begin() + enchantments.size() - 1);
    }
}

void Minion::clearEnchantments(Player &p) {
    while (enchantments.size() > 0) {
        removeTopEnchant(p);
    }
}


void Minion::alterStats(int a, int d, Player &p) {
    int health = defence + d;
    if(health <= 0) {
        defence = 0;
        p.deathrattle();
        clearEnchantments(p);
        p.getBoard()->checkDead();
    } else {
        defence = health;
        power += a;
    }
}


void Minion::setPlace(int i) {
    placeOnBoard = i;
}

int Minion::getPlace() {
    return placeOnBoard;
}

void Minion::resetAttack(){
    actionsLeft = maxActions;
}

Minion::~Minion() {
  //  clearEnchantments();
}



