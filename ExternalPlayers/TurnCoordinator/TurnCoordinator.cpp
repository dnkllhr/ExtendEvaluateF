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

TurnCoordinator::~TurnCoordinator()
{
    close(TurnCoordinator::clientSocket);
    close(TurnCoordinator::socket);
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
    AI::setPlayerNumber(TurnCoordinator::AIPlayerNumber);
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


Move& TurnCoordinator::convertInMove(gameMessage *msg)
{
    if(!(msg->moveMessage.placeable))
    {
        BoardManager::cannotPlace();
    }
    unsigned int zone;
    switch (msg->moveMessage.zone)
    {
        case 1:
            zone = 0;
            break;
        case 2:
            zone = 1;
            break;
        case 3:
            zone = 2;
            break;
        case 4:
            zone = 10;
            break;
        case 5:
            zone = 12;
            break;
        case 6:
            zone = 4;
            break;
        case 7:
            zone = 8;
            break;
        case 8:
            zone = 7;
            break;
        case 9:
            zone = 5;
            break;
        default:
            throw std::logic_error("Zone not recognized");
            break;
    }
    int playerNumber = (int)msg->moveMessage.p1 + 1;
    if(!strcmp((BoardManager::getTopTileStack()).getTileName(), (std::string)msg->moveMessage.tile)) 
    {
        throw std::logic_error("Top of the tile stack and current tile move do not match");
    }
    switch(msg->moveMessage.meepleType)
    {
        case 0:
            //No meeple
            Move mv = new Move(BoardManager::getTopTileStack(), msg->moveMessage.x, msg->moveMessage.y, msg->moveMessage.orientation);
            break;
        case 1:
            //Tiger
            Move mv = new Move(BoardManager::getTopTileStack(), msg->moveMessage.x, msg->moveMessage.y, msg->moveMessage.orientation, zone);
            break;
        case 2:
            //Croc
            Move mv = new Move(BoardManager::getTopTileStack(), msg->moveMessage.x, msg->moveMessage.y, msg->moveMessage.orientation, true);
            break;
        default:
            throw std::logic_error("Unrecognized meeple type");
            break;
    }
    return mv;
}

void TurnCoordinator::handleMessage(gameMessage *msg)
{
    //Take in the current message.

    //Determine if we need to pick a move
    switch(msg->whoAmIMessage.messageType)
    {
        case 0:
            BoardManager::inputStack(msg->tileStackMessage.tileStack, msg->tileStackMessage.lengthOfStack);
            break;
        case 1:
            if(((int)(msg->moveMessage.p1)+1) != TurnCoordinator::AIPlayerNumber){BoardManager::makeMove(TurnCoordinator::convertInMove(msg));}
            else
            {
                if(!strcmp((BoardManager::getTopTileStack()).getTileName(), (std::string)msg->moveMessage.tile)) 
                {
                    throw std::logic_error("Top of the tile stack and current tile move do not match");
                }
                TurnCoordinator::currentMove =  AI::chooseTurn(BoardManager::getTopTileStack());
            }
            break;
        case 2:
            TurnCoordinator::AIPlayerNumber = (int)(msg->whoAmIMessage.p1) + 1;
            TurnCoordinator::setUpAI();
            break;
        default:
            break;
    }

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

    char buffer[sizeof(gameMessage)]; //Change to message struct.
    gameMessage *msg = (gameMessage *)(&buffer);

    while(true)
    {
        if (TurnCoordinator::clientSocket < 0) 
        {
            throw std::runtime_error("ERROR on accept");
        }

        //Clear out any previous data
        bzero(buffer, sizeof(gameMessage));
        n = read(TurnCoordinator::clientSocket, buffer, sizeof(gameMessage) - 1);

        if (n < 0) 
        {
            throw std::runtime_errorperror("ERROR reading from socket");
        }

        //Handle message here
        TurnCoordinator::handleMessage(msg);


        //Build response here
        TurnCoordinator::buildResponse();

        n = write(TurnCoordinator::clientSocket, "I got your message", 18);

        if (n < 0) 
        {
            throw std::runtime_error("ERROR writing to socket");
        }
    }
}