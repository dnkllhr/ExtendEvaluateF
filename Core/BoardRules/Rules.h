#ifndef __RULES_H
#define __RULES_H

#include "../Tiles/Tile.h"
#include "../Board/Board.h"
#include "Regions.h"

#include <unordered_map>



class GameRules
{
    public:
        bool validTilePlacement(const Tile& placed, const Tile * boarderingTiles);
        bool validMeeplePlacement(const Tile& placed, unsigned int edgeIndex);
        unsigned int getCurrentScore(int tileID, int edge);
        unsigned int scoreEdge(int tileID, int edge);
    private:
        //Not sure?
};



#endif __RULES_H