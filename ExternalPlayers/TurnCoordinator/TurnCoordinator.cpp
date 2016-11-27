#include "TurnCoordinator.h"

//Main functionality is to receive messages from the external game client and tell the AI when to take a turn.
//It will also call the BoardManager to update opponent moves.

TurnCoordinator::TurnCoordinator(int port)
{
    TurnCoordinator::AISetup = false;
    TurnCoordinator::AIPlayerNumber = 0;
    TurnCoordinator::myAddr = new struct sockaddr_in;
    setupSocket(port);

}

void TurnCoordinator::setupSocket(int portNumber)
{
    /* First call to socket() function */
    TurnCoordinator::socket = socket(AF_INET, SOCK_STREAM, 0);
   
    if (TurnCoordinator::socket < 0) 
    {
        throw std::runtime_error("ERROR opening socket");
    }
   
    /* Initialize socket structure */
    bzero((char *) TurnCoordinator::myAddr, sizeof(*TurnCoordinator::myAddr));
   
    TurnCoordinator::myAddr.sin_family = AF_INET;
    TurnCoordinator::myAddr.sin_addr.s_addr = INADDR_ANY;
    TurnCoordinator::myAddr.sin_port = htons(portNumber);
   
   /* Now bind the host address using bind() call.*/
    if (bind(TurnCoordinator::socket, (struct sockaddr *) TurnCoordinator::myAddr, sizeof(*TurnCoordinator::myAddr)) < 0) 
    {
        throw std::runtime_error("ERROR binding socket");
    }
}

void TurnCoordinator::setUpAI()
{
    if(TurnCoordinator::AIPlayerNumber == 0)
    {
        throw std::logic_error("Trying to setup the AI before you know which player it is.");
    }
    AI::setPlayerNumber(AIPlayerNumber);
    AI::AISetup = true;
}

void TurnCoordinator::callAI(Tile& tile)
{
    if(!TurnCoordinator::AISetup)
    {
        if(TurnCoordinator::AIPlayerNumber == 0)
        {
            throw std::logic_error("Trying to call the AI before you know which player it is.");
        }
        TurnCoordinator::setUpAI();
    }
    Move chosenMove = AI::chooseTurn(tile);
    BoardManager::makeMove(chosenMove);
}

void TurnCoordinator::doOpponentMove()
{
    //Convert the received msg into a Move
    BoardManager::makeMove(mv);
}

void TurnCoordinator::handleMessage()
{
    //Take in the current message.

    //Determine if we need to pick a move

    if(AIMove)
    {
        //get tile ref
        callAI(tile);
    }
    else
    {
        //pass in the message
        doOpponentMove();
    }
}

void TurnCoordinator::startCoordinator()
{

    int clilen;
    struct sockaddr_in cli_addr;

    //Wait for a connection
    listen(TurnCoordinator::socket,5);
    clilen = sizeof(cli_addr);

    //Accept the new connection
    TurnCoordinator::clientSocket = accept(TurnCoordinator::socket, (struct sockaddr *) &cli_addr, &clilen);

    //Hanlde any game init stuff.

    TurnCoordinator::receiveMessage();
}


void TurnCoordinator::receiveMessage()
{
    int n;

    char buffer[256]; //Change to message struct.

    while(true)
    {
        if (TurnCoordinator::clientSocket < 0) 
        {
            throw std::runtime_error("ERROR on accept");
        }

        //Clear out any previous data
        bzero(buffer,256);
        n = read(TurnCoordinator::clientSocket, buffer, 255);

        if (n < 0) 
        {
            throw std::runtime_errorperror("ERROR reading from socket");
        }

        //Handle message here
        TurnCoordinator::handleMessage();


        //Build response here
        TurnCoordinator::buildResponse();

        n = write(TurnCoordinator::clientSocket, "I got your message", 18);

        if (n < 0) 
        {
            throw std::runtime_error("ERROR writing to socket");
        }
    }
}