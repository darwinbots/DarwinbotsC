#ifndef DNACLASS_H
#define DNACLASS_H

#include <iostream>
#include <vector>
#include <sstream>
#include <cassert>

#include "specie.h"
#include "Block.h"
#include "Mutations.h"
class Robot;

using namespace std;

struct MutationDetails
{
    int type;
    unsigned long cycle;
    unsigned long start, stop, location;
    vector<Block> Inserted; //holds the DNA added if DNA was added
    float Magnitude;
};

class DNA_Class
{
	friend istream& operator>>(istream& input, DNA_Class& newDNA); //Load DNA from an input source
	friend ostream& operator<<(ostream& output, DNA_Class& DNA);   //Output DNA into a Text File
    
    private:
    vector<Block> Code;
	vector<var>   Private_Variables;
	long DNAgenenum; //number of genes in the genome
	
    public:
    mutationprobs Mutables;

	//later we'll replace the below with pointers to a tree structure to save memory
    vector<MutationDetails> LastMutDetail;  // description of last mutations
    
    unsigned int Mutations;       			// total mutations
	unsigned int LastMut;         			// last mutations

    private:
    //functions
    
    bool Delete(int start, int end); //deletes blocks from start (inclusive) to end (inclusive)
    bool Reverse(unsigned int start, unsigned int end);
    bool Translocate(unsigned int start, unsigned int end);
    void MutatePoint(float multiplier);
    void MutateDelta(float multiplier);
    void MutateCopyError(float multiplier);
    void MutateReversal(float multiplier);
    void MutateTranslocation(float multiplier);
    void MutateInsertion(float multiplier);
    void MutateAmplification(float multiplier);
    void MutateDeletion(float multiplier);    

    string &SysvarDetok(__int16 number);
    __int16 SysvarTok(const string &in);
    Block ParseCommand(const string &Command);
    string &UnparseCommand(const Block &Command, bool converttosysvar);
    
	public:
    DNA_Class(); //constructor
    DNA_Class(const DNA_Class &other);
    ~DNA_Class();
	long length();
    long genenum();
    bool Mutate(bool reproducing, float multiplier = 1.0f);    

    string &text(); //parse into a string
    bool LoadDNA(string path);
    istream& LoadDNA(istream &input);
    istream& load(istream &inputStream);
    void Execute(Robot* bot);
    void Occurrs(int *OccurrArray);
};

inline istream& operator>>(istream& input, DNA_Class& DNA)
{
    return DNA.LoadDNA(input);
}

inline ostream& operator>>(ostream& output, DNA_Class& DNA)
{
    return output<<DNA.text();
}

//+ operator: concatenate two DNAs, placing an end at the end
//

#endif

