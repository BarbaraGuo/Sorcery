#ifndef _ENRAGE_H
#define _ENRAGE_H
#include <memory>
#include "enchantment.h"

class Minion;
class Board;

class Enrage : public Enchantment, 
	public std::enable_shared_from_this<Enrage> {

    	public:
        Enrage(int playerNum);             
        void enchant(std::shared_ptr<Minion> m) override;
};
#endif
