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
	Tile newTile = new Tile();
	newTile.has_shield = false;
	newTile.tile_type = TileType::B;
	newTile.edges = {
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
	};

	newTile.center = TerrainType::Church;
	newTile.edge_connections = {
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
	};
}

Tile Tile::CreateTileC() {
	Tile newTile = new Tile();
	newTile.has_shield = true;
	newTile.tile_type = TileType::C;
	newTile.edges = {
		TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
		TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
		TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
		TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
	};

	newTile.center = TerrainType::Castle;
	newTile.edge_connections = {
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
		111111111111b,
	};
}

Tile Tile::CreateTileD() {
	Tile newTile = new Tile();
	newTile.has_shield = false;
	newTile.tile_type = TileType::D;
	newTile.edges = {
		TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
		TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
		TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
	};

//	newTile.center = TerrainType::Castle;
	newTile.edge_connections = {
		111100000001b,
		000010000010b,
		000001000100b,
		000000111000b,
		000000111000b,
		000000111000b,
		000001000100b,
		000010000010b,
		111100000001b,
		111100000001b,
		111100000001b,
		111100000001b,
	};
}

Tile Tile::CreateTileE() {
	Tile newTile = new Tile();
	newTile.has_shield = false;
	newTile.tile_type = TileType::E;
	newTile.edges = {
		TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
		TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
	};

	newTile.center = TerrainType::Grass;
	newTile.edge_connections = {
		000000000111b,
		000000000111b,
		000000000111b,
		111111111000b,
		111111111000b,
		111111111000b,
		111111111000b,
		111111111000b,
		111111111000b,
		111111111000b,
		111111111000b,
		111111111000b,
	};
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
