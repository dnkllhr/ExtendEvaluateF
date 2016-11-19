#ifndef __BOARD_H
#define __BOARD_H

#include "../Tiles/Tile.h"
#include "../Tiles/TileStack.h"
#include "../BoardManager/Coord.h"
#include "../BoardManager/Move.h"
#include <unordered_set>

class Board {
    public:
        // Creates a new Board as a grid of tiles of the maximum needed size
        Board();
        // Returns the Board as a 2D Array of Tiles
        static const Array<Array<Tile&>>& getBoard();
        // Gets the Tile at the given Coord
        static const Tile& get(const Coord& coord);
        //Gets the Tile for a given tileID
        static const Tile& get(unsigned int tileID);
        //Find a way to get the coordinates from the ID
        static const Move& getCoordinates(unsigned int tileID);
        // For a given Move, place the specifed Tile at the specified Coord
        static void place(const Move& move);
        // Returns a set of gridID's of loactions adjacent to the border of already placed tiles
        static const std::unordered_set<unsigned int>& getAvailableLocations();

    private:
        //Keep track of the tile coordinates;
        static std::unordered_map<unsigned int , Move *> tileIDTracker;
        static std::unordered_set<unsigned int> availableLocations;
};

#endif
