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
                111101111111b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileB(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111111111111b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileC(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111111111111b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileD(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111100000001b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileE(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111111111000b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileF(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                000000000111b,
                000000000111b,
                000000000111b,
                111000111000b,
                111000111000b,
                111000111000b,
                000111000000b,
                000111000000b,
                000111000000b,
                111000111000b,
                111000111000b,
                111000111000b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileG(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                000111000111b,
                000111000111b,
                000111000111b,
                000000111000b,
                000000111000b,
                000000111000b,
                000111000111b,
                000111000111b,
                000111000111b,
                111000000000b,
                111000000000b,
                111000000000b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileH(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                000111000111b,
                000111000111b,
                000111000111b,
                000000111000b,
                000000111000b,
                000000111000b,
                000111000111b,
                000111000111b,
                000111000111b,
                111000000000b,
                111000000000b,
                111000000000b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileI(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000000111b,
                111000000111b,
                111000000111b,
                000000111000b,
                000000111000b,
                000000111000b,
                000111000000b,
                000111000000b,
                000111000000b,
                111000000111b,
                111000000111b,
                111000000111b
        };

        Tile * newTiles = new Tile[tileCount];
        
        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileJ(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                000000000111b,
                000000000111b,
                000000000111b,
                111100001000b,
                000010010000b,
                000001100000b,
                000001100000b,
                000010010000b,
                111100001000b,
                111100001000b,
                111100001000b,
                111100001000b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileK(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                100000000001b,
                010000000010b,
                001111000100b,
                000000111000b,
                000000111000b,
                000000111000b,
                001111000100b,
                001111000100b,
                001111000100b,
                001111000100b,
                010000000010b,
                100000000001b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileL(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                100000000001b,
                000000000010b,
                000001000100b,
                000000111000b,
                000000111000b,
                000000111000b,
                000001000100b,
                000010000000b,
                001100000000b,
                001100000000b,
                010000000000b,
                100000000001b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileM(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000000111b,
                111000000111b,
                111000000111b,
                000111111000b,
                000111111000b,
                000111111000b,
                000111111000b,
                000111111000b,
                000111111000b,
                111000000111b,
                111000000111b,
                111000000111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileN(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000000111b,
                111000000111b,
                111000000111b,
                000111111000b,
                000111111000b,
                000111111000b,
                000111111000b,
                000111111000b,
                000111111000b,
                111000000111b,
                111000000111b,
                111000000111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileO(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000000111b,
                111000000111b,
                111000000111b,
                000100001000b,
                000010010000b,
                000001100000b,
                000001100000b,
                000010010000b,
                000100001000b,
                111000000111b,
                111000000111b,
                111000000111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileP(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000000111b,
                111000000111b,
                111000000111b,
                000100001000b,
                000010010000b,
                000001100000b,
                000001100000b,
                000010010000b,
                000100001000b,
                111000000111b,
                111000000111b,
                111000000111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileQ(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                000111000000b,
                000111000000b,
                000111000000b,
                111000111111b,
                111000111111b,
                111000111111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileR(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                000111000000b,
                000111000000b,
                000111000000b,
                111000111111b,
                111000111111b,
                111000111111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileS(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                000001000000b,
                000010000000b,
                000100000000b,
                111000111111b,
                111000111111b,
                111000111111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileT(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                111000111111b,
                000001000000b,
                000010000000b,
                000100000000b,
                111000111111b,
                111000111111b,
                111000111111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileU(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                111100000001b,
                000010000010b,
                000001111100b,
                000001111100b,
                000001111100b,
                000001111100b,
                000001111100b,
                000010000010b,
                111100000001b,
                111100000001b,
                111100000001b,
                111100000001b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileV(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                100001111111b,
                100001111111b,
                100001111111b,
                100001111111b,
                100001111111b,
                100001111111b,
                100001111111b,
                010010000000b,
                001100000000b,
                001100000000b,
                010010000000b,
                100001111111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileW(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                100000001111b,
                100000001111b,
                100000001111b,
                100000001111b,
                000000010000b,
                000001100000b,
                000001100000b,
                000010000000b,
                001100000000b,
                001100000000b,
                010000000000b,
                100000001111b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}

Tile * Tile::CreateTileX(unsigned int tileCount, unsigned int& startId) {
        Tile newTile = new Tile();
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
                100000000001b,
                000000000010b,
                000000001100b,
                000000001100b,
                000000010000b,
                000001100000b,
                000001100000b,
                000010000000b,
                001100000000b,
                001100000000b,
                010000000000b,
                100000000001b
        };

        Tile * newTiles = new Tile[tileCount];

        for (int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tileId = startId++;
        }

        return newTiles;
}
