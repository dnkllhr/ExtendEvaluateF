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
        ////printf("TileNode %d at %X\n", i, currentNode.get());
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
        ////printf("TileNode %d at %X\n", i + 13, currentNode.get());
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
    ////printf("r1 : %X r2 : %x\n", r1.get(), r2.get());
    Regions::mergeRegions(0, 0, 13, 0);

    EXPECT_EQ(Regions::regionTracker[0][0], r2);
    EXPECT_EQ(Regions::regionTracker[13][0], r2);    
    EXPECT_NE(r1->head.get(), r2->head.get());
    EXPECT_EQ(r1->tail.get(), r2->tail.get());
    EXPECT_EQ(r2->edgesTillCompletion, preMergeTotalEdges);

}

TEST(RegionTests, addConnection) {

    BoardManager::gameInit();
    unsigned int startID = 18000;
    //Tile currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles = NULL; //Init'd to NULL

    unsigned int centerID = Board::get(Coord(76,76))->getId();
    /*
    //printf("centerID : %d\n", centerID);

    for(int i = 0; i < 12; i++)
    {
        //printf("edge : %d edgesTillCompletion : %d\n", i, Regions::regionTracker[centerID][i]->edgesTillCompletion);
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
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

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
    
    //std::cout << currentTile->getTileName() << std::endl;

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

    ////printf("Seg fault yet?\n");
    Tile tileE = (Tile::CreateTileE(1, startID, PreyType::None)[0]); //No prey, starting tile
    ////printf("Nah\n");
    currentTile = &tileE;
    //testingTilePlacement(&startID, 71, 71, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(75, 76), 2), 1);
    ////printf("Moves suck\n");

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));
    }

    ////printf("For loop is happy\n");
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 7)),2); //Make sure the castle has three sides open.
    ////printf("Keep going\n");

    Tile tileN = (Tile::CreateTileN(1, startID, PreyType::None)[0]); //No prey, starting tile

    ////printf("N is for no\n");
    currentTile = &tileN;
    //testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(77, 76), 2), 1);
    ////printf("Make that move\n");

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));

    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 10)),0); //Make sure the castle has three sides open.

    Tile tileL = (Tile::CreateTileL(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileL;
    //testingTilePlacement(&startID, 73, 71, currentTile, surroundingTiles);
    BoardManager::makeMove(Move(*currentTile, Coord(77, 74), 3), 2);

    for(int i = 0; i < 12; i++)
    {
        //Make sure everything has a region
        EXPECT_TRUE(Regions::checkRegionExistence(currentTile->getId(),i));

    }

    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 10)),0); //Make sure the road is completed
    EXPECT_EQ((Regions::checkRegionEdgesTillCompletion(currentTile->getId(), 1)),0); //Make sure the castle is completed
}

TEST(RulesTest, ScoreChurch) {
    unsigned int startID = 18000;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;
    BoardManager::gameInit();

    unsigned int expectedScore = 1;
    currentTile = &(Tile::CreateTileB(1, startID, PreyType::None)[0]);

    unsigned int currentTileID = currentTile->getId();
    unsigned int centerChurchID = currentTileID;
    currentTile->setRotation(0);
    BoardManager::makeMove(Move(*currentTile, Coord(72, 72), 0), 2);
    currentTile->placeTile();

    Coord *churchCoord = new Coord(72, 72);
    unsigned int tilesSurrounded = BoardManager::isSurrounded(currentTileID);

    ////printf("Found %d tiles\n", tilesSurrounded);
    unsigned int actualScore = GameRules::scoreChurch(tilesSurrounded, true);
    EXPECT_EQ(actualScore, 0);
    actualScore = GameRules::scoreChurch(tilesSurrounded, false);
    EXPECT_EQ(actualScore,1);
    ////printf("scored\n");

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue; // avoid overwriting the church tile
            }
            else
            {
                // place field tiles around church tile
                currentTile = &(Tile::CreateTileY(1, startID, PreyType::None)[0]);
                currentTileID = currentTile->getId();
                currentTile->setRotation(0);
                testingTilePlacement(&startID, (churchCoord->getX() + i), (churchCoord->getY() + j), currentTile, surroundingTiles);
                currentTile->placeTile();

                expectedScore++;
                tilesSurrounded = BoardManager::isSurrounded(centerChurchID);
                ////printf("placed tile %d at %d %d, expected score %d, surrounded %d\n", currentTileID, churchCoord->getX() + i, churchCoord->getY() + j, expectedScore, tilesSurrounded);


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
    BoardManager::gameInit();
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    /*currentTile = &(Tile::CreateTileD(1, startID, PreyType::Deer)[0]);
    unsigned int currentTileID = currentTile->getId();
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    */
    std::shared_ptr<struct regionSet> currentSet = std::shared_ptr<struct regionSet>(new regionSet);
    std::shared_ptr<struct tileNode> currentTileNode = std::shared_ptr<struct tileNode>(new tileNode);
    currentSet->head = currentTileNode;

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < NUM_PREY; j++)
        {
            currentTileNode->preyCounts[j] = 0;
        }
        currentTileNode->tileID = i;
        currentTileNode->edge = i;
        if(i+1 < 5)
        {
            currentTileNode->next = std::shared_ptr<struct tileNode>(new tileNode);
            currentTileNode = currentTileNode->next;
        }
    }
    currentSet->tail = currentTileNode;
    currentTileNode->next = NULL;

    currentSet->edgesTillCompletion = 1;



    unsigned int actualScore = GameRules::scoreCastle(currentSet, true, false);
    ////printf("Where am i\n");
    EXPECT_EQ(actualScore,0);
    actualScore = GameRules::scoreCastle(currentSet, false, false);
    EXPECT_EQ(actualScore,10);
    ////printf("Where am i\n");

    // add another tile to extend the lake region
    /*currentTile = &(Tile::CreateTileK(1, startID, PreyType::Boar)[0]);
    currentTileID = currentTile->getId();
    currentTile->setRotation(2);
    testingTilePlacement(&startID, 73, 72, currentTile, surroundingTiles);
    currentTile->placeTile();
    //printf("Where am i\n");
    */
    //currentSet = Regions::getRegions(currentTileID);

    ////printf("\nADDING NEW TILE NODES\n");

    currentTileNode->next = std::shared_ptr<struct tileNode>(new tileNode);
    currentTileNode = currentTileNode->next;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < NUM_PREY; j++)
        {
            currentTileNode->preyCounts[j] = 0;
        }
        currentTileNode->preyCounts[0] = 1;
        currentTileNode->tileID = i+5;
        currentTileNode->edge = i;
        if(i+1 < 5)
        {
            currentTileNode->next = std::shared_ptr<struct tileNode>(new tileNode);
            currentTileNode = currentTileNode->next;
        }
    }
    currentSet->tail = currentTileNode;
    currentTileNode->next = NULL;

    currentSet->edgesTillCompletion = 0;

    actualScore = GameRules::scoreCastle(currentSet, true, false);
    EXPECT_EQ(actualScore,30);
    actualScore = GameRules::scoreCastle(currentSet, false, false);
    EXPECT_EQ(actualScore,30);
    ////printf("Where am i\n");

}
/*
TEST(RulesTest, ScoreCastle2) {
    unsigned int startID = 100023;
    Tile *currentTile;

    Tile tileI = (Tile::CreateTileI(1, startID, PreyType::None)[0]);
    currentTile = &tileI;
    BoardManager::makeMove(Move(*currentTile, 72, 72), 1);

    Tile tileJ = (Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0]);
    currentTile = &tileJ;
    BoardManager::makeMove(Move(*currentTile, 71, 73), 2);

    Tile tileC = (Tile::CreateTileC(1, startID, PreyType::None)[0]);
    currentTile = &tileC;
    BoardManager::makeMove(Move(*currentTile, 72, 73), 1);

    Tile tileE = (Tile::CreateTileE(1, startID, PreyType::None)[0]);
    currentTile = &tileE;
    BoardManager::makeMove(Move(*currentTile, 72, 74), 2);

    Tile tileN = (Tile::CreateTileN(1, startID, PreyType::None)[0]);
    currentTile = &tileN;
    BoardManager::makeMove(Move(*currentTile, 73, 73, 3), 1);

    unsigned int currentTileID = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    unsigned int actualScore = GameRules::scoreCastle(*currentSet, true, false);
    EXPECT_EQ(actualScore,0);
    actualScore = GameRules::scoreCastle(*currentSet, false, false);
    EXPECT_EQ(actualScore,10);
    
    /* DUPLICATE PLACEMENT
    Tile tileN2 = (Tile::CreateTileN(1, startID, PreyType::None)[0]);
    currentTile = &tileN2;
    BoardManager::makeMove(Move(*currentTile, 73, 73, 2), 2);
    

    currentTileID = currentTile->getId();
    currentSet = Regions::getRegions(currentTileID);

    actualScore = GameRules::scoreCastle(*currentSet, true, false);
    EXPECT_EQ(actualScore,24);
    actualScore = GameRules::scoreCastle(*currentSet, false, false);
    EXPECT_EQ(actualScore,24);
}
*/
TEST(RulesTest, scoreRoad)
{
    unsigned int startID = 0;
    BoardManager::gameInit();
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    /*currentTile = &(Tile::CreateTileD(1, startID, PreyType::Deer)[0]);
    unsigned int currentTileID = currentTile->getId();
    currentTile->setRotation(0);
    testingTilePlacement(&startID, 72, 72, currentTile, surroundingTiles);
    currentTile->placeTile();

    */
    std::shared_ptr<struct regionSet> currentSet = std::shared_ptr<struct regionSet>(new regionSet);
    std::shared_ptr<struct tileNode> currentTileNode = std::shared_ptr<struct tileNode>(new tileNode);
    currentSet->head = currentTileNode;

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < NUM_PREY; j++)
        {
            currentTileNode->preyCounts[j] = 0;
        }
        currentTileNode->tileID = i;
        currentTileNode->edge = i;
        if(i+1 < 5)
        {
            currentTileNode->next = std::shared_ptr<struct tileNode>(new tileNode);
            currentTileNode = currentTileNode->next;
        }
    }
    currentSet->tail = currentTileNode;
    currentTileNode->next = NULL;

    currentSet->edgesTillCompletion = 1;

    // not sure what to pass through for bool actuallyScore
    unsigned int returnScore = GameRules::scoreRoad(currentSet, true);
    EXPECT_EQ(returnScore, 0);
    returnScore = GameRules::scoreRoad(currentSet, false);
    EXPECT_EQ(returnScore, 5);


    currentTileNode->next = std::shared_ptr<struct tileNode>(new tileNode);
    currentTileNode = currentTileNode->next;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < NUM_PREY; j++)
        {
            currentTileNode->preyCounts[j] = 1;
        }
        currentTileNode->tileID = i+5;
        currentTileNode->edge = i;
        if(i+1 < 5)
        {
            currentTileNode->next = std::shared_ptr<struct tileNode>(new tileNode);
            currentTileNode = currentTileNode->next;
        }
    }
    currentSet->tail = currentTileNode;
    currentTileNode->next = NULL;

    currentSet->edgesTillCompletion = 0;


    returnScore = GameRules::scoreRoad(currentSet, false);
    EXPECT_EQ(returnScore, 20);
    returnScore = GameRules::scoreRoad(currentSet, false);
    EXPECT_EQ(returnScore, 20);


}
/*
TEST(RulesTest, scoreGrassAndRoad)
{
    //Testing grass next to completed castle/lake and incomplete den
    //Testing complete road that starts with den and ends with castle
    unsigned int startID = 0;
    Tile *currentTile;

    //this creates a complete castle, so grass should be 5 pts
    Tile tileZ = (Tile::CreateTileZ(1, startID, PreyType::None)[0]);
    currentTile = &tileZ;
    BoardManager::makeMove(Move(*currentTile, 72, 71, 2), 1);

    Tile tileG = (Tile::CreateTileG(1, startID, PreyType::None)[0]);
    currentTile = &tileG;
    BoardManager::makeMove(Move(*currentTile, 72, 70, 1), 2);

    Tile tileE = (Tile::CreateTileE(1, startID, PreyType::None)[0]);
    currentTile = &tileE;
    BoardManager::makeMove(Move(*currentTile, 72, 69), 1);

    Tile tileA = (Tile::CreateTileA(1, startID, PreyType::None)[0]);
    currentTile = &tileA;
    BoardManager::makeMove(Move(*currentTile, 72, 72), 2);

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
*/
TEST(RulesTest, scoreGrass)
{
    //Testing grass next to completed den and completed lake
    unsigned int startID = 18000;
    //Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    BoardManager::gameInit();
    //printf("tile\n");
    Tile tileV = (Tile::CreateTileV(1, startID, PreyType::None)[0]); //No prey, starting tile
    Tile * currentTile = &tileV;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(76, 75)), 1);
    //printf("tile\n");

    Tile tileX = (Tile::CreateTileX(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileX;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);


    BoardManager::makeMove(Move(*currentTile, Coord(75, 75)), 1);
    //printf("tile\n");

    Tile tileU = (Tile::CreateTileU(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileU;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(75, 76)), 1);
    //printf("tile\n");


    Tile tileT = (Tile::CreateTileT(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileT;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(75, 77), 2), 1);
    //printf("tile\n");


    Tile tileP = (Tile::CreateTileP(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileP;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(76, 77), 2), 1);
    //printf("tile\n");


    Tile tileD2 = (Tile::CreateTileD(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileD2;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(77, 76), 2), 1);
    //printf("tile\n");


    Tile tileV2 = (Tile::CreateTileV(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileV2;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(77, 77), 3), 1);
    //printf("tile\n");

    /*
    Tile tileN = (Tile::CreateTileN(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileN;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);

    BoardManager::makeMove(Move(*currentTile, Coord(77, 76), 2), 1);
    //printf("tile\n");


    Tile tileZ = (Tile::CreateTileZ(1, startID, PreyType::None)[0]); //No prey, starting tile
    currentTile = &tileZ;
    //testingTilePlacement(&startID, 72, 73, currentTile, surroundingTiles);
    unsigned int grassGrass = tileZ.getId();
    
    BoardManager::makeMove(Move(*currentTile, Coord(77, 75)), 1);
    //printf("tile\n");
    */

    std::shared_ptr<struct regionSet> *currentSets = Regions::regionTracker[tileV.getId()];
    /*
    printf("currentSets addr : %X\n", currentSets);
    printf("head tileID : %d\n", currentSets[10]->head->tileID);
    printf("can access head\n");
    */
    unsigned int returnGrassScore = GameRules::scoreGrass(currentSets, tileV.getId(), 0);
    unsigned int realGrassScore = 0; //5 pt for completed lake + 3 pts for completed den

    EXPECT_EQ(returnGrassScore, realGrassScore);

    returnGrassScore = GameRules::scoreGrass(currentSets, tileV.getId(), 2);
    realGrassScore = 3; //5 pt for completed lake + 3 pts for completed den

    EXPECT_EQ(returnGrassScore, realGrassScore);
}
/*
TEST(RulesTest, scoreMoreRoads)
{
    //Testing incomplete road with prey animals
    unsigned int startID = 0;
    Tile *currentTile;

    Tile tileZ = Tile::CreateTileZ(1, startID, PreyType::Deer)[0];
    currentTile = &tileZ;
    BoardManager::makeMove(Move(*currentTile, 72, 72, 3), 1);

    Tile tileK = Tile::CreateTileK(1, startID, PreyType::Boar)[0];
    currentTile = &tileK;
    BoardManager::makeMove(Move(*currentTile, 73, 72, 0), 2);

    Tile tileU = Tile::CreateTileU(1, startID, PreyType::None)[0];
    currentTile = &tileU;
    BoardManager::makeMove(Move(*currentTile, 74, 73, 1), 1);

    Tile tileJ = Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0];
    currentTile = &tileJ;
    BoardManager::makeMove(Move(*currentTile, 73, 73, 3), 2);

    unsigned int currentTileID = currentTile->getId();

    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileID);

    unsigned int returnRoadScore = GameRules::scoreRoad(*currentSet, false);

    unsigned int realRoadScore = 7;

    EXPECT_EQ(realRoadScore, returnRoadScore);
}

TEST (RulesTest, scoreMoreMoreRoads)
{
    BoardManager::gameInit();

    //Testing complete road that starts with den and ends with den and has prey animals
    unsigned int startID = 758943;
    Tile *currentTile;

    Tile tileA = Tile::CreateTileA(1, startID, PreyType::None)[0];
    currentTile = &tileA;
    BoardManager::makeMove(Move(*currentTile, 72, 72, 3), 1);

    Tile tileJ = Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0];
    currentTile = &tileJ;
    BoardManager::makeMove(Move(*currentTile, 73, 72, 0), 2);

    Tile tileV = Tile::CreateTileV(1, startID, PreyType::None)[0];
    currentTile = &tileV;
    BoardManager::makeMove(Move(*currentTile, 73, 71, 1), 1);
    
    Tile tileA2 = Tile::CreateTileA(1, startID, PreyType::None)[0];
    currentTile = &tileA2;
    BoardManager::makeMove(Move(*currentTile, 72, 72, 1), 1);

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
    unsigned int startID = 214321;
    Tile *currentTile;

    Tile tileJ = Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0];
    currentTile = &tileJ;
    BoardManager::makeMove(Move(*currentTile, 72, 72, 3), 1);

    Tile tileV = Tile::CreateTileV(1, startID, PreyType::None)[0];
    currentTile = &tileV;
    BoardManager::makeMove(Move(*currentTile, 73, 72, 0), 2);

    Tile tileA = Tile::CreateTileA(1, startID, PreyType::None)[0];
    currentTile = &tileA;
    BoardManager::makeMove(Move(*currentTile, 72, 72, 1), 1);

    Tile tileU = Tile::CreateTileU(1, startID, PreyType::None)[0];
    currentTile = &tileU;
    BoardManager::makeMove(Move(*currentTile, 73, 70, 0), 2);

    Tile tileU2 = Tile::CreateTileU(1, startID, PreyType::None)[0];
    currentTile = &tileU2;
    BoardManager::makeMove(Move(*currentTile, 72, 70, 0), 1);

    Tile tileU3 = Tile::CreateTileU(1, startID, PreyType::None)[0];
    currentTile = &tileU3;
    BoardManager::makeMove(Move(*currentTile, 74, 72, 1), 2);

    Tile tileV2 = Tile::CreateTileV(1, startID, PreyType::None)[0];
    currentTile = &tileV2;
    BoardManager::makeMove(Move(*currentTile, 74, 70, 0), 1);

    Tile tileD = Tile::CreateTileD(1, startID, PreyType::Deer)[0];
    currentTile = &tileD;
    BoardManager::makeMove(Move(*currentTile, 74, 71, 0), 2);

    //Testing road portion of this landscape
    unsigned int currentTileId = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

    unsigned int returnRoadScore = GameRules::scoreRoad(*currentSet, false);

    unsigned int realRoadScore = 6;

    EXPECT_EQ(realRoadScore, returnRoadScore);

    Tile tileV3 = Tile::CreateTileV(1, startID, PreyType::None)[0];
    currentTile = &tileV3;
    BoardManager::makeMove(Move(*currentTile, 72, 71, 1), 1);

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

    BoardManager::gameInit();
    
    unsigned int startID = 565;
    Tile *currentTile;
    //Move *currentMove;
    //Coord *currentCoord;
    const Tile **surroundingTiles;

    Tile tileD = Tile::CreateTileD(1, startID, PreyType::None)[0];
    currentTile = &tileD;
    BoardManager::makeMove(Move(*currentTile, Coord(72, 72), 0), 1);

    unsigned int currentTileId = currentTile->getId();
    std::shared_ptr<struct regionSet> *currentSet = Regions::getRegions(currentTileId);

    unsigned int edge = 4; // uncompleted city on right side of tile
    unsigned int tilesSurrounded = BoardManager::isSurrounded(currentTileId);

    unsigned int actualScore = GameRules::getCurrentScore(currentSet, edge, currentTile, tilesSurrounded);
    unsigned int expectedScore = 1; // uncompleted city on right side of tile

    EXPECT_EQ(actualScore, expectedScore);

    Tile tileJ = Tile::CreateTileJ(1, startID, PreyType::Buffalo)[0];
    currentTile = &tileJ;
    BoardManager::makeMove(Move(*currentTile, Coord(73, 72), 2), 1);

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

    // LEFT 90
    tile.setRotation(0); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left)));
    tile.setRotation(1); EXPECT_TRUE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left)));
    tile.setRotation(2); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left)));
    tile.setRotation(3); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(left)));

    // RIGHT 180
    tile.setRotation(0); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right)));
    tile.setRotation(1); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right)));
    tile.setRotation(2); EXPECT_TRUE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right)));
    tile.setRotation(3); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(right)));

    // UP 0 270
    tile.setRotation(0); EXPECT_TRUE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up)));
    tile.setRotation(1); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up)));
    tile.setRotation(2); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up)));
    tile.setRotation(3); EXPECT_TRUE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(up)));

    // DOWN 90 180
    tile.setRotation(0); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down)));
    tile.setRotation(1); EXPECT_TRUE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down)));
    tile.setRotation(2); EXPECT_TRUE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down)));
    tile.setRotation(3); EXPECT_FALSE(GameRules::validTilePlacement(tile, Board::getBorderingTiles(down)));
}

*/