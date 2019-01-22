#include "graphicsView.h"
#include "player.h"
#include "card.h"
#include "textView.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
#include "window.h"
#include <string>
#include <sstream>

static std::string toString(int i) {
    std::ostringstream s;
    s << i;
    return s.str();
}

void GraphicsView::printDesc(std::string d, int x, int y) {
    int chars = width/40;
    int line = y;
    std::string curr;
    for(unsigned int i = 0; i < d.length(); i++) {
        curr += d[i];
        if (i % chars == 0 && i != 0) {
            w->drawString(x, line, curr);
            curr = "";
            line += 20;
        }
    }
    if (curr != "") {
        w->drawString(x, line, curr);
    }
}

GraphicsView::GraphicsView(std::vector<std::shared_ptr<Player>> *players): View{players}, text{std::make_unique<TextView>(players)}, w{std::make_unique<Xwindow>(900, 650)} {}

void GraphicsView::onAttack(unsigned int i) {
    displayBoard();
}

void GraphicsView::onAttack(unsigned int i, unsigned int j){
    displayBoard();
}

void GraphicsView::onPlay(int i){
    displayBoard();
}

void GraphicsView::onPlay(int i, int j, int p){
    displayBoard();
}

void GraphicsView::onUse(int i){
    displayBoard();
}

void GraphicsView::onUse(int i, int j, int p){
    displayBoard();
}

void GraphicsView::onHelp(){
    text->onHelp();
    int margin = width*0.08;
    w->fillRectangle(0, 0, width, height, 0);
    w->drawString(margin, 50, "Commands");
    w->drawString(margin, 70, "help -- Display this message");
    w->drawString(margin, 90, "end -- End the current player's turn.");
    w->drawString(margin, 110, "quit -- End the game.");
    w->drawString(margin, 130, "attack minion other-minion -- Orders minion to attack other-minion.");
    w->drawString(margin, 150,  "sttack minion -- Orders minion to attack the opponent.");
    w->drawString(margin, 170, "play card [target-player target-card] -- Play card, optionally targeting");
    w->drawString(margin, 190, "        target-card owned by target-player.");
    w->drawString(margin, 210, "use minion [target-player target-card] -- Use minion's special ability,");
    w->drawString(margin, 230, "        optionally targeting target-card owned by target-player.");
    w->drawString(margin, 250, "inspect minion -- View a minion's card & all enchantments on that minion");
    w->drawString(margin, 270, "hand -- Describe all cards in your hand.");
    w->drawString(margin, 290, "board -- Describe all cards on the board.");
}

void GraphicsView::onEnd(std::string p){
    text->onEnd(p);
    displayBoard();
}

void GraphicsView::onQuit(){
    text->onQuit();
}

void GraphicsView::onDraw(){
    text->onDraw();
}

void GraphicsView::onDiscard(int i){
    text->onDiscard(i);
}

void GraphicsView::onDescribe(int i, int p) {
    text->onDescribe(i, p);
    w->fillRectangle(0, 0, width, height, 0);
    int size = players->at(p)->getBoard()->getMinions().size();

    if (size != 0 && i > 0 && i <= size) {
        minionDisplay(*players->at(p)->getBoard()->getMinions().at(i-1).get(), 0, 0);
    }
    
    if (players->at(p)->getBoard()->getMinions().at(i-1)->getEnchants().size() != 0) {
        int num = 0;
        for(auto card : players->at(p)->getBoard()->getMinions().at(i-1)->getEnchants()) {
            enchantDisplay(*card.get(), (width/5)*(num%5), (height/5)*((num+5)/5));
            ++num;
        }
    }

}

void GraphicsView::onHand(int p){
    text->onHand(p);
    w->fillRectangle(0, height/5, width, 3*height/5, 0);
    w->drawBigString(width/4, 2*(height/5) - 25, players->at(p)->getName() + "'s Hand");
    int s = players->at(p)->getHand().size();
    if (s != 0) {
        for(int i = 0; i < s; i++) {
            displayCard(players->at(p)->getHand().at(i).get(), i*(width/5), 2*(height/5));
        }
    }
}

void GraphicsView::onBoard(){
    text->onBoard();
    displayBoard();
}

void GraphicsView::displayBoard() {
    w->fillRectangle(0, 0, width, height, 0);
    w->drawBigString(width/3 - 50, height/2, "S O R C E R Y");

    // printing minions on board;   
    for(unsigned int i = 0; i < players->at(0)->getBoard()->getMinions().size(); i++) {
         displayCard(players->at(0)->getBoard()->getMinions().at(i).get(), i*(width/5), height/5);
    }

    for(unsigned int i = 0; i < players->at(1)->getBoard()->getMinions().size(); i++) {
        displayCard(players->at(1)->getBoard()->getMinions().at(i).get(), i*(width/5), 3*(height/5));
    }

    //printing graveyards
    w->fillRectangle(4*(width/5) - 3, 0, width/5 + 3, height/5, 10);
    w->fillRectangle(4*(width/5), 3, width/5 - 3, height/5 - 6, 0);
    w->fillRectangle(4*(width/5) - 3, 4*(height/5), width/5 + 3, height/5, 10);
    w->fillRectangle(4*(width/5), 4*(height/5) + 3, width/5 - 3, height/5 - 6, 0);
    if (players->at(0)->getBoard()->getGraveyard().size() != 0) {
        displayCard(players->at(0)->getBoard()->getGraveyard().back().get(), 4*(width/5), 0);
    }
    if (players->at(1)->getBoard()->getGraveyard().size() != 0) {
        displayCard(players->at(1)->getBoard()->getGraveyard().back().get(), 4*(width/5), 4*(height/5));
    }

    //printing rituals
    w->fillRectangle(0, 0, width/5 + 3, height/5, 3);
    w->fillRectangle(3, 3, width/5 - 3, height/5 - 6, 0);
    w->fillRectangle(0, 4*(height/5), width/5 + 3, height/5, 3);
    w->fillRectangle(3, 4*(height/5) + 3, width/5 - 3, height/5 - 6, 0);
    if (players->at(0)->getBoard()->getRitual().get() != nullptr) {
        displayCard(players->at(0)->getBoard()->getRitual().get(), 0, 0);
    }
    if (players->at(1)->getBoard()->getRitual().get() != nullptr) {
        displayCard(players->at(1)->getBoard()->getRitual().get(), 0, 4*(height/5));
    }

    //printing players
    displayPlayer(*players->at(0).get(), 2*(width/5), 20);
    displayPlayer(*players->at(1).get(), 2*(width/5), 4*(height/5) + 20);

}

void GraphicsView::endGame(int i){
    text->endGame(i);
}

void GraphicsView::displayCard(Card *c, int x, int y) {
    if (c->getType() == "minion") {
        minionDisplay(*(dynamic_cast<Minion *>(c)), x, y);
    } else if (c->getType() == "spell") {
        spellDisplay(*(dynamic_cast<Spell *> (c)), x, y);
    } else if (c->getType() == "enchantment") {
        enchantDisplay(*(dynamic_cast<Enchantment *> (c)), x, y);
    } else if (c->getType() == "ritual") {
        ritualDisplay(*(dynamic_cast<Ritual *> (c)), x, y);
    }
}

void GraphicsView::minionDisplay(Minion &m, int x, int y) {
    int margin = (width/5)*0.1;
    w->drawLine(x, y, x + width/5, y);
    w->drawLine(x, y, x, y + height/5);
    w->drawLine(x, y + height/5, x + width/5, y + height/5);
    w->drawLine(x + width/5, y, x + width/5, y + height/5);
    w->drawString(x + margin, y + margin, m.getName()); // top left
    w->drawString(x + width/5 - margin, y +  margin, toString(m.getCost())); // top right
    w->drawString(x + margin, y + height/5 - margin, toString(m.getAttack())); // bottom left
    w->drawString(x + width/5 - margin, y + height/5 - margin, toString(m.getDefence())); // bottom right

    if (m.getActiveCost() != 0) {
        w->drawString(x + margin, y + height/15, toString(m.getActiveCost()));
        printDesc(m.getDescription(), x + 2*margin, y + height/15);
    } else if (m.getDescription() != "") {
        printDesc(m.getDescription(), x + margin, y + height/15);
    }

}

void GraphicsView::spellDisplay(Spell &s, int x, int y) {
    int margin = 0.1*width/5;
    w->drawLine(x, y, x + width/5, y);
    w->drawLine(x, y, x, y + height/5);
    w->drawLine(x, y + height/5, x + width/5, y + height/5);
    w->drawLine(x + width/5, y, x + width/5, y + height/5);
    w->drawString(x + margin, y + margin, s.getName()); // top left
    w->drawString(x + width/5 - 15, y + margin, toString(s.getCost())); // top right
     printDesc(s.getDescription(), x + margin, y + height/15);

}

void GraphicsView::enchantDisplay(Enchantment &e, int x, int y) {
    int margin = 0.1*width/5;
    w->drawLine(x, y, x + width/5, y);
    w->drawLine(x, y, x, y + height/5);
    w->drawLine(x, y + height/5, x + width/5, y + height/5);
    w->drawLine(x + width/5, y, x + width/5, y + height/5);  
    w->drawString(x + margin, y + margin, e.getName()); // top left
    w->drawString(x + width/5 - 15, y + margin, toString(e.getCost())); // top right
    if (e.getDescription() == "") {
        std::string a;
        std::string d;
        if (e.getName() == "Giant Strength") {
            a = "+2";
            d = "+2";
        } else if (e.getName() == "Enrage") {
            a = "*2";
            d = "*2";
        }

        w->drawString(x + margin, y + height/5 - margin, a); // bottom left
        w->drawString(x + width/5 - margin, y + height/5 - margin, d);
    } else {
       printDesc(e.getDescription(), x + margin, y + height/15);
    }
}

void GraphicsView::ritualDisplay(Ritual &r, int x, int y) {
    int margin = 0.1*width/5;
    w->drawLine(x, y, x + width/5, y);
    w->drawLine(x, y, x, y + height/5);
    w->drawLine(x, y + height/5, x + width/5, y + height/5);
    w->drawLine(x + width/5, y, x + width/5, y + height/5);
    w->drawString(x + margin, y + margin, r.getName()); // top left
    w->drawString(x + width/5 - 15, y + margin, toString(r.getCost())); // top right
    w->drawString(x + margin, y + height/15, toString(r.getActivationCost()));
    printDesc(r.getDescription(), x + 2*margin, y + height/15);
}

void GraphicsView::displayPlayer(Player &p, int x, int y) {
    std::string name = "Player " + toString(p.getPlayerNum()) + ": " + p.getName();
    std::string health = "Health: " + toString(p.getLife());
    std::string magic = "Magic: " + toString(p.getMagic());
    w->drawString(x, y, name);
    w->drawString(x, y + 20 , health);
    w->drawString(x, y + 40, magic);
}

void GraphicsView::displayError(std::string e) {
    text->displayError(e);
}
