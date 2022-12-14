#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

#include "DNAClass.h"
#include "Engine.h"
#include "HardDriveRoutines.h"

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

block &BasicCommandTok(const string &s)
{
    static block returnme(btBasicCommand,0);

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

block &AdvancedCommandTok(string s)
{
    static block returnme(btAdvancedCommand,0);

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

block &BitwiseCommandTok(string s)
{
    static block returnme(btBitwiseCommand,0);

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

block &ConditionsTok(string s)
{
    static block returnme(btCondition,0);

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

block &LogicTok(string s)
{
    static block returnme(btLogic,0);

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

block &StoresTok(string s)
{
    static block returnme(btStores,0);

    returnme.tipo = btStores;
    returnme.value = 0;

    if (s == "store") returnme.value = 1;
    if (s == "inc")   returnme.value = 2;
    if (s == "dec")   returnme.value = 3;

    return returnme;
}

string &TiesDetok(__int16 number)
{
    static string returnme;

    returnme = "";
    switch(number)
    {
        case 1:
            returnme = "settie"; break;

        case 2:
            returnme = "newttie"; break;

        case 3:
            returnme = "writetie"; break;
           
        case 4:
            returnme = "readtie"; break;

        default:
            returnme = ""; break;
    }

    return returnme;
}

block &TiesTok(string s)
{
    static block returnme(btStores,0);

    returnme.tipo = btStores;
    returnme.value = 0;

    if (s == "settie") returnme.value = 1;
    if (s == "newtie")   returnme.value = 2;
    if (s == "writetie")   returnme.value = 3;
    if (s == "readtie")   returnme.value = 4;

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

block &FlowTok(string s)
{
    static block returnme(btFlow,0);

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

block &MasterFlowTok(const string &s)
{
    static block returnme(btMasterFlow,0);

    returnme.tipo = btMasterFlow;
    returnme.value = 0;

    if (s == "end")
        returnme.value = 1;

    return returnme;
}

string &DNA_Class::text()
{
    long t=0;
    static string returnme("");
    string temp;
    unsigned int gene = 0;

    returnme = "";
    while(this->Code[t] != DNA_END)
    {
        temp = UnparseCommand(Code[t], Code[t+1].tipo == btStores);
        if (temp.size() == 0)
            temp = "VOID";

        if (Code[t].tipo == btCondition ||
            Code[t].tipo == btLogic ||
            Code[t].tipo == btStores ||
            Code[t].tipo == btFlow)
        {
            temp = temp + "\n";
            
            if (Code[t] == DNA_START || Code[t] == DNA_ELSE)
                gene++;
      
            if(Code[t] == DNA_STOP)
                temp += "\n";
        }
        else
            temp = temp + " ";
        
        returnme.append(temp);
        t++;
    }

    return returnme;   
}

//yet to be implemented:
//parsing for use, def, and shp
istream& DNA_Class::LoadDNA(istream &input)
{
    char *c_word = NULL; //cline is the buffer for the text line
    string line, word;
    block temp;
    
    char *nexttoken = NULL;

    Code.clear();

    while(!input.eof())
    {
        line = GetLine(input);
        line = line.substr(0, line.find_first_of("\'", 0)); //take out inline comments

        if (!(line[0] == '\'' || line == "")) //these lines are not either blank or comment lines
        {
            strcpy_s(buffer, 1024, line.c_str());
            
            c_word = strtok_s(buffer, "\n\t ", &nexttoken); //tokenize the string and find next token in it
            while(c_word != NULL)
            {
                this->Code.push_back(ParseCommand(c_word));
                c_word = strtok_s(NULL, "\n\t ", &nexttoken);
            }
        }
    }

    this->Code.push_back(DNA_END);
    assert(this->Code.size() > 0 && "An odd error that should never occurr.");
    this->length();
    this->genenum();
	return input;
}

string &DNA_Class::SysvarDetok(__int16 number)
{
    int t;
    char buffer[256];
    static string detok = "UNKNOWN_SYMBOL";

    detok = "UNKNOWN_SYMBOL";
    _itoa_s(number, buffer, 256, 10);
    
    detok = buffer;

    for(t = 0; t < (int)sysvar.size(); t++)
        if (sysvar[t].value == number)
        {
            detok = "." + sysvar[t].name;
            break;
        }

    for (t = 0; t < (int)this->Private_Variables.size(); t++)
        if (number == this->Private_Variables[t].value)
        {
            detok = "." + this->Private_Variables[t].name;
            break;
        }

    return detok;
}

string &SysvarDetok(__int16 number)
{
    int t;
    char buffer[256];
    static string detok = "UNKNOWN_SYMBOL";

    detok = "UNKNOWN_SYMBOL";
    _itoa_s(number, buffer, 256, 10);
    
    detok = buffer;

    for(t = 0; t < (int)sysvar.size(); t++)
        if (sysvar[t].value == number)
            detok = "." + sysvar[t].name;

    return detok;
}

__int16 DNA_Class::SysvarTok(const string &in)
{
    string a = in;
    int t;

    if (a[0] == '.') //is indeed a sysvar
    {
        a = a.substr(1, a.size()); //get rid of the period

        for (t = 0; t < (int)sysvar.size(); t++)
            if (sysvar[t].name == a)
                return sysvar[t].value;

        for (t = 0; t < (int)this->Private_Variables.size(); t++)
            if (this->Private_Variables[t].name == a)
                return this->Private_Variables[t].value;
    }

    return atoi(a.c_str());
}

__int16 SysvarTok(const string &in)
{
    string a = in;
    int t;

    if (a[0] == '.') //is indeed a sysvar
    {
        a = a.substr(1, a.size()); //get rid of the period

        for (t = 0; t < (int)sysvar.size(); t++)
            if (sysvar[t].name == a)
                return sysvar[t].value;
    }

    return atoi(a.c_str());
}

block DNA_Class::ParseCommand(const string &Command)
{
    block bp;

    if (bp.value == 0) bp = BasicCommandTok(Command);
    if (bp.value == 0) bp = AdvancedCommandTok(Command);
    if (bp.value == 0) bp = BitwiseCommandTok(Command);
    if (bp.value == 0) bp = ConditionsTok(Command);
    if (bp.value == 0) bp = LogicTok(Command);
    if (bp.value == 0) bp = StoresTok(Command);
    if (bp.value == 0) bp = FlowTok(Command);
    if (bp.value == 0) bp = MasterFlowTok(Command);
    if (bp.value == 0 && Command.at(0) == '*')
    {
        bp.tipo = btPointer;
        bp.value = SysvarTok(Command.substr(1, Command.size()));
    }
    else if (bp.value == 0)
    {
        bp.tipo = btValue;
        bp.value = SysvarTok(Command);
    }

    return bp;
}

block *block::ParseCommand(const string &Command)
{
    block bp;

    if (bp.value == 0) bp = BasicCommandTok(Command);
    if (bp.value == 0) bp = AdvancedCommandTok(Command);
    if (bp.value == 0) bp = BitwiseCommandTok(Command);
    if (bp.value == 0) bp = ConditionsTok(Command);
    if (bp.value == 0) bp = LogicTok(Command);
    if (bp.value == 0) bp = StoresTok(Command);
    if (bp.value == 0) bp = FlowTok(Command);
    if (bp.value == 0) bp = MasterFlowTok(Command);
    if (bp.value == 0 && Command.at(0) == '*')
    {
        bp.tipo = btPointer;
        bp.value = SysvarTok(Command.substr(1, Command.size()));
    }
    else if (bp.value == 0)
    {
        bp.tipo = btValue;
        bp.value = SysvarTok(Command);
    }

    (*this) = bp;
    return this;
}

block ParseCommand(const string &Command)
{
    block bp;

    bp.ParseCommand(Command);

    return bp;
}

string &DNA_Class::UnparseCommand(const block &Command, bool converttosysvar)
{
    static string returnme;
    char buffer[256];
    returnme = "";

    switch(Command.tipo)
    {
        case btValue: //number
            if (converttosysvar) returnme = SysvarDetok(Command.value);
            else
            {
                _itoa_s(Command.value, buffer, 256, 10);
                returnme = buffer;
            }
            break;

        case btPointer: //*.number
            returnme = "*" + SysvarDetok(Command.value);
            break;

        case btBasicCommand: //basic command
            returnme = BasicCommandDetok(Command.value); break;
        case btAdvancedCommand: //advanced command
            returnme = AdvancedCommandDetok(Command.value); break;
        case btBitwiseCommand: //bit command
            returnme = BitwiseCommandDetok(Command.value); break;
        case btCondition: //condition
            returnme = ConditionsDetok(Command.value); break;
        case btLogic: //logic
            returnme = LogicDetok(Command.value); break;
        case btStores: //stores
            returnme = StoresDetok(Command.value); break;
        case btTies: //tie commands
            returnme = TiesDetok(Command.value); break;
        case btFlow: //Flow Commands
            returnme = FlowDetok(Command.value); break;
        case btMasterFlow: //master flow
            returnme = MasterFlowDetok(Command.value); break;
        default:
            break;
    }

    return returnme;
}

string &block::UnparseCommand(bool converttosysvar)
{
    static string returnme;
    char buffer[256];
    returnme = "";

    switch(tipo)
    {
        case btValue: //number
            if (converttosysvar) returnme = SysvarDetok(value);
            else
            {
                _itoa_s(value, buffer, 256, 10);
                returnme = buffer;
            }break;

        case btPointer: //*.number
            returnme = "*" + SysvarDetok(value);
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
        case btTies: //tie commands
            returnme = TiesDetok(value); break;
        case btFlow: //Flow Commands
            returnme = FlowDetok(value); break;
        case btMasterFlow: //master flow
            returnme = MasterFlowDetok(value); break;
        default:
            break;
    }

    return returnme;
}