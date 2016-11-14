#ifndef __BOARD_H
#define __BOARD_H

#include "../Tiles/Tile.h"
#include "../BoardManager/Coord.h"

class Board {
        
	public:
	
		// Creates a new Board as a grid of tiles of the maximum needed size
		Board();
		// Returns the Board as a 2D Array of Tiles
		const Array<Array<Tile&>&>& getBoard();
		// Gets the Tile at the given Coord
		const Tile& get(const Coord& coord);
		// Place the given Tile at the given Coord
		void place(const Tile& tile, const Coord& coord);
        
	private:
	
		Array<Array<Tile&>&>& board;
        
};

#endif
