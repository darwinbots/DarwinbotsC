#ifndef DNA_EXECUTION_H
#define DNA_EXECUTION_H

#include "DNAClass.h"
#include "Robot.h"
#include <stack>

//the conditions stack
class BoolStack
{
    vector<bool> val;
    
    public:
    bool pop();
    void push(const bool& value);
    bool Addup();   //empties the stack and ANDs everything together    
};

//the integer stack
typedef vector<__int32> intstack_type;
extern intstack_type IntStack;

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

#endif
