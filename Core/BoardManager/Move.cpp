#include "Move.h"

Move::Move(const Tile& t, const Coord& c)
{
	this->tile = t;
	this->coord = c;
}

Move::Move(const Tile& t, unsigned int x, unsigned int y)
{
	thile->tile = t;
	this->coord(x, y);
}

const Tile& Move::getTile() const {
    return this->tile;
}

const Coord& Move::getCoord() const {
    return this->coord;
}
