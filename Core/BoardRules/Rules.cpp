#include "Rules.h"

bool Rules::validTilePlacement(const Tile& placed, const Tile * boarderingTiles)
{
    unsigned int sides = placed.getNumberOfSides();
    unsigned int countPerSide = placed.getCountPerSide();
    unsigned int edgeCount = sides * countPerSide;

    for (unsigned int edge = 0; edge < edgeCount; edge++) {
        unsigned int correspondingSide = (((edge / countPerSide) + (sides / 2)) % sides;
        unsigned int correspondingEdge = (countPerSide - (edge % countPerSide) - 1) + countPerSide * correspondingSide;

        if (placed.getTerrainType(edge) != boarderingTiles[correspondingSide].getTerrainType(correspondingEdge)) return false;
    }

    return true;
}

bool Rules::validMeeplePlacement(const Tile& placed, unsigned int edgeIndex)
{
    unsigned int id = placed.getId();
    bool hasRegion = regionTracker.count(id) > 0;
    if (!hasRegion) return true;

    bool hasPlayer1 = regionTracker.at(id)[edgeIndex]->player1Meeples > 0;
    bool hasPlayer2 = regionTracker.at(id)[edgeIndex]->player2Meeples > 0;

    return ((!hasPlayer1) && (!hasPlayer2));
}