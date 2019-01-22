#ifndef _SPELL_H
#define _SPELL_H
#include "card.h"
class Player;
class Minion;
class Board;

class Spell : public Card{
    const std::string type = "spell"; 
    public:
        Spell(std::string name, std::string description, int cost, int playerNum);
        std::string getType() override;
        virtual ~Spell() = 0;
        virtual void attack(Player &) override;
        virtual void attack(Minion &, Player &) override;
        virtual void attack(int, Player &) override;
};
#endif

