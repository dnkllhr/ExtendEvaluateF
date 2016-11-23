#include "FuzzyLogic.h"



FuzzySet::FuzzySet(unsigned int identifier, std::string name, Graph *g)
{
    this->graphDescriptor = g;
    this->name = name;
    this->identifier = identifier;
}
FuzzySet::~FuzzySet()
{
    delete graphDescriptor;
    delete &percentMembership;
}

std::string FuzzySet::getName()
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
    if(this->identifier == HURTING_ENEMY)
    {
        turnScore = (this->percentMembership[HURTING_GOOD_IDX]) * HURTING_GOOD_WHT + (this->percentMembership[HURTING_NEUTRAL_IDX]) * HURTING_NEUTRAL_WHT
                  + (this->percentMembership[HURTING_BAD_IDX]) * HURTING_BAD_WHT;
    }  
    else if(this->identifier == HELPING_ME)
    {
        turnScore = (this->percentMembership[HELPING_GOOD_IDX]) * HELPING_GOOD_WHT + (this->percentMembership[HELPING_NEUTRAL_IDX]) * HELPING_NEUTRAL_WHT
                  + (this->percentMembership[HELPING_BAD_IDX]) * HELPING_BAD_WHT;
    }
    else if(this->identifier == TURNS_AWAY)
    {
        turnScore = (this->percentMembership[TURNS_SHORT_IDX]) * TURNS_SHORT_WHT + (this->percentMembership[TURNS_MEDIUM_IDX]) * TURNS_MEDIUM_WHT
                  + (this->percentMembership[TURNS_LONG_IDX]) * TURNS_LONG_WHT;
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
    if(this->identifier == HURTING_ENEMY)
    {
        unsigned int diffScore = *((unsigned int *)p1);

        this->percentMembership[0] = this->scoreLeft(diffScore);
        this->percentMembership[1] = this->scoreMid(diffScore);
        this->percentMembership[2] = this->scoreRight(diffScore);
    }  
    else if(this->identifier == HELPING_ME)
    {
        unsigned int diffScore = *((unsigned int *)p1);

        this->percentMembership[0] = this->scoreLeft(diffScore);
        this->percentMembership[1] = this->scoreMid(diffScore);
        this->percentMembership[2] = this->scoreRight(diffScore);
    }
    else if(this->identifier == TURNS_AWAY)
    {
        unsigned int edges = *((unsigned int *)p1); 

        this->percentMembership[0] = this->scoreLeft(edges);
        this->percentMembership[1] = this->scoreMid(edges);
        this->percentMembership[2] = this->scoreRight(edges);
    }

}

float FuzzySet::scoreLeft(unsigned int diffScore)
{
    if(diffScore <= this->graphDescriptor->leftStart)
    {
        return 100.f;
    }
    else if(diffScore > this->graphDescriptor->leftEnd)
    {
        return 0.f;
    }
    else
    {
        return (float)(-(100.f/((float)this->graphDescriptor->leftEnd - (float)this->graphDescriptor->leftStart)) * diffScore + 100.f);
    }
}

float FuzzySet::scoreMid(unsigned int diffScore)
{
    float midPoint = ((float)this->graphDescriptor->midEnd - (float)this->graphDescriptor->midStart)/2.f;
    if(diffScore <= this->graphDescriptor->midStart)
    {
        return 0.f;
    }
    else if(diffScore > this->graphDescriptor->midEnd)
    {
        return 0.f;
    }
    else if(diffScore <= midPoint)
    {
        return ((100.f/((float)this->graphDescriptor->midStart - midPoint)) * (float)diffScore);
    }
    else
    {
        return (-(100.f/((float)this->graphDescriptor->midStart - midPoint)) * (float)diffScore + 100.f);
    }
}

float FuzzySet::scoreRight(unsigned int diffScore)
{
    if(diffScore <= this->graphDescriptor->rightStart)
    {
        return 0.f;
    }
    else if(diffScore > this->graphDescriptor->rightEnd)
    {
        return 100.f;
    }
    else
    {
        return (float)((100.f/((float)this->graphDescriptor->rightEnd - (float)this->graphDescriptor->rightStart)) * (float)diffScore);
    }

}

FuzzyLogic::FuzzyLogic()
{
    this->mySets = new FuzzySet*[NUM_SETS];
    struct Graph *g;
    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 2;
    g->midStart = 1;
    g->midEnd = 5;
    g->rightStart = 4;
    g->rightEnd = 10;
    this->mySets[HURTING_ENEMY] = new FuzzySet(HURTING_ENEMY, "Hurting Enemy", g);


    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 2;
    g->midStart = 1;
    g->midEnd = 5;
    g->rightStart = 4;
    g->rightEnd = 10;
    this->mySets[HELPING_ME] = new FuzzySet(HELPING_ME, "Helping Me", g);


    g = new Graph;
    g->leftStart = 0;
    g->leftEnd = 3;
    g->midStart = 2;
    g->midEnd = 5;
    g->rightStart = 4;
    g->rightEnd = 6;
    this->mySets[TURNS_AWAY] = new FuzzySet(TURNS_AWAY, "Turns Away", g);
}

FuzzyLogic::~FuzzyLogic()
{
    for(int i = 0; i < NUM_SETS; i++)
    {
        delete this->mySets[i];
    }
}

void FuzzyLogic::enterData(AIMove *m)
{
    this->mySets[HURTING_ENEMY]->enterData(&(m->diffEnemyScore));
    this->mySets[HELPING_ME]->enterData(&(m->diffMyScore));
    this->mySets[TURNS_AWAY]->enterData(&(m->edgesTillCompletion));
}

float FuzzyLogic::getResults()
{
    float turnScore = 0;
    for(int i = 0; i < NUM_SETS; i++)
    {
        turnScore += this->mySets[i]->getTurnScore();
    }
    return turnScore;
}