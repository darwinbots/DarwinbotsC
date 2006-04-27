#ifndef CQ_H
#define CQ_H

#include <iostream>
#include <vector>
class Robot;

using namespace std;

struct MemPair
{
    __int16 loc;
    __int16 val;

    MemPair(__int16 _loc, __int16 _val)
    {
        loc = _loc;
        val = _val;
    }
};

class CommandQueueClass
{
    private:
    vector<MemPair> Commands;
    Robot *base;

    public:
    __int16 FilterRead(__int16 location);
    __int16 Add(__int16 location, __int16 value);
    void Clear();
    CommandQueueClass();
    void SetBase(Robot *_base);
    void Apply();
};

#endif

