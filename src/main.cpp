#include <iostream>
#include "CGame.h"
#include "CDeck.h"
#include "CCard.h"
#include "CCreature.h"
#include "CWeapon.h"
#include "CSpell.h"
#include "CPLayer.h"
#include "CHuman.h"
#include "CComputer.h"

//class CDeck;

/**
 * @mainpage Terminal HearthStone
 * @section desc_sec Description
 * HearthStone based Card RPG in Terminal using c++.
 */


int main() {
    CGame newGame;
    newGame.InitGame();
    newGame.GameLoop();
    return 0;
}
