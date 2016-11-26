#include "../ExternalPlayers/AI/FuzzyLogic.h"
#include "gtest/gtest.h"

TEST(FuzzyTests, getTurnScore)
{
    struct Graph *g;
    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 3;
    g->midStart = 0;
    g->midPlatStart = 3;
    g->midPlatEnd = 4;
    g->midEnd = 10;
    g->rightStart = 4;
    g->rightEnd = 10;
    FuzzySet *fs = new FuzzySet(HURTING_ENEMY, "HURTING_ENEMY", g);

    float expectedScore;

    fs->enterData(0);
    expectedScore = (100)*(HURTING_GOOD_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(3);
    expectedScore = (100)*(HURTING_NEUTRAL_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(10);
    expectedScore = (100)*(HURTING_BAD_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(2);
    expectedScore = (100 * (2/3)) * HURTING_NEUTRAL_WHT + (100 * (1/3)) * HURTING_GOOD_WHT;
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(5);
    expectedScore = (500/6) * HURTING_NEUTRAL_WHT + (1 - (500/6)) * HURTING_BAD_WHT;
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    delete fs;

    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 3;
    g->midStart = 0;
    g->midPlatStart = 3;
    g->midPlatEnd = 4;
    g->midEnd = 10;
    g->rightStart = 4;
    g->rightEnd = 10;
    fs = new FuzzySet(HELPING_ME, "HELPING_ME", g);

    fs->enterData(0);
    expectedScore = (100)*(HELPING_BAD_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(3);
    expectedScore = (100)*(HELPING_NEUTRAL_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(10);
    expectedScore = (100)*(HELPING_GOOD_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(2);
    expectedScore = (100 * (2/3)) * HELPING_NEUTRAL_WHT + (100 * (1/3)) * HELPING_BAD_WHT;
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(5);
    expectedScore = (500/6) * HELPING_NEUTRAL_WHT + (1 - (500/6)) * HELPING_GOOD_WHT;
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 3;
    g->midStart = 0;
    g->midPlatStart = 3;
    g->midPlatEnd = 4;
    g->midEnd = 6;
    g->rightStart = 4;
    g->rightEnd = 6;
    fs = new FuzzySet(TURNS_AWAY, "TURNS_AWAY", g);

    fs->enterData(0);
    expectedScore = (100)*(TURNS_SHORT_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(3);
    expectedScore = (100)*(TURNS_MEDIUM_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(10);
    expectedScore = (100)*(TURNS_LONG_WHT);
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(2);
    expectedScore = (100 * (2/3)) * TURNS_MEDIUM_WHT + (100 * (1/3)) * TURNS_SHORT_WHT;
    EXPECT_EQ(fs->getTurnScore(), expectedScore);

    fs->enterData(5);
    expectedScore = (((1/2) * TURNS_MEDIUM_WHT) + (1/2)) * TURNS_LONG_WHT;
    EXPECT_EQ(fs->getTurnScore(), expectedScore);
}
