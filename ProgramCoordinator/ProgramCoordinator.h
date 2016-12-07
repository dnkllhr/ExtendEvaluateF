#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <iostream>

#include <unistd.h>

#define PATH_TO_GAME "./GameInstance"
#define GAME_NAME "GameInstance"


void handleGame (int gameSocket, int gamePort);

void setupServerAddr (struct sockaddr_in *serverAddr);


struct tileStackMessage
{
    int lengthOfStack;
    char tileStack[401];
};

struct moveMessage
{
    unsigned int p1;    //Player flag
    char tile[6];       //Tile Identifier
    bool placeable;     //Can you use tile?
    unsigned int x;              //X coordinate
    unsigned int y;              //Y coordinate
    unsigned int orientation;    //Orientation using network protocol offsets
    int meepleType;     //0: NONE    1: TIGER    2: CROC  3: GOAT
    bool pickupMeeple;
    bool placeSpecialTiger;
    bool pass;
    int zone;           //Zone for meeple if TIGER
};

struct whoAmIMessage
{
    unsigned int p1;            //Which player your are
};

union messageData
{
    tileStackMessage tile;
    moveMessage move;
    whoAmIMessage who;
};

struct gameMessage
{
    int messageType;
    messageData data;
};
