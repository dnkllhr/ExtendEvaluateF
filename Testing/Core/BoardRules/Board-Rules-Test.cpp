#include "../Core/BoardRules/Regions.h"
#include "../Core/Board/Board.h"
#include "../Core/BoardManager/BoardManager.h"
#include "../Core/BoardRules/Rules.h"

#include "gtest/gtest.h"

void testingTilePlacement(unsigned int *startID, unsigned int coordX, unsigned int coordY, Tile* currentTile, const Tile **surroundingTiles)
{
    Coord *currentCoord = new Coord(coordX, coordY); //Center
    Move *currentMove = new Move(*currentTile, *currentCoord);
    Board::place(*currentMove);
    surroundingTiles = Board::getBorderingTiles(*currentTile);
    Regions::addConnection(*currentTile, surroundingTiles);
}

TEST(RegionTests, mergeRegions) 
{
    std::shared_ptr<struct regionSet> r1 = std::shared_ptr<struct regionSet>(new regionSet);
    std::shared_ptr<struct regionSet> r2 = std::shared_ptr<struct regionSet>(new regionSet);

    r1->edgesTillCompletion = 4;
    std::shared_ptr<struct tileNode> currentNode = std::shared_ptr<struct tileNode>(new tileNode);
    r1->head = currentNode;

    std::shared_ptr<struct regionSet > *regionArray = new std::shared_ptr< struct regionSet>[13];
    for(int i = 0; i < 13; i++)
    {
        //printf("TileNode %d at %X\n", i, currentNode.get());
        currentNode->tileID = i;
        currentNode->edge = i;
        if (i + 1 < 13)
        {
            currentNode->next = std::shared_ptr<struct tileNode>(new tileNode);
            currentNode = currentNode->next;
        }

        Regions::regionTracker[i] = regionArray;
        regionArray[i] = r1;
    }
    r1->tail = currentNode;

    r2->edgesTillCompletion = 2;
    r2->head = std::shared_ptr<struct tileNode>(new tileNode);
    currentNode = r2->head;
    regionArray = new std::shared_ptr< struct regionSet>[13];
    for(int i = 0; i < 13; i++)
    {
        //printf("TileNode %d at %X\n", i + 13, currentNode.get());
        currentNode->tileID = i + 13;
        currentNode->edge = i;
        if (i + 1 < 13)
        {
            currentNode->next = std::shared_ptr<struct tileNode>(new tileNode);
            currentNode = currentNode->next;
        }

        Regions::regionTracker[i + 13] = regionArray;   
        regionArray[i] = r2;
    }
    r2->tail = currentNode;

    unsigned int preMergeTotalEdges = r1->edgesTillCompletion + r2->edgesTillCompletion;
    //printf("r1 : %X r2 : %x\n", r1.get(), r2.get());
    Regions::mergeRegions(0, 0, 13, 0);

    EXPECT_EQ(Regions::regionTracker[0][0], r2);
    EXPECT_EQ(Regions::regionTracker[13][0], r2);    
    EXPECT_NE(r1->head.get(), r2->head.get());
    EXPECT_EQ(r1->tail.get(), r2->tail.get());
    EXPECT_EQ(r2->edgesTillCompletion, preMergeTotalEdges);

}

TEST(RegionTests, addConnection) {

    BoardManager::gameInit();
    unsigned int startID = 10;
    //Tile currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles = NULL; //Init'd to NULL

    unsigned int centerID = Board::get(Coord(76,76))->getId();
    /*
    printf("centerID : %d\n", centerID);

    for(int i = 0; i < 12; i++)
    {
        printf("edge : %d edgesTillCompletion : %d\n", i, Regions::regionTracker[centerID][i]->edgesTillCompletion);
    }
    */


    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(centerID, 1)), 2); //Make sure the road has two sides open.

    Tile tileW = (Tile::CreateTileW(1, startID, PreyType::None)[0]); //No prey, starting tile
    Tile * currentTile = &tileW;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(76, 75)), 1);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 1)), 1); //Make sure the top road has one side open.
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 7)), 1); //Make sure the right road has one side open.
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 10)), 1); //Make sure the left road has one side open.

    Tile tileT = (Tile::CreateTileT(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileT;
    //testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(75, 75), 1), 1);


    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
         EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 4)), 0); //Make sure the road has zero sides open.
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 10)), 3); //Make sure the castle has three sides open.

    Tile tileH = (Tile::CreateTileH(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileH;
    //testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(77, 75)), 1);
    //std::cout << currentTile->getTileName() << std::endl;


    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));

    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 1)),1); //Make sure the right castle has one side open.
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 7)),1); //Make sure the left castle has zero sides open.

    Tile tileV = (Tile::CreateTileV(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileV;
    //testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(76, 74), 1), 1);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }
    
    std::cout << currentTile->getTileName() << std::endl;

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 4)), 1); //Make sure the road has one side open.

    Tile tileA = (Tile::CreateTileA(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileA;
    //testingTilePlacement(&startID, 71, 73, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(76, 77)), 1);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 7)),0); //Make sure the road has one side open.
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 12)),7); //Make sure the church has fives sides open.

    Tile tileB = (Tile::CreateTileB(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileB;
    //testingTilePlacement(&startID, 71, 72, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(77, 77)), 1);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 12)),6); //Make sure the church has three sides open.

    Tile tileE = (Tile::CreateTileE(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileE;
    //testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(75, 76), 2), 1);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 7)),2); //Make sure the castle has three sides open.

    Tile tileN = (Tile::CreateTileN(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileN;
    //testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(77, 76), 2), 1);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));

    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 10)),0); //Make sure the castle has three sides open.
}

TEST(RulesTest, ScoreChurch) {
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    unsigned int expectedScore = 1;

    currentTile = &(Tile::CreateTileB(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    Coord *churchCoord = new Coord(72, 72);

    unsigned int currentTileID = currentTile->getId();
    unsigned int tilesSurrounded = BoardManager::isSurrounded(currentTileID);

    unsigned int actualScore = GameRules::scoreChurch(tilesSurrounded, true);
    EXPECT_EQ(actualScore, 0);
    actualScore = GameRules::scoreChurch(tilesSurrounded, false);
    EXPECT_EQ(actualScore,1);

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                break; // avoid overwriting the church tile
            }
            else
            {
                // place field tiles around church tile
                currentTile = &(Tile::CreateTileY(1, startID, PreyType::None)[0]);
                currentTile->setRotation(0);
                testingTilePlacement(&startID, (churchCoord->getX() + i), (churchCoord->getY() + j), currentTile, surroundingTiles);
                currentTile->placeTile();

                expectedScore++;
                currentTileID = currentTile->getId();
                tilesSurrounded = BoardManager::isSurrounded(currentTileID);

                actualScore = GameRules::scoreChurch(tilesSurrounded, true);

                // just placed final boardering tile, actuallyScore set to true should return full value
                if (i == 1 && j == 1)
                {
                    EXPECT_EQ(actualScore,expectedScore);
                }

                // church isn't completely surrounded, actuallyScore set to true should return 0
                else
                {
                    EXPECT_EQ(actualScore,0);
                }
                actualScore = GameRules::scoreChurch(tilesSurrounded, false);
                EXPECT_EQ(actualScore,expectedScore);
            }
        }
    }
}

TEST(RulesTest, ScoreCastle1) {
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileD(1, startID, PreyType::Deer)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    unsigned int actualScore = GameRules::scoreCastle(*currentSet, true, false);
    EXPECT_EQ(actualScore,0);
    actualScore = GameRules::scoreCastle(*currentSet, false, false);
    EXPECT_EQ(actualScore,2);

    // add another tile to extend the lake region
    currentTile = &(Tile::CreateTileK(1, startID, PreyType::Boar)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTileID = currentTile->getId();
    currentSet = Regions::getRegions(currentTileID);

    actualScore = GameRules::scoreCastle(*currentSet, true, false);
    EXPECT_EQ(actualScore,12);
    actualScore = GameRules::scoreCastle(*currentSet, false, false);
    EXPECT_EQ(actualScore,12);

}

TEST(RulesTest, ScoreCastle2) {
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
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

    unsigned int actualScore = GameRules::scoreCastle(*currentSet, true, false);
    EXPECT_EQ(actualScore,0);
    actualScore = GameRules::scoreCastle(*currentSet, false, false);
    EXPECT_EQ(actualScore,10);
    
    currentTile = &(Tile::CreateTileN(1, startID, PreyType::None)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 73, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTileID = currentTile->getId();
    currentSet = Regions::getRegions(currentTileID);

    actualScore = GameRules::scoreCastle(*currentSet, true, false);
    EXPECT_EQ(actualScore,24);
    actualScore = GameRules::scoreCastle(*currentSet, false, false);
    EXPECT_EQ(actualScore,24);
}

TEST(RulesTest, scoreRoad)
{
    //Testing a completed road that forms a perfect square. Starts and ends on the same tile.
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
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
    unsigned int returnScore = GameRules::scoreRoad(*currentSet, true);

    //completed road = 1 pt per tile
    unsigned int realScore = 4;

    EXPECT_EQ(realScore, returnScore);

}

TEST(RulesTest, scoreGrassAndRoad)
{
    //Testing grass next to completed castle/lake and incomplete den
    //Testing complete road that starts with den and ends with castle
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
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
    unsigned int returnGrassScore = GameRules::scoreGrass(currentSet, currentTileID, 10);
   // get score for the completed road  in this set of 4 tiles placed together
    unsigned int returnRoadScore = GameRules::scoreRoad(*currentSet, true);
    unsigned int realGrassScore = 5;
    unsigned int realRoadScore = 2;

    EXPECT_EQ(realGrassScore, returnGrassScore);
    EXPECT_EQ(realRoadScore, returnRoadScore);
}

TEST(RulesTest, scoreMoreGrass)
{
    //Testing grass next to completed den and completed lake
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileB(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 71, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileU(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(3);
    testingTilePlacement(&startID, 71, 73, currentTile, surroundingTiles);
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

    unsigned int returnGrassScore = GameRules::scoreGrass(currentSet, currentTileID, 10);
    unsigned int realGrassScore = 8; //5 pt for completed lake + 3 pts for completed den

    EXPECT_EQ(returnGrassScore, realGrassScore);
}

TEST(RulesTest, scoreMoreRoads)
{
    //Testing incomplete road with prey animals
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
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

    unsigned int returnRoadScore = GameRules::scoreRoad(*currentSet, false);

    unsigned int realRoadScore = 7;

    EXPECT_EQ(realRoadScore, returnRoadScore);
}

TEST (RulesTest, scoreMoreMoreRoads)
{
    //Testing complete road that starts with den and ends with den and has prey animals
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
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

    unsigned int returnRoadScore = GameRules::scoreRoad(*currentSet, false);

    unsigned int realRoadScore = 5;

    EXPECT_EQ(realRoadScore, returnRoadScore);
}

TEST(RulesTest, scoreGrassWithJustCompleteDen)
{
    //Testing grass next to completed den but incomplete lake
    //Testing two different incomplete sets of roads
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
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

    currentTile = &(Tile::CreateTileD(1, startID, PreyType::Deer)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 74,71, currentTile, surroundingTiles);
    currentTile->placeTile();

    //Testing road portion of this landscape
    unsigned int currentTileId = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

    unsigned int returnRoadScore = GameRules::scoreRoad(*currentSet, false);

    unsigned int realRoadScore = 6;

    EXPECT_EQ(realRoadScore, returnRoadScore);

    currentTile = &(Tile::CreateTileV(1, startID, PreyType::None)[0]);
    currentTile->setRotation(1);
    testingTilePlacement(&startID, 72, 71, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet2 = Regions::getRegions(currentTileID);

    unsigned int returnRoadScore2 = GameRules::scoreRoad(*currentSet2, false);
    unsigned int returnGrassScore = GameRules::scoreGrass(currentSet2, currentTileID, 7);
    unsigned int realRoadScore2 = 5;
    unsigned int realGrassScore = 3;
    EXPECT_EQ(realRoadScore2, returnRoadScore2);
    EXPECT_EQ(realGrassScore, returnGrassScore);

}

TEST(RulesTest, getCurrentScore) {
    unsigned int startID = 0;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    currentTile = &(Tile::CreateTileD(1, startID, PreyType::None)[0]);
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    unsigned int currentTileId = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

    unsigned int edge = 4; // uncompleted city on right side of tile
    unsigned int tilesSurrounded = BoardManager::isSurrounded(currentTileId);

    unsigned int actualScore = GameRules::getCurrentScore(currentSet, edge, currentTile, tilesSurrounded);
    unsigned int expectedScore = 1; // uncompleted city on right side of tile

    EXPECT_EQ(actualScore, expectedScore);

    currentTile = &(Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    currentTileId = currentTile->getId();
    currentSet = Regions::getRegions(currentTileId);
    edge = 10; // test left side of tile
    tilesSurrounded = BoardManager::isSurrounded(currentTileId);

    actualScore = GameRules::getCurrentScore(currentSet, edge, currentTile, tilesSurrounded);
    expectedScore = 8; // 8 points for a completed city adjacent to 1 unique prey

    EXPECT_EQ(actualScore, expectedScore);
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
