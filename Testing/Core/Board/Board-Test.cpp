#include "../Core/Board/Board.h"
#include "../Core/BoardManager/Move.h"
#include "../Core/BoardManager/Coord.h"
#include "gtest/gtest.h"
#define GRID_SIZE 153

TEST(BoardTests, getBoard)
{
    Board::init();

    const Array<Array<Tile*>>& boardGrid = Board::getBoard();

    EXPECT_EQ(boardGrid.getSize(), (unsigned int)GRID_SIZE);

    for(unsigned int i = 0; i < (unsigned int)GRID_SIZE; i++)
    {
        EXPECT_EQ(boardGrid[i].getSize(), (unsigned int)GRID_SIZE);

        for(unsigned int j = 0; j < (unsigned int)GRID_SIZE; j++)
        {
            EXPECT_EQ(nullptr, boardGrid[i][j]);
        }
    }
}

TEST(BoardTests, place)
{
    Board::init();

    const Array<Array<Tile*>>& boardGrid = Board::getBoard();

    unsigned int tileIDcounter = 0;
    Tile& tile0 = Tile::CreateTileD(1, tileIDcounter, PreyType::None)[0];
    Tile& tile1 = Tile::CreateTileJ(1, tileIDcounter, PreyType::Buffalo)[0];
    Tile& tile2 = Tile::CreateTileV(1, tileIDcounter, PreyType::None)[0];

    const Move& move0 = Move(tile0, 76, 76);
    const Move& move1 = Move(tile1, 76, 75, 2); // rotate 180 degrees
    const Move& move2 = Move(tile2, 77, 75);

    for(unsigned int m = 0; m <= 3; m++)
    {
        for(unsigned int i = 0; i < GRID_SIZE; i++)
        {
            for(unsigned int j = 0; j < GRID_SIZE; j++)
            {
                if(m > 0 && i == 76 && j == 76)
                {
                    EXPECT_EQ(&tile0, boardGrid[i][j]);
                }
                else if(m > 1 && i == 76 && j == 75)
                {
                    EXPECT_EQ(&tile1, boardGrid[i][j]);
                }
                else if(m > 2 && i == 77 && j == 75)
                {
                    EXPECT_EQ(&tile2, boardGrid[i][j]);
                }
                else // expect all other locations to be empty
                {
                    EXPECT_EQ(nullptr, boardGrid[i][j]); 
                }
            }
        }
        switch(m)
        {
            case 0: Board::place(move0); return;
            case 1: Board::place(move1); return;
            case 2: Board::place(move2); return;
        }
    }
}

TEST(BoardTests, getFromCoord)
{
    Board::init();

    unsigned int tileIdCounter = 0;
    Tile& tile = Tile::CreateTileD(1, tileIdCounter, PreyType::None)[0];
    const Coord& coord = Coord(10, 20);
    const Move& move = Move(tile, coord);
    Board::place(move);

    EXPECT_EQ(&Board::get(coord), &tile);
}

TEST(BoardTests, getFromTileId)
{
    Board::init();

    unsigned int tileIdCounter = 5;
    Tile tile = Tile::CreateTileD(1, tileIdCounter, PreyType::None)[0];
    const Move& move = Move(tile, 76, 76);
    Board::place(move);

    Board::get((unsigned int) 5);
    //EXPECT_EQ(&Board::get((unsigned int) 5), &tile);
}

TEST(BoardTests, getBorderingTiles)
{
    Board::init();

    unsigned int tileIDcounter = 0;

    Tile& tileCenter = Tile::CreateTileI(1, tileIDcounter, PreyType::None)[0];
    Tile& tile0 = Tile::CreateTileA(1, tileIDcounter, PreyType::None)[0];
    Tile& tile1 = Tile::CreateTileB(1, tileIDcounter, PreyType::None)[0];
    Tile& tile2 = Tile::CreateTileC(1, tileIDcounter, PreyType::None)[0];
    Tile& tile3 = Tile::CreateTileD(1, tileIDcounter, PreyType::None)[0];
    Tile& tile4 = Tile::CreateTileE(1, tileIDcounter, PreyType::None)[0];
    Tile& tile5 = Tile::CreateTileG(1, tileIDcounter, PreyType::None)[0];
    Tile& tile6 = Tile::CreateTileH(1, tileIDcounter, PreyType::None)[0];
    
    const Move& moveCenter = Move(tileCenter, 1, 1);
    const Move& move0 = Move(tile0, 0, 2); // upper left
    const Move& move1 = Move(tile1, 1, 2); // upper
    const Move& move2 = Move(tile2, 2, 2); // upper right
    const Move& move3 = Move(tile3, 2, 1); // right
    const Move& move4 = Move(tile4, 2, 0); // lower right
    const Move& move5 = Move(tile5, 1, 0); // lower
    const Move& move6 = Move(tile6, 0, 0); // lower left
    // left is empty 
    /*

    Board::place(moveCenter);
    Board::place(move0);
    Board::place(move1);
    Board::place(move2);
    Board::place(move3);
    Board::place(move4);
    Board::place(move5);
    Board::place(move6);

    const Tile** borderingTiles = Board::getBorderingTiles(tileCenter);

    EXPECT_EQ(borderingTiles[0], &tile0);
    EXPECT_EQ(borderingTiles[1], &tile1);
    EXPECT_EQ(borderingTiles[2], &tile2);
    EXPECT_EQ(borderingTiles[3], &tile3);
    EXPECT_EQ(borderingTiles[4], &tile4);
    EXPECT_EQ(borderingTiles[5], &tile5);
    EXPECT_EQ(borderingTiles[6], &tile6);
    //EXPECT_EQ(borderingTiles[7], nullptr); // left is empty
    */
}

TEST(BoardTests, getCoordinatesFromTileId)
{
    Board::init();

    unsigned int tileIdCounter = 5;
    int x = 10;
    int y = 20;

    Tile tile = Tile::CreateTileD(1, tileIdCounter, PreyType::None)[0];
    const Coord& coord = Coord(x, y);
    const Move& move = Move(tile, coord);
    Board::place(move);

    const Coord& result = Board::getCoordinatesFromTileId((unsigned int) 5);

    EXPECT_EQ(result.getX(), x);
    EXPECT_EQ(result.getY(), y);
}

TEST(BoardTests, getCoordinatesFromGridId)
{
    Board::init();

    int x = 10;
    int y = 20;
    int gridId = y * GRID_SIZE + x;

    const Coord& result = Board::getCoordinatesFromGridId(gridId);

    EXPECT_EQ(result.getX(), x);
    EXPECT_EQ(result.getY(), y);
}

TEST(BoardTests, getGridId)
{
    Board::init();

    int x = 10;
    int y = 20;
    int gridId = y * GRID_SIZE + x;

    const Coord& coord = Coord(x, y);

    EXPECT_EQ(Board::getGridId(coord), (unsigned int)gridId);
}


TEST(BoardTests, getAvailableLocations)
{
    Board::init();

    unsigned int tileIDcounter = 0;
    Tile& tile0 = Tile::CreateTileD(1, tileIDcounter, PreyType::None)[0];
    Tile& tile1 = Tile::CreateTileJ(1, tileIDcounter, PreyType::Buffalo)[0];
    Tile& tile2 = Tile::CreateTileV(1, tileIDcounter, PreyType::None)[0];

    const Move& move0 = Move(tile0, 76, 76);
    const Move& move1 = Move(tile1, 76, 75, 2); // rotate 180 degrees
    const Move& move2 = Move(tile2, 77, 75);

    const std::unordered_set<unsigned int>& availableLocations = Board::getAvailableLocations();

    EXPECT_EQ(availableLocations.size(), (unsigned int)0);

    Board::place(move0);

        const unsigned int size0 = 4;
        EXPECT_EQ(availableLocations.size(), size0);

        unsigned int x0[size0] = { 76, 75, 77, 76 };
        unsigned int y0[size0] = { 77, 76, 76, 75 };

        for(unsigned int i = 0; i < size0; i++)
        {
            EXPECT_GT(availableLocations.count(Board::getGridId(x0[i], y0[i])), (unsigned int)0);
        }

    Board::place(move1);

        const unsigned int size1 = 6;
        EXPECT_EQ(availableLocations.size(), size1);

        unsigned int x1[size1] = { 76, 75, 77, 75, 77, 76 };
        unsigned int y1[size1] = { 77, 76, 76, 75, 75, 74 };

        for(unsigned int i = 0; i < size1; i++)
        {
            EXPECT_GT(availableLocations.count(Board::getGridId(x1[i], y1[i])), (unsigned int)0);
        }

    Board::place(move2);
    
        const unsigned int size2 = 7;
        EXPECT_EQ(availableLocations.size(), size2);

        unsigned int x2[size2] = { 76, 75, 77, 75, 76, 78, 77 };
        unsigned int y2[size2] = { 77, 76, 76, 75, 74, 75, 74 };

        for(unsigned int i = 0; i < size2; i++)
        {
            EXPECT_GT(availableLocations.count(Board::getGridId(x2[i], y2[i])), (unsigned int)0);
        }
}