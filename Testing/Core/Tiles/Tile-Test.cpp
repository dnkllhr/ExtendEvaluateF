#include "../Core/Tiles/Tile.h"
#include "../Core/Tiles/TileType.h"
#include "gtest/gtest.h"

TEST(TileTests, CreateTiles) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        unsigned int expectedSize = 24;
        unsigned int minInnerArray = 1;
        unsigned int maxInnerArray = 9;

        unsigned int actualSize = tiles.getSize();
        ASSERT_EQ(actualSize, expectedSize);
        
        for (unsigned int i = 0; i < actualSize; i++) {
                unsigned int innerSize = tiles[i].getSize();
                EXPECT_LE(minInnerArray, innerSize);
                EXPECT_GE(maxInnerArray, innerSize);
        }
}

TEST(TileTests, SetRotation) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tile = tiles[0][0];
        
        bool result = tile.setRotation(1);
        EXPECT_TRUE(result);
}

TEST(TileTests, SetRotationAfterPlacement) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tile = tiles[0][0];
       
        bool result = tile.setRotation(1);
        EXPECT_TRUE(result);

        tile.placeTile();

        result = tile.setRotation(2);
        EXPECT_FALSE(result);
}

TEST(TileTests, GetShield) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];
        Tile& tileC = tiles[2][0];

        EXPECT_FALSE(tileA.getShield());
        EXPECT_TRUE(tileC.getShield());
}

TEST(TileTests, GetNumberOfSides) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];
        Tile& tileC = tiles[2][0];

        EXPECT_EQ(tileA.getNumberOfSides(), (unsigned int)4);
        EXPECT_EQ(tileC.getNumberOfSides(), (unsigned int)4);
}

TEST(TileTests, GetCountPerSide) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];
        Tile& tileC = tiles[2][0];

        EXPECT_EQ(tileA.getCountPerSide(), (unsigned int)3);
        EXPECT_EQ(tileC.getCountPerSide(), (unsigned int)3);
}

TEST(TileTests, GetTerrainType) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];
        Tile& tileC = tiles[2][0];

        EXPECT_EQ(tileA.getTerrainType(0), TerrainType::Grass);
        EXPECT_EQ(tileC.getTerrainType(0), TerrainType::Castle);
}

TEST(TileTests, GetTileType) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];
        Tile& tileC = tiles[2][0];

        EXPECT_EQ(tileA.getTileType(), TileType::A);
        EXPECT_EQ(tileC.getTileType(), TileType::C);
}

TEST(TileTests, IsConnectedTileA) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];

        EXPECT_TRUE(tileA.isConnected(0, 11));
        EXPECT_TRUE(tileA.isConnected(11, 0));
        EXPECT_FALSE(tileA.isConnected(0, 7));
        EXPECT_FALSE(tileA.isConnected(7, 0));
}

TEST(TileTests, IsConnectedTileK) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileK = tiles[10][0];

        EXPECT_TRUE(tileK.isConnected(0, 11));
        EXPECT_TRUE(tileK.isConnected(11, 0));
        EXPECT_FALSE(tileK.isConnected(0, 2));
        EXPECT_FALSE(tileK.isConnected(2, 0));
}

TEST(TileTests, IsConnectedAfterRotationTileK) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileK = tiles[10][0];

        for (unsigned int i = 1; i < 4; i++) {
                tileK.setRotation(i);
                unsigned int first = (i * tileK.getCountPerSide());
                unsigned int last = 11 + (i * tileK.getCountPerSide());
                unsigned int second = 2 + (i * tileK.getCountPerSide());

                bool expectTrue = tileK.isConnected(first, last);
                bool expectFalse = tileK.isConnected(first, second);

                EXPECT_TRUE(expectTrue);
                EXPECT_FALSE(expectFalse);
        }
}

TEST(TileTests, PlaceTile) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile& tileA = tiles[0][0];

        bool expectFalse = tileA.isPlaced();
        tileA.placeTile();
        bool expectTrue = tileA.isPlaced();

        EXPECT_TRUE(expectTrue);
        EXPECT_FALSE(expectFalse);
}

TEST(TileTests, GetId) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        unsigned int id = tiles[0][0].getId();

        EXPECT_GE((unsigned int)0, id);
}
