#include "Move.h"

Move::Move(const Tile& t, const Coord& c)
{
	this->tile = t;
	this->coord = c;
}

const Tile& Move::getTile() {
    return this->tile;
}

const Coord& Move::getCoord() {
    return this->coord;
}
