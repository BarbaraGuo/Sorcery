#ifndef _MODEL_H
#define _MODEL_H
#include <memory>
#include <vector>

class Controller;
class Player;

class Model {
    int turn = 0;
    std::vector<std::shared_ptr<Player>> players;
    bool testing;

    public:
    Model(std::string name1, std::vector<std::string> deck1, std::string name2, std::vector<std::string> deck2, bool testing);
    std::vector<std::shared_ptr<Player>> *getPlayers();
    void onAttack(unsigned int i);
    void onAttack(unsigned int i, unsigned int j);
    void onPlay(unsigned int i);
    void onPlay(unsigned int, unsigned int, unsigned int);
    void onUse(unsigned int i);
    void onUse(unsigned int, unsigned int, unsigned int);
    void onDraw();
    void onDiscard(int i);
    void startTriggers();
    void endTriggers();
    void enterTriggers();
    void exitTriggers();
    void onEnd();
    void endGame(int);
    void checkForWin();
    void startGame();
    int getTurn();

};

#endif
