#ifndef _GIANTSTRENGTH_H
#define _GIANTSTRENGTH_H
#include <memory>
#include "enchantment.h"

class Minion;
class Board;

class GiantStrength : public Enchantment, 
	public std::enable_shared_from_this<GiantStrength> {
   	public:
        GiantStrength(int playerNum);             
        void enchant(std::shared_ptr<Minion> m) override;
};

#endif
