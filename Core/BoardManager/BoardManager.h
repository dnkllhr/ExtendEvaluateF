#ifndef __BOARD_MANAGER_H
#define __BOARD_MANAGER_H
#define NUMBER_OF_PLAYERS 2

#include "../Tiles/Tile.h"
#include "../Board/Board.h"
#include "../BoardRules/Rules.h"
#include "Coord.h"
#include "Move.h"

#include <vector>

class BoardManager {
    
    public:
    
        /// Creates a new BoardManager
        BoardManager();
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
    
};

#endif
