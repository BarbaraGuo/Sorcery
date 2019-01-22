#include "controller.h"
#include "model.h"
#include "view.h"
#include "graphicsView.h"
#include "textView.h"
#include "deck.h"
#include "player.h"
#include "card.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


Controller::Controller(std::string deck1, std::string deck2, bool testing, bool graphics, bool firstInput, std::fstream &in1, std::istream &in2): deck1{deck1}, deck2{deck2}, testing{testing}, graphics{graphics}, finished{false}, firstInput{firstInput}, is1{in1}, is2{in2} {

    initModel();

    if(graphics) {
        v = std::make_shared<GraphicsView>(GraphicsView(m->getPlayers()));
    } else {
        v = std::make_shared<TextView>(TextView(m->getPlayers()));
    }
}


void Controller::initModel() {
    std::string name1;
    std::string name2;

    if (firstInput) {
        if (is1 >> name1) {
            if (is1 >> name2) {
            } else {
                is2 >> name2;
                firstInput = false;
            }
        } else {
            is2 >> name1;
            is2 >> name2;
            firstInput = false;
        }
    } else {
        is2 >> name1;
        is2 >> name2;
    }
    m = std::make_shared<Model>(name1, initDeck(deck1, 1), name2, initDeck(deck2, 2), testing);
}


std::vector<std::string> Controller::initDeck(std::string deckFile, int playernum) {
    std::fstream f{deckFile};
    std::vector<std::string> deck;
    std::string line;
    
    while(std::getline(f, line)) {
        deck.emplace_back(line);
    }

    return deck;
}

void Controller::gameLoop(std::istream &in) {
    std::string s;
    int in1;
    int in2;
    int in3;
    char c;

    try {

    while(getline(in, s)) {
        if (s == "help") {
            onHelp();
        }
        else if (s == "end") {
            onEnd();
        }
        else if (s == "quit") {
            onQuit();
            break;
        }
        else if (s.substr(0, 6) == "attack") {
            std::istringstream sin{s.substr(6, s.length() - 6)};
            sin >> in1;
            if (sin >> in2) {
                onAttack(in1, in2);
            } else {
                sin.clear();
                onAttack(in1);
            } 
        }
        else if (s.substr(0, 4) == "play") {
            std::istringstream sin{s.substr(4, s.length() - 4)};
            sin >> in1;
            if (sin >> in2) {
                if(!(sin >> in3)){
                    sin.clear();
                    sin >> c;
                    onPlay(in1, in2, c);
                } else {
                    onPlay(in1, in2, in3);
                }  
            } else {
                sin.clear();
                onPlay(in1); 
            }
        }
        else if (s.substr(0, 3)  == "use") {
            std::istringstream sin{s.substr(3, s.length() - 3)};
            sin >> in1;
            if (sin >> in2) {
                sin >> in3;
                onUse(in1, in2, in3);
            } else {
                sin.clear();
                onUse(in1);
            }
        }

        else if (s.substr(0, 7) == "inspect") {
            std::istringstream sin{s.substr(7, s.length() - 7)};
            sin >> in1;
            onDescribe(in1);
        }
        else if (s == "hand") {
            onHand();
        }
        else if (s == "board") {
            onBoard();
        }
        if (testing) {
            if (s.substr(0, 7) == "discard") {
                std::istringstream sin{s.substr(7, s.length() - 7)};
                sin >> in1;
                onDiscard(in1);
            }
            else if (s == "draw") {
                onDraw();
            }
        }

    }

    } catch (int i) {
        endGame(i);
        finished = true;
    }


}

void Controller::playGame() {
    m->startGame();
    v->onEnd(m->getPlayers()->at(0)->getName());

    if (firstInput) {
        gameLoop(is1);
    }

    if (!finished) {
        gameLoop(is2);
    }

}

void Controller::onAttack(unsigned int i) {
    try {
        m->onAttack(i);
        v->onAttack(i);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onAttack(unsigned int i, unsigned int j) {
    try {
        m->onAttack(i, j);
        v->onAttack(i, j);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onPlay(unsigned int i) {
    try {
        m->onPlay(i);
        v->onPlay(i);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onPlay(unsigned int i, unsigned int p, unsigned int t) {
    try {
        m->onPlay(i, p, t);
        v->onPlay(i, p, t);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onUse(unsigned int i) {
    try {
        m->onUse(i);
        v->onUse(i);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onUse(unsigned int i, unsigned int p, unsigned int t) {
    try {
        m->onUse(i, p, t);
        v->onUse(i, p, t);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onHelp() {
    v->onHelp();
}

void Controller::onEnd() {
    m->onEnd();
    v->onEnd(m->getPlayers()->at(m->getTurn())->getName());
}

void Controller::onQuit() {
    finished = true;
    v->onQuit();
}

void Controller::onDraw() {
    m->onDraw();
    v->onDraw();
}

void Controller::onDiscard(unsigned int i) {
    try {
        m->onDiscard(i);
        v->onDiscard(i);
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onDescribe(unsigned int i) {
    try {
        v->onDescribe(i, m->getTurn());
    } catch (const char* e) {
        v->displayError(e);
    }
}

void Controller::onHand() {
    v->onHand(m->getTurn());
}

void Controller::onBoard() {
    v->onBoard();
}

void Controller::endGame(int i) {
    v->endGame(i);
    finished = true;
}


