#include "enchantment.h"
#include "minion.h"
#include "board.h"

Enchantment::Enchantment(std::string name, std::string description, 
    int cost, int playerNum): Card{name, description, "enchantment", 
    cost, playerNum} {}

Enchantment::~Enchantment(){

}

std::string Enchantment::getType() {
    return type;
}
