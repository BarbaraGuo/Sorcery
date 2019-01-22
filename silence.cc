#include <memory>
#include "silence.h"
#include "player.h"
#include "board.h"
#include "minion.h"

Silence::Silence(int playerNum): 
	Enchantment{"Silence", "Enchanted minion cannot use abilities", 1, 
	playerNum} {}

void Silence::enchant(std::shared_ptr<Minion> m) {
    	m->addSilence();
}


