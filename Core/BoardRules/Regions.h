#ifndef __REGIONS_H
#define __REGIONS_H

#include "../Tiles/Tile.h"

#include <unordered_map>

class Regions
{
    public:
        int addConnection(const Tile& newTile, const Tile **  boarderingTiles);
        int addMeeple(unsigned int playerNumber, unsigned int tileID, unsigned int edge);
        int checkOwner(unsigned int tileID, unsigned int edge);
        Tile * getRegion(unsigned int tileID, unsigned int edge);

    private:
        struct regionSet* createRegion(unsigned int tileID, unsigned int edge, TerrainType type);
        int  countEdgesTillCompletion(unsigned int placedTileID);
        void mergeRegions(unsigned int placedTileID, unsigned int placedEdge, unsigned int connectingTileID, unsigned int connectingEdge);
        std::unordered_map<unsigned int, struct regionSet **> regionTracker;    //Takes (tileID, edge) returns set pointer
        struct meeple ownerMeeples[TOTAL_MEEPLES];
};

struct tileNode
{
    tileNode() {
        previous = NULL;
        next = NULL;
        preyCounts = new unsigned int[NUM_PREY];
        tileId = 0;
        edge = 0;
    };

    ~tileNode() {
        delete[] preyCounts;
    }

    unsigned int tileID;
    unsigned int edge;
    unsigned int * preyCounts;
    struct tileNode *previous;
    struct tileNode *next;
    unsigned int preyValues[NUM_PREY];
};

struct regionSet
{
    regionSet() {
        head = NULL;
        tail = NULL;
        player1Meeples = 0;
        player2Meeples = 0;
        edgesTillCompletion = 0;
    };

    unsigned int player1Meeples;
    unsigned int player2Meeples;
    unsigned int edgesTillCompletion;
    TerrainType type;
    struct tileNode *head;
    struct tileNode *tail;
};

struct meeple
{
    meeple() {
        ownedRegion = NULL;
        inUse = false;
    };

    bool inUse;
    struct regionSet *ownedRegion;
};

#endif
