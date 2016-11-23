#include <unordered_set>

#define NUM_SETS        3
#define HURTING_ENEMY   0
#define HELPING_ME      1
#define TURNS_AWAY      2

#define HURTING_GOOD_IDX    0
#define HURTING_NEUTRAL_IDX 1
#define HURTING_BAD_IDX     2

#define TURNS_SHORT_WHT     20
#define HURTING_GOOD_WHT    10
#define HURTING_NEUTRAL_WHT 3
#define HURTING_BAD_WHT     -10

#define HELPING_GOOD_IDX    2
#define HELPING_NEUTRAL_IDX 1
#define HELPING_BAD_IDX     0

#define HELPING_GOOD_WHT    10
#define HELPING_NEUTRAL_WHT 5
#define HELPING_BAD_WHT     -20

#define TURNS_SHORT_IDX     0
#define TURNS_MEDIUM_IDX    1
#define TURNS_LONG_IDX      2

#define TURNS_SHORT_WHT     20
#define TURNS_MEDIUM_WHT    5
#define TURNS_LONG_WHT      1




struct Graph
{
    Graph() {
        leftStart = 0;
        leftEnd = 0;
        midStart = 0;
        midEnd = 0;
        rightStart = 0;
        rigthEnd = 0;
    };

    unsigned int leftStart;
    unsigned int leftEnd;
    unsigned int midStart;
    unsigned int midEnd;
    unsigned int rightStart;
    unsigned int rightEnd;
};

struct AIMove
{
    AIMove() {
        edgesTillCompletion = 0;
        myOwnership = 0;
        diffMyScore = 0;
        diffEnemyScore = 0;
    };

    unsigned int edgesTillCompletion;
    bool myOwnership;
    unsigned int diffMyScore;
    unsigned int diffEnemyScore;

};



class FuzzySet
{
public:
    string getName();
    unsigned int getIdentifier();
    float getTurnScore();
    void enterData(void *);
    ~FuzzySet();
private:
    unsigned int identifier;
    string name;
    Graph *graphDescriptor;
    float percentMembership[3];
    FuzzySet(unsigned int identifier, string name, Graph *g);
    unsigned int scoreLeft(unsigned int diffScore);
    unsigned int scoreMid(unsigned int diffScore);
    unsigned int scoreRight(unsigned int diffScore);
};

class Fuzzifier
{
public:
    void enterData(AIMove *m);
private:
    void sendDataToSets();
};

class Defuzzifier
{
public:
    float getFinalTurnScore();
private:
    float getSetScore();
};


class FuzzyLogic
{
public:
    void enterData(AIMove *m);
    float getResults();
    ~FuzzyLogic();
private:
    FuzzySet **mySets;
    Defuzzifier *df;
    Fuzzifier *fz;
    FuzzyLogic();
};