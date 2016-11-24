#include "Regions.h"

struct meeple Regions::ownerMeeples[] = {};
std::unordered_map<unsigned int, struct regionSet **> Regions::regionTracker = std::unordered_map<unsigned int, struct regionSet **>();

void Regions::mergeRegions(unsigned int placedTileID, unsigned int placedEdge, unsigned int connectingTileID, unsigned int connectingEdge)
{
    auto placedSearch = regionTracker.find(placedTileID);
    auto connectingSearch = regionTracker.find(connectingTileID);

    if (placedSearch == regionTracker.end() || connectingSearch == regionTracker.end()) throw std::logic_error("The placed or connecting tile can't be found in the regions.");

    if(placedSearch != regionTracker.end() && connectingSearch != regionTracker.end())
    {
        //Update meeple values
        (connectingSearch->second[connectingEdge])->player1Meeples      += (placedSearch->second[placedEdge])->player1Meeples;
        (connectingSearch->second[connectingEdge])->player2Meeples      += (placedSearch->second[placedEdge])->player2Meeples;

        //Update edgesTillCompletion, no need to increment becuase addConnection() handles
        (connectingSearch->second[connectingEdge])->edgesTillCompletion += (placedSearch->second[placedEdge])->edgesTillCompletion;

        //Take over the linked list.
        ((connectingSearch->second[connectingEdge])->tail)->next         = (placedSearch->second[placedEdge])->head;
        (connectingSearch->second[connectingEdge])->tail                 = (placedSearch->second[placedEdge])->tail;

        //Update Hash entries
        struct tileNode *iter = (placedSearch->second[placedEdge])->head;
        while(iter != NULL)
        {
            regionTracker[(placedSearch->first)][placedEdge] = (connectingSearch->second[connectingEdge]);
            iter = iter->next;
        }

        //Get rid of old region.
        delete placedSearch->second[connectingEdge];
    }
}

int Regions::addConnection(const Tile& newTile, const Tile ** allBoarderingTiles) {
    unsigned int numOfSides = newTile.getNumberOfSides();
    unsigned int countPerSide = newTile.getCountPerSide();
    unsigned int totalEdges = numOfSides * countPerSide;
    unsigned int id = newTile.getId();
    unsigned int centerEdge = countPerSide / 2;

    // add one to total edges so that we have an array location for the center
    struct regionSet ** newRegions = new struct regionSet*[totalEdges + 1];
    regionTracker[id] = newRegions;

    if (newTile.getCenter() == TerrainType::Church) {
        newRegions[totalEdges] = Regions::createRegion(id, totalEdges, newTile.getCenter());
        newRegions[totalEdges]->edgesTillCompletion = 8;
    }
    else {
        newRegions[totalEdges] = NULL;
    }

    const Tile* boarderingTiles[numOfSides];
    unsigned int sideInc = 0;
    for (unsigned int currSide = 0; currSide < numOfSides * 2; currSide++) {
        if (allBoarderingTiles[currSide] != NULL) {
            if (allBoarderingTiles[currSide]->getCenter() == TerrainType::Church) {
                unsigned int boarderingId = allBoarderingTiles[currSide]->getId();

                // decrement the church's region edges till completion tracker if we were placed as a tile around it
                regionTracker[boarderingId][totalEdges]->edgesTillCompletion--;
            }
            if (newTile.getCenter() == TerrainType::Church) regionTracker[id][totalEdges]->edgesTillCompletion--;
        }

        if ((currSide % 2) == 1) {
            boarderingTiles[sideInc] = allBoarderingTiles[currSide];
            sideInc++;
        }
    }

    // from what I can tell, this can't be optimised much. This is currently O(n + n^2) and the best case is we get O(n^2)
    for (unsigned int edge = 0; edge < totalEdges; edge++) {
        unsigned int side = edge / countPerSide;
        unsigned int correspondingSide = (side + (numOfSides / 2)) % numOfSides;
        unsigned int correspondingEdge = (countPerSide - (edge % countPerSide) - 1) + (countPerSide * correspondingSide);

        if (boarderingTiles[side] != NULL) {
            unsigned int boarderingId = boarderingTiles[side]->getId();
            newRegions[edge] = regionTracker[boarderingId][correspondingEdge];

            if (edge % countPerSide == centerEdge)
                newRegions[edge]->edgesTillCompletion--;

            struct tileNode * node = new struct tileNode();
            node->tileID = id;
            node->edge = edge;
            node->preyCounts[static_cast<int>(newTile.getPrey())]++;
            node->previous = newRegions[edge]->tail;
            newRegions[edge]->tail->next = node;
            newRegions[edge]->tail = node;
        }
        else {
           newRegions[edge] = NULL;
        }
    }

    for (unsigned int edge = 0; edge < totalEdges; edge++) {
        if (newRegions[edge] == NULL) {
            newRegions[edge] = createRegion(id, edge, newTile.getTerrainType(edge));
            newRegions[edge]->tail->preyCounts[static_cast<int>(newTile.getPrey())]++;

            if (edge % countPerSide == centerEdge)
                newRegions[edge]->edgesTillCompletion++;
        }

        for (unsigned int otherEdge = edge + 1; otherEdge < totalEdges; otherEdge++) {
            if (!newTile.isConnected(edge, otherEdge)) continue;
            else if (newRegions[otherEdge] == newRegions[edge]) continue;
            else if (newRegions[otherEdge] == NULL) {
                newRegions[otherEdge] = newRegions[edge];

                if (otherEdge % countPerSide == centerEdge)
                    newRegions[otherEdge]->edgesTillCompletion++;

                struct tileNode * node = new struct tileNode();
                node->tileID = id;
                node->edge = otherEdge;
                node->preyCounts[static_cast<int>(newTile.getPrey())]++;
                node->previous = newRegions[otherEdge]->tail;
                newRegions[otherEdge]->tail->next = node;
                newRegions[otherEdge]->tail = node;
            }
            else {
                mergeRegions(id, edge, id, otherEdge);

                if (otherEdge % countPerSide == centerEdge)
                    newRegions[edge]->edgesTillCompletion--;
            }
        }
    }

    return 0;
}

int Regions::addMeeple(unsigned int playerNumber, unsigned int tileID, unsigned int edge)
{
    unsigned int i;
    bool valid = false;
    for(i = (playerNumber)*(MEEPLES_PER_PLAYER); i < ((playerNumber)*(MEEPLES_PER_PLAYER) + (MEEPLES_PER_PLAYER)); i++)
    {
        if(!(ownerMeeples[i].inUse))
        {
            valid = true;
        }
    }
    if(!valid)
    {
        return -1;
    }

    if(Regions::checkOwner(tileID, edge) == -2) //No owner
    {
        ownerMeeples[i].inUse = true;
        ownerMeeples[i].ownedRegion = regionTracker.find(tileID)->second[edge];
        return 0;
    }
    return -1;
}

int Regions::removeMeeple(unsigned int tileID, unsigned int edge)
{
    struct regionSet *wantedRegion = regionTracker.find(tileID)->second[edge];
    for(int i = 0; i < TOTAL_MEEPLES; i++)
    {
        if(ownerMeeples[i].inUse && (ownerMeeples[i].ownedRegion == wantedRegion))
        {
            ownerMeeples[i].inUse = false;
            ownerMeeples[i].ownedRegion = NULL;
        }
    }
    return 0;
}


int Regions::checkOwner(unsigned int tileID, unsigned int edge)
{
    auto search = regionTracker.find(tileID);

    if (search == regionTracker.end()) throw std::logic_error("The tile can't be found in the regions.");

    if(search != regionTracker.end())
    {
        if((search->second[edge])->player1Meeples > (search->second[edge])->player2Meeples)
        {
            return OWNER_P1;
        }
        else if((search->second[edge])->player1Meeples == (search->second[edge])->player2Meeples && ((search->second[edge])->player2Meeples) != 0)
        {
            return OWNER_TIE;
        }
        return OWNER_P2;
    }
    return OWNER_NONE;
}

struct regionSet * Regions::createRegion(unsigned int tileID, unsigned int edge, TerrainType type) {
    struct regionSet * newRegion = new struct regionSet();
    struct tileNode * node = new struct tileNode();

    node->tileID = tileID;
    node->edge = edge;
    newRegion->type = type;
    newRegion->head = node;
    newRegion->tail = node;
    return newRegion;
}

struct regionSet ** Regions::getRegions(unsigned int tileID)
{
    auto tileSearch = regionTracker.find(tileID);
    if(tileSearch != regionTracker.end())
    {
        return (tileSearch->second);
    }

    return NULL;
}

#ifdef testing

void Regions::clearRegionTracker() {
    regionTracker = std::unordered_map<unsigned int, struct regionSet **>();
}

bool Regions::checkRegionExistence(unsigned int tileID, unsigned int edge) {
    auto search = regionTracker.find(tileID);
    if(search != regionTracker.end())
    {
        if((search->second)[edge] != NULL)
        {
            return true;
        }
    }
    return false;
}

unsigned int Regions::checkRegionEdgesTillCompletion(unsigned int tileID, unsigned int edge) {
    auto search = regionTracker.find(tileID);
    if(search != regionTracker.end())
    {
        if((search->second)[edge] != NULL)
        {
            return ((search->second)[edge]->edgesTillCompletion);
        }
    }

    throw std::logic_error("The tile, edge combination could not be found.");
}

void Regions::clearOwnerMeeples() {
    for (int i = 0; i < TOTAL_MEEPLES; i++) {
        ownerMeeples[i].inUse = false;
        if (ownerMeeples[i].ownedRegion != NULL) {
            delete ownerMeeples[i].ownedRegion;
            ownerMeeples[i].ownedRegion = NULL;
        }
    }
}

#endif
