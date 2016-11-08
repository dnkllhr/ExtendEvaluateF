#include "Tile.h"

Tile ** Tile::CreateTiles() {
        Tile ** arrayOfTiles = new Tile*[24];
        unsigned int startId = 0;

        arrayOfTiles[0] = CreateTileA(2, startId);
        arrayOfTiles[1] = CreateTileB(4, startId);
        arrayOfTiles[2] = CreateTileC(1, startId);
        arrayOfTiles[3] = CreateTileD(4, startId);
        arrayOfTiles[4] = CreateTileE(5, startId);
        arrayOfTiles[5] = CreateTileF(2, startId);
        arrayOfTiles[6] = CreateTileG(1, startId);
        arrayOfTiles[7] = CreateTileH(3, startId);
        arrayOfTiles[8] = CreateTileI(2, startId);
        arrayOfTiles[9] = CreateTileJ(3, startId);
        arrayOfTiles[10] = CreateTileK(3, startId);
        arrayOfTiles[11] = CreateTileL(3, startId);
        arrayOfTiles[12] = CreateTileM(2, startId);
        arrayOfTiles[13] = CreateTileN(3, startId);
        arrayOfTiles[14] = CreateTileO(2, startId);
        arrayOfTiles[15] = CreateTileP(3, startId);
        arrayOfTiles[16] = CreateTileQ(1, startId);
        arrayOfTiles[17] = CreateTileR(3, startId);
        arrayOfTiles[18] = CreateTileS(2, startId);
        arrayOfTiles[19] = CreateTileT(1, startId);
        arrayOfTiles[20] = CreateTileU(8, startId);
        arrayOfTiles[21] = CreateTileV(9, startId);
        arrayOfTiles[22] = CreateTileW(4, startId);
        arrayOfTiles[23] = CreateTileX(1, startId);

        return arrayOfTiles;
}

bool Tile::setRotation(unsigned int rotation) {
        if (this->placed) return false;

        this->rotation = ((rotation * 3) % 4);
        return true;
}

bool Tile::getShield() {
        return this->has_shield;
}

unsigned int Tile::getNumberOfSides() {
        return this->number_sides;
}

TileType Tile::getTileType() {
        return this->tile_type;
}

bool Tile::isConnected(unsigned int inEdge, unsigned int outEdge) {
        unsigned int offsetIn = (inEdge + this->rotation) % 12;
        unsigned int offsetOut = (outEdge + this->rotation) % 12;

        return (((this->edge_connections[offsetIn] >> offsetOut) & 1) == 1);
}

void Tile::placeTile() {
        this->placed = true;
}

bool Tile::isPlaced() {
        return this->placed;
}

Tile::Tile() {
        this->number_sides = 4;
        this->rotation = 0;
        this->placed = false;
}

Tile::~Tile() {
        delete[] edges;
        delete[] edge_connections;
}

Tile * Tile::CreateTileA(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;

        newTile.has_shield = false;
        newTile.tile_type = TileType::A;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Church;
        newTile.edge_connections = new unsigned int[12] {
                0b111101111111,
                0b111101111111,
                0b111101111111,
                0b111101111111,
                0b111101111111,
                0b111101111111,
                0b111101111111,
                0b000010000000,
                0b111101111111,
                0b111101111111,
                0b111101111111,
                0b111101111111
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileB(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::B;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Church;
        newTile.edge_connections = new unsigned int[12] {
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileC(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::C;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111,
                0b111111111111
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileD(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::D;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[12] {
                0b111100000001,
                0b000010000010,
                0b000001000100,
                0b000000111000,
                0b000000111000,
                0b000000111000,
                0b000001000100,
                0b000010000010,
                0b111100000001,
                0b111100000001,
                0b111100000001,
                0b111100000001
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileE(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::E;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b000000000111,
                0b000000000111,
                0b000000000111,
                0b111111111000,
                0b111111111000,
                0b111111111000,
                0b111111111000,
                0b111111111000,
                0b111111111000,
                0b111111111000,
                0b111111111000,
                0b111111111000
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileF(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::F;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b000000000111,
                0b000000000111,
                0b000000000111,
                0b111000111000,
                0b111000111000,
                0b111000111000,
                0b000111000000,
                0b000111000000,
                0b000111000000,
                0b111000111000,
                0b111000111000,
                0b111000111000
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileG(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::G;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b000111000111,
                0b000111000111,
                0b000111000111,
                0b000000111000,
                0b000000111000,
                0b000000111000,
                0b000111000111,
                0b000111000111,
                0b000111000111,
                0b111000000000,
                0b111000000000,
                0b111000000000
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileH(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::H;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b000111000111,
                0b000111000111,
                0b000111000111,
                0b000000111000,
                0b000000111000,
                0b000000111000,
                0b000111000111,
                0b000111000111,
                0b000111000111,
                0b111000000000,
                0b111000000000,
                0b111000000000
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileI(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::I;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b111000000111,
                0b111000000111,
                0b111000000111,
                0b000000111000,
                0b000000111000,
                0b000000111000,
                0b000111000000,
                0b000111000000,
                0b000111000000,
                0b111000000111,
                0b111000000111,
                0b111000000111
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileJ(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::J;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[12] {
                0b000000000111,
                0b000000000111,
                0b000000000111,
                0b111100001000,
                0b000010010000,
                0b000001100000,
                0b000001100000,
                0b000010010000,
                0b111100001000,
                0b111100001000,
                0b111100001000,
                0b111100001000
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileK(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::K;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[12] {
                0b100000000001,
                0b010000000010,
                0b001111000100,
                0b000000111000,
                0b000000111000,
                0b000000111000,
                0b001111000100,
                0b001111000100,
                0b001111000100,
                0b001111000100,
                0b010000000010,
                0b100000000001
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileL(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::L;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Fork;
        newTile.edge_connections = new unsigned int[12] {
                0b100000000001,
                0b000000000010,
                0b000001000100,
                0b000000111000,
                0b000000111000,
                0b000000111000,
                0b000001000100,
                0b000010000000,
                0b001100000000,
                0b001100000000,
                0b010000000000,
                0b100000000001
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileM(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::M;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b111000000111,
                0b111000000111,
                0b111000000111,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b111000000111,
                0b111000000111,
                0b111000000111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileN(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::N;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b111000000111,
                0b111000000111,
                0b111000000111,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b000111111000,
                0b111000000111,
                0b111000000111,
                0b111000000111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileO(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::O;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b111000000111,
                0b111000000111,
                0b111000000111,
                0b000100001000,
                0b000010010000,
                0b000001100000,
                0b000001100000,
                0b000010010000,
                0b000100001000,
                0b111000000111,
                0b111000000111,
                0b111000000111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileP(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::P;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[12] {
                0b111000000111,
                0b111000000111,
                0b111000000111,
                0b000100001000,
                0b000010010000,
                0b000001100000,
                0b000001100000,
                0b000010010000,
                0b000100001000,
                0b111000000111,
                0b111000000111,
                0b111000000111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileQ(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::Q;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b000111000000,
                0b000111000000,
                0b000111000000,
                0b111000111111,
                0b111000111111,
                0b111000111111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileR(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::R;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b000111000000,
                0b000111000000,
                0b000111000000,
                0b111000111111,
                0b111000111111,
                0b111000111111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileS(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::S;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b000001000000,
                0b000010000000,
                0b000100000000,
                0b111000111111,
                0b111000111111,
                0b111000111111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileT(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::T;
        newTile.edges = new TerrainType[12] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[12] {
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b111000111111,
                0b000001000000,
                0b000010000000,
                0b000100000000,
                0b111000111111,
                0b111000111111,
                0b111000111111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileU(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::U;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[12] {
                0b111100000001,
                0b000010000010,
                0b000001111100,
                0b000001111100,
                0b000001111100,
                0b000001111100,
                0b000001111100,
                0b000010000010,
                0b111100000001,
                0b111100000001,
                0b111100000001,
                0b111100000001
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileV(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::V;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[12] {
                0b100001111111,
                0b100001111111,
                0b100001111111,
                0b100001111111,
                0b100001111111,
                0b100001111111,
                0b100001111111,
                0b010010000000,
                0b001100000000,
                0b001100000000,
                0b010010000000,
                0b100001111111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileW(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::W;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Fork;
        newTile.edge_connections = new unsigned int[12] {
                0b100000001111,
                0b100000001111,
                0b100000001111,
                0b100000001111,
                0b000000010000,
                0b000001100000,
                0b000001100000,
                0b000010000000,
                0b001100000000,
                0b001100000000,
                0b010000000000,
                0b100000001111
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileX(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::X;
        newTile.edges = new TerrainType[12] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Fork;
        newTile.edge_connections = new unsigned int[12] {
                0b100000000001,
                0b000000000010,
                0b000000001100,
                0b000000001100,
                0b000000010000,
                0b000001100000,
                0b000001100000,
                0b000010000000,
                0b001100000000,
                0b001100000000,
                0b010000000000,
                0b100000000001
        };

        Tile * newTiles = new Tile[tileCount];

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}
