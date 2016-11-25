#include "Coord.h"

Coord::Coord(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::ostream& operator<<(std::ostream &out, Coord coord)
{
    out << coord.getX() << " " << coord.getY();
    return out;
}

int Coord::getX() const {
    return this->x;
}

int Coord::getY() const {
    return this->y;
}
