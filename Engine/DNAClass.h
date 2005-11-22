#ifndef DNACLASS_H
#define DNACLASS_H

#include <iostream>
#include <vector>

using namespace std;

struct block
{
	__int16 tipo;
    __int16 value;

    block(const int &a=0, const int &b=0) { tipo = a; value = b; }
    const bool operator == (const block &other) const
    {
        return tipo == other.tipo && value == other.value;
    }

    const bool operator != (const block &other) const
    {
        return !(tipo == other.tipo && value == other.value);
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

    //functions
    string &SysvarDetok(__int16 number);
    __int16 SysvarTok(const string &in);
    block ParseCommand(const string &Command);
    string &UnparseCommand(const block &Command, bool converttosysvar = false);
    void LoadDNA(ifstream &in);

	public:
    DNA_Class(); //constructor
	long length();
	long genenum();

    string &text(); //parse into a string
    bool LoadDNA(string path);
    void Execute();
};

//+ operator: concatenate two DNAs, placing an end at the end
//

extern var sysvar[1000]; //all possible sysvars
extern int maxsysvar;

const block DNA_END  (10,1 );
const block DNA_START(9 ,2 );
const block DNA_ELSE (9 ,3 );
const block DNA_STOP (9 ,4 );
const int   DNA_STORES_TYPE = 7;

#endif

