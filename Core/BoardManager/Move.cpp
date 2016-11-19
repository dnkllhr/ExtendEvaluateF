#include "Move.h"

Move::Move(const Tile& t, const Coord& c)
{
	this->tile = t;
	this->coord = c;
}

const Tile& Move::getTile() const {
    return this->tile;
}

const Coord& Move::getCoord() const {
    return this->coord;
}
