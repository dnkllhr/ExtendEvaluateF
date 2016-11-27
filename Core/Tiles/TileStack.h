#ifndef __TILESTACK_H
#define __TILESTACK_H

#include "Tile.h"
#include <queue>
#include <unordered_map>

class TileStack {
    public:
        TileStack()=delete;
        TileStack(unsigned int numOfPlayers);
        ~TileStack();

        Tile& front(unsigned int playerNum);
        Tile& front();
        Tile& pop(unsigned int playerNum);
        Tile& pop();
        Tile& back(unsigned int playerNum);
        Tile& back();
        void push(Tile& tile, unsigned int playerNum);
        void push(Tile& tile);
        unsigned int getCount(TileType type, PreyType prey, unsigned int playerNum);
        unsigned int getCount(TileType type, PreyType prey);
        unsigned int getCount(TileType type, unsigned int playerNum);
        unsigned int getCount(TileType type);
        std::queue<Tile*> getQueue(unsigned int playerNum);

    private:
        std::queue<Tile*> * queueArray;
        std::unordered_multimap<int, PreyType> * tileCounts;
        unsigned int lastQueueUsed;
        unsigned int numOfPlayers;
};

#endif
