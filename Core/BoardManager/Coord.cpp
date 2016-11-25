#include "Coord.h"

Coord::Coord(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::ostream &operator<<(std::ostream &out, Coord coord)
{
    out << this->x << " " << this->y;
    return out;
}

void Coord::setX(int x) {
    this->x = x;
}

void Coord::setY(int y) {
    this->y = y;
}

int Coord::getX() const {
    return this->x;
}

int Coord::getY() const {
    return this->y;
}
