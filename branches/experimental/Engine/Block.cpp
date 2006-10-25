#include "Block.h"
#include "DnaParser.h"
#include <vector>
using namespace std;

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

void Block::RandomizeValue()
{
    __int16 old = value;

    while(old == value)
        if(tipo != btValue)
            value = (__int16)frnd(ValueBounds[tipo].Min,ValueBounds[tipo].Max);
        else
            value = (__int16)Gauss(500, value);
};

void Block::RandomizeTipo()
{
    BlockType old = tipo;

    while(tipo == old || tipo == btMasterFlow)
        tipo = (BlockType)frnd(btValue, btMAX - 1);

    if(tipo >= btPointer)
        value = abs(value) % (ValueBounds[tipo].Max + 1) + 1;
};

//////////////////////////////////////////////

char buffer[1024];

string &BasicCommandDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "add"; break;
        case 2:
            returnme = "sub"; break;
        case 3:
            returnme = "mult"; break;
        case 4:
            returnme = "div"; break;
        case 5:
            returnme = "rnd"; break;
        case 6:
            returnme = "*"; break;
        case 7:
            returnme = "mod"; break;
        case 8:
            returnme = "sgn"; break;
        case 9:
            returnme = "abs"; break;
        case 10:
            returnme = "dup"; break;
        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &BasicCommandTok(const string &s)
{
    static Block returnme(btBasicCommand,0);

    returnme.tipo = btBasicCommand;
    returnme.value = 0;

    if (s == "add")
        returnme.value = 1;
    else if (s == "sub")
        returnme.value = 2;
    else if (s == "mult")
        returnme.value = 3;
    else if (s == "div")
        returnme.value = 4;
    else if (s == "rnd")
        returnme.value = 5;
    else if (s == "*")
        returnme.value = 6;
    else if (s == "mod")
        returnme.value = 7;
    else if (s == "sgn")
        returnme.value = 8;
    else if (s == "abs")
        returnme.value = 9;
    else if (s == "dup")
        returnme.value = 10;

    return returnme;
}

string &AdvancedCommandDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "angle"; break;
        case 2:
            returnme = "dist"; break;
        case 3:
            returnme = "ceil"; break;
        case 4:
            returnme = "floor"; break;
        case 5:
            returnme = "sqr"; break;
        case 6:
            returnme = "pow"; break;
        case 7:
            returnme = "pyth"; break;
        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &AdvancedCommandTok(string s)
{
    static Block returnme(btAdvancedCommand,0);

    returnme.tipo = btAdvancedCommand;
    returnme.value = 0;

    if (s == "angle") returnme.value = 1;
    if (s == "dist") returnme.value = 2;
    if (s == "ceil") returnme.value = 3;
    if (s == "floor") returnme.value = 4;
    if (s == "sqr") returnme.value = 5;
    if (s == "pow") returnme.value = 6;
    if (s == "pyth") returnme.value = 7;

    return returnme;
}

string &BitwiseCommandDetok(const __int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "~"; break;  //bitwise compliment
        case 2:
            returnme = "&"; break;  //bitwise AND
        case 3:
            returnme = "|"; break;  //bitwise OR
        case 4:
            returnme = "^"; break;  //bitwise XOR
        case 5:
            returnme = "++"; break; //valinc
        case 6:
            returnme = "--"; break; //valdec
        case 7:
            returnme = "-"; break;  //negate
        case 8:
            returnme = "<<"; break; //bit shift left
        case 9:
            returnme = ">>"; break; //bit shift right
        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &BitwiseCommandTok(string s)
{
    static Block returnme(btBitwiseCommand,0);

    returnme.tipo = btBitwiseCommand;
    returnme.value = 0;

    if (s == "~") returnme.value = 1;
    if (s == "&") returnme.value = 2;
    if (s == "|") returnme.value = 3;
    if (s == "^") returnme.value = 4;
    if (s == "++") returnme.value = 5;
    if (s == "--") returnme.value = 6;
    if (s == "<<") returnme.value = 7;
    if (s == ">>") returnme.value = 8;

    return returnme;
}

// "%=", "!%=", "~=", "!~=" aren't supported ATM.
string &ConditionsDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "<"; break;
        case 2:
            returnme = ">"; break;
        case 3:
            returnme = "="; break;
        case 4:
            returnme = "!="; break;
        case 5:
            returnme = ">="; break;
        case 6:
            returnme = "<="; break;
        default:
            returnme = ""; break;
    }

    return returnme;
}



Block &ConditionsTok(string s)
{
    static Block returnme(btCondition,0);

    returnme.tipo = btCondition;
    returnme.value = 0;

    if (s == "<") returnme.value = 1;
    if (s == ">") returnme.value = 2;
    if (s == "=") returnme.value = 3;
    if (s == "!=") returnme.value = 4;
    if (s == ">=") returnme.value = 5;
    if (s == "<=") returnme.value = 6;

    return returnme;
}

string &LogicDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "and"; break;

        case 2:
            returnme = "or"; break;

        case 3:
            returnme = "xor"; break;

        case 4:
            returnme = "not"; break;

        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &LogicTok(string s)
{
    static Block returnme(btLogic,0);

    returnme.tipo = btLogic;
    returnme.value = 0;

    if (s == "and") returnme.value = 1;
    if (s == "or")  returnme.value = 2;
    if (s == "xor") returnme.value = 3;
    if (s == "not") returnme.value = 4;

    return returnme;

}

string &StoresDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "store"; break;

        case 2:
            returnme = "inc"; break;

        case 3:
            returnme = "dec"; break;

        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &StoresTok(string s)
{
    static Block returnme(btStores,0);

    returnme.tipo = btStores;
    returnme.value = 0;

    if (s == "store") returnme.value = 1;
    if (s == "inc")   returnme.value = 2;
    if (s == "dec")   returnme.value = 3;

    return returnme;
}

string &FlowDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "cond"; break;
        case 2:
            returnme = "start"; break;
        case 3:
            returnme = "else"; break;
        case 4:
            returnme = "stop"; break;
        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &FlowTok(string s)
{
    static Block returnme(btFlow,0);

    returnme.tipo = btFlow;
    returnme.value = 0;

    if (s == "cond") returnme.value = 1;
    if (s == "start") returnme.value = 2;
    if (s == "else") returnme.value = 3;
    if (s == "stop") returnme.value = 4;

    return returnme;
}

string &MasterFlowDetok(__int16 number)
{
    static string returnme;

    returnme = "";

    switch(number)
    {
        case 1:
            returnme = "end"; break;
        default:
            returnme = ""; break;
    }

    return returnme;
}

Block &MasterFlowTok(const string &s)
{
    static Block returnme(btMasterFlow,0);

    returnme.tipo = btMasterFlow;
    returnme.value = 0;

    if (s == "end")
        returnme.value = 1;

    return returnme;
}

string &Block::UnparseCommand(const DnaParser* parser, bool converttosysvar)
{
    static string returnme;
    char buffer[256];
    returnme = "";

    switch(tipo)
    {
        case btValue: //number
            if (converttosysvar) returnme = parser->getSysvarName(value);
            else returnme = itoa(value, buffer, 10);
            break;

        case btPointer: //*.number
            returnme = "*" + parser->getSysvarName(value);
            break;

        case btBasicCommand: //basic command
            returnme = BasicCommandDetok(value); break;
        case btAdvancedCommand: //advanced command
            returnme = AdvancedCommandDetok(value); break;
        case btBitwiseCommand: //bit command
            returnme = BitwiseCommandDetok(value); break;
        case btCondition: //condition
            returnme = ConditionsDetok(value); break;
        case btLogic: //logic
            returnme = LogicDetok(value); break;
        case btStores: //stores
            returnme = StoresDetok(value); break;
        case btTies: //nothing (yet)
            //returnme = TiesDetok(value);
            break;
        case btFlow: //Flow Commands
            returnme = FlowDetok(value); break;
        case btMasterFlow: //master flow
            returnme = MasterFlowDetok(value); break;
        default:
            break;
    }

    return returnme;
}

Block::Block(const std::string& command, const DnaParser* parser)
{
    if (isdigit(command.at(0))||command.at(0)=='-')
    {
        tipo = btValue;
        value = atoi(command.c_str());
    }
    else if (command.at(0) == '.')
    {
        tipo = btValue;
        value = parser->getSysvarNumber(command);
    }
    else if (command.at(0) == '*')
    {
        tipo = btPointer;
        value = parser->getSysvarNumber(command.substr(1, command.size()));
    }
    else
    {
        Block bp;

        if (bp.value == 0) bp = BasicCommandTok(command);
        if (bp.value == 0) bp = AdvancedCommandTok(command);
        if (bp.value == 0) bp = BitwiseCommandTok(command);
        if (bp.value == 0) bp = ConditionsTok(command);
        if (bp.value == 0) bp = LogicTok(command);
        if (bp.value == 0) bp = StoresTok(command);
        if (bp.value == 0) bp = FlowTok(command);
        if (bp.value == 0) bp = MasterFlowTok(command);
        *this = bp;
    }
}
