#include "Move.h"

// With Coord Object
Move::Move(Tile& tile, const Coord& coord)  // No rotation, meeple, or crocodile
{
	this->tile = &tile;
	this->coord = &coord;
	this->rotation = 0;
	this->meepleLocation = -1;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation) // No meeple or crocodile
{
	this->tile = &tile;
	this->coord = &coord;
	this->rotation = rotation;
	this->meepleLocation = -1;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation, unsigned int meepleLocation) // Meeple
{
	this->tile = &tile;
	this->coord = &coord;
	this->rotation = rotation;
	this->meepleLocation = meepleLocation;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation, bool hasCrocodile) // Crocodile
{
	this->tile = &tile;
	this->coord = &coord;
	this->rotation = rotation;
	this->meepleLocation = -1;
	this->hasCrocodile = hasCrocodile;
}

// No Coord Object
Move::Move(Tile& tile, unsigned int x, unsigned int y) // No rotation, meeple, or crocodile
{
	this->tile = &tile;
	this->coord = new Coord(x, y);
	this->rotation = 0;
	this->meepleLocation = -1;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation) // No meeple or crocodile
{
	this->tile = &tile;
	this->coord = new Coord(x, y);
	this->rotation = rotation;
	this->meepleLocation = -1;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, unsigned int meepleLocation) // Meeple
{
	this->tile = &tile;
	this->coord = new Coord(x, y);
	this->rotation = rotation;
	this->meepleLocation = meepleLocation;
	this->hasCrocodile = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, bool hasCrocodile) // Crocodile
{
	this->tile = &tile;
	this->coord = new Coord(x, y);
	this->rotation = rotation;
	this->meepleLocation = -1;
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

int Move::getMeepleLocation() const {
	return this->meepleLocation;
}

bool Move::getHasCrocodile() const {
	return this->hasCrocodile;
}