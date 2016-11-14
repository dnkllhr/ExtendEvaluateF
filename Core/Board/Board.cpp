#include "Board.h"

Board::Board()
{
	const int NUMBER_OF_TILES = 76;
	
	const int BOARD_WIDTH = NUMBER_OF_TILES * 2 + 1;
	const int BOARD_HEIGHT = NUMBER_OF_TILES * 2 + 1;
	
	this->board = new Array<Array<Tile&>&>&(BOARD_WIDTH);
	for(int i = 0; i < BOARD_WIDTH; i++)
	{
		this->board[i] = new Array<Tile&>&(BOARD_HEIGHT);
	}
}

const Array<Array<Tile&>&>& Board::getBoard()
{
	return this->board;
}

const Tile& Board::get(const Coord& coord)
{
	return this->board[coord.getX()][coord.y];
}

void Board::place(const Tile& tile, const Coord& coord)
{
	this->board[coord.getX()][coord.getY()] = tile;
}
