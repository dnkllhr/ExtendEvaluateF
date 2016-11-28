#include "../Core/BoardRules/Regions.h"
#include "../Core/Board/Board.h"
#include "../Core/BoardManager/BoardManager.h"
#include "../Core/BoardRules/Rules.h"

#include "gtest/gtest.h"

void testingTilePlacement(unsigned int *startID, unsigned int coordX, unsigned int coordY, Tile *currentTile, const Tile **surroundingTiles)
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
    const Tile **surroundingTiles; //Init'd to NULL



    currentTile = &(Tile::CreateTileD(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 2); //Make sure the road has two sides open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 1); //Make sure the castle has one side open. 




    currentTile = &(Tile::CreateTileW(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 1); //Make sure the top road has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 1); //Make sure the right road has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 1); //Make sure the left road has one side open. 




    currentTile = &(Tile::CreateTileT(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 7)) == 0); //Make sure the road has zero sides open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 1)) == 3); //Make sure the castle has three sides open. 




    currentTile = &(Tile::CreateTileH(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 2); //Make sure the right castle has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 1); //Make sure the left castle has zero sides open. 




    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 10)) == 1); //Make sure the road has one side open. 




    currentTile = &(Tile::CreateTileA(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 71, 73, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 0); //Make sure the road has one side open. 
    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 12)) == 5); //Make sure the church has fives sides open. 




    currentTile = &(Tile::CreateTileB(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 12)) == 3); //Make sure the church has three sides open. 




    currentTile = &(Tile::CreateTileF(1, startID, PreyType::None)[0]); //No prey, starting tile
    testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        assert(Regions::checkRegionExistence(currentTile->getID()), i);
    }

    assert((Regions::checkRegionEdgesTillCompletion(currentTile->getID(), 4)) == 3); //Make sure the castle has three sides open. 




    currentTile = &(Tile::CreateTileN(1, startID, PreyType::None)[0]); //No prey, starting tile
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
	actualScore = Rules::scoreChurch(tilesSurrounded, true);
	ASSERT(actualScore == 0);
	actualScore = Rules::scoreChurch(tilesSurrounded, false);
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
				actualScore = Rules::scoreChurch(tilesSurrounded, true);

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
				actualScore = Rules::scoreChurch(tilesSurrounded, false);
				ASSERT(actualScore == expectedScore);
			}
		}
	}
}

TEST(RulesTest, ScoreCastle1) {
	unsigned int startID = 0;
	Tile *currentTile;
	Move *currentMove;
	Coord *currentCoord;
	const Tile **surroundingTiles;

	currentTile = &(Tile::CreateTileD(1, startID, PreyType::Deer)[0]);
	currentTile->setRotation(0);
	testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
	currentTile->placeTile();

	unsigned int currentTileID = currentTile->getId();
	std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

	unsigned int actualScore = Rules::scoreCastle(currentSet, true);
	ASSERT(actualScore == 0);
	actualScore = Rules::scoreCastle(currentSet, false);
	ASSERT(actualScore == 2);

	// add another tile to extend the lake region
	currentTile = &(Tile::CreateTileK(1, startID, PreyType::Boar)[0]);
	currentTile->setRotation(2);
	testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTileID = currentTile->getId();
	currentSet = Regions::getRegions(currentTileID);

	actualScore = Rules::scoreCastle(currentSet, true);
	ASSERT(actualScore == 12);
	actualScore = Rules::scoreCastle(currentSet, false);
	ASSERT(actualScore == 12);

}

TEST(RulesTest, ScoreCastle2) {
	unsigned int startID = 0;
	Tile *currentTile;
	Move *currentMove;
	Coord *currentCoord;
	const Tile **surroundingTiles;

	currentTile = &(Tile::CreateTileI(1, startID, PreyType::None)[0]);
	currentTile->setRotation(0);
	testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTile = &(Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
	currentTile->setRotation(0);
	testingTilePlacement(&startID, 71, 73, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTile = &(Tile::CreateTileC(1, startID, PreyType::None)[0]);
	currentTile->setRotation(0);
	testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTile = &(Tile::CreateTileE(1, startID, PreyType::None)[0]);
	currentTile->setRotation(0);
	testingTilePlacement(&startID, 72, 74, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTile = &(Tile::CreateTileN(1, startID, PreyType::None)[0]);
	currentTile->setRotation(3);
	testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);
	currentTile->placeTile();

	unsigned int currentTileID = currentTile->getId();
	std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

	unsigned int actualScore = Rules::scoreCastle(currentSet, true);
	ASSERT(actualScore == 0);
	actualScore = Rules::scoreCastle(currentSet, false);
	ASSERT(actualScore == 10);
	
	currentTile = &(Tile::CreateTileN(1, startID, PreyType::None)[0]);
	currentTile->setRotation(2);
	testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTileID = currentTile->getId();
	currentSet = Regions::getRegions(currentTileID);

	actualScore = Rules::scoreCastle(currentSet, true);
	ASSERT(actualScore == 24);
	actualScore = Rules::scoreCastle(currentSet, false);
	ASSERT(actualScore == 24);
}

TEST(RulesTest, scoreRoad)
{
    //Testing a completed road that forms a perfect square. Starts and ends on the same tile.
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    const Tile **surroundingTiles;

    // test four 'v' tiles placed so that road is closed square. No prey so should be awarded 4 points.
    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    //upperRightTile
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72,72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    //upperLeftTile
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    //bottomLeftTile
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    //bottomRightTile
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    // not sure what to pass through for bool actuallyScore
    unsigned int returnScore = Rules::scoreRoad(currentSet);

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
    const Tile **surroundingTiles;

    //this creates a complete castle, so grass should be 5 pts
    currentTile = &(Tile::CreateTileZ(1, startID, PreyType::None)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileG(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileE(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 69, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileA(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    // get score for Grass in this set of 4 tiles that is placed together
    unsigned int returnGrassScore = Rules::scoreGrass(currentSet, currentTileID, 10);
   // get score for the completed road  in this set of 4 tiles placed together
    unsigned int returnRoadScore = Rules::ad(currentSet);
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
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileB(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 71, 73), currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 71, 73), currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileW(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileY(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileE(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileZ(1, startID, PreyType::None)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();


    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    unsigned int returnGrassScore = Rules::scoreGrass(currentSet, currentTileID, 10);
    unsigned int realGrassScore = 8; //5 pt for completed lake + 3 pts for completed den

    ASSERT_EQ(returnGrassScore, realGrassScore);
}

TEST(RulesTest, scoreMoreRoads)
{
    //Testing incomplete road with prey animals
    unsigned int startID = 0;
    Tile *currentTile;
    Move *currentMove;
    Coord *currentCoord;
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileZ(1, startID, PreyType::Deer)[0]);
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileK(1, startID, PreyType::Boar)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 74, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getId();

    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    unsigned int returnRoadScore = Rules::scoreRoad(currentSet);

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
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileA(1, startID, PreyType::None)[0]);
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileA(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getId();

    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    unsigned int returnRoadScore = Rules::scoreRoad(currentSet);

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
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73,72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileA(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73,70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72,70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 74,72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 74,70, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileD(1, &startId, PreyType::Deer)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 74,71, currentTile, surroundingTiles);
    currentTile->placeTile();

    //Testing road portion of this landscape
    unsigned int currentTileId = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

    unsigned int returnRoadScore = Rules::scoreRoad(currentSet);

    unsigned int realRoadScore = 6;

    ASSERT_EQ(realRoadScore, returnRoadScore);

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile.setRotation(1);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile.placeTile();

    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet2 = Regions::getRegions(currentTileID);

    unsigned int return returnRoadScore2 = Rules::scoreRoad(currentSet2);
    unsigned int returnGrassScore = Rules::scoreGrass(currentSet2, currentTileID, 7);
    unsigned int realRoadScore2 = 5;
    unsigned int realGrassScore  3;
    ASSERT_EQ(realRoadScore2, returnRoadScore2);
    ASSERT_EQ(realGrassScore, returnGrassScore);

}

TEST(RulesTest, getCurrentScore) {
	unsigned int startID = 0;
	Tile *currentTile;
	Move *currentMove;
	Coord *currentCoord;
	const Tile **surroundingTiles;

	currentTile = &(Tile::CreateTileD(1, startID, PreyType::None)[0]);
	currentTile->setRotation(0);
	testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
	currentTile->placeTile();

	unsigned int currentTileId = currentTile->getId();
	std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

	unsigned int edge = 4; // uncompleted city on right side of tile
	unsigned int tilesSurrounded = BoardManager::isSurrounded(currentTileId);

	unsigned int actualScore = Rules::getCurrentScore(currentSet, edge, currentTile, tilesSurrounded);
	unsigned int expectedScore = 1; // uncompleted city on right side of tile

	ASSERT_EQ(actualScore, expectedScore);

	currentTile = &(Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
	currentTile->setRotation(2);
	testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
	currentTile->placeTile();

	currentTileId = currentTile->getId();
	currentSet = Regions::getRegions(currentTileId);
	edge = 10; // test left side of tile
	tilesSurrounded = BoardManager::isSurrounded(currentTileId);

	actualScore = Rules::getCurrentScore(currentSet, edge, currentTile, tilesSurrounded);
	expectedScore = 8; // 8 points for a completed city adjacent to 1 unique prey

	ASSERT_EQ(actualScore, expectedScore);
}

TEST(RulesTest, validTilePlacement)
{
    BoardManager::gameInit();

    unsigned int tileIdCounter = 100;


    Tile tile = Tile::CreateTileJ(1, tileIdCounter, PreyType::None)[0];


    const Coord left = Coord(75, 76);
    const Coord right = Coord(77, 76);
    const Coord up = Coord(76, 77);
    const Coord down = Coord(76, 75);

    tile.setRotation(0);
    std::cout << std::endl << "left ";
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left))) { std::cout <<  "0 "; }
    tile.setRotation(1);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left))) { std::cout <<  "1 "; }
    tile.setRotation(2);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left))) { std::cout <<  "2 "; }
    tile.setRotation(3);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left))) { std::cout <<  "3 "; }

    tile.setRotation(0);
    std::cout << std::endl << "right ";
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right))) { std::cout <<  "0 "; }
    tile.setRotation(1);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right))) { std::cout <<  "1 "; }
    tile.setRotation(2);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right))) { std::cout <<  "2 "; }
    tile.setRotation(3);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right))) { std::cout <<  "3 "; }

    tile.setRotation(0);
    std::cout << std::endl << "up ";
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up))) { std::cout <<  "0 "; }
    tile.setRotation(1);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up))) { std::cout <<  "1 "; }
    tile.setRotation(2);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up))) { std::cout <<  "2 "; }
    tile.setRotation(3);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up))) { std::cout <<  "3 "; }

    tile.setRotation(0);
    std::cout << std::endl << "down ";
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down))) { std::cout <<  "0 "; }
    tile.setRotation(1);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down))) { std::cout <<  "1 "; }
    tile.setRotation(2);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down))) { std::cout <<  "2 "; }
    tile.setRotation(3);
    if(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down))) { std::cout <<  "3 "; }

    /*
    Tile tile2 = Tile::CreateTileV(1, tileIdCounter, PreyType::None)[0];
    Coord coord2 = Coord(77, 75);
    Move move2 = Move(tile2, coord2);

    

    Tile tile3 = Tile::CreateTileK(1, tileIdCounter, PreyType::None)[0];
    Coord coord3 = Coord(77, 76);
    Move move3 = Move(tile3, coord3, 2);*/
}