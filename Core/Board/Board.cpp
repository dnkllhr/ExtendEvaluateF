#include "Board.h"

Board::Board()
{
	const int NUMBER_OF_PLAYABLE_TILES = 76; // excluding starting tile
	
	const int BOARD_WIDTH = NUMBER_OF_PLAYABLE_TILES * 2 + 1;
	const int BOARD_HEIGHT = NUMBER_OF_PLAYABLE_TILES * 2 + 1;
	
	this->board(Array<Array<Tile>>(BOARD_WIDTH));
	for(int i = 0; i < BOARD_WIDTH; i++)
	{
		this->board[i](Array<Tile>(BOARD_HEIGHT));
	}
}

const Array<Array<Tile&>>& Board::getBoard()
{
	return this->board;
}

const Tile& Board::get(const Coord& coord)
{
	return this->board[coord->getX()][coord->getY()];
}

const Tile& Board::get(unsigned int tileID)
{
    auto tileSearch = tileIDTracker.find(tileID);
    if(tileSearch != tileIDTracker.end())
    {
        return (Board::get(tileSearch->second));
    }
    else
    {
        //THROW ERRROR HERE
        return NULL;
    }
}

void Board::place(const Move& move)
{
	this->board[move.getCoord().getX()][move.getCoord().getY()] = move.getTile();
	//Used for accounting
	tileIDTracker[move.getTile().getID()] = move;
}

std::set Board::getAvailableLocations()
{
	return this->availableLocations;
}

const Move& Board::getCoordinates(unsigned int tileID)
{
    auto tileSearch = tileIDTracker.find(tileID);
    if(tileSearch != tileIDTracker.end())
    {
    	return tileSearch->second;
    }
    else
    {
    	//THROW ERRROR HERE
    	return NULL;
    }
}