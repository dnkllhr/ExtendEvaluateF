#ifndef __RULES_H
#define __RULES_H

#include "../Tiles/Tile.h"
#include "../Board/Board.h"


class GameRules
{
    public:
        validTilePlacement(const Tile& placed, const Tile * boarderingTiles);
        validMeeplePlacement(const Tile& placed, unsigned int edgeIndex);
        getCurrentScore(int tileID, int edge);
        scoreEdge(int tileID, int edge);
    private:
        //Not sure?
};



#endif __RULES_H