#include "Move.h"

Move::Move(Tile& t, const Coord& c)
{
	this->tile = &t;
	this->coord = &c;
	this->rotation = 0;
}

Move::Move(Tile& t, unsigned int x, unsigned int y)
{
	this->tile = &t;
	this->coord = new Coord(x, y);
	this->rotation = 0;
}

Move::Move(Tile& t, const Coord& c, unsigned int r)
{
	this->tile = &t;
	this->coord = &c;
	this->rotation = r;
}

Move::Move(Tile& t, unsigned int x, unsigned int y, unsigned int r)
{
	this->tile = &t;
	this->coord = new Coord(x, y);
	this->rotation = r;
}

std::ostream &operator<<(std::ostream &out, Move move)
{
    out << "PLACE " << move.getTile() << " AT " << move.getCoord() << " " << (move.getRotation() * 90);
    return out;
}

Tile& Move::getTile() const {
    return *this->tile;
}

const Coord& Move::getCoord() const {
    return *this->coord;
}

unsigned int Move::getRotation() const {
	return this->rotation;
}
