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


unsigned int GameRules::scoreRoad(struct regionSet * currentSet, bool actuallyScore)
{
    std::unordered_map<unsigned int, bool> edgeTracker;
    //Init starting values
    struct tileNode * currentNode = currentSet->head;    
    auto tileSearch = edgeTracker.find(currentNode->tileID);
    unsigned int score = 0;
    unsigned int preyCount = 0;

    if(actuallyScore && currentSet->edgesTillCompletion != 0)
    {
        return 0;
    }

    //Iterate through the linked list of the region
    while(currentNode != NULL)
    {
        //Search for an entry in the map
        tileSearch = edgeTracker.find(currentNode->tileID);
        //If the entry doesn't exist, we haven't visited the tile yet
        if(tileSearch == edgeTracker.end())
        {
            preyCount = 0;
            //Enter the tileID to make sure we don't revisit it
            edgeTracker[currentNode->tileID] = 1;
            for(int i = 0; i  < NUM_PREY; i++)
            {
                //Scoring for animal-road interaction
                preyCount += currentNode->preyValues[i];
            }
            score += ROAD_VALUE + preyCount;
        }
        //Get the next node in the list
        currentNode = currentNode->next;
    }
    return score;
}

unsigned int GameRules::scoreCastle(struct regionSet * currentSet, bool actuallyScore)
{
    std::unordered_map<unsigned int, bool> edgeTracker;
    //Init starting values
    struct tileNode * currentNode = currentSet->head;    
    auto tileSearch = edgeTracker.find(currentNode->tileID);
    unsigned int score = 0;
    unsigned int preyCount = 0;

    if(actuallyScore && currentSet->edgesTillCompletion != 0)
    {
        return 0;
    }


    //Iterate through the linked list of the region
    while(currentNode != NULL)
    {
        //Search for an entry in the map
        tileSearch = edgeTracker.find(currentNode->tileID);
        //If the entry doesn't exist, we haven't visited the tile yet
        if(tileSearch == edgeTracker.end())
        {
            preyCount = 0;
            //Make sure we don't revisit the tileID
            edgeTracker[currentNode->tileID] = 1;
            for(int i = 0; i  < NUM_PREY; i++)
            {
                if(currentNode->preyValues[i])
                {
                    preyCount++;
                }
            }
            //Scoring for castle-animal interaction
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
    const Tile * currentTile;

    //Iterate through the linked list of the given region
    while(currentNode != NULL)
    {        
        //Get all of the regions for the current tileID (associated with the current node)
        currentSets = Regions::getRegions(currentNode->tileID);
        //We need the actual tile to be able to determine which regions are actually touching.
        currentTile = &Board::get(tileID);
        for(int i = 0; i < NUM_TILE_EDGES; i++)
        {
            //Look for the other regions on the tile
            tileSearch = fieldTracker.find(currentSets[i]);
            //If you can't find the region
            if(tileSearch == fieldTracker.end() && currentTile->isConnected(i,currentNode->edge)) //Is connected is not the right function.  Need to know isTouching()
            {
                //And the region is a completed castle
                if((currentSets[i]->type == TerrainType::Castle) && (currentSets[i]->edgesTillCompletion == 0))
                {
                    //Score it, and add it to the hash map
                    score += FIELD_CASTLE_VALUE;
                    //Add the region to the hash map to make sure we don't re-score it.
                    fieldTracker[currentSets[i]] = true;
                }
                else if((currentSets[i]->type == TerrainType::Church) && (currentSets[i]->edgesTillCompletion == 0))
                {
                    //Score it, and add it to the hash map
                    score += FIELD_CHURCH_VALUE;
                    //Add the region to the hash map to make sure we don't re-score it.
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


//Entry point for scoring a region.
unsigned int GameRules::getCurrentScore(unsigned int tileID, unsigned int edge)
{
    bool isSurrounded = BoardManager::isSurrounded(tileID);

    struct regionSet ** currentRegion = Regions::getRegions(tileID);
    unsigned int returnValue = 0;

    switch (currentRegion[edge]->type)
    {
        case TerrainType::Grass:
            returnValue = scoreGrass(tileID, edge);
            break;
        case TerrainType::Road:
            returnValue = scoreRoad(currentRegion[edge], false);
            break;
        case TerrainType::Castle:
            returnValue = scoreCastle(currentRegion[edge], false);
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


unsigned int scoreEdge(unsigned int tileID, unsigned int edge)
{
    bool isSurrounded = BoardManager::isSurrounded(tileID);

    struct regionSet ** currentRegion = Regions::getRegions(tileID);
    unsigned int returnValue = 0;

    switch (currentRegion[edge]->type)
    {
        case TerrainType::Grass:
            returnValue = scoreGrass(tileID, edge);
            break;
        case TerrainType::Road:
            returnValue = scoreRoad(currentRegion[edge], true);
            break;
        case TerrainType::Castle:
            returnValue = scoreCastle(currentRegion[edge], true);
            break;
        case TerrainType::Church:
            returnValue = scoreChurch(isSurrounded);
            break;
        default:
            //Throw error
            break;
    }
    
    if (returnValue != 0)
    {
        Regions::removeMeeple(tileID, edge);
    }

    return returnValue;
}