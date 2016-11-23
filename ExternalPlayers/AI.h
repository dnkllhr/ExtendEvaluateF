#ifndef __AI_H
#define __AI_H


#include "FuzzyLogic.h"
//#include "path/to/TurnManger"

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