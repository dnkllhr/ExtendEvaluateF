#ifndef __COORD_H
#define __COORD_H

#include <ostream>

class Coord {
    public:
        int getX() const;
        int getY() const;

        friend std::ostream& operator<<(std::ostream &out, Coord coord);

        Coord()=delete;
        Coord(int x, int y);

    private:
        int x;
        int y;
};

#endif
