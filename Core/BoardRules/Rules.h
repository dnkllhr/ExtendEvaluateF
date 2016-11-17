#ifndef __RULES_H
#define __RULES_H

#include "../Tiles/Tile.h"
#include "../Board/Board.h"
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
        bool validTilePlacement(const Tile& placed, const Tile * boarderingTiles);
        bool validMeeplePlacement(const Tile& placed, unsigned int edgeIndex);
        unsigned int getCurrentScore(int tileID, int edge);
        unsigned int scoreEdge(int tileID, int edge);
    private:
        unsigned int scoreRoad(struct regionSet * currentSet);
        unsigned int scoreCastle(struct regionSet * currentSet);
        unsigned int scoreGrass(struct regionSet ** currentSet, unsigned int edge);
        unsigned int scoreChurch(struct regionSet * currentSet);
};



#endif __RULES_H