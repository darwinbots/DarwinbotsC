#include "Block.h"
#include "DNAParse.h"
#include <vector>
using namespace std;

vector<var> sysvar;
BlockValueBounds ValueBounds[20];

void SetDNAMutationsBounds()
{
    #define BOUNDS(x, min, max) ValueBounds[x].set(min, max);

    BOUNDS(btValue,             -32000, 32000);
    BOUNDS(btPointer,           1,      1000);
    BOUNDS(btBasicCommand,      1,      10);
    BOUNDS(btAdvancedCommand,   1,      6);
    BOUNDS(btBitwiseCommand,    1,      9);
    BOUNDS(btCondition,         1,      6);
    BOUNDS(btLogic,             1,      4);
    BOUNDS(btStores,            1,      3);
    BOUNDS(btFlow,              1,      4);
}

void block::RandomizeValue()
{
    __int16 old = value;

    while(old == value)
        if(tipo != btValue)
            value = (__int16)frnd(ValueBounds[tipo].Min,ValueBounds[tipo].Max);
        else
            value = (__int16)Gauss(500, value);
};

void block::RandomizeTipo()
{
    BlockType old = tipo;

    while(tipo == old || tipo == btMasterFlow)
        tipo = (BlockType)frnd(btValue, btMAX - 1);

    if(tipo >= btPointer)
        value = abs(value) % (ValueBounds[tipo].Max + 1) + 1;
};