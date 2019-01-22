#ifndef _VIEW_H
#define _VIEW_H
#include <memory>
#include <vector>
#include <string>

class Player;
class Card;

class View {

    protected:
        std::vector<std::shared_ptr<Player>> *players;

    public:
    View(std::vector<std::shared_ptr<Player>> *players);
    virtual void onAttack(unsigned int i);
    virtual void onAttack(unsigned int i, unsigned int j);
    virtual void onPlay(int i);
    virtual void onPlay(int i, int j, int t);
    virtual void onUse(int i);
    virtual void onUse(int i, int j, int t);
    virtual void onHelp();
    virtual void onEnd(std::string p);
    virtual void onQuit();
    virtual void onDraw();
    virtual void onDiscard(int i);
    virtual void onDescribe(int i, int p);
    virtual void onHand(int p);
    virtual void onBoard();
    virtual void endGame(int i);
    virtual void displayError(std::string e) = 0;
    virtual ~View() = 0;

};

#endif
