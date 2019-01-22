#ifndef _HASTE_H
#define _HASTE_H
#include <memory>
#include "enchantment.h"

class Minion;
class Board;

class Haste : public Enchantment, 
	public std::enable_shared_from_this<Haste> {

    	public:
        Haste(int playerNum);             
        void enchant(std::shared_ptr<Minion> m) override;
};
#endif
