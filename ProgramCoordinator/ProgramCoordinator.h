#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <iostream>

#include <unistd.h>

#include "../ExternalPlayers/TurnCoordinator/TurnCoordinator.h"

#define PATH_TO_GAME "/path/to/game/"


void handleGame (int gameSocket, int gamePort);

void setupServerAddr (struct sockaddr_in *serverAddr);

struct tileStackMessage
{
    tileStackMessage()
    {
        messageType = 0;
        lengthOfStack = 80;
        char **tileStack = new char*[80];
        for(int i = 0; i < lengthOfStack; i++)
        {
            tileStack[i] = new char[5];
        }
    };
    int messageType;
    int lengthOfStack;
    char **tileStack;
};

struct moveMessage
{
    moveMessage()
    {
        messageType = 1;
    };
    int messageType;    //Used to differentiate messages
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
    whoAmIMessage()
    {
        messageType = 2;
    };
    int messageType;
    bool p1;            //Tells the system if they start
};


union gameMessage
{
    struct tileStackMessage;
    struct moveMessage;
    struct whoAmIMessage;
};
