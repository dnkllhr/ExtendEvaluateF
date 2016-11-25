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

        // default rotation = 0
        Move(Tile& t, const Coord& c);
        Move(Tile& t, unsigned int x, unsigned int y);

        // can specify rotation ( 90 * r degrees CCW )
        Move(Tile& t, const Coord& c, unsigned int r);
        Move(Tile& t, unsigned int x, unsigned int y, unsigned int r);

        Move()=delete;

    private:
        Tile& tile;
        Coord& coord;
        unsigned int rotation;
};

#endif
