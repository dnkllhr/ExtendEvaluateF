#include "regions.h"
class Regions
{
public:
    int addConnection(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge);
    int addMeeple(int playerNumber, int tileID, int edge);
    int checkOwner(int tileID, int edge);
private:
    void createRegion(int tileID, int edge);
    int  countEdgesTillCompletion(int placedTileID);
    void mergeRegions(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge);
    std::unordered_map<std::tuple<int, int>, struct regionSet *> regionTracker;    //Takes (tileID, edge) returns set pointer
    struct meeple ownerMeeples[TOTAL_MEEPLES];
};


void mergeRegions(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge)
{
    auto placedSearch = regionTracker.find(std::make_tuple(placedTileID, placedEdge));
    auto connectingSearch = regionTracker.find(std::make_tuple(connectingTileID, connectingEdge));
    if(placedSearch != regionTracker.end() && connectingSearch != regionTracker.end())
    {
        //Update meeple values
        (connectingSearch->second)->player1Meeples      += (placedSearch->second)->player1Meeples;
        (connectingSearch->second)->player2Meeples      += (placedSearch->second)->player2Meeples;

        //Update edgesTillCompletion, no need to increment becuase addConnection() handles
        (connectingSearch->second)->edgesTillCompletion += (placedSearch->second)->edgesTillCompletion;

        //Take over the linked list.
        ((connectingSearch->second)->tail)->next         = (placedSearch->second)->head;
        (connectingSearch->second)->tail                 = (placedSearch->second)->tail;

        //Update Hash entries
        struct tileNode *iter = (placedSearch->second)->head;
        while(iter != NULL)
        {
            regionTracker[(placedSearch->first)] = (connectingSearch->second); 
            iter = iter->next;
        }

        //Bye bye memory leaks.
        delete(iter);
        //Get rid of old region.
        delete((placedSearch->second));
    }
}

int Regions::addConnection(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge)
{
    if(connectingTileID == -1) //Empty Edge
    {
        Regions::createRegion(placedTileID, placedEdge);
        auto search = regionTracker.find(std::make_tuple(tileID, edge));
        if(search != regionTracker.end())
        {
          //
        }
    }
    auto search = regionTracker.find(std::make_tuple(tileID, edge));
    if(search != example.end())
    {
        (search->second)->edgesTillCompletion--;
        //Add connection logic
        //Loop through tile sides to find connections
        (search->second)->edgesTillCompletion++;
        return 0;
}

void mergeRegions(int placedTileID, )

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
        ownedMeeples[i].ownedRegion = regionTracker.find(std::make_tuple(tileID, edge));
        return 0;
    }
    return -1;
}

int Regions::checkOwner(int tileID, int edge)
{
    auto search = regionTracker.find(std::make_tuple(tileID, edge));
    if(search != example.end())
    {
        if((search->second)->player1Meeples > (search->second)->player2Meeples)
        {
            return 1;
        }
        else if((search->second)->player1Meeples == (search->second)->player2Meeples)
        {
            return 0;
        }
        return -1;
    }
    return -2;
}