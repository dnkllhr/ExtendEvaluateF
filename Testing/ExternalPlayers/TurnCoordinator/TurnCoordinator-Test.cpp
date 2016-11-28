#include "../ExternalPlayers/TurnCoordinator/TurnCoordinator.h"
#include <string.h>
#include "gtest/gtest.h"

//Move& TurnCoordinator::convertInMove(gameMessage *msg)
/*
struct moveMessage
{
    unsigned int p1;            //Player flag
    char tile[6];       //Tile Identifier
    bool placeable;     //Can you use tile?
    unsigned int x;              //X coordinate
    unsigned int y;              //Y coordinate
    unsigned int orientation;    //Orientation using network protocol offsets
    int meepleType;     //0: NONE    1: TIGER    2: CROC
    bool pickupMeeple;
    bool pass;
    int zone;           //Zone for meeple if TIGER
};
struct gameMessage
{
    int messageType;
    messageData data;
};


Tile& getTile() const;
const Coord& getCoord() const;
unsigned int getRotation() const;
int getMeepleLocation() const;
bool getHasCrocodile() const;
bool getPickupMeeple() const;


*/
TEST(TurnCoordinator, convertInMove)
{
    gameMessage *msg = new gameMessage;
    msg->messageType = 1;
    msg->data.move.p1 = 1;
    strcpy(msg->data.move.tile, "TJJT-");
    msg->data.move.placeable = true;
    msg->data.move.x = 1;
    msg->data.move.y = 1;
    msg->data.move.orientation = 0;
    msg->data.move.meepleType = 1;
    msg->data.move.pickupMeeple = false;
    msg->data.move.pass = false;
    msg->data.move.zone = 1;

    Move mv = TurnCoordinator::convertInMove(msg);    
    ASSERT_EQ(mv.getCoord().getX(), msg->data.move.x);
    ASSERT_EQ(mv.getCoord().getY(), msg->data.move.y);  
    ASSERT_EQ(mv.getMeepleLocation(), 0);               //Output for converting zone to edges
    ASSERT_EQ(mv.getRotation(), msg->data.move.orientation); 
    ASSERT_FALSE(mv.getHasCrocodile()); 

}