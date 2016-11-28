#include "Move.h"

Move& Move::operator=(const Move& other)
{
    this->tile = other.tile;
    this->coord = new Coord(*other.coord);
    this->rotation = other.rotation;
    this->meepleLocation = other.meepleLocation;
    this->hasCrocodile = other.hasCrocodile;

    this->placesTile = other.placesTile;
    this->pickupMeeple = other.pickupMeeple;

    return *this;
}

Move::Move(const Move& other)
{
    this->tile = other.tile;
    this->coord = new Coord(*other.coord);
    this->rotation = other.rotation;
    this->meepleLocation = other.meepleLocation;
    this->hasCrocodile = other.hasCrocodile;

    this->placesTile = true;
    this->pickupMeeple = false;
}

// With Coord Object
Move::Move(Tile& tile, const Coord& coord)  // No rotation, meeple, or crocodile
{
    this->tile = &tile;
    this->coord = new Coord(coord);
    this->rotation = 0;
    this->meepleLocation = -1;
    this->hasCrocodile = false;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation) // No meeple or crocodile
{
    this->tile = &tile;
    this->coord = new Coord(coord);
    this->rotation = rotation;
    this->meepleLocation = -1;
    this->hasCrocodile = false;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation, unsigned int meepleLocation) // Meeple
{
    this->tile = &tile;
    this->coord = new Coord(coord);
    this->rotation = rotation;
    this->meepleLocation = meepleLocation;
    this->hasCrocodile = false;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, const Coord& coord, unsigned int rotation, bool hasCrocodile) // Crocodile
{
    this->tile = &tile;
    this->coord = new Coord(coord);
    this->rotation = rotation;
    this->meepleLocation = -1;
    this->hasCrocodile = hasCrocodile;

    this->placesTile = true;
    this->pickupMeeple = false;
}

// No Coord Object
Move::Move(Tile& tile, unsigned int x, unsigned int y) // No rotation, meeple, or crocodile
{
    this->tile = &tile;
    this->coord = new Coord(x, y);
    this->rotation = 0;
    this->meepleLocation = -1;
    this->hasCrocodile = false;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation) // No meeple or crocodile
{
    this->tile = &tile;
    this->coord = new Coord(x, y);
    this->rotation = rotation;
    this->meepleLocation = -1;
    this->hasCrocodile = false;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, unsigned int meepleLocation) // Meeple
{
    this->tile = &tile;
    this->coord = new Coord(x, y);
    this->rotation = rotation;
    this->meepleLocation = meepleLocation;
    this->hasCrocodile = false;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, unsigned int x, unsigned int y, unsigned int rotation, bool hasCrocodile) // Crocodile
{
    this->tile = &tile;
    this->coord = new Coord(x, y);
    this->rotation = rotation;
    this->meepleLocation = -1;
    this->hasCrocodile = hasCrocodile;

    this->placesTile = true;
    this->pickupMeeple = false;
}

Move::Move(Tile& tile, bool pickupMeeple)// pickup or place extra meeple
{
    this->tile = &tile;
    this->coord = nullptr;
    this->rotation = 0;
    this->meepleLocation = -1;
    this->hasCrocodile = false;

    this->placesTile = false;
    this->pickupMeeple =  pickupMeeple;
}

Move::Move(bool throwaway) // passes
{
    this->placesTile = false;
    this->pickupMeeple = false;
}

Move::~Move()
{
    //delete this->coord;
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

bool Move::getPlacesTile() const {
    return this->placesTile;
}

bool Move::getPickupMeeple() const {
    return this->pickupMeeple;
}

bool Move::getPlaceExtraMeeple() const {
    return !this->placesTile && !this->pickupMeeple;
}