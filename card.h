#ifndef _CARD_H_
#define _CARD_H_
#include <string>
#include<iostream>
#include <memory>
class Player;
class Minion;
class Board;
class Spell;

class Card {
    std::string type;
    bool targeted;
    std::string name;
    std::string description;
    int cost;
    int playerNum;

    public:
    Card(const std::string name, const std::string description, const std::string type, int cost, int playernum);
    virtual ~Card() = 0;
    virtual std::string getType() = 0;
    int getCost();
    std::string getName();
    std::string getDescription();
    bool getTargeted();
    void setTargeted(bool b);
    virtual void attack(Player &);
    virtual void attack(Minion &, Player &);
    virtual void attack(int, Player &);
    virtual void getAttackedBy(Minion &, Player &);
    virtual void use(Player &, Player &);
    virtual void use(Player &, int);
    virtual void startTrigger(Player &, Player &);
    virtual void endTrigger(Player &, Player &);
    virtual void opponentMinionEnter(Player &, Player &);
    virtual void minionEnter(Player &, Player &);
    virtual void minionLeave(Player &, Player &);

};

#endif
