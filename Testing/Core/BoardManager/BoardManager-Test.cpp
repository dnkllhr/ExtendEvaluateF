#include "../Core/Board/Board.h"
#include "../Core/BoardManager/Move.h"
#include "../Core/BoardManager/Coord.h"
#include "../Core/BoardManager/BoardManager.h"
#include "gtest/gtest.h"
#define GRID_SIZE 153

TEST(BoardManagerTests, getBoard)
{
    BoardManager::gameInit();
    EXPECT_EQ(&BoardManager::getBoard(), &Board::getBoard());
}

TEST(BoardManagerTests, gameInit)
{
    BoardManager::gameInit();

    const Array<Array<Tile*>>& boardGrid = BoardManager::getBoard();

    for(unsigned int i = 0; i < GRID_SIZE; i++)
    {
        for(unsigned int j = 0; j < GRID_SIZE; j++)
        {
            if(i == 76 && j == 76) // center
            {
                Tile* tile = boardGrid[i][j];
                EXPECT_EQ(tile->getTileType(), TileType::D);
                //EXPECT_EQ(tile->getRotation(), 0); floating point exception???
                EXPECT_EQ(tile->isPlaced(), true);

            }
            else // expect all other locations to be empty
            {
                EXPECT_EQ(nullptr, boardGrid[i][j]); 
            }
        }
    }
}

TEST(BoardManagerTests, getTileStack)
{
    BoardManager::gameInit();
    int actualTileCounts[NUM_TILES]   = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    int expectedTileCounts[NUM_TILES] = { 2,4,1,3,2,5,3,3,2,1,1,1,2,1,2,5,3,2,4,1,2,8,9,4,1,1,1,2 };
    expectedTileCounts[3]--; // starting Tile

    const TileStack* tileStack = BoardManager::getTileStack();
    std::queue<const Tile*> tileQueue1 = tileStack->getQueue((unsigned int) 1);
    std::queue<const Tile*> tileQueue2 = tileStack->getQueue((unsigned int) 2);

    EXPECT_EQ(tileQueue1.size(), (unsigned int)(NUMBER_OF_PLAYABLE_TILES / 2 - 1));
    EXPECT_EQ(tileQueue2.size(), (unsigned int)(NUMBER_OF_PLAYABLE_TILES / 2 - 1));

    while(!tileQueue1.empty() || !tileQueue2.empty())
    {
        const Tile* next;
        if(!tileQueue1.empty())
        {
            next = tileQueue1.front();
            tileQueue1.pop();
        }
        else
        {
            next = tileQueue2.front();
            tileQueue2.pop();
        }

        switch(next->getTileType())
        {
            case TileType::A : actualTileCounts[0]++; break;
            case TileType::B : actualTileCounts[1]++; break;
            case TileType::C : actualTileCounts[2]++; break;
            case TileType::D :
                 if(next->getPrey() == PreyType::None)
                 {
                    actualTileCounts[3]++;
                 }
                 else if(next->getPrey() == PreyType::Deer)
                 {
                    actualTileCounts[4]++;
                 }
                 break;
            case TileType::E : actualTileCounts[5]++; break;
            case TileType::G : actualTileCounts[6]++; break;
            case TileType::H : actualTileCounts[7]++; break;
            case TileType::I : actualTileCounts[8]++; break;
            case TileType::J :
                 if(next->getPrey() == PreyType::None)
                 {
                    actualTileCounts[9]++;
                 }
                 else if(next->getPrey() == PreyType::Buffalo)
                 {
                    actualTileCounts[10]++;
                 }
                break;
            case TileType::K :
                if(next->getPrey() == PreyType::None)
                {
                    actualTileCounts[11]++;
                }
                else if(next->getPrey() == PreyType::Boar)
                {
                    actualTileCounts[12]++;
                }
                break;
            case TileType::L :
                if(next->getPrey() == PreyType::None)
                {
                    actualTileCounts[13]++;
                }
                else if(next->getPrey() == PreyType::Boar)
                {
                    actualTileCounts[14]++;
                }
                break;
            case TileType::N : actualTileCounts[15]++; break;
            case TileType::P :
                if(next->getPrey() == PreyType::None)
                {
                    actualTileCounts[16]++;
                }
                else if(next->getPrey() == PreyType::Buffalo)
                {
                    actualTileCounts[17]++;
                }
                break;
            case TileType::R : actualTileCounts[18]++; break;
            case TileType::T :
                if(next->getPrey() == PreyType::None)
                {
                    actualTileCounts[19]++;
                }
                else if(next->getPrey() == PreyType::Croc)
                {
                    actualTileCounts[20]++;
                }
                break;
            case TileType::U : actualTileCounts[21]++; break;
            case TileType::V : actualTileCounts[22]++; break;
            case TileType::W : actualTileCounts[23]++; break;
            case TileType::X : actualTileCounts[24]++; break;
            case TileType::Y : actualTileCounts[25]++; break;
            case TileType::Z :
                if(next->getPrey() == PreyType::None)
                {
                    actualTileCounts[26]++;
                }
                else if(next->getPrey() == PreyType::Deer)
                {
                    actualTileCounts[27]++;
                }
                break;
        }
    }

    for(unsigned int i = 0; i < 28; i++)
    {
        EXPECT_EQ(actualTileCounts[i], expectedTileCounts[i]) << "CreateTiles Index = " << i << std::endl;
    }
}

TEST(BoardManagerTests, getValidMoves)
{
    throw std::logic_error("\n----------------------------------------------------\nTest writing incomplete, will finish later. -Michael\n----------------------------------------------------\n");
}

TEST(BoardManagerTests, makeMove)
{
    throw std::logic_error("\n----------------------------------------------------\nTest writing incomplete, will finish later. -Michael\n----------------------------------------------------\n");
}

TEST(BoardManagerTests, isSurrounded)
{
    throw std::logic_error("\n----------------------------------------------------\nTest writing incomplete, will finish later. -Michael\n----------------------------------------------------\n");
}
