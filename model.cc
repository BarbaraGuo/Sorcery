#include "model.h"
#include "player.h"
#include "controller.h"

Model::Model(std::string name1, std::vector<std::string> deck1, std::string name2, std::vector<std::string> deck2, bool testing): testing{testing} {
    auto p1 = std::make_shared<Player>(name1, 1, testing, deck1);
    auto p2 = std::make_shared<Player>(name2, 2, testing, deck2);
    p1->setOpponent(p2.get());
    p2->setOpponent(p1.get());
    players.emplace_back(p1);
    players.emplace_back(p2);
}

std::vector<std::shared_ptr<Player>> *Model::getPlayers() {
    return &players;
}

void Model::onAttack(unsigned int i) {
    players.at(turn)->attack(i);
    checkForWin();
}

void Model::onAttack(unsigned int i, unsigned int j) {
    players.at(turn)->attack(i, j);
    checkForWin();
}

void Model::onPlay(unsigned int i) {
    try {
        players.at(turn)->play(i);
        checkForWin();
    } catch (const char* e) {
        throw e;
    }
}

void Model::onPlay(unsigned int i, unsigned int p, unsigned int t) {
    players.at(turn)->play(i, p, t);
    checkForWin();
}

void Model::onUse(unsigned int i) {
    players.at(turn)->use(i);
    checkForWin();
}

void Model::onUse(unsigned int i, unsigned int p, unsigned int t) {
    players.at(turn)->use(i, p, t);
    checkForWin();
}

void Model::onDraw() {
    players.at(turn)->draw();
}

void Model::onDiscard(int i) {
    players.at(turn)->discard(i);
}

void Model::startTriggers() {
    // Call current player's start turn trigger
    players.at(turn)->startTurn();
    checkForWin();
}

void Model::endTriggers() {
    // call current player's end turn trigger
    players.at(turn)->endTurn();
    checkForWin();
}


void Model::onEnd() {
    endTriggers();
    players.at(turn)->getBoard()->resetMinionAttacks(); 
    ++turn;
    turn = turn % 2;
    players.at(turn)->getBoard()->resetMinionAttacks(); 
    startTriggers();
    players.at(turn)->setMagic(players.at(turn)->getMagic() + 1);
    players.at(turn)->draw();
}

void Model::startGame() {
    players.at(0)->setLife(20);
    players.at(1)->setLife(20);

    if (!testing) {
        players.at(0)->shuffleDeck();
        players.at(1)->shuffleDeck();
    }

    for(int i = 0; i < 5; i++) {
        players.at(0)->draw();
        players.at(1)->draw();
    }
    players.at(0)->setMagic(4);
    players.at(1)->setMagic(3);
}

void Model::endGame(int i) {
    //throws the player number of the player than wins
    throw i + 1;
}

void Model::checkForWin() {
    if (players.at(0)->getLife() <= 0) {
        endGame(1);
    }
    
    if (players.at(1)->getLife() <= 0) {
        endGame(0);
    }
}

int Model::getTurn() {
    return turn;
}



