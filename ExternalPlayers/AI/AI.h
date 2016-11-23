#ifndef __AI_H
#define __AI_H


#include "FuzzyLogic.h"
#include "../TurnManger/TurnManager.h"

class AI
{
public:
    static int chooseTurn(struct ValidMoves *v);
    static AI();
    static ~AI();
private:
    FuzzyLogic *fz;
    AIMove *move;
};

#endif