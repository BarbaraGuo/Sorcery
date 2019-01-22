#ifndef _MAGICFATIGUE_H_
#define _MAGICFATIGUE_H_
#include <memory>
#include "enchantment.h"

class Minion;
class Board;

class MagicFatigue : public Enchantment, 
	public std::enable_shared_from_this<MagicFatigue>{

    	public:
        MagicFatigue(int playerNum);             
        void enchant(std::shared_ptr<Minion> m) override;
};
#endif
