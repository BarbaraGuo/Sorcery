#include "airElemental.h"
#include "player.h"
#include "board.h"


AirElemental::AirElemental(int playerNum): 
    Minion{"Air Elemental", "", 0, playerNum, 1, 1, 0} {
    setTargeted(false);
}
