#include "ProgramCoordinator.h"

void setupServerAddr (struct sockaddr_in *serverAddr, int portNumber)
{
    //Zero out the structure
    bzero((char *)(serverAddr), sizeof(*serverAddr));
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_addr.s_addr = INADDR_ANY; //Allow any addr to connect
    serverAddr->sin_port = htons(portNumber); //Convert port number
}

int main( int argc, char *argv[] ) {
    int masterSocket, connectionSocket;
    int portNumber, clientAddrLength, forkedPID;
    struct sockaddr_in serverAddr, clientAddr;


    std::cout << "Enter portNumber: ";
    std::cin >> portNumber;

    setupServerAddr(&serverAddr, portNumber);

    /* First call to socket() function */
    masterSocket = socket(AF_INET, SOCK_STREAM, 0);


/*  SERVER CODE
    if (masterSocket < 0)
    {
        printf("Can't open master socket.\n");
        exit(1);
    }

    if (bind(masterSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("Can't bind master socket.\n");
        exit(1);
    }

    //Block and wait for a connection, limit 5.
    listen(masterSocket,5);
    clientAddrLength = sizeof(clientAddr);

    while (true)
    {

        connectionSocket = accept(masterSocket, (struct sockaddr *) &clientAddr, &clientAddrLength);

        if (connectionSocket < 0)
        {
            printf("Failed to accept connection.\n");
            exit(1);
        }

        //Fork the server to handle the request
        portNumber++;
        forkedPID = fork();

        if (forkedPID < 0)
        {
            printf("Failed to fork.\n")
            exit(1);
        }

        if (forkedPID == 0)
        {
            //Handle the game connection
            close(masterSocket);
            handleGame(connectionSocket, portNumber);
            exit(0);
        }

        else
        {
            close(connectionSocket);
        }

    }
*/
}

void handleGame (int gameSocket, int gamePort)
{
    int bytes, forkedPID;
    char messageBuffer[2048];

    char *gameArgs = new char[10]; //Way more than enough digits
    int stringLength = sprintf(gameArgs, "%d", gamePort); //Convert gamePort into a char* so that it can be passed as an arg


    forkedPID = fork();
    if(forkedPID < 0)
    {
        printf("Failed to fork.\n");
        exit(1);
    }
    if (forkedPID == 0)
    {
        //Create a game process
        execl(PATH_TO_GAME, gameArgs);
        exit(0);
    }


    int gameSendSocket;
    struct sockaddr_in gameAddr;

    setupServerAddr(&gameAddr, gamePort);

    /* First call to socket() function */
    int masterSocket = socket(AF_INET, SOCK_STREAM, 0);

    while(true)
    {
        //Zero out data.
        bzero(messageBuffer,256);
        bytes = read(gameSocket,messageBuffer,255);

        if (bytes < 0)
        {
            printf("Error on handleGame read.\n");
            exit(1);
        }

        printf("Received message: %s\n",messageBuffer);
        bytes = write(gameSocket,"I got your message",18);

        if (bytes < 0)
        {
            printf("Error on handleGame write.\n");
            exit(1);
        }
    }
}
