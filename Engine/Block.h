#ifndef BLOCK_H
#define BLOCK_H

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <string>
#include <vector>
#include <utility>
#include "../Common/Random.h"

//' var structure, to store the correspondance name<->value
struct var
{
    std::string name;
    __int16 value;
};

enum tBlockType {
    btNONE = -1 ,
    btValue,              //0
    btPointer,            //1
    btBasicCommand,       //2
    btAdvancedCommand,    //3
    btBitwiseCommand,     //4
    btCondition,          //5
    btLogic,              //6
    btStores,             //7
    btReserved,           //8
    btFlow,               //9
    btMasterFlow,         //10
    btMAX
};

struct block
{
	tBlockType tipo;
    __int16 value;

  public:
    block():tipo(btNONE), value(0) {};
    block(const tBlockType &a, const __int16 &b): tipo(a), value(b){};
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
    std::string& text(bool converttosysvar=false) const;
};

const block DNA_END  (btMasterFlow,1 );
const block DNA_START(btFlow ,2 );
const block DNA_ELSE (btFlow ,3 );
const block DNA_STOP (btFlow ,4 );


block ParseCommand(const std::string &Command);
block RandomBlock();

extern var sysvar[1000]; //all possible sysvars
extern int maxsysvar;
extern std::vector<std::pair<std::string,__int16> > vSysvars;
#endif
