#ifndef __REGIONS_H
#define __REGIONS_H

#include "../Tiles/Tile.h"
#include <unordered_map>

#define MEEPLES_PER_PLAYER   7
#define TOTAL_MEEPLES   (MEEPLES_PER_PLAYER * 2)

#define CROCS_PER_PLAYER   2
#define TOTAL_CROCS        (CROCS_PER_PLAYER * 2)

#define OWNER_P1        1
#define OWNER_TIE       0
#define OWNER_P2        -1
#define OWNER_NONE      -2

class Regions
{
    public:
        static int                  addConnection(const Tile& newTile, const Tile **  boarderingTiles);

        static int                  addMeeple(unsigned int playerNumber, unsigned int tileID, unsigned int edge);
        static int                  removeMeeple(unsigned int tileID, unsigned int edge);
        static unsigned int         meeplesAvailable(unsigned int playerNumber);
        static int                  checkOwner(unsigned int tileID, unsigned int edge);

        static int                  addCroc(unsigned int playerNumber, unsigned int tileID, unsigned int edge);
        static unsigned int         crocsAvailable(unsigned int playerNumber);
        
        static struct regionSet **  getRegions(unsigned int tileID);
        static bool                 checkRegionExistence(unsigned int tileID, unsigned int edge);
        static unsigned int         checkRegionEdgesTillCompletion(unsigned int tileID, unsigned int edge);

#ifdef testing
        static void                 clearRegionTracker();
        static void                 clearOwnerMeeples();
#endif

    private:
        static struct regionSet *   createRegion(unsigned int tileID, unsigned int edge, TerrainType type);
        static int                  countEdgesTillCompletion(unsigned int placedTileID);
        static void                 mergeRegions(unsigned int placedTileID, unsigned int placedEdge, unsigned int connectingTileID, unsigned int connectingEdge);

        static std::unordered_map<unsigned int, struct regionSet **> regionTracker;    //Takes (tileID, edge) returns set pointer

        static struct meeple ownerMeeples[TOTAL_MEEPLES];
        static unsigned int availableMeeples[2];

        static struct croc ownerCrocs[TOTAL_CROCS];
        static unsigned int availableCrocs[2];
};

struct tileNode
{
    tileNode() {
        previous = NULL;
        next = NULL;
        preyCounts = new unsigned int[NUM_PREY];
        tileID = 0;
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

struct croc
{
    croc() {
        ownedRegion = NULL;
        inUse = false;
    };

    bool inUse;
    struct regionSet *ownedRegion;
};

#endif
