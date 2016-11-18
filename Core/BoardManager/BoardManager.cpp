#include "BoardManager.h"

BoardManager::BoardManager()
{

}

const Board& BoardManager::getBoard()
{
    return board;
}
    
void BoardManager::gameInit(int numberOfPlayers)
{
	// Create new Board
	Board board();
	
	// Initalize TileStack
	TileStack tileStack(numberOfPlayers);
	
    // Build the Tile list   
    Tile& startingTile;
    Array<Array<Tile>> tiles = Tile::CreateTiles();
    
    std::vector<Tile&> tileList();
    
    for(unsigned int i = 0; i < tiles.getSize(); i++)
    {
		for(unsigned int j = 0; j < tiles[i].getSize(); j++)
		{
			if(tiles[i][j].getTileType() == TileType::D && j == 0)
			{
				// Place starting tile in center
				Coord center(76,76);
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
	std::random_shuffle( tileList.begin(), tileOrder.end() );
	
	// Build the TileStack from randomized list
	for(unsigned int i = 0; i < tileList.size(); i++)
	{
		tileStack.push(tileList[i]);
	}
}

const TileStack& BoardManager::getTileStack()
{
    return tileStack;
}

std::vector<Move> BoardManager::getLegalMoves(const Tile& tile)
{
    std::vector<Move> legalMoves;
    Coord * edgeLocations = board.getEdgeLocations();
    
    for(Coord edgeLocation : edgeLocations)
    {
        if(GameRules->isLegalMove(tile, edgeLocation))
        {
            legalMoves.push_back(Move(tile, edgeLocation));
        }
    }

    return legalMoves;
}

void BoardManager::makeMove(const Move& move)
{
    // if calling this method, it is assumed that this is a legal move
    
    // consider checking whether the passed Tile == top?
    
    // to implement based on Board implementaiton
    board.place(move.getTile(), move.getCoord());
    
    // remove top Tile from list
    tileStack.pop();
}

bool BoardManager::isSurrounded(int tileID)
{
	bool surrounded = false;
	/*for
		for*/
			//find coord of tileID
			Coord tileCoord;

	int xLocation = tileCoord.getX();
	int yLocation = tileCoord.getY();
	
	int i = -1;
	while (i < 2)
	{
		int j = -1;
		while (j < 2)
		{
			if (board[xLocation + i][yLocation + j])
			{
				surrounded = true;
			}
			else
			{
				return false;
			}
			j++;
		}
		i++;
	}
	return surrounded;
}
