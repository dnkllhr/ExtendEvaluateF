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


unsigned int scoreRoad(struct regionSet * currentSet)
{
    std::unordered_map<unsigned int, bool> edgeTracker;
    //Init starting values
    struct tileNode * currentNode = currentSet->head;    
    auto tileSearch = edgeTracker.find(currentNode->tileID);
    unsigned int score = 0;
    unsigned int preyCount = 0;

    while(currentNode != NULL)
    {
        //Search for an entry in the map
        tileSearch = edgeTracker.find(currentNode->tileID);
        //If the entry doesn't exist, we haven't visited the tile yet
        if(tileSearch == edgeTracker.end())
        {
            preyCount = 0;
            edgeTracker[tileNode->tileID] = 1;
            for(int i = 0; i  < NUM_PREY; i++)
            {
                preyCount += currentNode->preyValues[i];
            }
            score += ROAD_VALUE + preyCount;
        }
        //Get the next node in the list
        currentNode = currentNode->next;
    }

}

unsigned int scoreCastle(struct regionSet * currentSet)
{

}

unsigned int scoreGrass(struct regionSet * currentSet)
{

}

unsigned int scoreChurch(struct regionSet * currentSet)
{

}


unsigned int getCurrentScore(unsigned int tileID, unsigned int edge)
{
    struct regionSet * currentRegion = Regions::getRegion(tileID, edge);
    unsigned int returnValue;
    switch (currentRegion->type)
    {
        case TerrainType::Grass:
            returnValue = scoreGrass(currentRegion);
            break;
        case TerrainType::Road:
            returnValue = scoreRoad(currentRegion);
            break;
        case TerrainType::Castle:
            returnValue = scoreCastle(currentRegion);
            break;
        case TerrainType::Church:
            returnValue = scoreChurch(currentRegion);
            break;
        default:
            //Throw error
            break;
    }
}