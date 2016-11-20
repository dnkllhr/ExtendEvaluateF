#include "BoardManager.h"

BoardManager::BoardManager()
{
	tileStack = new TileStack(NUMBER_OF_PLAYERS);
}

const Board& BoardManager::getBoard()
{
    return board;
}
    
void BoardManager::gameInit()
{
	// Create new Board
	Board board;
	
	// Initalize TileStack
	
    // Build the Tile list   
    Array<Array<Tile>> tiles = Tile::CreateTiles();
    
    std::vector<Tile> tileList;
    
    for(unsigned int i = 0; i < tiles.getSize(); i++)
    {
		for(unsigned int j = 0; j < tiles[i].getSize(); j++)
		{
			if(tiles[i][j].getTileType() == TileType::D && j == 0)
			{
				// Place starting tile in center
				Coord center(NUMBER_OF_PLAYABLE_TILES, NUMBER_OF_PLAYABLE_TILES);
				Tile& startingTile = tiles[i][j];
				Move startingMove(startingTile, center);
				board.place(startingMove);
			}
			else
			{
				tileList.push_back(tiles[i][j]);
			}
		}
	}
	
	// Randomize tile order
	std::random_shuffle( tileList.begin(), tileList.end() );
	
	// Build the TileStack from randomized list
	for(unsigned int i = 0; i < tileList.size(); i++)
	{
		tileStack->push(tileList[i]);
	}
}

const TileStack* BoardManager::getTileStack()
{
    return tileStack;
}

std::vector<Move> BoardManager::getLegalMoves(const Tile& tile)
{
    std::vector<Move> legalMoves;
    std::unordered_set<unsigned int> availableLocations = board.getAvailableLocations();
    
    for(const int gridId : availableLocations)
    {
    	Coord location = Board::getCoordinatesFromGridId(gridId);
    	const Tile ** borderingTiles = Board::getBorderingTiles(Board::get(location));

        if(GameRules::validTilePlacement(tile, borderingTiles))
        {
            legalMoves.push_back(Move(tile, location));
        }
    }

    return legalMoves;
}

void BoardManager::makeMove(const Move& move)
{
    // if calling this method, it is assumed that this is a legal move
    
    // consider checking whether the passed Tile == top?
    
    board.place(move);
    
    const Tile& tile = move.getTile();
    const Tile ** borderingTiles = Board::getBorderingTiles(tile);
	Regions::addConnection(tile, borderingTiles);

    // remove top Tile from list
    tileStack->pop();
}

bool BoardManager::isSurrounded(int tileID)
{
	bool surrounded = false;
	const Coord& tileCoord = Board::getCoordinatesFromTileId(tileID);
	
	int xLocation = tileCoord.getX();
	int yLocation = tileCoord.getY();

	const Array<Array<Tile>>& boardGrid = Board::getBoard();
	
	for(int i = -1; i <= 1; i++)
	{
		for(int j = -1; j <= 1; j++)
		{
			if (&boardGrid[xLocation + i][yLocation + j] != NULL)
			{
				surrounded = true;
			}
			else
			{
				return false;
			}
		}
	}
	return surrounded;
}