#ifndef __BOARD_MANAGER_H
#define __BOARD_MANAGER_H

#include "../Tiles/Tile.h"
#include "Coord.h"
#include "Move.h"

#include <vector>

class BoardManager {
        
        public:
        
                /// Creates a new BoardManager
                BoardManager();
                /// Prints board
                std::ostream& operator<<(std::ostream& os, const BoardManager& obj);
                /// Returns the current Board
                const Board& getBoard();
                /// Sets up a new Board with starting Tile for a new game
                void gameInit();
                /// Returns the next Tile to be played
                const Tile& nextTile();
                /// Returns all following Tiles to be played
                const std::vector<Tile&>& getTileOrder();
                /// Gets all possible legal moves with the given Tile and current Board
                std::vector<Move> getLegalMoves(const Tile& tile);
                /// Makes the given Move
                void makeMove(const Move& move);
        
        private:
        
                // current Board
                Board board;
                // remaining Tiles to be played
                std::vector<Tile&> tileOrder;
                // for displaying purposes, the min (x,y) and max (x,y) that are currently in use
                Coord minCoord;
                Coord maxCoord;
        
};

#endif
