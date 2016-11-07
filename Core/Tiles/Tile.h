#include "TileType.h"
#include "TerrainType.h"

class Tile {
	public:
		Tile CreateTileA();
		Tile CreateTileB();
		Tile CreateTileC();
		Tile CreateTileD();
		Tile CreateTileE();
		Tile CreateTileF();
		Tile CreateTileG();
		Tile CreateTileH();
		Tile CreateTileI();
		Tile CreateTileJ();
		Tile CreateTileK();
		Tile CreateTileL();
		Tile CreateTileM();
		Tile CreateTileN();
		Tile CreateTileO();
		Tile CreateTileP();
		Tile CreateTileQ();
		Tile CreateTileR();
		Tile CreateTileS();
		Tile CreateTileT();
		Tile CreateTileU();
		Tile CreateTileV();
		Tile CreateTileW();
		Tile CreateTileX();

		void setRotation(int rotation);
		bool getShield();
		int getNumberOfSides();
		TileType getTileType();
		bool isConnected(int edgeIndex);

	private:
		Tile();

		// The number of sides this tile has
		int number_sides;
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
		int rotation;
		// Edge Connections is an array of integer arrays where the index correlates to an edge part and the array of integers at that location contains all of the edge parts that it connects to.
		// This should be the same size as the edges array
		int * edge_connections;
}
