#include "../Core/BoardRules/Regions.h"
#include "../Core/Board/Board.h"
#include "../Core/BoardManager/BoardManager.h"

#include "gtest/gtest.h"

TEST(RegionTests, addConnection) {
    
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile *surroundingTiles[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}; //Init'd to NULL

    currentTile = &(Tile::CreateTileD(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(72,72); //Center
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);
    Regions::addConnection(currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 2); //Make sure the road has two sides open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 1); //Make sure the castle has one side open. 

    currentTile = &(Tile::CreateTileW(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(72,73); //
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileT(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(72,71); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileH(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(73,72); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileV(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(73,73); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileA(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(71,73); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileB(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(71,72); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileF(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(71,71); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);

    currentTile = &(Tile::CreateTileN(1, &startID, None)); //No prey, starting tile
    currentCoord = new Coord(73,71); //    
    currentMove = new Move(currentTile, currentCoord);
    Board::place(currentMove);
}