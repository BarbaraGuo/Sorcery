#include "view.h"
#include "player.h"
#include "card.h"

View::View(std::vector<std::shared_ptr<Player>> *players): players{players} {};

View::~View() {}

void View::onAttack(unsigned int i) {}
void View::onAttack(unsigned int i, unsigned int j){}
void View::onPlay(int i){}
void View::onPlay(int i, int j, int t){}
void View::onUse(int i){}
void View::onUse(int i, int j, int t){}
void View::onHelp() { }
void View::onEnd(std::string  p){}
void View::onQuit(){}
void View::onDraw(){}
void View::onDiscard(int i){}
void View::onDescribe(int i, int p){}
void View::onHand(int p){}
void View::onBoard(){}
void View::endGame(int i){}

