#include "Move.h"

Move::Move(Tile& tile, const Coord& coord)
{
	this->tile = &tile;
	this->coord = &coord;
	this->rotation = 0;
	this->meepleLocation = -1;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y)
{
	this->tile = &tile;
	this->coord = new Coord(x, y);
	this->rotation = 0;
	this->meepleLocation = -1;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation, int meepleLocation, bool hasCrocodile)
{
	this->tile = &tile;
	this->coord = &coord;
	this->rotation = rotation;
	this->meepleLocation = meepleLocation;
	this->hasCrocodile = hasCrocodile;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, int meepleLocation, bool hasCrocodile)
{
	this->tile = &tile;
	this->coord = new Coord(x, y);
	this->rotation = rotation;
	this->meepleLocation = meepleLocation;
	this->hasCrocodile = hasCrocodile;
}

/// TODO: Include meepleLocation and crocodile 
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
