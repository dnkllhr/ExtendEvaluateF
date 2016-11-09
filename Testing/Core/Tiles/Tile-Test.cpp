#include "../Core/Tiles/Tile.h"
#include "../Core/Tiles/TileType.h"
#include "gtest/gtest.h"

#include <iostream>

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
        std::cout << "Creating tiles" << std::endl;
        Array<Array<Tile>> tiles = Tile::CreateTiles();

        std::cout << "Reading tile 0,0" << std::endl;
        Tile tile = tiles[0][0];
        
        std::cout << "Setting rotation to 1" << std::endl;
        bool result = tile.setRotation(1);
        std::cout << "Set rotation" << std::endl;
        EXPECT_EQ(result, true);
}

TEST(TileTests, SetRotationAfterPlacement) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile tile = tiles[0][0];
       
        bool result = tile.setRotation(1);
        EXPECT_EQ(result, true);

        tile.placeTile();

        result = tile.setRotation(2);
        EXPECT_EQ(result, false);
}

TEST(TileTests, GetShield) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile tileA = tiles[0][0];
        Tile tileC = tiles[2][0];

        EXPECT_EQ(tileA.getShield(), false);
        EXPECT_EQ(tileC.getShield(), true);
}

TEST(TileTests, GetNumberOfSides) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile tileA = tiles[0][0];
        Tile tileC = tiles[2][0];

        EXPECT_EQ(tileA.getNumberOfSides(), (unsigned int)4);
        EXPECT_EQ(tileC.getNumberOfSides(), (unsigned int)4);
}

TEST(TileTests, GetTileType) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile tileA = tiles[0][0];
        Tile tileC = tiles[2][0];

        EXPECT_EQ(tileA.getTileType(), TileType::A);
        EXPECT_EQ(tileC.getTileType(), TileType::C);
}

TEST(TileTests, IsConnectedTileA) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile tileA = tiles[0][0];

        bool expectTrue = tileA.isConnected(0, 11);
        bool expectFalse = tileA.isConnected(0, 7);

        EXPECT_EQ(expectTrue, true);
        EXPECT_EQ(expectFalse, false);
}

TEST(TileTests, PlaceTile) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        Tile tileA = tiles[0][0];

        bool expectFalse = tileA.isPlaced();
        tileA.placeTile();
        bool expectTrue = tileA.isPlaced();

        EXPECT_EQ(expectTrue, true);
        EXPECT_EQ(expectFalse, false);
}

TEST(TileTests, GetId) {
        Array<Array<Tile>> tiles = Tile::CreateTiles();
        unsigned int id = tiles[0][0].getId();

        EXPECT_GE((unsigned int)0, id);
}
