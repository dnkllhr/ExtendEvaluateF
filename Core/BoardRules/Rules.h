#ifndef __RULES_H
#define __RULES_H

#include "../Tiles/Tile.h"
#include "Regions.h"

#include <unordered_map>

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
        static unsigned int getCurrentScore(unsigned int tileID, unsigned int edge, bool isSurrounded);
        static unsigned int scoreEdge(unsigned int tileID, unsigned int edge);
    private:
        static unsigned int scoreRoad(struct regionSet * currentSet);
        static unsigned int scoreCastle(struct regionSet * currentSet);
        static unsigned int scoreGrass(unsigned int tileID, unsigned int edge);
        static unsigned int scoreChurch(bool isSurrounded);
};



#endif