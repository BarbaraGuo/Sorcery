#ifndef _MINION_H
#define _MINION_H
#include "card.h"
#include <vector>
class Enchantment;
class NovicePyromancer;
class ApprenticeSummoner;
class MasterSummoner;

class Minion : public Card{
    const std::string type = "minion";
    int placeOnBoard;
   // bool canAttack;

    protected:
        int power;
        int defence;
        int activeCost;
        int cost;
        std::vector<std::shared_ptr<Enchantment>> enchantments;
        int silences = 0;
        int maxActions = 1;
        int actionsLeft;
    public:

        Minion(std::string name, std::string description, int cost, int playerNum, int attack, int defence, int activecost);
        //getters and setters
        void setAttack(int a);
        int getAttack();
        void setDefence(int d);
        int getDefence();
        std::string getType() override;
        int getActiveCost();

 	    void setActiveCost(int a);
        std::vector<std::shared_ptr<Enchantment>> &getEnchants();
	    void setEnchants(std::vector<std::shared_ptr<Enchantment>> e);
	    void addSilence();
	    void setMaxActions(int m);
	    int getMaxActions();
	    void setActionsLeft(int l);
	    int getActionsLeft();

      //  bool getCanAttack();
        
        virtual void attack(Player &) override;
        virtual void attack(Minion &, Player &) override;
        virtual void attack(int, Player &) override;
        virtual void getAttackedBy(Minion &, Player &) override;
        //virtual void getAttackedBy(Spell &) override;
        virtual void use(Minion &, Player &);
        virtual void use(Player &);
        virtual void getUsedBy(NovicePyromancer &, Player &);
        virtual void getUsedBy(ApprenticeSummoner &, Player &);
        virtual void getUsedBy(MasterSummoner &, Player &);
        virtual void startTrigger(Player &, Player &) override;
        virtual void endTrigger(Player &, Player &) override;
        virtual void opponentMinionEnter(Player &, Player &) override;
        virtual void minionEnter(Player &, Player &) override;
        virtual void minionLeave(Player &, Player &) override;
        void enchant();
        void removeTopEnchant(Player &p);
        void clearEnchantments(Player &p);
        void alterStats(int, int, Player &p);
        void setPlace(int i);
        int getPlace();
        void resetAttack();
        virtual ~Minion() = 0;
};
#endif




