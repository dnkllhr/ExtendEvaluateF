#ifndef __REGIONS_H
#define __REGIONS_H

#include "Rules.h"
#include "../BoardManager/Move.h"
#include "../Tiles/Tile.h"
#include <unordered_map>
#include <memory>

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
        static std::shared_ptr<struct regionSet> * addConnection(const Tile& newTile, const Tile **  boarderingTiles, std::unordered_map<unsigned int, std::shared_ptr<struct regionSet> *> * tracker = NULL);
        static int addMeeple(unsigned int playerNumber, unsigned int tileID, unsigned int edge, std::unordered_map<unsigned int, std::shared_ptr<struct regionSet> *> * tracker = NULL);
        static int addMeepleSpecial(unsigned int playerNumber, unsigned int tileID, std::unordered_map<unsigned int, std::shared_ptr<struct regionSet> *> * tracker = NULL);
        static int specialRemoveMeeple(unsigned int playerNumber, unsigned int tileID);
        static int checkOwner(unsigned int tileID, unsigned int edge, std::unordered_map<unsigned int, std::shared_ptr<struct regionSet> *> * tracker = NULL);
        static std::shared_ptr<struct regionSet> * getRegions(unsigned int tileID);
        static int removeMeeple(unsigned int tileID, unsigned int edge, std::unordered_map<unsigned int, std::shared_ptr<struct regionSet> *> * tracker = NULL);
        static bool checkRegionExistence(unsigned int tileID, unsigned int edge);
        static unsigned int checkRegionEdgesTillCompletion(unsigned int tileID, unsigned int edge);
        static struct moveResult tryMove(const Tile& tile, const Tile ** boarderingTiles);

        static unsigned int meeplesAvailable(unsigned int playerNumber);

        static int addCroc(unsigned int playerNumber, unsigned int tileID);
        static unsigned int crocsAvailable(unsigned int playerNumber);

#ifdef __testing
        static void clearRegionTracker();
        static void clearOwnerMeeples();
#else

    private:
#endif
        static std::shared_ptr<struct regionSet> createRegion(unsigned int tileID, unsigned int edge, TerrainType type);
        static int countEdgesTillCompletion(unsigned int placedTileID);
        static void mergeRegions(unsigned int placedTileID, unsigned int placedEdge, unsigned int connectingTileID, unsigned int connectingEdge);

        static std::unordered_map<unsigned int, std::shared_ptr<struct regionSet> *> regionTracker;    //Takes (tileID, edge) returns set pointer

        static struct meeple ownerMeeples[TOTAL_MEEPLES];
        static unsigned int availableMeeples[2];

        static struct croc ownerCrocs[TOTAL_CROCS];
        static unsigned int availableCrocs[2];
};

struct moveResult
{
    unsigned int edgesTillCompletion;
    int player1ScoreChange;
    int player2ScoreChange;
};

struct tileNode
{
    tileNode() {
        preyCounts = new unsigned int[NUM_PREY];
        tileID = 0;
        edge = 0;
    };

    tileNode(const struct tileNode& other) : tileID(other.tileID), edge(other.edge) {
        std::copy(other.preyCounts, other.preyCounts + NUM_PREY, this->preyCounts);
        this->previous = std::shared_ptr<struct tileNode>(new struct tileNode(*other.previous));
        this->next = std::shared_ptr<struct tileNode>(new struct tileNode(*other.next));
    };

    struct tileNode& operator=(const struct tileNode& other) {
        this->tileID = other.tileID;
        this->edge = other.edge;
        std::copy(other.preyCounts, other.preyCounts + NUM_PREY, this->preyCounts);
        this->previous = std::shared_ptr<struct tileNode>(new struct tileNode(*other.previous));
        this->next = std::shared_ptr<struct tileNode>(new struct tileNode(*other.next));

        return *this;
    };

    ~tileNode() {
        delete[] preyCounts;
    }

    unsigned int tileID;
    unsigned int edge;
    unsigned int * preyCounts;
    std::shared_ptr<struct tileNode> previous;
    std::shared_ptr<struct tileNode> next;
};

struct regionSet
{
    regionSet() {
        player1Meeples = 0;
        player2Meeples = 0;
        edgesTillCompletion = 0;
        hasCroc = false;
    };

    regionSet(const struct regionSet& other) : player1Meeples(other.player1Meeples), player2Meeples(other.player2Meeples), type(other.type) {
        this->head = std::shared_ptr<struct tileNode>(new struct tileNode(*head));
        this->tail = std::shared_ptr<struct tileNode>(new struct tileNode(*tail));
    };

    struct regionSet& operator=(const struct regionSet& other) {
        this->player1Meeples = other.player1Meeples;
        this->player2Meeples = other.player2Meeples;
        this->head = std::shared_ptr<struct tileNode>(new struct tileNode(*head));
        this->tail = std::shared_ptr<struct tileNode>(new struct tileNode(*tail));

        return *this;
    };

    unsigned int player1Meeples;
    unsigned int player2Meeples;
    unsigned int edgesTillCompletion;
    TerrainType type;
    std::shared_ptr<struct tileNode> head;
    std::shared_ptr<struct tileNode> tail;
    bool hasCroc;
};

struct meeple
{
    meeple()
    {
        tileID = 0;
        ownedRegion = NULL;
        inUse = false;
    };
    unsigned int tileID;
    bool inUse;
    std::shared_ptr<struct regionSet> ownedRegion;
};

struct croc
{
    croc()
    {
        ownedRegions = NULL;
        inUse = false;
    };

    bool inUse;
    std::shared_ptr<struct regionSet> *ownedRegions;
};

#endif
