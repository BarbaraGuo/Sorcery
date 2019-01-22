#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include <memory>
#include <vector>
#include <string>
#include <istream>
#include <fstream>
#include "model.h"
#include "view.h"

//class Model;
//class View;
class Card;

class Controller {
    std::shared_ptr<Model> m;
    std::shared_ptr<View> v;
    std::string deck1;
    std::string deck2;
    bool testing;
    bool graphics;
    bool finished;
    bool firstInput;
    std::fstream &is1;
    std::istream &is2;


    public:
    Controller(std::string deck1, std::string deck2,  bool testing, bool graphics, bool firstInput, std::fstream &in1, std::istream &in2);
    void initModel();
    std::vector<std::string> initDeck(std::string, int);
    void gameLoop(std::istream &in);
    void playGame();
    void onAttack(unsigned int i);
    void onAttack(unsigned int i, unsigned int j);
    void onPlay(unsigned int, unsigned int, unsigned int);
    void onPlay(unsigned int);
    void onUse(unsigned int);
    void onUse(unsigned int, unsigned int, unsigned int);
    void onHelp();
    void onEnd();
    void onQuit();
    void onDraw();
    void onDiscard(unsigned int i);
    void onDescribe(unsigned int i);
    void onHand();
    void onBoard();
    void endGame(int);
};

#endif
