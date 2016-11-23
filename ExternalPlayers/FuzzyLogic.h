#include <string>

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
        rightEnd = 0;
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
        diffMyScore = 0;
        diffEnemyScore = 0;
    };

    unsigned int edgesTillCompletion;
    unsigned int diffMyScore;
    unsigned int diffEnemyScore;

};



class FuzzySet
{
public:
    std::string getName();
    unsigned int getIdentifier();
    float getTurnScore();
    void enterData(void *p1);
    ~FuzzySet();
    FuzzySet(unsigned int identifier, std::string name, Graph *g);
private:
    unsigned int identifier;
    std::string name;
    Graph *graphDescriptor;
    float percentMembership[3];
    float scoreLeft(unsigned int diffScore);
    float scoreMid(unsigned int diffScore);
    float scoreRight(unsigned int diffScore);
};


class FuzzyLogic
{
public:
    void enterData(AIMove *m);
    float getResults();
    ~FuzzyLogic();
private:
    FuzzySet **mySets;
    FuzzyLogic();
};