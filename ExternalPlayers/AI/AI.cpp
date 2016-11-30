#include "AI.h"


FuzzyLogic AI::fz;
AIMove AI::move;
unsigned int AI::myPlayerNumber;
#ifndef __testing
Move AI::chooseTurn(const Tile& currentTile)
{
    std::vector<Move> moveList = BoardManager::getValidMoves((Tile&)currentTile, AI::myPlayerNumber);

    auto highestIndex = moveList.begin();
    float highestValue = 0;

    float currentValue;
    for(auto currentMove = moveList.begin(); currentMove != moveList.end(); ++currentMove)
    {
        struct moveResult currentResult = BoardManager::tryMove(currentMove->getTile());

        if (AI::myPlayerNumber == 1)
        {
            AI::move.edgesTillCompletion = currentResult.edgesTillCompletion;
            AI::move.diffMyScore = currentResult.player1ScoreChange;
            AI::move.diffEnemyScore = currentResult.player2ScoreChange;
        }
        else
        {
            AI::move.edgesTillCompletion = currentResult.edgesTillCompletion;
            AI::move.diffEnemyScore = currentResult.player1ScoreChange;
            AI::move.diffMyScore = currentResult.player2ScoreChange;
        }

        AI::fz.enterData(AI::move);
        currentValue = AI::fz.getResults();

        if(currentValue > highestValue)
        {
            highestValue = currentValue;
            highestIndex = currentMove;
        }
    }
    return moveList.at(highestIndex - moveList.begin()) ;
}
#else
/*
struct moveResult
{
    unsigned int edgesTillCompletion;
    int player1ScoreChange;
    int player2ScoreChange;
};
*/
struct moveResult pseudoTryMove(int i)
{
    struct moveResult ret;
    ret.edgesTillCompletion = 10 - i;
    ret.player1ScoreChange = i;
    ret.player2ScoreChange = 10 - i;
    //printf("Randomized values: edgesTillCompletion %d player1ScoreChange %d player2ScoreChange %d\n", ret.edgesTillCompletion, ret.player1ScoreChange, ret.player2ScoreChange);
    return ret;
}

std::vector<Move> getMoveList()
{
    std::vector<Move> mvs;
    for(int i = 0; i < 10; i++)
    {
        Coord c = Coord(i, 2);
        //printf("Coord : %d %d\n", c.getX(), c.getY());
        Move m = Move(BoardManager::getTopTileStack(), c);
        mvs.push_back(m);
    }
    return mvs;
}


Move AI::chooseTurn(const Tile& currentTile)
{
    std::vector<Move> moveList = getMoveList();
    auto highestIndex = moveList.begin();
    float highestValue = 0;

    float currentValue;
    int i = 0;
    for(auto currentMove = moveList.begin(); currentMove != moveList.end(); ++currentMove)
    {
        struct moveResult currentResult = pseudoTryMove(i);

        if (AI::myPlayerNumber == 1)
        {
            AI::move.edgesTillCompletion = currentResult.edgesTillCompletion;
            AI::move.diffMyScore = currentResult.player1ScoreChange;
            AI::move.diffEnemyScore = currentResult.player2ScoreChange;
        }
        else
        {
            AI::move.edgesTillCompletion = currentResult.edgesTillCompletion;
            AI::move.diffEnemyScore = currentResult.player1ScoreChange;
            AI::move.diffMyScore = currentResult.player2ScoreChange;
        }

        AI::fz.enterData(AI::move);
        currentValue = AI::fz.getResults();

        //printf("Coord : %d %d\nscore :%4.4f\n", currentMove->getCoord().getX(), currentMove->getCoord().getY(), currentValue);

        if(currentValue > highestValue)
        {
            highestValue = currentValue;
            highestIndex = currentMove;
        }
        i++;
    }
    //printf("movelist.at() %d\n", (moveList.at(highestIndex - moveList.begin())).getCoord().getX());
    //std::cout << typeid(moveList.at(highestIndex - moveList.begin())).name() << '\n';

    Move ret = moveList.at(highestIndex - moveList.begin());
    return ret;
}
#endif


void AI::setPlayerNumber(unsigned int playerNumber)
{
    AI::myPlayerNumber = playerNumber;
}
