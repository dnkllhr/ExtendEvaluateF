#include "Tile.h"

Array<Array<Tile>> Tile::CreateTiles() {
    const unsigned int numberOfTiles = NUM_TILES;
    Array<Array<Tile>> arrayOfTiles(numberOfTiles);
    unsigned int startId = 0;

    arrayOfTiles[0] = Tile::CreateTileA(2, startId, PreyType::None);
    arrayOfTiles[1] = Tile::CreateTileB(4, startId, PreyType::None);
    arrayOfTiles[2] = Tile::CreateTileC(1, startId, PreyType::None);
    arrayOfTiles[3] = Tile::CreateTileD(3, startId, PreyType::None);
    arrayOfTiles[4] = Tile::CreateTileD(2, startId, PreyType::Deer);
    arrayOfTiles[5] = Tile::CreateTileE(5, startId, PreyType::None);
    arrayOfTiles[6] = Tile::CreateTileG(3, startId, PreyType::None);
    arrayOfTiles[7] = Tile::CreateTileH(3, startId, PreyType::None);
    arrayOfTiles[8] = Tile::CreateTileI(2, startId, PreyType::None);
    arrayOfTiles[9] = Tile::CreateTileJ(1, startId, PreyType::None);
    arrayOfTiles[10] = Tile::CreateTileJ(2, startId, PreyType::Buffalo);
    arrayOfTiles[11] = Tile::CreateTileK(1, startId, PreyType::None);
    arrayOfTiles[12] = Tile::CreateTileK(2, startId, PreyType::Boar);
    arrayOfTiles[13] = Tile::CreateTileL(1, startId, PreyType::None);
    arrayOfTiles[14] = Tile::CreateTileL(2, startId, PreyType::Boar);
    arrayOfTiles[15] = Tile::CreateTileN(5, startId, PreyType::None);
    arrayOfTiles[16] = Tile::CreateTileP(3, startId, PreyType::None);
    arrayOfTiles[17] = Tile::CreateTileP(2, startId, PreyType::Buffalo);
    arrayOfTiles[18] = Tile::CreateTileR(4, startId, PreyType::None);
    arrayOfTiles[19] = Tile::CreateTileT(1, startId, PreyType::None);
    arrayOfTiles[20] = Tile::CreateTileT(2, startId, PreyType::Croc);
    arrayOfTiles[21] = Tile::CreateTileU(8, startId, PreyType::None);
    arrayOfTiles[22] = Tile::CreateTileV(9, startId, PreyType::None);
    arrayOfTiles[23] = Tile::CreateTileW(4, startId, PreyType::None);
    arrayOfTiles[24] = Tile::CreateTileX(1, startId, PreyType::None);
    arrayOfTiles[25] = Tile::CreateTileY(1, startId, PreyType::None);
    arrayOfTiles[26] = Tile::CreateTileZ(1, startId, PreyType::None);
    arrayOfTiles[27] = Tile::CreateTileZ(2, startId, PreyType::Deer);

    return arrayOfTiles;
}

unsigned int Tile::getId() const {
    return this->tileId;
}

unsigned int Tile::getRotation() const {
    return (this->numberSides - (this->rotation / this->countPerSide)) % this->numberSides;
}

bool Tile::setRotation(unsigned int rotation) {
    if (this->placed) return false;

    unsigned int totalIndices = this->countPerSide * this->numberSides;
    this->rotation = (totalIndices - ((rotation * this->countPerSide) % totalIndices)) % totalIndices;
    return true;
}

PreyType Tile::getPrey() const {
    return this->prey;
}

unsigned int Tile::getNumberOfSides() const {
    return this->numberSides;
}

unsigned int Tile::getCountPerSide() const {
    return this->countPerSide;
}

TileType Tile::getTileType() const {
    return this->tileType;
}

TerrainType Tile::getCenter() const {
    return this->center;
}

TerrainType Tile::getTerrainType(unsigned int edge) const {
    return this->edges[edge];
}

std::string Tile::getTileName() const {
    std::string name = std::string(*this->tileName);

    if (this->prey == PreyType::Deer) name += "D";
    else if (this->prey == PreyType::Buffalo) name += "B";
    else if (this->prey == PreyType::Boar) name += "P";
    else if (this->prey == PreyType::Croc) name += "C";

    return name;
}

bool Tile::isConnected(unsigned int inEdge, unsigned int outEdge) const {
    unsigned int offsetIn = (inEdge + this->rotation) % (this->numberSides * this->countPerSide);
    unsigned int offsetOut = (outEdge + this->rotation) % (this->numberSides * this->countPerSide);

    return (((this->edgeConnections[offsetIn] >> offsetOut) & 1) == 1);
}

void Tile::placeTile() {
    this->placed = true;
}

bool Tile::isPlaced() const {
    return this->placed;
}

Tile::Tile() {
    this->tileName = NULL;
    this->edges = NULL;
    this->edgeConnections = NULL;
    this->numberSides = NUM_TILE_SIDES;
    this->countPerSide = NUM_TILE_EDGES_PER_SIDE;
    this->rotation = 0;
    this->placed = false;
}

Tile::~Tile() {
    if (this->edges != NULL) {
        delete[] this->edges;
        this->edges = NULL;
    }
    if (this->edgeConnections != NULL) {
        delete[] this->edgeConnections;
        this->edgeConnections = NULL;
    }
    if (this->tileName != NULL) {
        delete this->tileName;
        this->tileName = NULL;
    }
}

Tile::Tile(const Tile& other) : tileId(other.tileId), numberSides(other.numberSides), countPerSide(other.countPerSide), prey(other.prey), tileType(other.tileType), center(other.center), rotation(other.rotation), placed(other.placed) {
    this->tileName = new std::string(*other.tileName);
    this->edges = new TerrainType[this->numberSides * this->countPerSide];
    this->edgeConnections = new unsigned int[this->numberSides * this->countPerSide];
    std::copy(other.edges, other.edges + (this->numberSides * this->countPerSide), this->edges);
    std::copy(other.edgeConnections, other.edgeConnections + (this->numberSides * this->countPerSide), this->edgeConnections);
}

Tile& Tile::operator=(const Tile& other) {
    this->tileId = other.tileId;
    this->numberSides = other.numberSides;
    this->countPerSide = other.countPerSide;
    this->prey = other.prey;
    this->tileType = other.tileType;
    this->center = other.center;
    this->rotation = other.rotation;
    this->placed = other.placed;

    this->tileName = new std::string(*other.tileName);
    this->edges = new TerrainType[this->numberSides * this->countPerSide];
    this->edgeConnections = new unsigned int[this->numberSides * this->countPerSide];
    std::copy(other.edges, other.edges + (this->numberSides * this->countPerSide), this->edges);
    std::copy(other.edgeConnections, other.edgeConnections + (this->numberSides * this->countPerSide), this->edgeConnections);

    return *this;
}

bool operator==(const Tile& curr, const Tile& other) {
    return (curr.tileId == other.tileId) && (curr.prey == other.prey) && (curr.tileType == other.tileType) && (curr.rotation == other.rotation);
}

std::ostream& operator<<(std::ostream& out, Tile tile) {
    out << tile.getTileName();

    return out;
}

Array<Tile> Tile::CreateTileA(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;

    newTile.tileName = new std::string("JJTJX");
    newTile.prey = preyType;
    newTile.tileType = TileType::A;

    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Church;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileB(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("JJJJX");
    newTile.prey = preyType;
    newTile.tileType = TileType::B;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Church;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileC(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("LLLL");
    newTile.prey = preyType;
    newTile.tileType = TileType::C;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
    };

    newTile.center = TerrainType::Castle;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileD(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TLTJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::D;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
    };

    newTile.center = TerrainType::Road;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileE(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("LJJJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::E;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Grass;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileG(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("JLJL");
    newTile.prey = preyType;
    newTile.tileType = TileType::G;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
    };

    newTile.center = TerrainType::Castle;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileH(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("LJLJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::H;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Grass;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileI(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("JLLJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::I;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Grass;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileJ(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("JLTT");
    newTile.prey = preyType;
    newTile.tileType = TileType::J;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Road;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
        0b100001000111,
        0b100001000111,
        0b100001000111,
        0b000000111000,
        0b000000111000,
        0b000000111000,
        0b100001000111,
        0b010010000000,
        0b001100000000,
        0b001100000000,
        0b010010000000,
        0b100001000111,
    };

    Array<Tile> newTiles(tileCount);

    for (unsigned int i = 0; i < tileCount; i++) {
        newTiles[i] = newTile;
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileK(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TLJT");
    newTile.prey = preyType;
    newTile.tileType = TileType::K;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Road;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileL(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TLTT");
    newTile.prey = preyType;
    newTile.tileType = TileType::L;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Fork;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileN(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("LLJJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::N;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
    };

    newTile.center = TerrainType::Grass;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileP(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TLLT");
    newTile.prey = preyType;
    newTile.tileType = TileType::P;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Grass;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
        0b100000000001,
        0b010000000010,
        0b001000000100,
        0b000111111000,
        0b000111111000,
        0b000111111000,
        0b000111111000,
        0b000111111000,
        0b000111111000,
        0b001000000100,
        0b010000000010,
        0b100000000001
    };

    Array<Tile> newTiles(tileCount);

    for (unsigned int i = 0; i < tileCount; i++) {
        newTiles[i] = newTile;
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileR(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("JLLL");
    newTile.prey = preyType;
    newTile.tileType = TileType::R;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
    };

    newTile.center = TerrainType::Castle;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileT(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TLLL");
    newTile.prey = preyType;
    newTile.tileType = TileType::T;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle
    };

    newTile.center = TerrainType::Castle;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
        0b000000000001,
        0b000000000010,
        0b000000000100,
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileU(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TJTJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::U;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Road;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileV(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TJJT");
    newTile.prey = preyType;
    newTile.tileType = TileType::V;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Road;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
        0b100000000001,
        0b010000000010,
        0b001111111100,
        0b001111111100,
        0b001111111100,
        0b001111111100,
        0b001111111100,
        0b001111111100,
        0b001111111100,
        0b001111111100,
        0b010000000010,
        0b100000000001
    };

    Array<Tile> newTiles(tileCount);

    for (unsigned int i = 0; i < tileCount; i++) {
        newTiles[i] = newTile;
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileW(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TJTT");
    newTile.prey = preyType;
    newTile.tileType = TileType::W;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Fork;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
        0b100000000001,
        0b010010000010,
        0b000001111100,
        0b000001111100,
        0b000001111100,
        0b000001111100,
        0b000001111100,
        0b010010000010,
        0b001100000000,
        0b001100000000,
        0b010010000010,
        0b100000000001
    };

    Array<Tile> newTiles(tileCount);

    for (unsigned int i = 0; i < tileCount; i++) {
        newTiles[i] = newTile;
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileX(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("TTTT");
    newTile.prey = preyType;
    newTile.tileType = TileType::X;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass
    };

    newTile.center = TerrainType::Fork;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileY(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("JJJJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::Y;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Fork;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
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
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}

Array<Tile> Tile::CreateTileZ(unsigned int tileCount, unsigned int& startId, PreyType preyType) {
    Tile newTile;
    newTile.tileName = new std::string("WJTJ");
    newTile.prey = preyType;
    newTile.tileType = TileType::Z;
    newTile.edges = new TerrainType[(newTile.numberSides * newTile.countPerSide)] {
        TerrainType::Castle, TerrainType::Castle, TerrainType::Castle,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Road, TerrainType::Grass,
        TerrainType::Grass, TerrainType::Grass, TerrainType::Grass
    };

    newTile.center = TerrainType::Fork;
    newTile.edgeConnections = new unsigned int[(newTile.numberSides * newTile.countPerSide)] {
        0b000000000111,
        0b000000000111,
        0b000000000111,
        0b000001111000,
        0b000001111000,
        0b000001111000,
        0b000001111000,
        0b000010000000,
        0b111100000000,
        0b111100000000,
        0b111100000000,
        0b111100000000
    };

    Array<Tile> newTiles(tileCount);

    for (unsigned int i = 0; i < tileCount; i++) {
        newTiles[i] = newTile;
        newTiles[i].tileId = startId++;
    }

    return newTiles;
}
