#ifndef __COORD_H
#define __COORD_H

class Coord {
        public:
                int getX();
                int getY();

                Coord()=delete;
                Coord(int x, int y);

        private:
                int x;
                int y;
};

#endif
