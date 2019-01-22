#include <memory>
#include "giantStrength.h"
#include "player.h"
#include "board.h"
#include "minion.h"

GiantStrength::GiantStrength(int playerNum): 
	Enchantment{"Giant Strength", "", 1, playerNum} {}

void GiantStrength::enchant(std::shared_ptr<Minion> m) {
    m->setAttack(m->getAttack() + 2);
	m->setDefence(m->getDefence() + 2);
}
