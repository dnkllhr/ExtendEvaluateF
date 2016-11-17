#include "GuiManager.h"
/*
Currently INCOMPLETE ... use client.cpp to see print sample
  - need to somehow return tile type from tile as string/char[]
  - need to add tile orientation to string serialization
*/
GuiManager::GuiManager()
{
  //  Prepare our context and socket
  zmq::context_t context (1);
  zmq::socket_t socket (context, ZMQ_REQ);

  //  Connect to the python server
  socket.connect ("tcp://localhost:5555");
}

GuiManager::~GuiManager()
{
}

GuiManager::print(const Board gameBoard, const unsigned int offset)
{
  std::ostringstream oss;

  //size is the number of tiles per row/col
  int size = 2*offset + 1;
  oss << size << ":";
  for(int row = 77 + offset; row < 77 - offset; row--)  //top row
  {
    for(int col = 77 - offset; col < 77 + offset; col++) // left col
    {
      oss<<gameBoard.getBoard()[row][col].getTileType(); //NEED TO CONVERT ENUM TO STRING INCOMPLETE
    }
  }
  char* message = oss.str();

  //send message
  zmq::message_t request (MAX_MSG_SIZE); //MAX SIZE OF 100 FOR NOW
  memcpy (request.data (), message, MAX_MSG_SIZE);
  socket.send (request);

  //await message return
  zmq::message_t reply;
  socket.recv (&reply);

}
