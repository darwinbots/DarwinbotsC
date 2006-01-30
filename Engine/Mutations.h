#ifndef MUTATIONS_H
#define MUTATIONS_H

class DNA_Class;
class cMutationBase;
#include "DNAClass.h"

//ABC for mutations
class cMutationBase
{
public:
    virtual void mutate(DNA_Class& DNA) = 0;  //pure virtual
    virtual cMutationBase* clone() = 0;        //virtual copy constructor
    virtual ~cMutationBase() {}               //virtual dtor
};

class cPointMutation : public cMutationBase
{
protected:
    float param; //param = 1 - prob_per_turn_per_block
public:
    explicit cPointMutation(float proba):param(1.f - proba){};
    void SetProb(float proba){param = 1.f - proba;}
    float Prob(){return 1.f - param;}
};

class cPointDeletion : public cPointMutation
{
public:
    explicit cPointDeletion(float proba): cPointMutation(proba){};
    virtual void mutate(DNA_Class& DNA);
    virtual cMutationBase* clone() {return new cPointDeletion(*this);}
};

class cPointInsertion : public cPointMutation
{
public:
    explicit cPointInsertion(float proba): cPointMutation(proba){};
    virtual void mutate(DNA_Class& DNA);
    virtual cMutationBase* clone() {return new cPointInsertion(*this);}
};

class cPointChange : public cPointMutation
{
public:
    explicit cPointChange(float proba): cPointMutation(proba){};
    virtual void mutate(DNA_Class& DNA);
    virtual cMutationBase* clone() {return new cPointChange(*this);}
};

#endif //MUTATIONS_H
