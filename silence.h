#ifndef _SILENCE_H
#define _SILENCE_H
#include <memory>
#include "enchantment.h"

class Minion;
class Board;

class Silence : public Enchantment, 
	public std::enable_shared_from_this<Silence> {
    	public:
        Silence(int playerNum);             
        void enchant(std::shared_ptr<Minion> m) override;
};
#endif
