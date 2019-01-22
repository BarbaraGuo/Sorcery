#include <memory>
#include "enrage.h"
#include "player.h"
#include "board.h"
#include "minion.h"

Enrage::Enrage(int playerNum): Enchantment{"Enrage",
	 "", 2, playerNum} {}

void Enrage::enchant(std::shared_ptr<Minion> m) {
    m->setAttack(m->getAttack() * 2);
	m->setDefence(m->getDefence() * 2);
}
