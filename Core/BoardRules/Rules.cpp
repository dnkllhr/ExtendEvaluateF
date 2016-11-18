#include "Rules.h"

bool GameRules::validTilePlacement(const Tile& placed, const Tile ** boarderingTiles)
{
    unsigned int sides = placed.getNumberOfSides();
    unsigned int countPerSide = placed.getCountPerSide();
    unsigned int edgeCount = sides * countPerSide;

    for (unsigned int edge = 0; edge < edgeCount; edge++) {
        unsigned int correspondingSide = ((edge / countPerSide) + (sides / 2)) % sides;
        unsigned int correspondingEdge = (countPerSide - (edge % countPerSide) - 1) + countPerSide * correspondingSide;

        if (placed.getTerrainType(edge) != boarderingTiles[correspondingSide]->getTerrainType(correspondingEdge)) return false;
    }

    return true;
}

bool GameRules::validMeeplePlacement(const Tile& placed, unsigned int edgeIndex)
{
    unsigned int id = placed.getId();
    bool hasRegion = Regions::getRegions(id) != NULL;
    if (!hasRegion) return true;

    bool hasPlayer1 = Regions::getRegions(id)[edgeIndex]->player1Meeples > 0;
    bool hasPlayer2 = Regions::getRegions(id)[edgeIndex]->player2Meeples > 0;

    return ((!hasPlayer1) && (!hasPlayer2));
}


unsigned int GameRules::scoreRoad(struct regionSet * currentSet)
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
            edgeTracker[currentNode->tileID] = 1;
            for(int i = 0; i  < NUM_PREY; i++)
            {
                preyCount += currentNode->preyValues[i];
            }
            score += ROAD_VALUE + preyCount;
        }
        //Get the next node in the list
        currentNode = currentNode->next;
    }
    return score;
}

unsigned int GameRules::scoreCastle(struct regionSet * currentSet)
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
            edgeTracker[currentNode->tileID] = 1;
            for(int i = 0; i  < NUM_PREY; i++)
            {
                if(currentNode->preyValues[i])
                {
                    preyCount++;
                }
            }
            score += CASTLE_VALUE * (1 + preyCount);
        }
        //Get the next node in the list
        currentNode = currentNode->next;
    }
    return score;
}

unsigned int GameRules::scoreGrass(unsigned int tileID, unsigned int edge)
{
    unsigned int score = 0;
    struct regionSet ** currentSets = Regions::getRegions(tileID);
    std::unordered_map<struct regionSet * , bool> fieldTracker;
    //Init starting values
    struct tileNode * currentNode = (currentSets[edge])->head;    
    auto tileSearch = fieldTracker.find(currentSets[edge]);
    Tile * currentTile;

    while(currentNode != NULL)
    {        
        currentSets = Regions::getRegions(currentNode->tileID);
        currentTile = Board::get(tileID);
        for(int i = 0; i < NUM_TILE_EDGES; i++)
        {
            //Look for the other regions on the tile
            tileSearch = fieldTracker.find(currentSets[i]);
            //If you can't find the region
            if(tileSearch == fieldTracker.end() && currentTile->isConnected(i,currentNode->edge))
            {
                //And the region is a completed castle
                if((currentSets[i]->type == TerrainType::Castle) && (currentSets[i]->edgesTillCompletion == 0))
                {
                    //Score it, and add it to the hash map
                    score += FIELD_CASTLE_VALUE;
                    fieldTracker[currentSets[i]] = true;
                }
                else if((currentSets[i]->type == TerrainType::Church) && (currentSets[i]->edgesTillCompletion == 0))
                {
                    //Score it, and add it to the hash map
                    score += FIELD_CHURCH_VALUE;
                    fieldTracker[currentSets[i]] = true;
                }
            }
        }
        currentNode = currentNode->next;
    }
    return score;
}

unsigned int GameRules::scoreChurch(bool isSurrounded)
{
    unsigned int score = 0;

    if(isSurrounded)
    {
        score += 9;
    }

    return score;
}


unsigned int GameRules::getCurrentScore(unsigned int tileID, unsigned int edge, bool isSurrounded)
{
    struct regionSet ** currentRegion = Regions::getRegions(tileID);
    unsigned int returnValue = 0;
    switch (currentRegion[edge]->type)
    {
        case TerrainType::Grass:
            returnValue = scoreGrass(tileID, edge);
            break;
        case TerrainType::Road:
            returnValue = scoreRoad(currentRegion[edge]);
            break;
        case TerrainType::Castle:
            returnValue = scoreCastle(currentRegion[edge]);
            break;
        case TerrainType::Church:
            returnValue = scoreChurch(isSurrounded);
            break;
        default:
            //Throw error
            break;
    }
    return returnValue;
}
