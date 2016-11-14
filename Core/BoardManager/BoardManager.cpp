#include "BoardManager.h"

BoardManager::BoardManager()
{
        
}

Board BoardManager::getBoard()
{
        return board;
}

std::ostream& BoardManager::operator<<(std::ostream& os, const BoardManager& obj)
{
        /// TODO: consider basic image-based board grid
        
        Tile[][] boardTiles = board.getTileMatrix();
        
        for(Tile[] row : boardTiles)
        {
                for(Tile[] tile : row)
                {
                        if(tile == null)
                        {
                                os << "-";
                        }
                        else
                        {
                                /// TODO: make this an enum / something better
                                os << tile.getTileType();
                        }
                }
        }

        return os;
}
        
void BoardManager::gameInit()
{
        Coord center(77,77);
        
        minCoord = center;
        maxCoord = center;
        
        // place inital center tile
        Tile startingTile = Tile.... /// TODO
        Move startingMove(startingTile, center);
        
        // create the Tile stack
        tileOrder = new TilePool(); // outside method?
}

const Tile& BoardManager::nextTile()
{
        return tileOrder.front();
}

const std::vector<Tile&>& BoardManager::getTileOrder()
{
        return tileOrder;
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
        board.set(move.tile, move.coord);
        
        // tracking the minimum and maximum coordinates in use allows partial displaying of the Board grid for debugging purposes
        if(move.getCoord().getX() < minCoord.getX()) minCoord.setX(move.getCoord().getX());
        if(move.getCoord().getY() < minCoord.getY()) minCoord.setY(move.getCoord().getY());
        if(move.getCoord().getX() > maxCoord.getX()) maxCoord.setX(move.getCoord().getX());
        if(move.getCoord().getY() > maxCoord.getY()) maxCoord.setY(move.getCoord().getY());
        
        // remove tile from list
        tileOrder.erase(tileOrder.begin());
}
