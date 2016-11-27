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

        const Tile& front(unsigned int playerNum) const;
        const Tile& front() const;
        const Tile& pop(unsigned int playerNum);
        const Tile& pop();
        const Tile& back(unsigned int playerNum);
        const Tile& back();
        void push(const Tile& tile, unsigned int playerNum);
        void push(const Tile& tile);
        unsigned int getCount(TileType type, PreyType prey, unsigned int playerNum);
        unsigned int getCount(TileType type, PreyType prey);
        unsigned int getCount(TileType type, unsigned int playerNum);
        unsigned int getCount(TileType type);
        std::queue<const Tile*> getQueue(unsigned int playerNum) const;

    private:
        std::queue<const Tile*> * queueArray;
        std::unordered_multimap<int, PreyType> * tileCounts;
        unsigned int lastQueueUsed;
        unsigned int numOfPlayers;
};

#endif
