#ifndef __TILE_H
#define __TILE_H

#include <algorithm>
#include "TileType.h"
#include "TerrainType.h"
#include "../../Common/Array.h"

class Tile {
        public:
                static Array<Array<Tile>> CreateTiles();

                Tile& operator=(const Tile& other);
                ~Tile();

                bool setRotation(unsigned int rotation);
                bool getShield();
                unsigned int getNumberOfSides();
                TerrainType getTerrainType(unsigned int edge);
                TileType getTileType();
                bool isConnected(unsigned int inEdge, unsigned int outEdge);
                void placeTile();
                bool isPlaced();
                unsigned int getId();

        private:
                Tile();

                static Array<Tile> CreateTileA(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileB(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileC(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileD(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileE(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileF(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileG(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileH(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileI(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileJ(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileK(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileL(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileM(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileN(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileO(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileP(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileQ(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileR(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileS(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileT(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileU(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileV(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileW(unsigned int tileCount, unsigned int& startId);
                static Array<Tile> CreateTileX(unsigned int tileCount, unsigned int& startId);

                unsigned int tileId;
                // The number of sides this tile has
                unsigned int number_sides;
                unsigned int count_per_side;
                // Specifies whether this tile has a shield
                bool has_shield;
                // The type of tile
                TileType tile_type;
                // An array of TerrainTypes that specifies what is in each part of each edge.
                // Each edge should have 3 array elements.
                TerrainType * edges;
                // Seperate variable to hold what is in the center
                TerrainType center;
                // Rotation is an offset to the edges and edge_connections array
                unsigned int rotation;
                // Edge Connections is an array of integer arrays where the index correlates to an edge part and the array of integers at that location contains all of the edge parts that it connects to.
                // This should be the same size as the edges array
                unsigned int * edge_connections;
                // Determines if the tile has been placed (used).
                bool placed;
};

#endif
