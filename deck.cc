#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "deck.h"
#include "banish.h"
#include "unsummon.h"
#include "recharge.h"
#include "disenchant.h"
#include "raiseDead.h"
#include "blizzard.h"
#include "airElemental.h"
#include "earthElemental.h"
#include "boneGolem.h"
#include "fireElemental.h"
#include "potionSeller.h"
#include "novicePyromancer.h"
#include "apprenticeSummoner.h"
#include "masterSummoner.h"
#include "giantStrength.h"
#include "enrage.h"
#include "haste.h"
#include "magicFatigue.h"
#include "silence.h"
#include "darkRitual.h"
#include "auraOfPower.h"
#include "standstill.h"

Deck::Deck(int playernum, std::vector<std::string> c) : playernum{playernum}  {
    for(auto line: c) {
        if (line == "Banish") {
            cards.emplace_back(std::move(std::make_shared<Banish>(playernum)));
        } else if (line ==  "Unsummon") {
            cards.emplace_back(std::move(std::make_shared<Unsummon>(playernum)));
        } else if (line ==  "Recharge") {
            cards.emplace_back(std::move(std::make_shared<Recharge>(playernum)));
        } else if (line == "Disenchant") {
            cards.emplace_back(std::move(std::make_shared<Disenchant>(playernum)));

        } else if (line == "Raise Dead") {
            cards.emplace_back(std::move(std::make_shared<RaiseDead>(playernum)));

        } else if (line == "Blizzard") {
            cards.emplace_back(std::move(std::make_shared<Blizzard>(playernum)));

        } else if (line == "Air Elemental") {
            cards.emplace_back(std::move(std::make_shared<AirElemental>(playernum)));

        } else if (line == "Earth Elemental") {
            cards.emplace_back(std::move(std::make_shared<EarthElemental>(playernum)));

        } else if (line == "Bone Golem") {
            cards.emplace_back(std::move(std::make_shared<BoneGolem>(playernum)));

        } else if (line == "Fire Elemental") {
            cards.emplace_back(std::move(std::make_shared<FireElemental>(playernum)));

        } else if (line == "Potion Seller") {
            cards.emplace_back(std::move(std::make_shared<PotionSeller>(playernum)));

        } else if (line == "Novice Pyromancer") {
            cards.emplace_back(std::move(std::make_shared<NovicePyromancer>(playernum)));

        } else if (line == "Apprentice Summoner") {
            cards.emplace_back(std::move(std::make_shared<ApprenticeSummoner>(playernum)));

        } else if (line == "Master Summoner") {
            cards.emplace_back(std::move(std::make_shared<MasterSummoner>(playernum)));

        } else if (line == "Giant Strength") {
            cards.emplace_back(std::make_shared<GiantStrength>(playernum));

        } else if (line == "Enrage") {
            cards.emplace_back(std::move(std::make_shared<Enrage>(playernum)));

        } else if (line == "Haste") {
            cards.emplace_back(std::move(std::make_shared<Haste>(playernum)));

        } else if (line == "Magic Fatigue") {
            cards.emplace_back(std::move(std::make_shared<MagicFatigue>(playernum)));

        } else if (line == "Silence") {
            cards.emplace_back(std::move(std::make_shared<Silence>(playernum)));

        } else if (line == "Dark Ritual") {
            cards.emplace_back(std::move(std::make_shared<DarkRitual>(playernum)));

        } else if (line == "Aura Of Power") {
            cards.emplace_back(std::move(std::make_shared<AuraOfPower>(playernum)));

        } else if (line == "Standstill") {
            cards.emplace_back(std::move(std::make_shared<Standstill>(playernum)));
        }

    }
}


int randomer(int i) { return rand()%i; }

void Deck::shuffle() {
	random_shuffle(cards.begin(), cards.end(), randomer);
}

std::vector<std::shared_ptr<Card>> Deck::getCards() {
    return cards;
}

bool Deck::isEmpty() {
	return cards.empty();
}

std::shared_ptr<Card> Deck::draw() {
    if (isEmpty()) {
        throw "Empty Deck.";
    } else {
        std::shared_ptr<Card> temp = cards.back();
	cards.pop_back();
	return temp;
    }
}


