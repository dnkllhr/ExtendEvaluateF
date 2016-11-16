#include "Regions.h"

void Regions::mergeRegions(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge)
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

int Regions::addConnection(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge)
{
    if(connectingTileID == -1) //Empty Edge
    {
        createRegion(placedTileID, placedEdge);
        auto search = regionTracker.find(tileID);
        if(search != regionTracker.end())
        {
          //
        }
    }
    auto search = regionTracker.find(tileID);
    if(search != example.end())
    {
        (search->second[placedEdge])->edgesTillCompletion--;
        //Add connection logic
        //Loop through tile sides to find connections
        (search->second[placedEdge])->edgesTillCompletion++;
        return 0;
    }

    return -1;
}

int Regions::addMeeple(int playerNumber, int tileID, int edge)
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

int Regions::checkOwner(int tileID, int edge)
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

void Regions::createRegion(int tileID, int edge)
{
	tileNode currentNode;
	currentNode.tileID = tileID;
	currentNode.edge = edge;

	regionSet newRegion;
	newRegion.player1Meeples = 0;
	newRegion.player2Meeples = 0;
	newRegion.edgesTillCompletion = 0;
	newRegion->head = currentNode;
	newRegion->tail = currentNode;

	struct regionSet* edges[12];
	edges[edge] = &newRegion;
	regionTracker[tileID] = &edges;
}