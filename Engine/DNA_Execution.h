#ifndef DNA_EXECUTION_H
#define DNA_EXECUTION_H

#include "DNAClass.h"
#include "Robot.h"
#include <deque>

//the conditions stack
class BoolStack
{
    std::deque<bool> val;
    static const int BOOLSTACK_MAX;
public:
    bool pop();
    bool Addup();   //empties the stack and ANDs everything together
    void push(const bool& value);
};


//the integer stack
struct intstack_type
{
    __int32 val[21];
    int pos;
}extern IntStack;

enum FlowType
{
    CLEAR,
    COND,
    BODY,
    ELSEBODY
}extern CurrentFlow;

extern bool CurrentCondFlag;
const bool NEXTBODY = true;
const bool NEXTELSE = false;

extern bool DEBUGMODE;

#endif
