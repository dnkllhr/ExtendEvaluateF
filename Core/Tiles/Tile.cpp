#include "Tile.h"

Tile Tile::CreateTileA() {
	Tile newTile = new Tile();
	newTile.has_shield = false;
	newTile.tile_type = TileType::A;
	newTile.edges = { 
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass 
	};

	newTile.center = TerrainType::Church;
	newTile.edge_connections = {
		111101111111b,
		111101111111b,
		111101111111b,
		111101111111b,
		111101111111b,
		111101111111b,
		111101111111b,
		000010000000b,
		111101111111b,
		111101111111b,
		111101111111b,
		111101111111b,
	};
}

Tile Tile::CreateTileB() {

}

Tile Tile::CreateTileC() {

}

Tile Tile::CreateTileD() {

}

Tile Tile::CreateTileE() {

}

Tile Tile::CreateTileF() {

}

Tile Tile::CreateTileG() {

}

Tile Tile::CreateTileH() {

}

Tile Tile::CreateTileI() {

}

Tile Tile::CreateTileJ() {

}

Tile Tile::CreateTileK() {

}

Tile Tile::CreateTileL() {

}

Tile Tile::CreateTileM() {

}

Tile Tile::CreateTileN() {

}

Tile Tile::CreateTileO() {

}

Tile Tile::CreateTileP() {

}

Tile Tile::CreateTileQ() {

}

Tile Tile::CreateTileR() {

}

Tile Tile::CreateTileS() {

}

Tile Tile::CreateTileT() {

}

Tile Tile::CreateTileU() {

}

Tile Tile::CreateTileV() {

}

Tile Tile::CreateTileW() {

}

Tile Tile::CreateTileX() {

}

void Tile::setRotation(int rotation) {
	this->rotation = rotation;
}

bool Tile::getShield() {
	return this->has_shield;
}

int Tile::getNumberOfSides() {
	return this->number_sides;
}

TileType Tile::getTileType() {
	return this->tile_type;
}

bool Tile::isConnected(int edgeIndex) {
	// TODO
}

Tile::Tile() {
	this->number_sides = 4;
	this->rotation = 0;
	this->edges = new TerrainType[12];
	this->edge_connections = new int[12];
}
