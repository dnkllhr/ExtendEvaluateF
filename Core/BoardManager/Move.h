#ifndef __MOVE_H
#define __MOVE_H

#include "../Tiles/Tile.h"
#include "Coord.h"

class Move {
    public:
        Tile& getTile() const;
        const Coord& getCoord() const;
        unsigned int getRotation() const;
        int getMeepleLocation() const;
        bool getHasCrocodile() const;
        bool getPickupMeeple() const;

        friend std::ostream &operator<<(std::ostream &out, Move move);

        ~Move();

        Move(const Move& other);
        Move& operator=(const Move& other);
        
        // Coord object
        Move(Tile& tile, const Coord& coord); // No rotation, meeple, or crocodile
        Move(Tile& tile, const Coord& coord, unsigned int rotation); // No meeple or crocodile
        Move(Tile& tile, const Coord& coord, unsigned int rotation, unsigned int meepleLocation); // Meeple
        Move(Tile& tile, const Coord& coord, unsigned int rotation, bool hasCrocodile); // Crocodile

        // No Coord object
        Move(Tile& tile, unsigned int x, unsigned int y); // No rotation, meeple, or crocodile
        Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation); // No meeple or crocodile
        Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, unsigned int meepleLocation); // Meeple
        Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, bool hasCrocodile); // Crocodile
        //Special Case for no placabe tile
        Move(Tile& tile, bool pickupMeeple);

        Move()=delete;

    private:
        Tile* tile;
        const Coord* coord;
        unsigned int rotation;
        int meepleLocation; // -1 = no meeple/tiger
        bool hasCrocodile;
        bool pickupMeeple;
};

#endif
