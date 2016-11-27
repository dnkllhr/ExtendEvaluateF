#include "BoardManager.h"

TileStack* BoardManager::tileStack = new TileStack(NUMBER_OF_PLAYERS);
unsigned int BoardManager::tileIDCounter = 0;
Tile * BoardManager::startingTile = NULL;
std::unordered_map<std::string, TileFunction> BoardManager::getTileFunctionFromName = std::unordered_map<std::string, TileFunction>();
int v = BoardManager::setupHashMap();


int BoardManager::setupHashMap()
{
    BoardManager::getTileFunctionFromName["JJJJ-"] = Tile::CreateTileY;
    BoardManager::getTileFunctionFromName["JJJJX"] = Tile::CreateTileB;
    BoardManager::getTileFunctionFromName["JJTJX"] = Tile::CreateTileA;
    BoardManager::getTileFunctionFromName["TTTT-"] = Tile::CreateTileX;
    BoardManager::getTileFunctionFromName["TJTJ-"] = Tile::CreateTileU;
    BoardManager::getTileFunctionFromName["TJJT-"] = Tile::CreateTileV;
    BoardManager::getTileFunctionFromName["TJTT-"] = Tile::CreateTileW;
    BoardManager::getTileFunctionFromName["LLLL-"] = Tile::CreateTileC;
    BoardManager::getTileFunctionFromName["JLLL-"] = Tile::CreateTileR;
    BoardManager::getTileFunctionFromName["LLJJ-"] = Tile::CreateTileN;
    BoardManager::getTileFunctionFromName["JLJL-"] = Tile::CreateTileG;
    BoardManager::getTileFunctionFromName["LJLJ-"] = Tile::CreateTileH;
    BoardManager::getTileFunctionFromName["LJJJ-"] = Tile::CreateTileE;
    BoardManager::getTileFunctionFromName["JLLJ-"] = Tile::CreateTileI;
    BoardManager::getTileFunctionFromName["TLJT-"] = Tile::CreateTileK;
    BoardManager::getTileFunctionFromName["TLJTP"] = Tile::CreateTileK;
    BoardManager::getTileFunctionFromName["JLTT-"] = Tile::CreateTileJ;
    BoardManager::getTileFunctionFromName["JLTTB"] = Tile::CreateTileJ;
    BoardManager::getTileFunctionFromName["TLTJ-"] = Tile::CreateTileD;
    BoardManager::getTileFunctionFromName["TLTJD"] = Tile::CreateTileD;
    BoardManager::getTileFunctionFromName["TLLL-"] = Tile::CreateTileT;
    BoardManager::getTileFunctionFromName["TLTT-"] = Tile::CreateTileL;
    BoardManager::getTileFunctionFromName["TLTTP"] = Tile::CreateTileL;
    BoardManager::getTileFunctionFromName["TLLT-"] = Tile::CreateTileP;
    BoardManager::getTileFunctionFromName["TLLTB"] = Tile::CreateTileP;
    BoardManager::getTileFunctionFromName["LJTJ-"] = Tile::CreateTileZ;
    BoardManager::getTileFunctionFromName["LJTJD"] = Tile::CreateTileZ;
    BoardManager::getTileFunctionFromName["TLLLC"] = Tile::CreateTileZ;
    return 0;
}






BoardManager::~BoardManager()
{
    if (startingTile != NULL) delete startingTile;
    if (tileStack != NULL) delete tileStack;
}

const Array<Array<Tile*>>& BoardManager::getBoard()
{
    return Board::getBoard();
}

void BoardManager::gameInit()
{
    Board::set(); // Set/reset the Board
    tileStack = new TileStack(NUMBER_OF_PLAYERS); // Initialize Tile stack

    // Build the Tile list
    Array<Array<Tile>> tiles = Tile::CreateTiles();

    std::vector<Tile> tileList;

    for(unsigned int i = 0; i < tiles.getSize(); i++)
    {
        for(unsigned int j = 0; j < tiles[i].getSize(); j++)
        {
            if(tiles[i][j].getTileType() == TileType::D && tiles[i][j].getPrey() == PreyType::None && j == 0)
            {
                // Place starting tile in center
                Coord center(NUMBER_OF_PLAYABLE_TILES, NUMBER_OF_PLAYABLE_TILES);
                if (startingTile != NULL) delete startingTile;
                startingTile = new Tile(tiles[i][j]);
                Move startingMove(*startingTile, center);
                Board::place(startingMove);
                const Tile ** borderingTiles = Board::getBorderingTiles(*startingTile);
                Regions::addConnection(*startingTile, borderingTiles);
                startingTile->placeTile();
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

TileStack* BoardManager::getTileStack()
{
    return tileStack;
}

Tile& BoardManager::getTopTileStack()
{
    return tileStack->front();
}

std::vector<Move> BoardManager::getValidMoves(const Tile& tile)
{
    std::vector<Move> validMoves;
    std::unordered_set<unsigned int> availableLocations = Board::getAvailableLocations();

    for(const int gridId : availableLocations)
    {
        const Coord location = Board::getCoordinatesFromGridId(gridId);
        const Tile ** borderingTiles = Board::getBorderingTiles(location);
        Tile tileCopy = tile;
        // ^^ was orginally going to use a copy of the Tile to rotate intermediately, but the copy constructor exceptioned on copying the Tile Name

        for(unsigned int rotation = 0; rotation < (unsigned int) NUM_TILE_SIDES; rotation++)
        {
////////////// FLOATING POINT EXCEPTION vvvvv
            tileCopy.setRotation(rotation);
////////////// FLOATING POINT EXCEPTION ^^^^^

            unsigned int numberOfEdges = NUM_TILE_SIDES * NUM_TILE_EDGES_PER_SIDE;

            if(GameRules::validTilePlacement(tileCopy, borderingTiles))
            {
                validMoves.push_back(Move(tileCopy, Coord(location), rotation)); // no meeple or croc

                for(unsigned int edgeIndex = 0; edgeIndex < numberOfEdges; edgeIndex++)
                {
                    if(GameRules::validMeeplePlacement(location, edgeIndex))
                    {
                        validMoves.push_back(Move(tileCopy, Coord(location), rotation, edgeIndex));
                    }
                }
////////////////// SEG FAULT vvvvv
                if(true)//GameRules::validCrocPlacement(tile, location))
////////////////// SEG FAULT ^^^^^
                {
                    validMoves.push_back(Move(tileCopy, Coord(location), rotation, true));
                }
            }   
        }
    }

    return validMoves;
}

void BoardManager::makeMove(const Move& move, unsigned int playerNumber)
{
    // if calling this method, it is assumed that this is a legal move
    Board::place(move);

    Tile& tile = move.getTile();
    const Tile ** borderingTiles = Board::getBorderingTiles(tile);
    Regions::addConnection(tile, borderingTiles);

    if(move.getMeepleLocation() != -1) // if Move includes Meeple
    {
        Regions::addMeeple(playerNumber, tile.getId(), move.getMeepleLocation());
    }
    else if(move.getHasCrocodile())
    {
        Regions::addCroc(playerNumber, tile.getId());
    }

    tile.placeTile(); // mark Tile as placed so it can no longer be rotated
    tileStack->pop(); // remove top Tile from list
}

#include <iostream>
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

//Entry points for AI
struct moveResult BoardManager::tryMove(const Tile& tile)
{
    return Regions::tryMove(tile, Board::getBorderingTiles(tile));
}





void BoardManager::cannotPlaceTile()
{
    //Code special cases.
}

void BoardManager::addTileToStack(std::string tileName)
{
    auto iter = getTileFunctionFromName.find(tileName);
    if (iter != getTileFunctionFromName.end())
    {
        int pseudoPreyType;
        switch(tileName.at(4)) //Prey identifier
        {
            case 'D':
                pseudoPreyType = 0;
                break;
            case 'B':
                pseudoPreyType = 1;
                break;
            case 'P':
                pseudoPreyType = 2;
                break;
            case 'C':
                pseudoPreyType = 3;
                break;
            default:
                pseudoPreyType = 4;
                break;
        }
        Array<Tile> thisTile = (*iter->second)(1, BoardManager::tileIDCounter, (PreyType)pseudoPreyType);
        tileStack->push(thisTile[0]);
    }
    else
    {
        throw std::logic_error("Could not find the function pointer for tile.");
    }
}


void BoardManager::inputTileStack(char stack[], int length)
{
    if(sizeof(stack) != (length * 5 + 1))
    {
        throw std::logic_error("sizeof stack and anticipated stack size differ");
    }

    std::string currentTile;
    for(int i = length - 6; i > 0; i -= 5)          //Skip over the null char and the first set of chars.
    {
        currentTile.assign(stack + i, stack + i + 5);
        //std::cout << "Current tile being added to stack is :" << currentTile << std::endl;
        BoardManager::addTileToStack(currentTile);
    }
}