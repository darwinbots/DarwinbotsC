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
//#include "Robot.h"

using namespace std;


template <class T>
bool from_string(T &t,
                 const std::string &s,
                 std::ios_base & (*f)(std::ios_base&))
{
   std::istringstream iss(s);
   return !(iss>>f>>t).fail();
}


typedef vector<cMutationBase*> cMutList;

class DNA_Class
{
	friend istream& operator>>(istream& input, DNA_Class& newDNA);
	friend ostream& operator<<(ostream& output, DNA_Class& DNA);
    friend class cPointDeletion;
    friend class cPointInsertion;
    friend class cPointChange;
private:
	vector<block> Code;
	vector<var>   Private_Variables;
	long DNAgenenum; //number of genes in the genome
	long DNAlength;
public: //temporarily
    cMutList contMutations;
    cMutList reproMutations;
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
    
	
    bool Delete(int start, int end); //deletes blocks from start (inclusive) to end (exclusive)
#ifdef _MSC_VER
public: //stupid VC++ 6.0 doesn't handle friend functions
#endif
    std::istream& LoadDNA(std::istream &input);
    
	public:
    DNA_Class(); //constructor
    DNA_Class(const DNA_Class &other);
    ~DNA_Class();
	long length();
    long genenum();
    bool Mutate(bool reproducing);

    string &text(); //parse into a string
    bool LoadDNA(string path);
    void Execute(Robot* bot);
};

inline istream& operator>>(istream& input, DNA_Class& newDNA)
{
    return newDNA.LoadDNA(input);
}

inline ostream& operator>>(ostream& output, DNA_Class& DNA)
{
    return output<<DNA.text();
}

//+ operator: concatenate two DNAs, placing an end at the end
//

#endif

