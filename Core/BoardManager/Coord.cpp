#include "Coord.h"

Coord::Coord(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Coord::setX(int x) {
        this->x = x;
}

void Coord::setY(int y) {
        this->y = y;
}

int Coord::getX() {
        return this->x;
}

int Coord::getY() {
        return this->y;
}
