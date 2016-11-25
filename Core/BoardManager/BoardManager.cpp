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


std::vector<Move> BoardManager::getValidMoves(Tile& tile)
{
    std::vector<Move> validMoves;
    std::unordered_set<unsigned int> availableLocations = board.getAvailableLocations();
    
    for(const int gridId : availableLocations)
    {
    	Coord location = Board::getCoordinatesFromGridId(gridId);
    	const Tile ** borderingTiles = Board::getBorderingTiles(Board::get(location));
    	Tile tileCopy = tile;

    	for(int r = 0; r < NUM_TILE_SIDES; r++)
    	{
    		tileCopy.setRotation(r);
	        if(GameRules::validTilePlacement(tileCopy, borderingTiles))
	        {
	            validMoves.push_back(Move(tile, location, r));
	        }   		
    	}
    }

    return validMoves;
}

void BoardManager::makeMove(const Move& move)
{
    // if calling this method, it is assumed that this is a legal move
    
    board.place(move);
    
    Tile& tile = move.getTile();
    const Tile ** borderingTiles = Board::getBorderingTiles(tile);
	Regions::addConnection(tile, borderingTiles);

    tile.placeTile(); // mark Tile as placed so it can no longer be rotated
    tileStack->pop(); // remove top Tile from list
}

unsigned int BoardManager::isSurrounded(int tileID)
{
	unsigned int surrounded = 0;
	const Coord& coord = Board::getCoordinatesFromTileId(tileID);
    const Array<Array<Tile*>>& boardGrid = Board::getBoard();
    unsigned int xLocation = coord.getX();
    unsigned int yLocation = coord.getY();
	
	for(int i = -1; i <= 1; i++)
	{
		for(int j = -1; j <= 1; j++)
		{
			if (boardGrid[xLocation + i][yLocation + j] != NULL && (i != 0 && j != 0))
			{
				surrounded++;
			}
		}
	}
	return surrounded;
}
