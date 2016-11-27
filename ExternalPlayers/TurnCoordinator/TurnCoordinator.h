#include "../AI.h"
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
    void handleMessage();
    void doOpponentMove();
    void callAI();
    void setupAI();
    void setupSocket(int portNumber);
    void buildResponse();
    static unsigned int AIPlayerNumber;
    static bool AISetup;
    static int socket;
    static int clientSocket;
    static struct sockaddr_in *myAddr;
    static struct sockaddr_in *clientAddr;
};