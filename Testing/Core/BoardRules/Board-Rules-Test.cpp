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

TEST(RulesTest, ScoreChurch) {
	Array<Array<Tile>> tiles = Tile::CreateTiles();
	Board board;
	// Church is worth 1 point regardless of surrounding tiles
	unsigned int expectedScore = 1;
	unsigned int actualScore;

	// Place church tile in center
	Tile& churchTile = tiles[0][0];
	Coord *center = new Coord(76, 76);
	Move *churchMove = new Move(churchTile, center);
	Board::place(churchMove);
	Tile **surroundingTiles = Board::getBorderingTiles(churchTile);
	Regions::addConnection(churchTile, surroundingTiles);

	unsigned int tileID = churchTile.getID();
	unsigned int tilesSurrounded = isSurrounded(tileID);

	// how should actuallyScore change the values returned?
	actualScore = scoreChurch(tilesSurrounded, true);
	ASSERT(actualScore == 0);
	actualScore = scoreChurch(tilesSurrounded, false);
	ASSERT(actualScore == 1);

	//place other tiles around churchTile
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
			{
				break; // avoid overwriting church tile
			}
			else
			{
				Tile& borderingTile = tiles[24][0];
				Coord *churchBorder = new Coord((center.getX() + i), (center.getY() + j));
				Move *borderMove = new Move(borderingTile, churchBorder);
				Board::place(borderMove);
				surroundingTiles = Board::getBorderingTiles(churchBorder);
				Regions::addConnection(churchBorder, surroundingTiles);

				expectedScore++;
				tilesSurrounded = isSurrounded(tileID);

				// how should actuallyScore change values returned?
				actualScore = scoreChurch(tilesSurrounded, true);

				// just placed final boardering tile, actuallyScore set to true should return full value
				if (i == 1 && j == 1)
				{
					ASSERT(actualScore == expectedScore)
				}

				// church isn't completely surrounded, actuallyScore set to true should return 0
				else
				{
					ASSERT(actualScore == 0);
				}
				actualScore = scoreChurch(tilesSurrounded, false);
				ASSERT(actualScore == expectedScore);
			}
		}
	}
}

TEST(RulesTest, ScoreCastle1) {
	Array<Array<Tile>> tiles = Tile::CreateTiles();
	Board board;
	unsigned int actualScore;

	Tile& castleTile1 = tiles[4][0];
	unsigned int tileID1 = castleTile1.getId();
	Coord *position1 = new Coord(76, 76);
	Move *castleMove1 = new Move(castleTile1, position1);
	Board::place(castleMove1);
	std::shared_ptr<struct regionSet> newRegion(Regions::getRegions(tileID1));

	// How should actuallyScore change the return value?
	actualScore = scoreCastle(newRegion, true);
	ASSERT(actualScore == 0);
	actualScore = scoreCastle(newRegion, false);
	ASSERT(actualScore == 2);

	// add another tile to extend the lake region
	Tile& castleTile2 = tiles[12][0];
	castleTile2.setRotation(2);
	unsigned int tileID2 = castleTile2.getId();
	Coord *position2 = new Coord(77, 77);
	Move *castleMove2(castleTile2, position2);
	Board::place(castleMove2);
	Tile** surroundingTiles = Board::getBorderingTiles(castleTile2);
	Regions::addConnection(castleTile2, surroundingTiles);

	// How should actuallyScore change the return value?
	actualScore = scoreCastle(newRegion, true);
	ASSERT(actualScore == 12);
	actualScore = scoreCastle(newRegion, false);
	ASSERT(actualScore == 12);
}

TEST(RulesTest, ScoreCastle2) {
	Array<Array<Tile>> tiles = Tile::CreateTiles();
	unsigned int actualScore;

	Tile& castleTile1 = tiles[8][0];
	unsigned int tileID1 = castleTile1.getId();
	Coord *position1 = new Coord(76, 76);
	Move *castleMove1 = new Move(castleTile1, position1);
	Board::place(castleMove1);
	std::shared_ptr<struct regionSet> newRegion(Regions::getRegions(tileID1)); // create new region for the first tile placed

	Tile& castleTile2 = tiles[10][0];
	Coord *position2 = new Coord(75, 77);
	Move *castleMove2 = new Move(castleTile2, position2);
	Board::place(castleMove2);
	Tile** surroundingTiles = Board::getBorderingTiles(castleTile2);
	Regions::addConnection(castleTile2, surroundingTiles);

	Tile& castleTile3 = tiles[2][0];
	Coord *position3 = new Coord(76, 77);
	Move *castleMove3 = new Move(castleTile3, position3);
	Board::place(castleMove3);
	surroundingTiles = Board::getBorderingTiles(castleTile3);
	Regions::addConnection(castleTile3, surroundingTiles);

	Tile& castleTile4 = tiles[5][0];
	Coord *position4 = new Coord(76, 78);
	Move *castleMove4 = new Move(castleTile4, position4);
	Board::place(castleMove4);
	surroundingTiles = Board::getBorderingTiles(castleTile4);
	Regions::addConnection(castleTile4, surroundingTiles);

	Tile& castleTile5 = tiles[15][0];
	castleTile5.setRotation(3);
	Coord *position5 = new Coord(77, 77);
	Move *castleMove5 = new Move(castleTile5, position5);
	Board::place(castleMove5);
	surroundingTiles = Board::getBorderingTiles(castleTile5);
	Regions::addConnection(castleTile5, surroundingTiles);

	// still pass newRegion to scoreCastle function?
	actualScore = scoreCastle(newRegion, true);
	ASSERT(actualScore == 0);
	actualScore = scoreCastle(newRegion, false);
	ASSERT(actualScore == 10);

	Tile& castleTile6 = tiles[15][0];
	Coord *position6 = new Coord(77, 76);
	Move *castleMove6 = new Move(castleTile6, position6);
	Board::place(castleMove6);
	surroundingTiles = Board::getBorderingTiles(castleTile6);
	Regions::addConnection(castleTile6, surroundingTiles);

	// still pass newRegion to scoreCastle function?
	actualScore = scoreCastle(newRegion, true);
	ASSERT(actualScore == 24);
	actualScore = scoreCastle(newRegion, false);
	ASSERT(actualScore == 24);
}