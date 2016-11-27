#include "AI.h"

Move& AI::chooseTurn(Tile& currentTile)
{
    std::vector<Move> moveList = BoardManager::getValidMoves(currentTile);

    auto highestIndex = moveList.begin();
    float highestValue = 0;

    float currentValue;
    for(auto currentMove = moveList.begin(); currentMove != moveList.end(); ++currentMove)
    {
        struct moveResult currentResult = BoardManager::tryMove(currentMove->getTile());

        if(AI::myPlayerNumber == 1)
        {
            AI::move->edgesTillCompletion = currentResult.edgesTillCompletion;
            AI::move->diffMyScore = currentResult.player1ScoreChange;
            AI::move->diffEnemyScore = currentResult.player2ScoreChange;
        }
        else
        {
            AI::move->edgesTillCompletion = currentResult.edgesTillCompletion;
            AI::move->diffEnemyScore = currentResult.player1ScoreChange;
            AI::move->diffMyScore = currentResult.player2ScoreChange;
        }

        AI::fz->enterData(AI::move);
        currentValue = AI::fz->getResults();

        if(currentValue > highestValue)
        {
            highestValue = currentValue;
            highestIndex = currentMove;
        }
    }
    return moveList.at(highestIndex - moveList.begin()) ;
}


void AI::setPlayerNumber(unsigned int playerNumber)
{
    AI::myPlayerNumber = playerNumber;
}
