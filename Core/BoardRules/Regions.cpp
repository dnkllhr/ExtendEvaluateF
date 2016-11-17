#include "Regions.h"


void mergeRegions(unsigned int placedTileID, unsigned int placedEdge, unsigned int connectingTileID, unsigned int connectingEdge)
{   
    auto placedSearch = regionTracker.find(placedTileID);
    auto connectingSearch = regionTracker.find(connectingTileID);
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
            regionTracker[(placedSearch->first)] = (connectingSearch->second[connectingEdge]);
            iter = iter->next;
        }

        //Get rid of old region.
        delete placedSearch->second[connectingEdge];
    }
}

int Regions::addConnection(const Tile& newTile, const Tile ** boarderingTiles) {
    unsigned int numOfSides = newTile.getNumberOfSides();
    unsigned int countPerSide = newTile.getCountPerSide();
    unsigned int totalEdges = numOfSides * countPerSide;
    unsigned int id = newTile.getId();
    unsigned int centerEdge = countPerSide / 2;

    struct regionSet * newRegions = new struct regionSet*[totalEdges];
    regionTracker[id] = newRegions;

    // from what I can tell, this can't be optimised much. This is currently O(n + n^2) and the best case is we get O(n^2)
    for (unsigned int edge = 0; edge < totalEdges; edge++) {
        unsigned int side = edge / countPerSide;
        unsigned int correspondingSide = (side + (numOfSides / 2)) % numOfSides;
        unsigned int correspondingEdge = (countPerSide - (edge % countPerSide) - 1) + (countPerSide * correspondingSide);

        if (boarderingTiles[side] != NULL) {
            unsigned int boarderingId = boarderingTiles[side]->getId();
            newRegions[edge] = regionTracker.at(boarderingId)[correspondingEdge];

            if (edge % countPerEdge == centerEdge)
                newRegions[edge]->edgesTillCompletion--;

            struct tileNode * node = new struct tileNode();
            node->tileID = id;
            node->edge = edge;
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
            newRegions[edge] = createRegion(id, edge);

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
    int i;
    bool valid = false;
    for(i = (playerNumber)*7; i < ((playerNumber)*7 + 7); i++)
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
        ownedMeeples[i].ownedRegion = regionTracker.find(tileID)[edge];
        return 0;
    }
    return -1;
}

int Regions::checkOwner(unsigned int tileID, unsigned int edge)
{
    auto search = regionTracker.find(tileID, edge);
    if(search != example.end())
    {
        if((search->second[edge])->player1Meeples > (search->second[edge])->player2Meeples)
        {
            return 1;
        }
        else if((search->second[edge])->player1Meeples == (search->second[edge])->player2Meeples)
        {
            return 0;
        }
        return -1;
    }
    return -2;
}

struct regionSet* Regions::createRegion(unsigned int tileID, unsigned int edge) {
    struct regionSet * newRegion = new struct regionSet();
    struct tileNode * node = new struct tileNode();

    node->tileID = tileID;
    node->edge = edge;
    newRegion->head = node;
    newRegion->tail = node;
    return newRegion;
}
