#ifndef __BOARD_MANAGER_H
#define __BOARD_MANAGER_H

#include "../../Common/Coord.h"
#include "../../Common/Move.h"

class BoardManager {
	
        public:
        
			/// Creates a new BoardManager
        	BoardManager();
        	/// Returns the current Board
        	Board getBoard();
        	/// Displays the current Board
        	void printBoard();
        	/// Sets up a new Board with starting Tile for a new game
        	void gameInit();
        	/// Returns the next Tile to be played
        	Tile nextTile();
        	/// Returns all following Tiles to be played
        	Vector<Tile> getTileOrder();
        	/// Gets all possible legal moves with the given Tile and current Board
        	Vector<Move> getLegalMoves(Tile tile);
        	/// Makes the given Move
        	void makeMove(Move move);
	
		private:
		
			// current Board
			Board board;
			// remaining Tiles to be played
			Vector<Tile> tileOrder;
			// for displaying purposes, the min (x,y) and max (x,y) that are currently in use
			Coord minCoord;
			Coord maxCoord;
        
};

#endif
