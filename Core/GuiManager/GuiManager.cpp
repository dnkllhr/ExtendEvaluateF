#include "GuiManager.h"

GuiManager::GuiManager()
{
  const std::string * enumStrings[] = {
    "A","A270","A180","A90",
    "B","B270","B180","B90",
    "C","C270","C180","C90",
    "D","D270","D180","D90",
    "E","E270","E180","E90",
    "F","F270","F180","F90",
    "G","G270","G180","G90",
    "H","H270","H180","H90",
    "I","I270","I180","I90",
    "J","J270","J180","J90",
    "K","K270","K180","K90",
    "L","L270","L180","L90",
    "M","M270","M180","M90",
    "N","N270","N180","N90",
    "O","O270","O180","O90",
    "P","P270","P180","P90",
    "Q","Q270","Q180","Q90",
    "R","R270","R180","R90",
    "S","S270","S180","S90",
    "T","T270","T180","T90",
    "U","U270","U180","U90",
    "V","V270","V180","V90",
    "W","W270","W180","W90",
    "X","X270","X180","X90",
    "Y","Y270","Y180","Y90",
    "Z","Z270","Z180","Z90"
  }


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
  int center = 76;
  std::ostringstream oss;

  //size is the number of tiles per row/col
  int size = 2*offset + 1;
  oss << size << ":";
  for(int row = center + offset; row < center - offset; row--)  //top row
  {
    for(int col = center - offset; col < center + offset; col++) // left col
    {

      std::string tileString;
      int tileType =  gameBoard.getBoard()[row][col].getTileType();
      int rotation =  gameBoard.getBoard()[row][col].getRotation();
      tileString = enumStrings[(tileType*4)+(rotation)];

      oss<<tileString<<":";
    }
  }
  char* message = oss.str().c_str();

  //send message
  zmq::message_t request (std::strlen(message)-1);
  memcpy (request.data (), message, std::strlen(message)-1);
  socket.send (request);

  //await message return
  zmq::message_t reply;
  socket.recv (&reply);

}
