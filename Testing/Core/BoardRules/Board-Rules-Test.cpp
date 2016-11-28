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
	Array<Array<Tile>> tiles = Tile::CreateTiles();
	Board board;
	unsigned int actualScore;

	const Tile *castleTile1 = tiles[4][0];
	unsigned int tileID1 = castleTile1.getId();
	Coord *position1 = new Coord(76, 76);
	Move *castleMove1 = new Move(castleTile1, position1);
	Board::place(castleMove1);
	std::shared_ptr<struct regionSet> *newRegion(Regions::getRegions(tileID1));

	// How should actuallyScore change the return value?
	actualScore = Rules::scoreCastle(newRegion, true);
	ASSERT(actualScore == 0);
	actualScore = Rules::scoreCastle(newRegion, false);
	ASSERT(actualScore == 2);

	// add another tile to extend the lake region
	const Tile *castleTile2 = tiles[12][0];
	castleTile2->setRotation(2);
	unsigned int tileID2 = castleTile2.getId();
	Coord *position2 = new Coord(77, 77);
	Move *castleMove2(castleTile2, position2);
	Board::place(castleMove2);
	Tile** surroundingTiles = Board::getBorderingTiles(castleTile2);
	Regions::addConnection(castleTile2, surroundingTiles);

	// How should actuallyScore change the return value?
	actualScore = Rules::scoreCastle(newRegion, true);
	ASSERT(actualScore == 12);
	actualScore = Rules::scoreCastle(newRegion, false);
	ASSERT(actualScore == 12);
}

TEST(RulesTest, ScoreCastle2) {
	Array<Array<Tile>> tiles = Tile::CreateTiles();
	unsigned int actualScore;

	const Tile *castleTile1 = tiles[8][0];
	unsigned int tileID1 = castleTile1.getId();
	Coord *position1 = new Coord(76, 76);
	Move *castleMove1 = new Move(castleTile1, position1);
	Board::place(castleMove1);
	std::shared_ptr<struct regionSet> *newRegion(Regions::getRegions(tileID1)); // create new region for the first tile placed

	// anotha one
	const Tile *castleTile2 = tiles[10][0];
	Coord *position2 = new Coord(75, 77);
	Move *castleMove2 = new Move(castleTile2, position2);
	Board::place(castleMove2);
	Tile** surroundingTiles = Board::getBorderingTiles(castleTile2);
	Regions::addConnection(castleTile2, surroundingTiles);

	// anotha one
	const Tile *castleTile3 = tiles[2][0];
	Coord *position3 = new Coord(76, 77);
	Move *castleMove3 = new Move(castleTile3, position3);
	Board::place(castleMove3);
	surroundingTiles = Board::getBorderingTiles(castleTile3);
	Regions::addConnection(castleTile3, surroundingTiles);

	// anotha one
	const Tile *castleTile4 = tiles[5][0];
	Coord *position4 = new Coord(76, 78);
	Move *castleMove4 = new Move(castleTile4, position4);
	Board::place(castleMove4);
	surroundingTiles = Board::getBorderingTiles(castleTile4);
	Regions::addConnection(castleTile4, surroundingTiles);

	// anotha one
	const Tile *castleTile5 = tiles[15][0];
	castleTile5->setRotation(3);
	Coord *position5 = new Coord(77, 77);
	Move *castleMove5 = new Move(castleTile5, position5);
	Board::place(castleMove5);
	surroundingTiles = Board::getBorderingTiles(castleTile5);
	Regions::addConnection(castleTile5, surroundingTiles);

	actualScore = Rules::scoreCastle(newRegion, true);
	ASSERT(actualScore == 0);
	actualScore = Rules::scoreCastle(newRegion, false);
	ASSERT(actualScore == 10);

	// anotha one
	const Tile *castleTile6 = tiles[15][0];
	Coord *position6 = new Coord(77, 76);
	Move *castleMove6 = new Move(castleTile6, position6);
	Board::place(castleMove6);
	surroundingTiles = Board::getBorderingTiles(castleTile6);
	Regions::addConnection(castleTile6, surroundingTiles);

	actualScore = Rules::scoreCastle(newRegion, true);
	ASSERT(actualScore == 24);
	actualScore = Rules::scoreCastle(newRegion, false);
	ASSERT(actualScore == 24);
}

TEST(RulesTest, scoreRoad)
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
    Tile **surroundingTiles;

    //this creates a complete castle, so grass should be 5 pts
    currentTile = &(Tile::CreateTileZ(1, &startID, None));
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
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
    Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileB(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 71, 73), currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, &startID, None));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 71, 73), currentTile, surroundingTiles);
    currentTile->placeTile();

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
    testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileE(1, &startID, None));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileZ(1, &startID, None));
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
    Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileZ(1, &startID, Deer));
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileK(1, &startID, Boar));
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, &startID, None));
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 74, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileJ(1, &startID, Buffalo));
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
    unsigned int currentTileId = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

    unsigned int returnRoadScore = Rules::scoreRoad(currentSet);

    unsigned int realRoadScore = 6;

    ASSERT_EQ(realRoadScore, returnRoadScore);

    currentTile = &(Tile::CreateTileV(1, &startID, None));
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
	Tile **surroundingTiles;

	currentTile = &(Tile::CreateTileD(1, &startID, None));
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

	currentTile = &(Tile::CreateTileJ(1, &startID, Buffalo));
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