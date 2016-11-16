
#ifndef __GUI_MANAGER_H
#define __GUI_MANAGER_H

#include "Board.h"
#include "../Tiles/Tile.h"
#include "Coord.h"
#include "Move.h"
#include <vector>
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <sstream>

#define MAX_MSG_SIZE   100

class GuiManager {
  public:

    ///Constructor will open connection
    GuiManager();
    ///Deconstructor closes connection
    ~GuiManager();
    ///Print will serialize and send the current board structure to the python server
    void print(const gameBoard, const unsigned int offset);

};

#endif
