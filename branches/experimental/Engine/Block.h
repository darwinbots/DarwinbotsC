#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <utility>
#include "../Common/Random.h"

class DnaParser;

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

struct Block
{
	BlockType tipo;
    __int16 value;

    Block():tipo(btNONE), value(0) {};
    Block(const BlockType &a, const __int16 &b): tipo(a), value(b){};
    Block(const std::string& command, const DnaParser* parser);

    const bool operator == (const Block &other) const
    {
        return tipo == other.tipo && value == other.value;
    }

    const bool operator != (const Block &other) const
    {
        return !(tipo == other.tipo && value == other.value);
    }

    void erase()
    {
        this->tipo = btNONE;
        this->value = -1;
    }

    Block *ParseCommand(const string &Command);
    string &UnparseCommand(const DnaParser* parser, bool converttosysvar = true);

    void RandomizeValue();
    void RandomizeTipo();
};

const Block DNA_END  (btMasterFlow,1 );
const Block DNA_START(btFlow ,2 );
const Block DNA_ELSE (btFlow ,3 );
const Block DNA_STOP (btFlow ,4 );

Block RandomBlock();
Block ParseCommand(const string &Command);

//extern vector<var> sysvar; //all possible sysvars
#endif
