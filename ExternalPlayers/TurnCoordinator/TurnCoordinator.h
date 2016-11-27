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
    void startCoordinator();  //Infinite loop for receiving messages from external client
private:
    void receiveMessage();
    void handleMessage(gameMessage *msg);
    void callAI();
    void setUpAI();
    void setupSocket(int portNumber);
    void buildResponse();
    Move& convertInMove(gameMessage *msg);
    static unsigned int ourPlayerNumber;
    static unsigned int otherPlayerNumber;
    static bool AISetup;
    static int mySocket;
    static int clientSocket;
    static struct sockaddr_in *myAddr;
    static struct sockaddr_in *clientAddr;
    static Move currentMove;
};


#endif