#include "TurnCoordinator.h"

//Main functionality is to receive messages from the external game client and tell the AI when to take a turn.
//It will also call the BoardManager to update opponent moves.

TurnCoordinator::TurnCoordinator(int port)
{
    TurnCoordinator::AISetup = false;
    TurnCoordinator::ourPlayerNumber = 0;
    TurnCoordinator::otherPlayerNumber = 0;
    TurnCoordinator::myAddr = new struct sockaddr_in;
    setupSocket(port);
}

TurnCoordinator::~TurnCoordinator()
{
    close(TurnCoordinator::clientSocket);
    close(TurnCoordinator::mySocket);
}

void TurnCoordinator::setupSocket(int portNumber)
{
    /* First call to socket() function */
    TurnCoordinator::mySocket = socket(AF_INET, SOCK_STREAM, 0);
   
    if (TurnCoordinator::mySocket < 0) 
    {
        throw std::runtime_error("ERROR opening socket");
    }
   
    /* Initialize socket structure */
    bzero((char *) TurnCoordinator::myAddr, sizeof(*TurnCoordinator::myAddr));
   
    TurnCoordinator::myAddr->sin_family = AF_INET;
    TurnCoordinator::myAddr->sin_addr.s_addr = INADDR_ANY;
    TurnCoordinator::myAddr->sin_port = htons(portNumber);
   
   /* Now bind the host address using bind() call.*/
    if (bind(TurnCoordinator::mySocket, (struct sockaddr *) TurnCoordinator::myAddr, sizeof(*TurnCoordinator::myAddr)) < 0) 
    {
        throw std::runtime_error("ERROR binding socket");
    }
}

void TurnCoordinator::setUpAI()
{
    if(TurnCoordinator::ourPlayerNumber == 0)
    {
        throw std::logic_error("Trying to setup the AI before you know which player it is.");
    }
    AI::setPlayerNumber(TurnCoordinator::ourPlayerNumber);
    TurnCoordinator::AISetup = true;
}

void TurnCoordinator::callAI()
{
    if(!TurnCoordinator::AISetup)
    {
        if(TurnCoordinator::ourPlayerNumber == 0)
        {
            throw std::logic_error("Trying to call the AI before you know which player it is.");
        }
        TurnCoordinator::setUpAI();
    }
    Move chosenMove = AI::chooseTurn(BoardManager::getTopTileStack());
    BoardManager::makeMove(chosenMove, TurnCoordinator::ourPlayerNumber);
}

Move& TurnCoordinator::convertInMove(gameMessage *msg)
{
    if(!(msg->u.moveMessage.placeable))
    {
        BoardManager::cannotPlaceTile();
    }
    unsigned int zone;
    switch (msg->u.moveMessage.zone)
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
    if(!strcmp((BoardManager::getTopTileStack()).getTileName().c_str(), msg->u.moveMessage.tile))
    {
        throw std::logic_error("Top of the tile stack and current tile move do not match");
    }
    Move *mv;
    switch(msg->u.moveMessage.meepleType)
    {
        case 0:
            //No meeple
            mv = new Move((Tile&)BoardManager::getTopTileStack(), msg->u.moveMessage.x, msg->u.moveMessage.y, msg->u.moveMessage.orientation);
            break;
        case 1:
            //Tiger
            mv = new Move((Tile&)BoardManager::getTopTileStack(), msg->u.moveMessage.x, msg->u.moveMessage.y, msg->u.moveMessage.orientation, zone);
            break;
        case 2:
            //Croc
            mv = new Move((Tile&)BoardManager::getTopTileStack(), msg->u.moveMessage.x, msg->u.moveMessage.y, msg->u.moveMessage.orientation, true);
            break;
        default:
            throw std::logic_error("Unrecognized meeple type");
            break;
    }
    return (*mv);
}

void TurnCoordinator::handleMessage(gameMessage *msg)
{
    //Determine if we need to pick a move
    switch(msg->messageType)
    {
        case 0:
            BoardManager::inputTileStack(msg->u.tileStackMessage.tileStack, msg->u.tileStackMessage.lengthOfStack);
            break;
        case 1:
            if(msg->u.moveMessage.p1 != TurnCoordinator::ourPlayerNumber)
            {
                BoardManager::makeMove(TurnCoordinator::convertInMove(msg), TurnCoordinator::otherPlayerNumber);
            }
            else
            {
                if(!strcmp((BoardManager::getTopTileStack()).getTileName().c_str(), msg->u.moveMessage.tile)) 
                {
                    throw std::logic_error("Top of the tile stack and current tile move do not match");
                }
                TurnCoordinator::callAI();
            }
            break;
        case 2:
            if(msg->u.whoAmIMessage.p1 == 1)
            {
                TurnCoordinator::ourPlayerNumber = 1;
                TurnCoordinator::otherPlayerNumber = 2;
            }
            else
            {
                TurnCoordinator::otherPlayerNumber = 1;
                TurnCoordinator::ourPlayerNumber = 2;                
            }
            TurnCoordinator::setUpAI();
            break;
        default:
            break;
    }
}

void TurnCoordinator::startCoordinator()
{

    int clilen;
    struct sockaddr_in cli_addr;

    //Wait for a connection
    listen(TurnCoordinator::mySocket,5);
    clilen = sizeof(cli_addr);

    //Accept the new connection
    TurnCoordinator::clientSocket = accept(TurnCoordinator::mySocket, (struct sockaddr *) &cli_addr,(socklen_t *) &clilen);

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
            throw std::runtime_error("ERROR reading from socket");
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