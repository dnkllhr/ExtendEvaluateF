#include "Tile.h"

Array<Array<Tile>> Tile::CreateTiles() {
        const unsigned int numberOfTiles = 24;
        Array<Array<Tile>> arrayOfTiles(numberOfTiles);
        unsigned int startId = 0;

        arrayOfTiles[0] = Tile::CreateTileA(2, startId);
        arrayOfTiles[1] = Tile::CreateTileB(4, startId);
        arrayOfTiles[2] = Tile::CreateTileC(1, startId);
        arrayOfTiles[3] = Tile::CreateTileD(4, startId);
        arrayOfTiles[4] = Tile::CreateTileE(5, startId);
        arrayOfTiles[5] = Tile::CreateTileF(2, startId);
        arrayOfTiles[6] = Tile::CreateTileG(1, startId);
        arrayOfTiles[7] = Tile::CreateTileH(3, startId);
        arrayOfTiles[8] = Tile::CreateTileI(2, startId);
        arrayOfTiles[9] = Tile::CreateTileJ(3, startId);
        arrayOfTiles[10] = Tile::CreateTileK(3, startId);
        arrayOfTiles[11] = Tile::CreateTileL(3, startId);
        arrayOfTiles[12] = Tile::CreateTileM(2, startId);
        arrayOfTiles[13] = Tile::CreateTileN(3, startId);
        arrayOfTiles[14] = Tile::CreateTileO(2, startId);
        arrayOfTiles[15] = Tile::CreateTileP(3, startId);
        arrayOfTiles[16] = Tile::CreateTileQ(1, startId);
        arrayOfTiles[17] = Tile::CreateTileR(3, startId);
        arrayOfTiles[18] = Tile::CreateTileS(2, startId);
        arrayOfTiles[19] = Tile::CreateTileT(1, startId);
        arrayOfTiles[20] = Tile::CreateTileU(8, startId);
        arrayOfTiles[21] = Tile::CreateTileV(9, startId);
        arrayOfTiles[22] = Tile::CreateTileW(4, startId);
        arrayOfTiles[23] = Tile::CreateTileX(1, startId);

        return arrayOfTiles;
}

unsigned int Tile::getId() {
        return this->tile_id;
}

bool Tile::setRotation(unsigned int rotation) {
        if (this->placed) return false;

        unsigned int totalIndices = this->count_per_side * this->number_sides;
        this->rotation = (totalIndices - ((rotation * this->count_per_side) % totalIndices)) % totalIndices;
        return true;
}

bool Tile::getShield() {
        return this->has_shield;
}

unsigned int Tile::getNumberOfSides() {
        return this->number_sides;
}

unsigned int Tile::getCountPerSide() {
        return this->count_per_side;
}

TileType Tile::getTileType() {
        return this->tile_type;
}

TerrainType Tile::getTerrainType(unsigned int edge) {
        return this->edges[edge];
}

bool Tile::isConnected(unsigned int inEdge, unsigned int outEdge) {
        unsigned int offsetIn = (inEdge + this->rotation) % (this->number_sides * this->count_per_side);
        unsigned int offsetOut = (outEdge + this->rotation) % (this->number_sides * this->count_per_side);

        return (((this->edge_connections[offsetIn] >> offsetOut) & 1) == 1);
}

void Tile::placeTile() {
        this->placed = true;
}

bool Tile::isPlaced() {
        return this->placed;
}

Tile::Tile() {
        this->edges = NULL;
        this->edge_connections = NULL;
        this->number_sides = 4;
        this->count_per_side = 3;
        this->rotation = 0;
        this->placed = false;
}

Tile::~Tile() {
        if (this->edges != NULL) { 
                delete[] this->edges;
                this->edges = NULL;
        }
       if (this->edge_connections != NULL) {
                delete[] this->edge_connections;
                this->edge_connections = NULL;
        }
}

Tile::Tile(const Tile& other) : tile_id(other.tile_id), number_sides(other.number_sides), count_per_side(other.count_per_side), has_shield(other.has_shield), tile_type(other.tile_type), center(other.center), rotation(other.rotation), placed(other.placed) {
        this->edges = new TerrainType[this->number_sides * this->count_per_side];
        this->edge_connections = new unsigned int[this->number_sides * this->count_per_side];
        std::copy(other.edges, other.edges + (this->number_sides * this->count_per_side), this->edges);
        std::copy(other.edge_connections, other.edge_connections + (this->number_sides * this->count_per_side), this->edge_connections);
}

Tile& Tile::operator=(const Tile& other) {
        this->tile_id = other.tile_id;
        this->number_sides = other.number_sides;
        this->count_per_side = other.count_per_side;
        this->has_shield = other.has_shield;
        this->tile_type = other.tile_type;
        this->center = other.center;
        this->rotation = other.rotation;
        this->placed = other.placed;

        this->edges = new TerrainType[this->number_sides * this->count_per_side];
        this->edge_connections = new unsigned int[this->number_sides * this->count_per_side];
        std::copy(other.edges, other.edges + (this->number_sides * this->count_per_side), this->edges);
        std::copy(other.edge_connections, other.edge_connections + (this->number_sides * this->count_per_side), this->edge_connections);

        return *this;
}

Array<Tile> Tile::CreateTileA(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;

        newTile.has_shield = false;
        newTile.tile_type = TileType::A;

        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Church;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileB(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::B;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Church;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileC(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::C;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileD(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::D;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileE(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::E;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileF(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::F;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileG(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::G;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileH(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::H;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileI(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::I;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);
        
        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileJ(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::J;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileK(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::K;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileL(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::L;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Fork;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) {        
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileM(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::M;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileN(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::N;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileO(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::O;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileP(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::P;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Grass;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileQ(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::Q;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileR(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::R;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileS(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = true;
        newTile.tile_type = TileType::S;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileT(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::T;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
        };

        newTile.center = TerrainType::Castle;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileU(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::U;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileV(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::V;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Road;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileW(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::W;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Fork;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}

Array<Tile> Tile::CreateTileX(unsigned int tileCount, unsigned int& startId) {
        Tile newTile;
        newTile.has_shield = false;
        newTile.tile_type = TileType::X;
        newTile.edges = new TerrainType[(newTile.number_sides * newTile.count_per_side)] {
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
                TerrainType::Grass, TerrainType::Road, TerrainType::Grass
        };

        newTile.center = TerrainType::Fork;
        newTile.edge_connections = new unsigned int[(newTile.number_sides * newTile.count_per_side)] {
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

        Array<Tile> newTiles(tileCount);

        for (unsigned int i = 0; i < tileCount; i++) { 
                newTiles[i] = newTile;
                newTiles[i].tile_id = startId++;
        }

        return newTiles;
}
