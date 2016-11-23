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
        //printf("Hurting Enemy memberships %4.4f, %4.4f, %4.4f\n", this->percentMembership[0],this->percentMembership[1],this->percentMembership[2]);
        turnScore = (this->percentMembership[HURTING_GOOD_IDX]) * HURTING_GOOD_WHT + (this->percentMembership[HURTING_NEUTRAL_IDX]) * HURTING_NEUTRAL_WHT
                  + (this->percentMembership[HURTING_BAD_IDX]) * HURTING_BAD_WHT;
        //printf("Hurting Enemy return %4.4f\n", turnScore);
    }  
    else if(this->identifier == HELPING_ME)
    {
        //printf("Helping Me memberships %4.4f, %4.4f, %4.4f\n", this->percentMembership[0],this->percentMembership[1],this->percentMembership[2]);
        turnScore = (this->percentMembership[HELPING_GOOD_IDX]) * HELPING_GOOD_WHT + (this->percentMembership[HELPING_NEUTRAL_IDX]) * HELPING_NEUTRAL_WHT
                  + (this->percentMembership[HELPING_BAD_IDX]) * HELPING_BAD_WHT;
        //printf("Helping Me return %4.4f\n", turnScore);
    }
    else if(this->identifier == TURNS_AWAY)
    {
        //printf("Turns Away memberships %4.4f, %4.4f, %4.4f\n", this->percentMembership[0],this->percentMembership[1],this->percentMembership[2]);
        turnScore = (this->percentMembership[TURNS_SHORT_IDX]) * TURNS_SHORT_WHT + (this->percentMembership[TURNS_MEDIUM_IDX]) * TURNS_MEDIUM_WHT
                  + (this->percentMembership[TURNS_LONG_IDX]) * TURNS_LONG_WHT;
        //printf("Turns Away return %4.4f\n", turnScore);
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

void FuzzySet::enterData(unsigned int input)
{
    std::cout << this->getName() << std::endl;

    this->percentMembership[0] = this->scoreLeft(input);
    this->percentMembership[1] = this->scoreMid(input);
    this->percentMembership[2] = this->scoreRight(input);
}

float FuzzySet::scoreLeft(unsigned int diffScore)
{
    //printf("Score Left input: %d, start %d end %d\n", diffScore, this->graphDescriptor->leftStart, this->graphDescriptor->leftEnd);
    if(diffScore <= this->graphDescriptor->leftStart)
    {
        //printf("left equation: y = 100\n");
        return 100.f;
    }
    else if(diffScore > this->graphDescriptor->leftEnd)
    {
        //printf("left equation: y = 0\n");
        return 0.f;
    }
    else
    {
        float slope = -(100.f/((float)this->graphDescriptor->leftEnd - (float)this->graphDescriptor->leftStart));
        float intercept = 100.f;
        float offset = (float)this->graphDescriptor->leftStart;

        //printf("left equation: y = %4.4f * (x - %4.4f) + %4.4f\n", slope, offset, intercept);

        return (slope * ((float)diffScore - offset) + intercept);
    }
}

float FuzzySet::scoreMid(unsigned int diffScore)
{
    float midPoint = ((float)this->graphDescriptor->midEnd + (float)this->graphDescriptor->midStart)/2.f;
    //printf("Score Mid input: %d, start %d, mid %4.4f, end %d\n", diffScore, this->graphDescriptor->midStart, midPoint, this->graphDescriptor->midEnd);
    if(diffScore <= this->graphDescriptor->midStart)
    {
        //printf("mid equation: y = 0\n");
        return 0.f;
    }
    else if(diffScore > this->graphDescriptor->midEnd)
    {
        //printf("mid equation: y = 0\n");
        return 0.f;
    }
    else if(diffScore <= midPoint)
    {
        float slope = (100.f/(midPoint - (float)this->graphDescriptor->midStart));
        float offset = (float)this->graphDescriptor->midStart;
        float intercept = 0.f;

        //printf("left mid equation: y = %4.4f * (x - %4.4f) + %4.4f\n", slope, offset, intercept);

        return (slope * ((float)diffScore - offset) + intercept);
    }
    else
    {
        float slope = -(100.f/((float)this->graphDescriptor->midEnd - midPoint)) ;
        float offset = (float)this->graphDescriptor->midStart;
        float intercept = 100.f;

        //printf("right mid equation: y = %4.4f * (x - %4.4f) + %4.4f\n", slope, offset, intercept);

        return (slope * ((float)diffScore - offset) + intercept);
    }
}

float FuzzySet::scoreRight(unsigned int diffScore)
{
    //printf("Score Right input: %d, start %d, end %d\n", diffScore, this->graphDescriptor->rightStart, this->graphDescriptor->rightEnd);
    if(diffScore <= this->graphDescriptor->rightStart)
    {
        //printf("right equation: y = 0\n");
        return 0.f;
    }
    else if(diffScore > this->graphDescriptor->rightEnd)
    {
        //printf("right equation: y = 100\n");
        return 100.f;
    }
    else
    {
        float slope = (100.f/((float)this->graphDescriptor->rightEnd - (float)this->graphDescriptor->rightStart)) ;
        float offset = (float)this->graphDescriptor->rightStart;
        float intercept = 0.f;

        //printf("right equation: y = %4.4f * (x - %4.4f) + %4.4f\n", slope, offset, intercept);

        return (slope * ((float)diffScore - offset) + intercept);
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
    this->mySets[HURTING_ENEMY]->enterData(m->diffEnemyScore);
    this->mySets[HELPING_ME]->enterData(m->diffMyScore);
    this->mySets[TURNS_AWAY]->enterData(m->edgesTillCompletion);
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
