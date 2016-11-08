#include "TileType.h"
#include "TerrainType.h"

class Tile {
        public:
                Tile ** CreateTiles();

                void setRotation(unsigned int rotation);
                bool getShield();
                unsigned int getNumberOfSides();
                TileType getTileType();
                bool isConnected(unsigned int inEdge, unsigned int outEdge);
                void placeTile();
                bool isPlaced();
                int getId();

        private:
                Tile();

                Tile * CreateTileA(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileB(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileC(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileD(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileE(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileF(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileG(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileH(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileI(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileJ(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileK(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileL(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileM(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileN(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileO(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileP(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileQ(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileR(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileS(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileT(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileU(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileV(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileW(unsigned int tileCount, unsigned int& startId);
                Tile * CreateTileX(unsigned int tileCount, unsigned int& startId);

                unsigned int tileId;
                // The number of sides this tile has
                unsigned int number_sides;
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
}
