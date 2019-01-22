#ifndef _GRAPHICS_VIEW
#define _GRAPHICS_VIEW
#include "view.h"
#include "window.h"
#include <vector>
#include <memory>
#include <string>

class Player;
class Card;
class TextView;
class Spell;
class Ritual;
class Minion;
class Enchantment;

class GraphicsView : public View {

    std::unique_ptr<TextView> text;
    std::unique_ptr<Xwindow> w;
    int width = 900;
    int height = 650;
    

    public:
    explicit GraphicsView(std::vector<std::shared_ptr<Player>> *players);
    void onAttack(unsigned int i) override;
    void onAttack(unsigned int i, unsigned int j) override;
    void onPlay(int i) override;
    void onPlay(int i, int j, int p) override;
    void onUse(int i) override;
    void onUse(int i, int j, int p) override;
    void onHelp() override;
    void onEnd(std::string p) override;
    void onQuit() override;
    void onDraw() override;
    void onDiscard(int i) override;
    void onDescribe(int i, int p) override;
    void onHand(int p) override;
    void onBoard() override;
    void endGame(int i) override;
    void displayBoard();
    void displayCard(Card *, int x, int y);
    void displayPlayer(Player &p, int x, int y);
    void minionDisplay(Minion &, int x, int y);
    void spellDisplay(Spell &, int x, int y);
    void ritualDisplay(Ritual &, int x, int y);
    void enchantDisplay(Enchantment &, int x, int y);
    void printDesc(std::string, int x, int y);
    void displayError(std::string e) override;

};

#endif
