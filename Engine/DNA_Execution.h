#ifndef DNA_EXECUTION_H
#define DNA_EXECUTION_H

#include "DNAClass.h"
#include "Robot.h"

//the conditions stack
struct boolstack_type
{
    bool val[21];
    int pos;
}extern Condst;

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