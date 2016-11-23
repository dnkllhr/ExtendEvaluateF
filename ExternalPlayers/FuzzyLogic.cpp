#include "FuzzyLgoic.h"



FuzzySet::FuzzySet(unsigned int identifier, string name, Graph *g)
{
    this->graphDescriptor = g;
    this->name = name;
    this->identifier = identifier;
}
FuzzySet::~FuzzySet()
{
    delete graphDescriptor;
    delete percentMembership;
}

string FuzzySet::getName()
{
    return name;
}

unsigned int FuzzySet::getIdentifier()
{
    return identifier;
}

float FuzzySet::getTurnScore()
{
    float turnScore = 0;
    if(identifier == HURTING_ENEMY)
    {
        turnScore = (percentMembership[HURTING_GOOD_IDX]) * HURTING_GOOD_WHT + (percentMembership[HURTING_NEUTRAL_IDX]) * HURTING_NEUTRAL_WHT
                  + (percentMembership[HURTING_BAD_IDX]) * HURTING_BAD_WHT;
    }  
    else if(identifier == HELPING_ME)
    {
        turnScore = (percentMembership[HELPING_GOOD_IDX]) * HELPING_GOOD_WHT + (percentMembership[HELPING_NEUTRAL_IDX]) * HELPING_NEUTRAL_WHT
                  + (percentMembership[HELPING_BAD_IDX]) * HELPING_BAD_WHT;
    }
    else if(identifier == TURNS_AWAY)
    {
        turnScore = (percentMembership[TURNS_SHORT_IDX]) * TURNS_SHORT_WHT + (percentMembership[TURNS_MEDIUM_IDX]) * TURNS_MEDIUM_WHT
                  + (percentMembership[TURNS_LONG_IDX]) * TURNS_LONG_WHT;
    }
    return turnScore;
}




/*  Graph looks like this:

100%------------------------------
    |\            /\            /|
    | \          /  \          / |
    |  \        /    \        /  |
    |   \      /      \      /   |
    |    \    /        \    /    |
    |     \  /          \  /     |
    |      \/            \/      |
    |      /\            /\      |
    |     /  \          /  \     |
  0%------------------------------

*/

void FuzzySet::enterData(void *p1)
{
    if(identifier == HURTING_ENEMY)
    {
        unsigned int diffScore = *((unsigned int *)p1);

        percentMembership[0] = HurtingThem::scoreLeft(diffScore);
        percentMembership[1] = HurtingThem::scoreMid(diffScore);
        percentMembership[2] = HurtingThem::scoreRight(diffScore);
    }  
    else if(identifier == HELPING_ME)
    {
        unsigned int diffScore = *((unsigned int *)p1);

        percentMembership[0] = HurtingThem::scoreLeft(diffScore);
        percentMembership[1] = HurtingThem::scoreMid(diffScore);
        percentMembership[2] = HurtingThem::scoreRight(diffScore);
    }
    else if(identifier == TURNS_AWAY)
    {
        unsigned int edges = *((unsigned int *)p1); 

        percentMembership[0] = HurtingThem::scoreLeft(edges);
        percentMembership[1] = HurtingThem::scoreMid(edges);
        percentMembership[2] = HurtingThem::scoreRight(edges);
    }

}

float FuzzySet::scoreLeft(unsigned int diffScore)
{
    if(diffScore <= graphDescriptor->leftStart)
    {
        return 100f;
    }
    else if(diffScore > graphDescriptor->leftEnd)
    {
        return 0f;
    }
    else
    {
        return (float)(-(100f/((float)graphDescriptor->leftEnd - (float)graphDescriptor->leftStart)) * diffScore + 100f);
    }
}

float FuzzySet::scoreMid(unsigned int diffScore)
{
    if(diffScore <= graphDescriptor->midStart)
    {
        return 0f;
    }
    else if(diffScore > graphDescriptor->midEnd)
    {
        return 0f;
    }
    float midPoint = ((float)graphDescriptor->midEnd - (float)graphDescriptor->midStart)/2f
    else if(diffScore <= )
    {
        return ((100f/((float)graphDescriptor->midStart - midPoint)) * (float)diffScore);
    }
    else
    {
        return (-(100f/((float)graphDescriptor->midStart - midPoint)) * (float)diffScore + 100f);
    }
}

float FuzzySet::scoreRight(unsigned int diffScore)
{
    if(diffScore <= graphDescriptor->rightStart)
    {
        return 0f;
    }
    else if(diffScore > graphDescriptor->rightEnd)
    {
        return 100f;
    }
    else
    {
        return (float)((100f/((float)graphDescriptor->rightEnd - (float)graphDescriptor->rightStart)) * (float)diffScore);
    }

}

FuzzyLogic::FuzzyLogic()
{
    this->mySets = new *FuzzySet[NUM_SETS];
    struct Graph *g;
    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 2;
    g->midStart = 1;
    g->midEnd = 5;
    g->rightStart = 4;
    g->rightEnd = 10;
    mySets[HURTING_ENEMY] = new FuzzySet(HURTING_ENEMY, "Hurting Enemy", g);


    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 2;
    g->midStart = 1;
    g->midEnd = 5;
    g->rightStart = 4;
    g->rightEnd = 10;
    mySets[HELPING_ME] = new FuzzySet(HELPING_ME, "Helping Me", g);


    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 3;
    g->midStart = 2;
    g->midEnd = 5;
    g->rightStart = 4;
    g->rightEnd = 6;
    mySets[TURNS_AWAY] = new FuzzySet(TURNS_AWAY, "Turns Away", g);

    this->df = new Defuzzifier;
    this->fz = new Fuzzifier;
}

FuzzyLogic::~FuzzyLogic()
{
    for(int i = 0; i < NUM_SETS; i++)
    {
        delete this->mySets[i];
    }
    delete this->fz;
    delete this->df;
}



    unsigned int edgesTillCompletion;
    bool myOwnership;
    unsigned int diffMyScore;
    unsigned int diffEnemyScore;

FuzzyLogic::enterData(AIMove *m)
{
    this->fz->enterData(m);
}

FuzzyLogic::getResults()
{
    return this->df->getFinalTurnScore();
}