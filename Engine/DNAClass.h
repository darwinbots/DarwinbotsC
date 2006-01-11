#ifndef DNACLASS_H
#define DNACLASS_H

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

#include <iostream>
#include <vector>
#include <sstream>

#include "specie.h"

using namespace std;

template <class T>
bool from_string(T &t,
                 const std::string &s,
                 std::ios_base & (*f)(std::ios_base&))
{
   std::istringstream iss(s);
   return !(iss>>f>>t).fail();
}

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

    block(const tBlockType &a=btNONE, const __int16 &b=0): tipo(a), value(b){};
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
};

//' var structure, to store the correspondance name<->value
struct var
{
    string name;
    __int16 value;
};

class DNA_Class
{
	private:
	vector<block> Code;
	vector<var>   Private_Variables;
	long DNAgenenum; //number of genes in the genome
	long DNAlength;

  public:
    //Mutation related
	mutationprobs Mutables;

	long PointMutCycle;      				// Next cycle to point mutate (expressed in cycles since birth.  ie: age)
	long PointMutBP;         				// the base pair to mutate

    //later we'll replace the below with pointers to a tree structure to save memory
    string LastMutDetail;    				// description of last mutations
    
    unsigned int Mutations;       			// total mutations
	unsigned int LastMut;         			// last mutations

  private:
    //functions
    string &SysvarDetok(__int16 number);
    __int16 SysvarTok(const string &in);
    block ParseCommand(const string &Command);
    string &UnparseCommand(const block &Command, bool converttosysvar = false);
    void LoadDNA(ifstream &in);
    bool Delete(int start, int end); //deletes blocks from start (inclusive) to end (exclusive)
    
	public:
    DNA_Class(); //constructor
    DNA_Class(const DNA_Class &other);
	long length();
    long genenum();
    bool Mutate(bool reproducing);

    string &text(); //parse into a string
    bool LoadDNA(string path);
    void Execute();
};

//+ operator: concatenate two DNAs, placing an end at the end
//

extern var sysvar[1000]; //all possible sysvars
extern int maxsysvar;
extern vector<pair<string,__int16> > vSysvars;

const block DNA_END  (btMasterFlow,1 );
const block DNA_START(btFlow ,2 );
const block DNA_ELSE (btFlow ,3 );
const block DNA_STOP (btFlow ,4 );
//const int   DNA_STORES_TYPE = 7;

#endif

