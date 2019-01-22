#ifndef _TEXTVIEW_H
#define _TEXTVIEW_H
#include "view.h"
#include <vector>
#include <memory>
#include <string>
#include "ascii_graphics.h"

class Player;
class Card;
class Minion;
class Spell;
class Enchantment;
class Ritual;

class TextView : public View {
    public: 
    TextView(std::vector<std::shared_ptr<Player>> *players);
    void onHelp() override;
    void onEnd(std::string p) override;
    void onQuit() override;
    void onDescribe(int i, int p) override;
    void onHand(int p) override;
    void onBoard() override;
    void endGame(int i) override;
    void displayCard(Card *c);
    void displayPlayer(Player &);
    card_template_t cardDisplay(Card *c);
    card_template_t minionDisplay(Minion &c);
    card_template_t spellDisplay(Spell &c);
    card_template_t enchantDisplay(Enchantment &c);
    card_template_t ritualDisplay(Ritual &c);
    card_template_t playerDisplay(Player &c);
    std::vector<std::vector<std::string>> outsideBoard(Player &p);
    std::vector<std::vector<std::string>> insideBoard(Player &p);
    void displayError(std::string e) override;
};

#endif
