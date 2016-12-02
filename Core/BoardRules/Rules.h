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
        static Array<bool> validMeeplePlacement(const Tile& toBePlaced, const Coord& location);
        static bool validCrocPlacement(unsigned int tileID);
        static bool hasCroc(unsigned int tileID);
        static bool checkSideForCroc(unsigned int x, unsigned int y);
        static bool validCrocPlacement(const Tile& toPlace, const Coord& location);
        static unsigned int getCurrentScore(unsigned int tileID, unsigned int edge);
        static unsigned int getCurrentScore(std::shared_ptr<struct regionSet> * currentRegions, unsigned int edge, Tile * tile, unsigned int tilesSurrounded);
        static unsigned int scoreEdge(unsigned int tileID, unsigned int edge, bool endOfGame = false);
        static unsigned int getPlayerScore(unsigned int player);
#ifndef __testing
    private:
#endif
        static unsigned int scoreRoad(std::shared_ptr<struct regionSet> currentSet, bool actuallyScore);
        static unsigned int scoreCastle(std::shared_ptr<struct regionSet> currentSet, bool actuallyScore, bool endOfGame = false);
        static unsigned int scoreGrass(std::shared_ptr<struct regionSet> * currentSets, unsigned int tileID, unsigned int edge, Tile * passedTile = NULL);
        static unsigned int scoreChurch(unsigned int isSurrounded, bool actuallyScore);
        static unsigned int player1Score;
        static unsigned int player2Score;
};



#endif
