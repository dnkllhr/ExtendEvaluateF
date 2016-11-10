#include "regions.h"
class Regions
{
public:
  int addConnection(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge);
  int addMeeple(int playerNumber, int tileID, int edge);
  int checkOwner(int tileID, int edge);
private:
  void createRegion(int tileID, int edge);
  int countEdgesTillCompletion(int placedTileID);
  void mergeRegions(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge);
  std::unordered_map<std::tuple<int, int>, struct regionSet *> regionTracker;  //Takes (tileID, edge) returns set pointer
  struct meeple ownerMeeples[TOTAL_MEEPLES];
};

int Regions::addConnection(int placedTileID, int placedEdge, int connectingTileID, int connectingEdge)
{
  if(connectingTileID == -1) //Empty Edge
  {
    Regions::createRegion(placedTileID, placedEdge);
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