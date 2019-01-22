#ifndef _RITUAL_H
#define _RITUAL_H
#include <string>
#include <memory>
#include <vector>
#include "card.h"
class Player;
class Board;
class Trigger;


class Ritual : public Card {
	const std::string type = "ritual";
	
    	int charges;
    	int activationCost;

    	public:
        Ritual(std::string name, std::string description, int cost, int playerNum, 
		int activationCost, int charges);
	virtual ~Ritual() = 0;
	// getter and setter
        void setCharge(int c);
	int getCharge();
	void setActivationCost(int a);
	int getActivationCost();
        std::string getType() override;
        virtual void startTurn(Player &p, Minion &m);
        virtual void minionEnter(Player &p, Minion &m);
        virtual void oppMinionEnter(Player &p, Minion &m);
        virtual bool activate(Player &p, Minion &m) = 0;

};
#endif
