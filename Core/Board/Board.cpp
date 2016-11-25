#include "Board.h"

std::unordered_map<unsigned int, Move&> Board::tileIDTracker = std::unordered_map<unsigned int, Move&>();
std::unordered_set<unsigned int> Board::availableLocations = std::unordered_set<unsigned int>();
TileStack tileStack(unsigned int NUMBER_OF_PLAYERS);

Board::Board()
{
	boardWidth = NUMBER_OF_PLAYABLE_TILES * 2 + 1;
    boardHeight = NUMBER_OF_PLAYABLE_TILES * 2 + 1;
	
	board = Array<Array<Tile*>>(boardWidth);
    
	for(unsigned int i = 0; i < boardWidth; i++)
	{
		board[i] = Array<Tile*>(boardHeight);
	}
}

const Array<Array<Tile*>>& Board::getBoard()
{
	return board;
}

const Tile& Board::get(const Coord& coord)
{
	return *board[coord.getX()][coord.getY()];
}

const Tile& Board::get(unsigned int tileID)
{
    auto tileSearch = tileIDTracker.find(tileID);
    if(tileSearch != tileIDTracker.end())
    {
        return Board::get((tileSearch->second).getCoord());
    }
    else
    {
        throw std::invalid_argument("Invalid Tile ID");
    }
}

const Tile** Board::getBorderingTiles(const Tile& tile)
{
    const Coord& coord = Board::getCoordinatesFromTileId(tile.getId());

    const unsigned int numberOfBorderingTiles = 8;
    const Tile** borderingTiles = new const Tile*[numberOfBorderingTiles];
    int dx[numberOfBorderingTiles] = { -1, 0, 1, 1, 1, 0, -1, -1 };
    int dy[numberOfBorderingTiles] = { 1, 1, 1, 0, -1, -1, -1, 0 };

    const Array<Array<Tile*>>& boardGrid = Board::getBoard();

    for(unsigned int i = 0; i < numberOfBorderingTiles; i++)
    {
        unsigned int x = coord.getX() + dx[i];
        unsigned int y = coord.getY() + dy[i];
        borderingTiles[i] = boardGrid[x][y];
    }

    return borderingTiles;
}

const Coord Board::getCoordinatesFromGridId(unsigned int gridId)
{
    const Coord coord(gridId % boardWidth, gridId / boardWidth);
    return coord;
}

unsigned int Board::getGridId(const Coord& coord)
{
    unsigned int gridId = coord.getY() * boardWidth + coord.getX();
    return gridId;
}

unsigned int Board::getGridId(unsigned int x, unsigned int y)
{
    unsigned int gridId = y * boardWidth + x;
    return gridId;
}

void Board::place(const Move& move)
{
    const Coord& coord = move.getCoord();
    Tile& tile = move.getTile();
    unsigned int gridId = Board::getGridId(coord);

    availableLocations.erase(gridId);
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    const Array<Array<Tile*>>& boardGrid = Board::getBoard();

    for(unsigned int i = 0; i < 4; i++)
    {
        unsigned int x = coord.getX() + dx[i];
        unsigned int y = coord.getY() + dy[i];

        if(boardGrid[x][y] == NULL)
        {
            availableLocations.insert(Board::getGridId(x, y));
        }
    }

	board[coord.getX()][coord.getY()] = &tile;

	//Used for accounting
    Move moveCopy = move; // not const
    tileIDTracker.insert( std::pair<unsigned int, Move&>(tile.getId(), moveCopy) );
}

const std::unordered_set<unsigned int>& Board::getAvailableLocations()
{
	return availableLocations;
}

const Coord& Board::getCoordinatesFromTileId(unsigned int tileID)
{
    auto tileSearch = tileIDTracker.find(tileID);
    if(tileSearch != tileIDTracker.end())
    {
    	return tileSearch->second.getCoord();
    }
    else
    {
    	throw std::invalid_argument("Invalid Tile ID");
    }
}
