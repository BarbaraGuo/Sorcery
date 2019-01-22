#include <memory>
#include "magicFatigue.h"
#include "player.h"
#include "board.h"
#include "minion.h"

MagicFatigue::MagicFatigue(int playerNum): 
	Enchantment{"Magic Fatigue", "Enchanted minion's activated ability costs 2 more", 0, playerNum} {}

void MagicFatigue::enchant(std::shared_ptr<Minion> m) {
	m->setActiveCost(m->getActiveCost() + 2);
}
