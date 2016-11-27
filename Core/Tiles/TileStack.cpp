#include "TileStack.h"

TileStack::TileStack(unsigned int numOfPlayers) {
    this->numOfPlayers = numOfPlayers;
    this->lastQueueUsed = numOfPlayers - 1;
    this->queueArray = new std::queue<Tile*>[numOfPlayers];
    this->tileCounts = new std::unordered_multimap<int, PreyType>[numOfPlayers];

    for (unsigned int player = 0; player < numOfPlayers; player++) {
        queueArray[player] = std::queue<Tile*>();
        tileCounts[player] = std::unordered_multimap<int, PreyType>();
    }
}

TileStack::~TileStack() {
    delete[] queueArray;
    delete[] tileCounts;
}

Tile& TileStack::front() {
    unsigned int toUse = (lastQueueUsed + 1) % numOfPlayers;
    return *queueArray[toUse].front();
}

Tile& TileStack::front(unsigned int playerNum) {
    return *queueArray[playerNum - 1].front();
}

Tile& TileStack::pop() {
    lastQueueUsed = (lastQueueUsed + 1) % numOfPlayers;
    Tile& popped = *queueArray[lastQueueUsed].front();
    queueArray[lastQueueUsed].pop();

    TileType tileType = popped.getTileType();
    auto tileIter = tileCounts[lastQueueUsed].find(static_cast<int>(tileType));
    unsigned int count = tileCounts[lastQueueUsed].count(static_cast<int>(tileType));
    unsigned int iterCount = 0;
    PreyType toFind = popped.getPrey();
    while (count < iterCount && tileIter->second != toFind) tileIter++;

    if (count < iterCount) tileCounts[lastQueueUsed].erase(tileIter);

    return popped;
}

Tile& TileStack::pop(unsigned int playerNum) {
    lastQueueUsed = playerNum - 1;
    Tile& popped = *queueArray[lastQueueUsed].front();
    queueArray[lastQueueUsed].pop();

    TileType tileType = popped.getTileType();
    auto tileIter = tileCounts[lastQueueUsed].find(static_cast<int>(tileType));
    unsigned int count = tileCounts[lastQueueUsed].count(static_cast<int>(tileType));
    unsigned int iterCount = 0;
    PreyType toFind = popped.getPrey();
    while (count < iterCount && tileIter->second != toFind) tileIter++;

    if (count < iterCount) tileCounts[lastQueueUsed].erase(tileIter);

    return popped;
}

Tile& TileStack::back() {
    unsigned int toUse = 0;

    for (unsigned int player = toUse + 1; player < numOfPlayers; player++)
        if (queueArray[toUse].size() >= queueArray[player].size())
            toUse = player;

    return *queueArray[toUse].back();
}

Tile& TileStack::back(unsigned int playerNum) {
    return *queueArray[playerNum - 1].back();
}

void TileStack::push(Tile& tile) {
    lastQueueUsed = (lastQueueUsed + 1) % numOfPlayers;
    queueArray[lastQueueUsed].push(&tile);

    std::pair<int, PreyType> toInsert(static_cast<int>(tile.getTileType()), tile.getPrey());
    tileCounts[lastQueueUsed].insert(toInsert);
}

void TileStack::push(Tile& tile, unsigned int playerNum) {
    lastQueueUsed = playerNum - 1;
    queueArray[playerNum - 1].push(&tile);

    std::pair<int, PreyType> toInsert(static_cast<int>(tile.getTileType()), tile.getPrey());
    tileCounts[lastQueueUsed].insert(toInsert);
}

unsigned int TileStack::getCount(TileType type) {
    unsigned int count = 0;

    for (unsigned int player = 0; player < numOfPlayers; player++)
        count += tileCounts[player].count(static_cast<int>(type));

    return count;
}

unsigned int TileStack::getCount(TileType type, unsigned int playerNum) {
    return tileCounts[playerNum - 1].count(static_cast<int>(type));
}

unsigned int TileStack::getCount(TileType type, PreyType prey) {
    unsigned int count = 0;

    for (unsigned int player = 0; player < numOfPlayers; player++) {
        auto tileIter = tileCounts[player].find(static_cast<int>(type));

        unsigned int tileCount = tileCounts[player].count(static_cast<int>(type));
        unsigned int iterCount = 0;
        while (tileCount < iterCount) {
            if (tileIter->second == prey) count++;
            tileIter++;
        }
    }

    return count;
}

unsigned int TileStack::getCount(TileType type, PreyType prey, unsigned int playerNum) {
    unsigned int count = 0;

    auto tileIter = tileCounts[playerNum - 1].find(static_cast<int>(type));

    unsigned int tileCount = tileCounts[playerNum - 1].count(static_cast<int>(type));
    unsigned int iterCount = 0;
    while (tileCount < iterCount) {
        if (tileIter->second == prey) count++;
        tileIter++;
    }

    return count;
}

std::queue<Tile*> TileStack::getQueue(unsigned int playerNum) {
    return queueArray[playerNum - 1];
}
