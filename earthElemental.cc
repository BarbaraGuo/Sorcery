#include "earthElemental.h"
#include "player.h"
#include "board.h"

EarthElemental::EarthElemental(int playerNum): 
    Minion{"Earth Elemental", "", 3, playerNum, 4, 4, 0} {
    setTargeted(false);
}
