#ifndef __MOVE_H
#define __MOVE_H

class Move {
    public:
        const Tile& getTile() const;
        const Coord& getCoord() const;

        Move(const Tile& t, const Coord& c);
        Move()=delete;

    private:
        Tile& tile;
        Coord& coord;
};

#endif
