#ifndef __TURN_COORDINATOR_H
#define __TURN_COORDINATOR_H
#include "../AI/AI.h"
#include "../../ProgramCoordinator/ProgramCoordinator.h"

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <iostream>

#include <unistd.h>

//Needs structure(s) defined for the messages from the external game client.


//Define message types

class TurnCoordinator
{
public:
    TurnCoordinator(int port);
    ~TurnCoordinator();
    static void startCoordinator();  //Infinite loop for receiving messages from external client
#ifndef testing
private:
#endif
    static void receiveMessage();
    static void handleMessage(gameMessage *msg);
    static void callAI();
    static void setUpAI();
    static void setupSocket(int portNumber);
    static int convertEdgeToZone(int edge);
    static gameMessage buildResponse(Move& move);
    static Move& convertInMove(gameMessage *msg);
    static unsigned int ourPlayerNumber;
    static unsigned int otherPlayerNumber;
    static bool AISetup;
    static int mySocket;
    static int clientSocket;
    static struct sockaddr_in *myAddr;
    static struct sockaddr_in *clientAddr;
};


#endif