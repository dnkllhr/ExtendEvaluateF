#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <iostream>

#include <unistd.h>

#define PATH_TO_GAME "/path/to/game/"


void handleGame (int gameSocket, int gamePort);

void setupServerAddr (struct sockaddr_in *serverAddr);


typedef struct 
{
    int lengthOfStack;
    char tileStack[401];
}tileStackMessage;

typedef struct 
{
    unsigned int p1;            //Player flag
    char tile[6];       //Tile Identifier
    bool placeable;     //Can you use tile?
    unsigned int x;              //X coordinate
    unsigned int y;              //Y coordinate
    unsigned int orientation;    //Orientation using network protocol offsets
    int meepleType;     //0: NONE    1: TIGER    2: CROC
    int zone;           //Zone for meeple if TIGER
    std::string gid;    //Game ID
}moveMessage;

typedef struct 
{
    unsigned int p1;            //Which player your are
}whoAmIMessage;

typedef union
{
    tileStackMessage tile;
    moveMessage move;
    whoAmIMessage who;
}messageData;

typedef struct
{
    int messageType;
    messageData data;
}gameMessage;
