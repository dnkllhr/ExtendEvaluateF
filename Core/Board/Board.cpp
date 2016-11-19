#include "Board.h"

std::unordered_map<unsigned int, Move *> Board::tileIDTracker = std::unordered_map<unsigned int, Move *>();
std::unordered_set<unsigned int> Board::availableLocations = std::unordered_set<unsigned int>();
TileStack tileStack = TileStack(unsigned int n = NUMBER_OF_PLAYERS);

Board::Board()
{
	this->boardWidth = NUMBER_OF_PLAYABLE_TILES * 2 + 1;
    this->boardHeight = NUMBER_OF_PLAYABLE_TILES * 2 + 1;
	
	Board::board = Array<Array<Tile>>(this->boardWidth);
    
	for(int i = 0; i < this->boardWidth; i++)
	{
		Board::board[i] = Array<Tile>(this->boardHeight);
	}
}

const Array<Array<Tile>>& Board::getBoard()
{
	return Board::board;
}

const Tile& Board::get(const Coord& coord)
{
	return Board::board[coord.getX()][coord.getY()];
}

/* Error handling needed to get it to compile */
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

const Coord Board::getCoordinatesFromGridId(unsigned int gridId)
{
    Coord coord(gridId % Board::boardWidth, gridId / Board::boardWidth);
    return coord;
}

const unsigned int Board::getGridId(const Coord& coord)
{
    unsigned int gridId = coord.getY() * Board::boardWidth + coord.getX();
    return gridId;
}

/* Work needed to make this compile */
void Board::place(const Move& move)
{
	Board::board[move.getCoord().getX()][move.getCoord().getY()] = move.getTile();
	//Used for accounting
	tileIDTracker[move.getTile().getId()] = move;
}

const std::unordered_set<unsigned int>& Board::getAvailableLocations()
{
	return Board::availableLocations;
}

/* Method unfinished */
const Move& Board::getCoordinatesFromTileId(unsigned int tileID)
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
