#ifndef __FUZZY_H
#define __FUZZY_H

#include <string>
#include <iostream>

#define NUM_SETS        3
#define HURTING_ENEMY   0
#define HELPING_ME      1
#define TURNS_AWAY      2

#define HURTING_GOOD_IDX    0
#define HURTING_NEUTRAL_IDX 1
#define HURTING_BAD_IDX     2

#define HURTING_GOOD_WHT    -1
#define HURTING_NEUTRAL_WHT -5
#define HURTING_BAD_WHT     -10

#define HELPING_GOOD_IDX    2
#define HELPING_NEUTRAL_IDX 1
#define HELPING_BAD_IDX     0

#define HELPING_GOOD_WHT    10
#define HELPING_NEUTRAL_WHT 5
#define HELPING_BAD_WHT     -10

#define TURNS_SHORT_IDX     0
#define TURNS_MEDIUM_IDX    1
#define TURNS_LONG_IDX      2

#define TURNS_SHORT_WHT     10
#define TURNS_MEDIUM_WHT    5
#define TURNS_LONG_WHT      1

struct Graph
{
    Graph() {
        leftStart = 0;
        leftEnd = 0;
        midStart = 0;
        midPlatStart = 0;
        midPlatEnd = 0;
        midEnd = 0;
        rightStart = 0;
        rightEnd = 0;
    };

    int leftStart;
    int leftEnd;
    int midStart;
    int midPlatStart;
    int midPlatEnd;
    int midEnd;
    int rightStart;
    int rightEnd;
};

struct AIMove
{
    AIMove() {
        edgesTillCompletion = 0;
        diffMyScore = 0;
        diffEnemyScore = 0;
    };

    unsigned int edgesTillCompletion;
    int diffMyScore;
    int diffEnemyScore;

};

class FuzzySet
{
public:
    std::string getName();
    unsigned int getIdentifier();
    float getTurnScore();
    void enterData(unsigned int input);
    ~FuzzySet();
    FuzzySet(unsigned int identifier, std::string name, Graph *g);
private:
    unsigned int identifier;
    std::string name;
    Graph *graphDescriptor;
    float percentMembership[3];
    float scoreLeft(int diffScore);
    float scoreMid(int diffScore);
    float scoreRight(int diffScore);
};


class FuzzyLogic
{
public:
    void enterData(struct AIMove *m);
    float getResults();
    ~FuzzyLogic();
    FuzzyLogic();
private:
    FuzzySet **mySets;
};

#endif
