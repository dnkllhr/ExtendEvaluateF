#include "BoardManager.h"

BoardManager::BoardManager()
{
	
}

Board BoardManager::getBoard()
{
	return board;
}

void BoardManager::printBoard()
{
	/// TODO: consider basic image-based board grid
	
	Tile[][] boardTiles = board.getTileMatrix();
	
	for(Tile[] row : boardTiles)
	{
		for(Tile[] tile : row)
		{
			if(tile == null)
			{
				std::cout << "-";
			}
			else
			{
				/// TODO: make this an enum / something better
				std::cout << tile.getTileType();
			}
		}
	}		
}
	
void BoardManager::gameInit()
{
	board = new Board();
	
	Coord center = new Coord(77,77);
	
	minCoord = center;
	maxCoord = center;
	
	// place inital center tile
	Tile startingTile = Tile.... /// TODO
	Move startingMove = new Move(startingTile, center);
	
	// create the Tile stack
	tileOrder = new TilePool(); // outside method?
}

Tile BoardManager::nextTile()
{
	return tileOrder.front();
}

Vector<Tile> BoardManager::getTileOrder()
{
	return tileOrder;
}

Vector<Move> BoardManager::getLegalMoves(Tile tile)
{
	Vector<Move> legalMoves = new Vector<Move>();
	Coord[] edgeLocations = board.getEdgeLocations();
	
	for(Coord edgeLocation : edgeLocations)
	{
		if(GameRules->isLegalMove(tile, edgeLocation))
		{
			legalMoves.push_back(new Move(tile, edgeLocation));
		}
	}
	return legalMoves;
}

void BoardManager::makeMove(Move move)
{
	// if calling this method, it is assumed that this is a legal move
	
	// consider checking whether the passed Tile == top?
	
	// to implement based on Board implementaiton
	board->set(move.tile, move.coord);
	
	// tracking the minimum and maximum coordinates in use allows partial displaying of the Board grid for debugging purposes
	if(move.coord.x < minCoord.x) { minCoord.x = move.coord.x; }
	if(move.coord.y < minCoord.y) {	minCoord.y = move.coord.y; }
	if(move.coord.x > maxCoord.x) {	maxCoord.x = move.coord.x; }
	if(move.coord.y > maxCoord.y) {	maxCoord.x = move.coord.y; }
	
	// remove tile from list
	tileOrder.erase(tileOrder.begin());
}
