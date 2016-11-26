#include "../Core/Board/Board.h"
#include "../Core/BoardManager/Move.h"
#include "../Core/BoardManager/Coord.h"
#include "../Core/BoardManager/BoardManager.h"
#include "gtest/gtest.h"
#define GRID_SIZE 153

TEST(BoardManagerTests, getBoard)
{
    Board::set();
    BoardManager::gameInit();
    EXPECT_EQ(&BoardManager::getBoard(), &Board::getBoard());
}

TEST(BoardManagerTests, gameInit)
{

}

TEST(BoardManagerTests, getTileStack)
{

}

TEST(BoardManagerTests, getValidMoves)
{

}

TEST(BoardManagerTests, makeMove)
{

}

TEST(BoardManagerTests, isSurrounded)
{

}
/*
        /// Returns the current Board
        static const Board& getBoard();
        /// Sets up a new Board with starting Tile for a new game
        static void gameInit();
        /// Returns all following Tiles to be played
        static const TileStack* getTileStack();
        /// Gets all possible legal moves with the given Tile and current Board
        static std::vector<Move> getValidMoves(Tile& tile);
        /// Makes the given Move
        static void makeMove(const Move& move);
        /// Returns whether the given tile is fully surrounded by other tiles
        static unsigned int isSurrounded(int tileID);
    
    private:
    
        // current Board
        static Board board;
        // remaining Tiles to be played
        static TileStack* tileStack;
    
};*/