#include "AI.h"


AI::AI()
{
    this->fz = new FuzzyLogic;
    this->move = new AIMove;
}

AI::~AI()
{
    delete fz;
    delete move;
}


int AI::chooseTurn(struct ValidMoves *v)
{
    int highestIndex = 0;
    float highestValue = 0;

    float currentValue;
    for(int i = 0; i < v->numMoves; i++)
    {
        this->move = &(TurnManager::tryMove(v->moveList[i]));
        this->fz->enterData(this->move);
        currentValue = this->fz->getResults();
        if(currentValue > highestValue)
        {
            highestValue = currentValue;
            highestIndex = i;
        }
    }
    return highestIndex;
}