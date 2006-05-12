#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <utility>
#include "../Common/Random.h"

using namespace std;

struct BlockValueBounds
{
    __int16 Min, Max;
    BlockValueBounds::BlockValueBounds(int min = 0, int max = 0)
    {
        Min = min;
        Max = max;
    };

    void BlockValueBounds::set(int min = 0, int max = 0)
    {
        Min = min;
        Max = Max;
    };
}extern ValueBounds[20];
void SetDNAMutationsBounds();

struct var
{
    std::string name;
    __int16 value;
};

enum BlockType
{
    btNONE = -1 ,
    btValue,              //0
    btPointer,            //1
    btBasicCommand,       //2
    btAdvancedCommand,    //3
    btBitwiseCommand,     //4
    btCondition,          //5
    btLogic,              //6
    btStores,             //7
    btTies,               //8
    btFlow,               //9
    btMasterFlow,         //10
    btMAX
};

struct block
{
	BlockType tipo;
    __int16 value;

    block():tipo(btNONE), value(0) {};
    block(const BlockType &a, const __int16 &b): tipo(a), value(b){};
    
    const bool operator == (const block &other) const
    {
        return tipo == other.tipo && value == other.value;
    }

    const bool operator != (const block &other) const
    {
        return !(tipo == other.tipo && value == other.value);        
    }

    void erase()
    {
        this->tipo = btNONE;
        this->value = -1;
    }

    block *ParseCommand(const string &Command);
    string &UnparseCommand(bool converttosysvar = true);

    void RandomizeValue();
    void RandomizeTipo();
};

const block DNA_END  (btMasterFlow,1 );
const block DNA_START(btFlow ,2 );
const block DNA_ELSE (btFlow ,3 );
const block DNA_STOP (btFlow ,4 );

block RandomBlock();
block ParseCommand(const string &Command);

extern vector<var> sysvar; //all possible sysvars
#endif
