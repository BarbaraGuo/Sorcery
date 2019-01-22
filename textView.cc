#include "textView.h"
#include "player.h"
#include "card.h"
#include "spell.h"
#include "ritual.h"
#include "enchantment.h"
#include "minion.h"
#include <iostream>

TextView::TextView(std::vector<std::shared_ptr<Player>> *players): View{players} {}

void TextView::onHelp(){
    std::cout << "Commands" << std::endl;
    std::cout << "help -- Display this message" << std::endl;
    std::cout << "end -- End the current player's turn" << std::endl;
    std::cout << "quit -- End the game" << std::endl;
    std::cout << "attack minion other-minion -- Orders miinion to attack other-minion" << std::endl;
    std::cout << "attack minion -- Orders minion to attack the opponent" << std::endl;
    std::cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player" << std::endl;
    std::cout << "use minon [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << std::endl;
   std::cout << "inspect minion -- View a minion's card and all enchantments on that minion." << std::endl;
    std::cout << "hand -- Describe all cards in your hand." << std::endl;
    std::cout << "board -- Describe all cards on the board." << std::endl;
}

void TextView::onEnd(std::string p){
    std::cout << p << "'s turn." << std::endl;
}

void TextView::onQuit(){
    std::cout << "Game Over" << std::endl;
}

void TextView::onDescribe(int i, int p) {
    int size = players->at(p)->getBoard()->getMinions().size();
    if (size != 0 && i > 0 && i <= size) {
        displayCard(players->at(p)->getBoard()->getMinions().at(i-1).get());
        unsigned int line = 1;
        int numEnchants = players->at(p)->getBoard()->getMinions().at(i-1)->getEnchants().size();
        std::vector<std::vector<std::string>> s;
        if (numEnchants != 0) {
            for(auto card : players->at(p)->getBoard()->getMinions().at(i-1)->getEnchants()) {
                s.emplace_back(cardDisplay(card.get()));
             }
            
            while(line*5 <= s.size()) {
                for(unsigned int y = 0; y < s.at(0).size(); ++y) {
                    for( unsigned int x = 0; x < 5; ++x) {
                        std::cout << s.at(x).at(y);
                    }   
                    std::cout << std::endl;
                }
                ++line;
            }
        
            if ((line - 1)*5 < s.size()) {
                for(unsigned int y = 0; y < s.at(0).size(); ++y) {
                    for( unsigned int x = ((line-1)*5); x < s.size(); ++x) {
                        std::cout << s.at(x).at(y);
                    }   
                    std::cout << std::endl;
                }
            }
            
        }
    }
}

void TextView::onHand(int p) {
    std::vector<std::vector<std::string>> s;
    if (players->at(p)->getHand().size() != 0) {
    for(auto card: players->at(p)->getHand()) {
         s.emplace_back(cardDisplay(card.get()));
    }
    for(unsigned int i = 0; i < s.at(0).size(); i++) {
        for(unsigned int x = 0; x < players->at(p)->getHand().size(); x++) {
            std::cout << s.at(x).at(i);
        }
        std::cout << std::endl;
    }
    }
}


std::vector<std::vector<std::string>> TextView::outsideBoard(Player &p) {
    std::vector<std::vector<std::string>> s;
    if (p.getBoard()->getRitual() != nullptr) {
        s.emplace_back(ritualDisplay(*p.getBoard()->getRitual().get()));
    } else {
        s.emplace_back(CARD_TEMPLATE_BORDER);
    }

    s.emplace_back(CARD_TEMPLATE_EMPTY);
    s.emplace_back(playerDisplay(p));
    s.emplace_back(CARD_TEMPLATE_EMPTY);
    
    if (p.getBoard()->getGraveyard().size() != 0) {
            s.emplace_back(cardDisplay(p.getBoard()->getGraveyard().back().get()));
    } else {
        s.emplace_back(CARD_TEMPLATE_BORDER);
    }

    return s;
}

std::vector<std::vector<std::string>> TextView::insideBoard(Player &p) {
    std::vector<std::vector<std::string>> s;
    int empty = 5 - p.getBoard()->getMinions().size();

    for(int i = 0; i < 5 - empty; i++) {
        s.emplace_back(minionDisplay(*p.getBoard()->getMinions().at(i).get()));
    }

    for(int i = 0; i < empty; i++) {
        s.emplace_back(CARD_TEMPLATE_BORDER);
    }

    return s;
}

void TextView::onBoard(){
    std::vector<std::string> centre = CENTRE_GRAPHIC;
    std::vector<std::vector<std::string>> topOutside = outsideBoard(*players->at(0).get());
    std::vector<std::vector<std::string>> bottomOutside = outsideBoard(*players->at(1).get());
    std::vector<std::vector<std::string>> topInside = insideBoard(*players->at(0).get());
    std::vector<std::vector<std::string>> bottomInside = insideBoard(*players->at(1).get());

    int width = centre.at(1).length();
    //print top line
    std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for(int w = 0; w < width - 2; w++) {
        std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;

    //player ritual /empty /player card /empty/ first card of player graveyard
    for(unsigned int i = 0; i < topOutside.at(0).size(); i++) {
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for(unsigned int x = 0; x < topOutside.size(); x++) {
            std::cout << topOutside.at(x).at(i);
        }
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
    }
    //player minions on board
    for(unsigned int i = 0; i < topInside.at(0).size(); i++) {
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for(unsigned int x = 0; x < topInside.size(); x++) {
            std::cout << topInside.at(x).at(i);
        }
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
    }


    for(auto line : centre) {
        std::cout << line << std::endl;
    }

    //player minions on board
    for(unsigned int i = 0; i < bottomInside.at(0).size(); i++) {
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for(unsigned int x = 0; x < bottomInside.size(); x++) {
            std::cout << bottomInside.at(x).at(i);
        }
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
    }


    //player ritual /empty /player card /empty/ first card of player graveyard
    for(unsigned int i = 0; i < bottomOutside.at(0).size(); i++) {
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for(unsigned int x = 0; x < bottomOutside.size(); x++) {
            std::cout << bottomOutside.at(x).at(i);
        }
        std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
    }

    //print bottom line
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for(int w = 0; w < width - 2; w++) {
        std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;


}

void TextView::endGame(int i){
    std::cout << "Player: " << i << " Wins!" << std::endl;
}

void TextView::displayCard(Card *c) {
    card_template_t s = cardDisplay(c);
        for(auto line : s) {
        std::cout << line << std::endl;
    }
}

card_template_t TextView::cardDisplay(Card *c) {
    card_template_t s;
    if (c->getType() == "minion") {
        s = minionDisplay(*(dynamic_cast<Minion *>(c)));
    } else if (c->getType() == "spell") {
        s = spellDisplay(*(dynamic_cast<Spell *>(c)));
    } else if (c->getType() == "enchantment") {
        s = enchantDisplay(*(dynamic_cast<Enchantment *>(c)));
    } else if (c->getType() == "ritual") {
        s = ritualDisplay(*(dynamic_cast<Ritual *>(c)));
    }
    return s;
}

card_template_t TextView::spellDisplay(Spell &c) {
    card_template_t s = display_spell(c.getName(), c.getCost(), c.getDescription());
    return s;
}

card_template_t TextView::ritualDisplay(Ritual &c) {
    card_template_t s = display_ritual(c.getName(), c.getCost(), c.getActivationCost(), c.getDescription(), c.getCharge());
    return s;
}

card_template_t TextView::enchantDisplay(Enchantment &c) {
    card_template_t s;
    std::string a = "";
    std::string d = "";
    if (c.getName() == "Giant Strength") {
    	a = "+2";
    	d = "+2";
    } else if (c.getName() == "Enrage") {
	    a = "*2";
	    d = "*2";
    }
    if (a != "") {
        s = display_enchantment_attack_defence(c.getName(), c.getCost(), c.getDescription(), a, d);
    } else {
        s = display_enchantment(c.getName(), c.getCost(), c.getDescription());
    }
    return s;
}

card_template_t TextView::minionDisplay(Minion &c) {
    card_template_t s;
    if (c.getActiveCost() != 0) {
        s = display_minion_activated_ability(c.getName(), c.getCost(), c.getAttack(), c.getDefence(), c.getActiveCost(), c.getDescription());
    } else if (c.getDescription() != "") {
        s = display_minion_triggered_ability(c.getName(), c.getCost(), c.getAttack(), c.getDefence(), c.getDescription());
    } else {
        s = display_minion_no_ability(c.getName(), c.getCost(), c.getAttack(), c.getDefence());
    }
    return s;
}



void TextView::displayPlayer(Player &c) {
    card_template_t s = playerDisplay(c);
    for(unsigned int i = 0; i < s.size(); i++) {
        std::cout << s.at(i) << std::endl;
    }
}

card_template_t TextView::playerDisplay(Player &p) {
    card_template_t s = display_player_card(p.getPlayerNum(), p.getName(), p.getLife(), p.getMagic());
    return s;
}

void TextView::displayError(std::string e) {
    std::cout << e << std::endl;
}

