#ifndef __MOVE_H
#define __MOVE_H

#include "../Tiles/Tile.h"
#include "Coord.h"

class Move {
    public:
        Tile& getTile() const;
        const Coord& getCoord() const;
        unsigned int getRotation() const;

        friend std::ostream &operator<<(std::ostream &out, Move move);

        // No rotation, meeple, or crocodile
        Move(Tile& tile, const Coord& coord);
        Move(Tile& tile, unsigned int x, unsigned int y);

        // If you need to specify one, you must specify all (-1 = no meeple)
        // Figured this was better than having a lot more constructors
        Move(Tile& tile, const Coord& coord, unsigned int rotation, int meepleLocation, bool hasCrocodile);
        Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, int meepleLocation, bool hasCrocodile);

        Move()=delete;

    private:
        Tile* tile;
        const Coord* coord;
        unsigned int rotation;
        int meepleLocation; // -1 = no meeple/tiger
        bool hasCrocodile;
};

#endif
