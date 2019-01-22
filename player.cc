#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <exception>
#include "player.h"
#include "card.h"
#include "ritual.h"
#include "enchantment.h"
#include "board.h"

using namespace std;

Player::Player(string name, int n, bool testing, std::vector<std::string> deckName) : name{name}, playernum{n}, testing{testing}, deck{make_unique<Deck>(n, deckName)}, lastMinion{nullptr}, opponent{nullptr} {}

Player::~Player() {}

// getters and setters
Player *Player::getOpponent(){
    return opponent;
}

void Player::setOpponent(Player *opp){
        opponent = opp;
}

int Player::getPlayerNum(){
    return playernum;
}

shared_ptr<Board> Player::getBoard() {
    return board;
}

std::shared_ptr<Minion> Player::getLastMinionPlayed(){
    return lastMinion;
}

int Player::getMagic() {
    return magic;
}

void Player::setMagic(int m) {
    magic = m;
}

std::string Player::getName() {
    return name;
}


vector<shared_ptr<Card>> Player::getHand() {
     return hand;
}

void Player::shuffleDeck() {
    deck->shuffle();
}

int Player::getLife() {
    return life;
}

void Player::setLife(int l) {
    life = l;
}

bool Player::draw() {
        if (hand.size() < 5) {
            try {
                hand.emplace_back(deck->draw());
                return true;
            } catch (const char *e) {
                //what should happen if the deck is empty
                return false;
            }
        }  else {
            return false;
        }
}

void Player::discard(unsigned int i) {
        if (1 <= i && i <= hand.size()) {
                hand.erase(hand.begin() + i - 1);
        } else {
                throw "Invalid Index";
        }
}

void Player::oneMagic() {
        setMagic(getMagic() + 1);
}

void Player::attack(unsigned int i){ // orders ith minion to attack opposing player
	if ( 1 <= i && i <= board->getMinions().size()) {
		if (board->getMinions().at(i-1)->getActionsLeft() > 0) {
			// do thing
                        board->getMinions().at(i - 1)->attack(*opponent);
		} else {
        		throw "That minion does not have any actions left.";
    		}
	} else {
		throw "Invalid Index.";
	}
}

void Player::attack(unsigned int i, unsigned int j){ // orders active player's ith minion
        if ( 1 <= i && i <= board->getMinions().size()) {
		if (board->getMinions().at(i-1)->getActionsLeft() > 0) {
			// do thing	
                	try{
                        	opponent->getBoard()->getMinions().at(j - 1)->
                        	getAttackedBy(*(board->getMinions().at(i - 1)), *opponent);
                	} catch(const std::out_of_range &e) {
                    		throw "Invalid target.";
                	}
        	} else {
            		throw "That minion does not have any actions left.";
       	 	}
	} else {
		throw "Invalid Index.";
	}
}

void Player::returnCard(Minion &m){
        if(hand.size() < 5) {
            	int place = m.getPlace();
            	hand.emplace_back(board->getMinions().at(place));
            	board->getMinions().erase(board->getMinions().begin() + place);
            	m.setPlace(-1);
        } else {
	    	throw "Not enough hand space, discarded card.";
	}
}

bool Player::resurrect(shared_ptr<Minion> c) {
        if (board->getMinions().size() < 5) {
                int place = board->getMinions().size();
                c->setPlace(place);
                board->getMinions().emplace_back(c);
                return true;
        } else if (hand.size() < 5) {
                hand.emplace_back(c);
                return true;
        }
        return false;
}

void Player::takeDamage(int d) {
        life -= d;
}

void Player::play(unsigned int i) {
        if (1 <= i && i <= hand.size()) {
                shared_ptr<Card> toplay = hand[i - 1];
                string type = toplay->getType();
                int cost = toplay->getCost();
                if (type == "minion" && magic >= cost) {
                        //triggers for minion enter play runs
                        board->playMinion(std::dynamic_pointer_cast<Minion>(toplay));
                        lastMinion = std::dynamic_pointer_cast<Minion>(toplay);
			battlecry();
                        discard(i);
                        magic -= cost;
                } else if ((type == "spell") && (magic >= cost || testing)) {
			if (!toplay->getTargeted()) {
                                // play untargeted spells only
                                try{
                                     	toplay->attack(*this);
                                       	discard(i);
                                       	magic -= cost;
                                       	if (magic < 0) {
                                        	magic = 0;
                                        }
                                } catch (std::string e) {
                                       	throw e;
                                }
			} else {
				throw "Specify a player and target for a targeted spell.";
			} 
                } else if (type == "ritual" && magic >= cost) {
                        try {
                                board->playRitual(std::dynamic_pointer_cast<Ritual>(toplay));
                                discard(i);
                                magic -= cost;
                        } catch (std::string e){
                                throw e;
                        }
                } else if (type == "enchantment") {
			throw "Specify a target for an enchantment.";
		} else {	
			throw "Not enough magic.";
		} 
        } else {
                throw "Invalid Index.";
        }
}

void Player::play(unsigned int i, int p, unsigned int t) {
        if (1 <= i && i <= hand.size() && (p == 1 || p == 2)) {
                shared_ptr<Card> toplay = hand[i - 1];
                string type = toplay->getType();
                int cost = toplay->getCost();
                if (type == "spell" && (magic >= cost || testing)) {
			if (toplay->getTargeted()) {
                         	(p == playernum) ? toplay->attack(t, *this) : 
					toplay->attack(t, *opponent);
                            	discard(i);
                            	magic -=cost;
                            	if (magic < 0) {
                                	magic = 0;
                            	}
			} else {
				throw "Do not specify a player and index for an untargeted spell.";
			}
                } else if (type == "enchantment" || magic >= cost) {
                       // play enchantment on target
                        if (p == playernum) {
                               	if (1 <= t && t <= this->getBoard()->getMinions().size()) {
                                    	(std::dynamic_pointer_cast<Enchantment>(toplay))->enchant(getBoard()->getMinions().at(t-1));
                                	getBoard()->getMinions().at(t-1)->getEnchants().emplace_back(std::dynamic_pointer_cast<Enchantment>(toplay));
                                } else {
                                    	throw "Invalid Index.";
                               	}
                        } else { 
                                if (1 <= t && t <= opponent->getBoard()->getMinions().size()) {
                                    	(std::dynamic_pointer_cast<Enchantment>(toplay))->enchant(opponent->getBoard()->getMinions().at(t-1));
                                } else {
                                    	throw "Invalid Index.";
                                }
                        }
                        discard(i);
                        magic -=cost;
                } else if (type == "ritual") {
			throw "Do not specify a player and index for a ritual.";
		} else if (type == "minion") {
			throw "Do not specify a player and index for a minion.";
		} else {
			throw "Not enough magic.";
		}
       	} else {
            	throw "Invalid Index.";
	}
}

void Player::use(unsigned int i) {
        unsigned int size = board->getMinions().size();
        if (size == 0) {
            throw "You have no minions to use.";
        } else if (1 <= i && i <= size) {
		int cost = board->getMinions().at(i-1)->getActiveCost();
		if (cost > 0 && !board->getMinions().at(i-1)->getTargeted()) {
			if (board->getMinions().at(i-1)->getActionsLeft() >= 1) {
                        	// use the activated ability
                        	if (magic >= cost || testing) {
                                	board->getMinions().at(i-1)->use(*this);
                                	magic -= cost;
                                	if (magic < 0) {
                                        	magic = 0;
                                	}
                        	} else {
					throw "Not enough magic to activate ability.";
				}
			} else {
				throw "That minion has no remaining actions this turn.";
			}
		} else if (board->getMinions().at(i-1)->getActiveCost() > 0) {
			throw "Specify a target for that minion's activated ability.";
		} else {
			throw "That minion does not have an activated ability.";
		}
	} else {
		// no remaining actions
                throw "Invalid Index.";
	}
}

void Player::use(unsigned int i, int p, unsigned int t) {
        unsigned int size = board->getMinions().size();
        if (size == 0) {
            	throw "You have no minions to use.";
        } else if (1 <= i && i <= size && (p == 1 || p == 2)) {
             	int cost = board->getMinions().at(i-1)->getActiveCost();
            	if (cost > 0 && board->getMinions().at(i-1)->getTargeted()) {
			if (board->getMinions().at(i-1)->getActionsLeft() >= 1) {
				// use minion activated ability
                        	if (magic >= cost || testing) {
                                	if (p == playernum){
                                   		 if (1 <= t && t <= board->getMinions().size()) {
                                        		board->getMinions().at(i-1)->use(*(board->getMinions().at(t-1)), *this); 
                                    		} else {
                                        		throw "Invalid Index";
                                    		}
                                	} else {
                                    		if (1 <= t && t <= opponent->getBoard()->getMinions().size()) {
                                        		board->getMinions().at(i-1)->use(*(opponent->getBoard()->getMinions().at(t-1)), *opponent);
                                    		} else {
                                        		throw "Invalid Index";
                                    		}
                                	}
                                	magic -= cost;
                               		if (magic < 0) {
                                        	magic = 0;
                                	}
             	        	} else {
					throw "Not enough magic.";
				}
			} else {
                		throw "That minion has no remaining actions this turn.";
             		}
		} else if (cost > 0) {
			throw "Do not specify a target for an untargeted activated ability.";
		} else {
			throw "That minion does not have an activated ability.";
		}
        } else {
           	throw "Invalid Index.";
        }
}


void Player::remove(unsigned int i){
        if(i == 'r'){
                if(board->getRitual()){
                        board->getRitual().reset();  
                        board->setRitual(nullptr);
                } else {
                        throw "No ritual in play";
                }
                
        } else {
            if ( 1 <= i && i <= getBoard()->getMinions().size()) {
                getBoard()->killMinion(i);
            } else {
                throw "Cannot remove minion that does not exist";
            }
        }
}


void Player::startTurn() {
        std::vector<std::shared_ptr<Minion>> minions = board->getMinions();
        std::vector<std::shared_ptr<Minion>>::iterator ptr; 
        for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
            (*ptr)->startTrigger(*this, *opponent);
        } 
        if(board->getRitual()){
                board->getRitual()->startTurn(*this, *(getLastMinionPlayed()));
                if (board->getRitual()->getCharge() <= 0) {
                    board->playRitual(nullptr);
                }
        }
}

void Player::endTurn() {
        std::vector<std::shared_ptr<Minion>> minions = board->getMinions();
        std::vector<std::shared_ptr<Minion>>::iterator ptr; 
        for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
            (*ptr)->endTrigger(*this, *opponent);
        } 

}

void Player::opponentBattlecry() {
        std::vector<std::shared_ptr<Minion>> minions = board->getMinions();
        std::vector<std::shared_ptr<Minion>>::iterator ptr; 
        for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
            (*ptr)->opponentMinionEnter(*this, *opponent);
        } 
        if(board->getRitual()){
                board->getRitual()->oppMinionEnter(*opponent, *opponent->getLastMinionPlayed());
                if (board->getRitual()->getCharge() <= 0) {
                    board->playRitual(nullptr);
                }
        }     
}

void Player::battlecry() {

        std::vector<std::shared_ptr<Minion>> minions = board->getMinions();
        std::vector<std::shared_ptr<Minion>>::iterator ptr; 
        for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
            (*ptr)->minionEnter(*this, *opponent);
        } 
        if(board->getRitual()){
                board->getRitual()->minionEnter(*this, *(getLastMinionPlayed()));
                if (board->getRitual()->getCharge() <= 0) {
                    board->playRitual(nullptr);
                }
        }
        opponent->opponentBattlecry();
}

void Player::deathrattle() {
        std::vector<std::shared_ptr<Minion>> minions = board->getMinions();
        std::vector<std::shared_ptr<Minion>>::iterator ptr; 
        for (ptr = minions.begin(); ptr < minions.end(); ptr++) {
            (*ptr)->minionLeave(*this, *opponent);
        } 

        std::vector<std::shared_ptr<Minion>> oppMinions = opponent->getBoard()->getMinions();
        for (ptr = oppMinions.begin(); ptr < oppMinions.end(); ptr++) {
            (*ptr)->minionLeave(*opponent, *this);
        } 

}
