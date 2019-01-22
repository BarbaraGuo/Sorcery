#ifndef _ENCHANTMENT_H_
#define _ENCHANTMENT_H_
#include <memory>
#include "card.h"
class Minion;
class Board;

class Enchantment : public Card{
    const std::string type = "enchantment";
    int cost;

    public:
    Enchantment(std::string name, std::string description, int cost, int playerNum);             
    virtual ~Enchantment() = 0;
    virtual void enchant(std::shared_ptr<Minion> m) = 0;
    std::string getType() override;
};
#endif
