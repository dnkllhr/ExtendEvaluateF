#ifndef __BOARD_H
#define __BOARD_H

#include "../Tiles/Tile.h"
#include "../Tiles/TileStack.h"
#include "../BoardManager/Coord.h"
#include "../BoardManager/Move.h"

class Board {
        
	public:
	
		// Creates a new Board as a grid of tiles of the maximum needed size
		Board();
		// Returns the Board as a 2D Array of Tiles
		const Array<Array<Tile&>>& getBoard();
		// Gets the Tile at the given Coord
		const Tile& get(const Coord& coord);
		// For a given Move, place the specifed Tile at the specified Coord
		void place(const Move& move);
        
	private:
	
		Array<Array<Tile&>> board;
        std::set<unsigned int> availableLocations;
};

#endif
