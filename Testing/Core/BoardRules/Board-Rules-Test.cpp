#include "../Core/BoardRules/Regions.h"
#include "../Core/Board/Board.h"
#include "../Core/BoardManager/BoardManager.h"
#include "../Core/BoardRules/Rules.h"

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
	Coord center(76, 76);
	Tile& churchTile = tiles[0][0];
	Move churchMove(churchTile, center);
	board.place(churchMove);

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
				Coord churchBoarder((center.getX() + i), (center.getY() + j));
				Tile& boarderingTile = tiles[24][0]; // chose to surround with field tiles
				Move boarderMove(boarderingTile, churchBoarder);
				board.place(boarderMove);

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

TEST(RulesTest, ScoreCastle) {
	Array<Array<Tile>> tiles = Tile::CreateTiles();
	Board board;
	unsigned int actualScore;

	Tile& castleTile1 = tiles[4][0];
	unsigned int tileID1 = castleTile1.getId();
	Coord position1(76, 76);
	Move castleMove1(castleTile1, position1);
	board.place(castleMove1);
	std::shared_ptr<struct regionSet> newRegion(Regions::getRegions(tileID1));

	// How should actuallyScore change the return value?
	actualScore = scoreCastle(newRegion, true);
	ASSERT(actualScore == 0);
	actualScore = scoreCastle(newRegion, false);
	ASSERT(actualScore == 2);

	// add another tile to extend the lake region
	Tile& castleTile2 = tiles[12][0];
	bool rotate = setRotation(2);
	unsigned int tileID2 = castleTile2.getId();
	Coord position2(77, 77);
	Move castleMove2(castleTile2, position2);
	board.place(castleMove2);
	newRegion.reset(Regions::getRegions(tileID2));

	// How should actuallyScore change the return value?
	actualScore = scoreCastle(newRegion, true);
	ASSERT(actualScore == 12);
	actualScore = scoreCastle(newRegion, false);
	ASSERT(actualScore == 12);
}

Test(RulesTest, scoreRoad)
{
    //Testing a completed road that forms a perfect square. Starts and ends on the same tile.
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles;

    // test four 'v' tiles placed so that road is closed square. No prey so should be awarded 4 points.
    currentTile = &(Tile::CreateTileV(1, &startID, None));
    //upperRightTile
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72,72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    //upperLeftTile
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None);
    //bottomLeftTile
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    //bottomRightTile
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getTileId();
    shared_ptr<struct regionSet> currentSet = getRegions(currentTileID);

    // not sure what to pass through for bool actuallyScore
    unsigned int returnScore = scoreRoad(currentSet);

    //completed road = 1 pt per tile
    unsigned int realScore = 4;

    ASSERT_EQ(realScore, returnScore);

}

TEST(RulesTest, scoreGrassAndRoad)
{
    //Testing grass next to completed castle/lake and incomplete den
    //Testing complete road that starts with den and ends with castle
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles;

    //this creates a complete castle, so grass should be 5 pts
    currentTile = &(Tile::CreateTileZ(1, &startID, None));
    currentTile->setRotation(2);
    testingTilePlacement(&startId, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileG(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileE(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 69, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileA(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getTileId();
    shared_ptr<struct regionSet> currentSet = getRegions(currentTileID);

    // get score for Grass in this set of 4 tiles that is placed together
    unsigned int returnGrassScore = scoreGrass(currentSet, currentTileID, 10);
   // get score for the completed road  in this set of 4 tiles placed together
    unsigned int returnRoadScore = scoreRoad(currentSet);
    unsigned int realGrassScore = 5;
    unsigned int realRoadScore = 2;

    ASSERT_EQ(realGrassScore, returnGrassScore);
    ASSERT_EQ(realRoadScore, returnRoadScore);
}

TEST(RulesTest, scoreMoreGrass)
{
    //Testing grass next to completed den and completed lake
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileB(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(2)
    testingTilePlacement(&startID, 71, 73), currentTile, surroundingTiles);
    currentTile->placeTile()

    currentTile = &(Tile::CreateTileU(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 71, 73), currentTile, surroundingTiles);
    currentTile->placeTile()

    currentTile = &(Tile::CreateTileW(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileY(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startId, 71, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileE(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 71);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileZ(1, &startID, None));
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();


    unsigned int currentTileID = currentTile->getTileId();
    shared_ptr<struct regionSet> currentSet = getRegions(currentTileID);

    unsigned int returnGrassScore = scoreGrass(currentSet, currentTileID, 10);
    int realGrassScore = 8; //5 pt for completed lake + 3 pts for completed den

    ASSERT_EQ(returnGrassScore, realGrassScore);
}

TEST(RulesTest, scoreMoreRoads)
{
    //Testing incomplete road with prey animals
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileZ(1, &startID, Deer));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileK(1, &startID, Boar));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile:CreateTileU(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&tartID, 74, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileJ(1, &startID, Buffalo));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getTileId();

    shared_ptr<struct regionSet> currentSet = getRegions(currentTileID);

    unsigned int returnRoadScore = scoreRoad(currentSet);

    unsigned int realRoadScore = 7;

    ASSERT_EQ(realRoadScore, returnRoadScore);
}

TEST (RulesTest, scoreMoreMoreRoads)
{
    //Testing complete road that starts with den and ends with den and has prey animals
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileA(1, &startID, None));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileJ(1, &startID, Buffalo));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileA(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getTileId();

    shared_ptr<struct regionSet> currentSet = getRegions(currentTileID);

    unsigned int returnRoadScore = scoreRoad(currentSet);

    unsigned int realRoadScore = 5;

    ASSERT_EQ(realRoadScore, returnRoadScore);
}

TEST(RulesTest, scoreGrassWithJustCompleteDen)
{
    //Testing grass next to completed den but incomplete lake
    //Testing two different incomplete sets of roads
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileJ(1, &startID, Buffalo));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73,72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileA(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73,70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72,70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 74,72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 74,70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileD(1, &startId, Deer));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 74,71, currentTile, surroundingTiles);
    currentTile->placeTile();

    //Testing road portion of this landscape
    unsigned int currentTileId = currentTile->getTileId();
    shared_ptr<struct regionSet> currentSet = getRegions(currentTileId);

    unsigned int returnRoadScore = scoreRoad(currentSet);

    unsigned int realRoadScore = 6;

    ASSERT_EQ(realRoadScore, returnRoadScore);

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile.setRotation(1);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile.placeTile();

    unsigned int currentTileID = currentTile->getTileId();
    shared_ptr<struct regionSet> currentSet2 = getRegions(currentTileID);

    unsigned int return returnRoadScore2 = scoreRoad(currentSet2);
    unsigned int returnGrassScore = scoreGrass(currentSet2, currentTileID, 7);
    unsigned int realRoadScore2 = 5;
    unsigned int realGrassScore  3;
    ASSERT_EQ(realRoadScore2, returnRoadScore2);
    ASSERT_EQ(realGrassScore, returnGrassScore);

}

