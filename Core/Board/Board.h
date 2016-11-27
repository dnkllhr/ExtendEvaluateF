#ifndef __BOARD_H
#define __BOARD_H
#define NUMBER_OF_PLAYABLE_TILES 76

#include "../../Common/Array.h"
#include "../Tiles/Tile.h"
#include "../Tiles/TileStack.h"
#include "../BoardManager/Coord.h"
#include "../BoardManager/Move.h"
#include <unordered_set>
#include <stdexcept>

class Board {
    public:
        // Initializes or resets the Board to a blank/empty grid
        static int set();
        // Returns the Board as a 2D Array of Tiles
        static const Array<Array<Tile*>>& getBoard();
        // Gets the Tile at the given Coord
        static const Tile* get(const Coord& coord);
        //Gets the Tile for a given tileID
        static const Tile* get(unsigned int tileID);
        //Get all neighbors of a given Coord or place Tile
        static const Tile** getBorderingTiles(const Coord& coord);
        static const Tile** getBorderingTiles(const Tile& tile);
        //Find a way to get the coordinates from the ID
        static const Coord& getCoordinatesFromTileId(unsigned int tileID);
        // GridId is used for the set of Available Locations
        static const Coord getCoordinatesFromGridId(unsigned int gridId);
        // Get the GridId for a given Coord
        static unsigned int getGridId(const Coord& coord);
        static unsigned int getGridId(unsigned int x, unsigned int y);
        // For a given Move, place the specifed Tile at the specified Coord
        static void place(const Move& move);
        // Returns a set of gridID's of loactions adjacent to the border of already placed tiles
        static const std::unordered_set<unsigned int>& getAvailableLocations();

#ifndef testing
    private:
#endif
        static Array<Array<Tile*>> board;
        //Keep track of the tile coordinates;
        static std::unordered_map<unsigned int , Move> tileIDTracker;
        static std::unordered_set<unsigned int> availableLocations;
        static const unsigned int boardWidth;
        static const unsigned int boardHeight;
};

#endif
