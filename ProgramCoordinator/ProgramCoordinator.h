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

struct tileStackMessage
{
    tileStackMessage()
    {
        lengthOfStack = 80;
    };
    int lengthOfStack;
    char tileStack[80*5+1];
};

struct moveMessage
{
    bool p1;            //Player flag
    char tile[6];       //Tile Identifier
    bool placeable;     //Can you use tile?
    int x;              //X coordinate
    int y;              //Y coordinate
    int orientation;    //Orientation using network protocol offsets
    int meepleType;     //0: NONE    1: TIGER    2: CROC
    int zone;           //Zone for meeple if TIGER
    std::string gid;    //Game ID
};

struct whoAmIMessage
{
    bool p1;            //Tells the system if they start
};


struct gameMessage
{
    int messageType;
    union 
    {
        struct tileStackMessage;
        struct moveMessage;
        struct whoAmIMessage;
    }u;
};
