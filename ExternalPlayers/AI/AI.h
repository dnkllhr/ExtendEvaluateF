#ifndef __AI_H
#define __AI_H

#include <typeinfo>
#include "FuzzyLogic.h"
#include "../../Core/BoardManager/BoardManager.h"
#include "../../Core/BoardRules/Regions.h"
#include "../../Core/Board/Board.h"

class AI
{
public:
    static Move chooseTurn(const Tile& currentTile);
    static void setPlayerNumber(unsigned int playerNumber);
#ifndef __testing
private:
#endif
    static FuzzyLogic fz;
    static AIMove move;
    static unsigned int myPlayerNumber;
};

#endif
