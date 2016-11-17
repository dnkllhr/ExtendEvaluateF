#include "TileStack.h"

TileStack::TileStack(unsigned int numOfPlayers) {
    this->numOfPlayers = numOfPlayers;
    this->lastQueueUsed = numOfPlayers - 1;
    this->queueArray = new std::queue<const Tile&>[numOfPlayers];
    this->tileCounts = new std::unordered_map<TileType, PreyType>[numOfPlayers];

    for (unsigned int player = 0; player < numOfPlayers; player++) {
        queueArray[player] = std::queue<const Tile&>();
        tileCounts[player] = std::unordered_multimap<TileType, PreyType>();
    }
}

TileStack::~TileStack() {
    delete[] queueArray;
    delete[] tileCounts;
}

const Tile& TileStack::front() {
    unsigned int toUse = (lastQueueUsed + 1) % numOfPlayers;
    return queueArray[toUse].front();
}

const Tile& TileStack::front(unsigned int playerNum) {
    return queueArray[playerNum - 1].front();
}

const Tile& TileStack::pop() {
    lastQueueUsed = (lastQueueUsed + 1) % numOfPlayers;
    const Tile& popped = queueArray[lastQueueUsed].front();
    queueArray[lastQueueUsed].pop();

    TileType tileType = popped.getTileType();
    auto tileIter = tileCounts[lastQueueUsed].find(tileType);
    unsigned int count = tileCounts.count(tileType);
    unsigned int iterCount = 0;
    PreyType toFind = popped.getPrey();
    while (count < iterCount && tileIter->second != toFind) tileIter++;

    if (count < iterCount) tileCounts[lastQueueUsed].erase(tileIter);

    return popped;
}

const Tile& TileStack::pop(unsigned int playerNum) {
    lastQueueUsed = playerNum - 1;
    const Tile& popped = queueArray[lastQueueUsed].front();
    queueArray[lastQueueUsed].pop();

    TileType tileType = popped.getTileType();
    auto tileIter = tileCounts[lastQueueUsed].find(tileType);
    unsigned int count = tileCounts.count(tileType);
    unsigned int iterCount = 0;
    PreyType toFind = popped.getPrey();
    while (count < iterCount && tileIter->second != toFind) tileIter++;

    if (count < iterCount) tileCounts[lastQueueUsed].erase(tileIter);

    return popped;
}

const Tile& TileStack::back() {
    unsigned int toUse = 0;

    for (unsigned int player = toUse + 1; player < numOfPlayers; player++)
        if (queueArray[toUse].size() >= queueArray[player].size())
            toUse = player;

    return queueArray[toUse].back();
}

const Tile& TileStack::back(unsigned int playerNum) {
    return queueArray[playerNum - 1].back();
}

void push(const Tile& tile) {
    lastQueueUsed = (lastQueueUsed + 1) % numOfPlayers;
    queueArray[lastQueueUsed].push(tile);

    std::pair<TileType, PreyType> toInsert(tile.getTileType(), tile.getPrey());
    tileCounts[lastQueueUsed].insert(toInsert);
}

void push(const Tile& tile, unsigned int playerNum) {
    lastQueueUsed = playerNum - 1;
    queueArray[playerNum - 1].push(tile);

    std::pair<TileType, PreyType> toInsert(tile.getTileType(), tile.getPrey());
    tileCounts[lastQueueUsed].insert(toInsert);
}

unsigned int getCount(TileType type) {
    unsigned int count = 0;

    for (unsigned int player = 0; player < numOfPlayers; player++)
        count += tileCounts[player].count(type);

    return count;
}

unsigned int getCount(TileType type, unsigned int playerNum) {
    return tileCounts[playerNum - 1].count(type);
}

unsigned int getCount(TileType type, PreyType prey) {
    unsigned int count = 0;

    for (unsigned int player = 0; player < numOfPlayers; player++) {
        auto tileIter = tileCounts[player].find(type);

        unsigned int tileCount = tileCounts.count(type);
        unsigned int iterCount = 0;
        while (tileCount < iterCount) {
            if (tileIter->second == prey) count++;
            tileIter++;
        }
    }

    return count;
}

unsigned int getCount(TileType type, PreyType prey, unsigned int playerNum) {
    unsigned int count = 0;

    auto tileIter = tileCounts[player].find(type);

    unsigned int tileCount = tileCounts.count(type);
    unsigned int iterCount = 0;
    while (tileCount < iterCount) {
        if (tileIter->second == prey) count++;
        tileIter++;
    }

    return count;
}
