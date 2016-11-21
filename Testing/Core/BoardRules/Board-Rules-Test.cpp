#include "../Core/BoardRules/Regions.h"
#include "../Core/Board/Board.h"
#include "../Core/BoardManager/BoardManager.h"

#include "gtest/gtest.h"

void testingTilePlacement(unsigned int *startID, unsigned int coordX, unsigned int coordY, Tile *currentTile, Tile **surroundingTiles)
{
    Coord *currentCoord = new Coord(coordX, coordY); //Center
    Move *currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);
    surroundingTiles = Board::getBorderingTiles(currentTile);
    Regions::addConnection(currentTile, surroundingTiles);
}

TEST(RegionTests, addConnection) {
    
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles; //Init'd to NULL



    currentTile = &(Tile::CreateTileD(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 2); //Make sure the road has two sides open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 1); //Make sure the castle has one side open. 




    currentTile = &(Tile::CreateTileW(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 1); //Make sure the top road has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 1); //Make sure the right road has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 1); //Make sure the left road has one side open. 




    currentTile = &(Tile::CreateTileT(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 7)) == 0); //Make sure the road has zero sides open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 3); //Make sure the castle has three sides open. 




    currentTile = &(Tile::CreateTileH(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 2); //Make sure the right castle has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 1); //Make sure the left castle has zero sides open. 




    currentTile = &(Tile::CreateTileV(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 1); //Make sure the road has one side open. 




    currentTile = &(Tile::CreateTileA(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 71, 73, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 0); //Make sure the road has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 12)) == 5); //Make sure the church has fives sides open. 




    currentTile = &(Tile::CreateTileB(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 12)) == 3); //Make sure the church has three sides open. 




    currentTile = &(Tile::CreateTileF(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 3); //Make sure the castle has three sides open. 




    currentTile = &(Tile::CreateTileN(1, &startID, None)); //No prey, starting tile
    testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 3); //Make sure the castle has three sides open. 
}