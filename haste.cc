#include <memory>
#include "haste.h"
#include "player.h"
#include "board.h"
#include "minion.h"

Haste::Haste(int playerNum): 
	Enchantment{"Haste", "Enchanted minion gains +1 action each turn",
	1, playerNum} {}

void Haste::enchant(std::shared_ptr<Minion> m) {
	m->setMaxActions(m->getMaxActions() + 1);
	m->setActionsLeft(m->getActionsLeft() + 1);
}


