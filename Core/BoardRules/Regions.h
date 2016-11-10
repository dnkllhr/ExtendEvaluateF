struct tileNode
{
  int tileID;
  int edge;
  struct tileNode *previous;
  struct tileNode *next;
};

struct regionSet
{
  int player1Meeples;
  int player2Meeples;
  int edgesTillCompletion;
  struct tileNode *head;
  struct tileNode *tail;
};

struct meeple
{
  bool inUse;
  struct regionSet *ownedRegion;
};
