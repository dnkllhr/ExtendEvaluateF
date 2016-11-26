#include "TurnCoordinator.h"

//Main functionality is to receive messages from the external game client and tell the AI when to take a turn.
//It will also call the BoardManager to update opponent moves.

TurnCoordinator::TurnCoordinator()
{
    TurnCoordinator::AISetup = false;
    TurnCoordinator::AIPlayerNumber = 0;
}

void TurnCoordinator::setUpAI()
{
    if(TurnCoordinator::AIPlayerNumber == 0)
    {
        throw std::logic_error("Trying to setup the AI before you know which player it is.");
    }
    AI::setPlayerNumber(AIPlayerNumber);
}

void TurnCoordinator::callAI(Tile& tile)
{
    if(!TurnCoordinator::AISetup)
    {
        if(TurnCoordinator::AIPlayerNumber == 0)
        {
            throw std::logic_error("Trying to call the AI before you know which player it is.");
        }
        TurnCoordinator::setUpAI();
    }
    Move chosenMove = AI::chooseTurn(tile);
    BoardManager::makeMove(chosenMove);
}

