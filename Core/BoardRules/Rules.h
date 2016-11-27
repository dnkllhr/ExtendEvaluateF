#ifndef __RULES_H
#define __RULES_H

#include "../Board/Board.h"
#include "../BoardManager/BoardManager.h"
#include "../Tiles/Tile.h"
#include "Regions.h"

#include <unordered_map>
#include <memory>

#define ROAD_VALUE              1
#define CASTLE_VALUE            2
#define CHURCH_VALUE            9
#define FIELD_CASTLE_VALUE      3
#define FIELD_CHURCH_VALUE      5



class GameRules
{
    public:
        static bool validTilePlacement(const Tile& placed, const Tile ** boarderingTiles);
        static bool validMeeplePlacement(const Tile& placed, unsigned int edgeIndex);
        static bool validMeeplePlacement(const Coord& location, unsigned int edgeIndex);
        static unsigned int getCurrentScore(unsigned int tileID, unsigned int edge);
        static unsigned int getCurrentScore(std::shared_ptr<struct regionSet> * currentRegions, unsigned int edge, const Tile * tile, unsigned int tilesSurrounded);
        static unsigned int scoreEdge(unsigned int tileID, unsigned int edge);
        static unsigned int getPlayerScore(unsigned int player);
    private:
        static unsigned int scoreRoad(std::shared_ptr<struct regionSet> currentSet, bool actuallyScore);
        static unsigned int scoreCastle(std::shared_ptr<struct regionSet> currentSet, bool actuallyScore);
        static unsigned int scoreGrass(std::shared_ptr<struct regionSet> * currentSets, unsigned int tileID, unsigned int edge, const Tile * passedTile = NULL);
        static unsigned int scoreChurch(unsigned int isSurrounded, bool actuallyScore);
        static unsigned int player1Score;
        static unsigned int player2Score;
};



#endif
