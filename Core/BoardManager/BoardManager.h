#ifndef __BOARD_MANAGER_H
#define __BOARD_MANAGER_H

#include "../Tiles/Tile.h"
#include "../Board/Board.h"
#include "Coord.h"
#include "Move.h"

#include <vector>

class BoardManager {
    
    public:
    
        /// Creates a new BoardManager
        BoardManager();
        /// Returns the current Board
        const Board& getBoard();
        /// Sets up a new Board with starting Tile for a new game
        void gameInit();
        /// Returns the next Tile to be played
        const Tile& nextTile();
        /// Returns all following Tiles to be played
        const TileStack& getTileStack();
        /// Gets all possible legal moves with the given Tile and current Board
        std::vector<Move> getLegalMoves(const Tile& tile);
        /// Makes the given Move
        void makeMove(const Move& move);
		/// Returns whether the given tile is fully surrounded by other tiles
		bool isSurrounded(int tileID);
    
    private:
    
        // current Board
        Board board;
        // remaining Tiles to be played
        TileStack tileStack;
    
};

#endif
