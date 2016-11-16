#ifndef __REGIONS_H
#define __REGIONS_H

#include "../Tiles/Tile.h"
#include <unordered_map>

class Regions
{
    public:
        static bool validTilePlacement(const Tile& newTile, const Tile ** boarderingTiles);
        /// Determines if a placement of a meeple is valid where placed is the new tile that was just placed and edge index is the edge index in which the meeple was placed.
        static bool validMeeplePlacement(const Tile& newTile, unsigned int edgeIndex);

        int addConnection(const Tile& newTile, const Tile **  boarderingTiles);
        int addMeeple(int playerNumber, int tileID, int edge);
        int checkOwner(int tileID, int edge);

    private:
        void createRegion(int tileID, int edge);
        int  countEdgesTillCompletion(int placedTileID);
        void mergeRegions(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge);
        std::unordered_map<int, struct regionSet **> regionTracker;    //Takes (tileID, edge) returns set pointer
        struct meeple ownerMeeples[TOTAL_MEEPLES];
};

struct tileNode
{
    tileNode() {
        previous = NULL;
        next = NULL;
        tileId = 0;
        edge = 0;
    };

    unsigned int tileID;
    unsigned int edge;
    struct tileNode *previous;
    struct tileNode *next;
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
