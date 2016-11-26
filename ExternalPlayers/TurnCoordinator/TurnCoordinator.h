#include "../AI.h"

//Needs structure(s) defined for the messages from the external game client.


//Define message types

class TurnCoordinator
{
public:
    TurnCoordinator();
    ~TurnCoordinator();
    void startCoordinator();  //Infinite loop for receiving messages from external client
private:
    void receiveMessage();
    void handleMessage();
    void doOpponentMove();
    void callAI();
    void setupAI();
    static unsigned int AIPlayerNumber;
    static bool AISetup;
};