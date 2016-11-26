#include "AI.h"


AI::AI()
{
    AI::fz = new FuzzyLogic;
    AI::move = new AIMove;
}

AI::~AI()
{
    delete fz;
    delete move;
}


Move& AI::chooseTurn(Tile& currentTile)
{
    std::vector<Move> moveList = BoardManager::getValidMoves(currentTile);

    auto highestIndex = moveList.begin();
    float highestValue = 0;

    float currentValue;
    for(auto currentMove = moveList.begin(); currentMove != moveList.end(); ++currentMove)
    {
        struct moveResult currentResult = Regions::tryMove(currentMove->getTile(), Board::getBorderingTiles(currentTile));

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
