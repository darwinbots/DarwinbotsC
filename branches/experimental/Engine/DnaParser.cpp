#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "DnaParser.h"

using namespace std;

#include "DNAClass.h"
#include "Block.h"

DnaParser::DnaParser()
{
    //ctor
}

DnaParser::~DnaParser()
{
    //dtor
}

bool DnaParser::buildSysvars(std::string path)
{
    string line;

	ifstream in(path.c_str());

    if (in.fail() == true)
    {
        //can't find sysvars file
        std::cout << "Sysvars file " << path.c_str() << " not found." << endl;
		in.close();
		return false;
    }

    while (!in.eof())
    {
        var temp;

        in >> line;
        temp.value = atoi(line.c_str());

        in >> line;
        temp.name = line;

        sysvar.push_back(temp);
    }

    in.close();
    /*for (std::vector<var>::iterator currVar = sysvar.begin(); currVar != sysvar.end(); ++currVar)
    {
        std::cout<<"Sysvar "<<currVar->value<<" = "<<currVar->name<<"."<<std::endl;
    }*/
    return true;
}

Dna DnaParser::loadFile(string path) const
{
    Dna dna;
    ifstream DNAfile(path.c_str() );
	if (DNAfile.fail() == true)
	{
		//this isn't a valid robot DNA file
		cout << "Robot file " << path.c_str() << " not found." << endl;
	}
    else
        dna=load(DNAfile);

    DNAfile.close();
    return dna;
}

Dna DnaParser::load(istream &inputStream) const
{
    vector<string> tokenList = tokenize(inputStream);

    Dna dna;
    vector<string>::iterator token;
    vector<Block> code;
    for(token = tokenList.begin(); token!=tokenList.end(); token++){
        code.push_back(toBlock(*token));
    }
    code.push_back(DNA_END);
    dna.setCode(code);
    assert(dna.length() >= 0 && "An odd error that should never occurr.");
    return dna;
}

string DnaParser::getText(Dna &dna) const
{
    std::vector<Block> code = dna.getCode();
    string temp="";
    unsigned int gene = 0;

    for(std::vector<Block>::iterator block = code.begin(); block+1 != code.end(); ++block)
    {
        temp += block->UnparseCommand(this, (block+1)->tipo == btStores);

        if (block->tipo == btCondition ||
            block->tipo == btLogic ||
            block->tipo == btStores ||
            block->tipo == btFlow)
        {
            temp += "\n";

            if (*block == DNA_START || *block == DNA_ELSE)
                gene++;
            if(*block == DNA_STOP)
                temp += "\n";
        }
        else
            temp += " ";
    }
    return temp;
}

Block DnaParser::toBlock(const std::string &token) const
{
    return Block(token,this);
}


//yet to be implemented:
//parsing for use, def, and shp
/*
istream& Dna::LoadDNA(istream &input)
{
    char buffer[1024];
    char *c_word = NULL; //cline is the buffer for the text line
    string line, word;
    Block temp;

    Code.clear();

    while(!input.eof())
    {
        line = GetLine(input);
        line = line.substr(0, line.find_first_of("\'", 0)); //take out inline comments

        if (!(line[0] == '\'' || line == "")) //these lines are not either blank or comment lines
        {
            strcpy(buffer, line.c_str());

            c_word = strtok(buffer, "\n\t "); //tokenize the string and find next token in it
            while(c_word != NULL)
            {
                this->Code.push_back(Block(c_word));
                c_word = strtok(NULL, "\n\t ");
            }
        }
    }

    this->Code.push_back(DNA_END);
    assert(this->Code.size() > 0 && "An odd error that should never occurr.");
    this->length();
    this->genenum();
	return input;
}*/

/*bool Dna::loadFile(string path)
{
    ifstream DNAfile(path.c_str() );
	if (DNAfile.fail() == true)
	{
		//this isn't a valid robot DNA file
		cout << "Robot file " << path.c_str() << " not found." << endl;
		DNAfile.close();
		return false;
	}

    this->load(DNAfile);

    DNAfile.close();
    return true;
}*/

/*istream& Dna::load(istream &inputStream)
{
    vector<string> tokenList = tokenize(inputStream);

    Code.clear();

    vector<string>::iterator token;
    for(token = tokenList.begin(); token!=tokenList.end(); token++){
        Code.push_back(*token);
    }
    this->Code.push_back(DNA_END);
    assert(this->Code.size() > 0 && "An odd error that should never occurr.");
    this->length();
    this->genenum();
    return inputStream;
}*/

string DnaParser::getSysvarName(__int16 number) const
{
    int t;
    char buffer[256];
    static string detok = "UNKNOWN_SYMBOL";

    detok = itoa(number, buffer, 10);

    for(t = 0; t < (int)sysvar.size(); t++)
        if (sysvar[t].value == number)
            detok = "." + sysvar[t].name;

    return detok;
}

__int16 DnaParser::getSysvarNumber(const string &in) const
{
    string a = in;
    if (a[0] == '.') //is indeed a sysvar
    {
        a = a.substr(1, a.size()); //get rid of the period

        for (std::vector<var>::const_iterator currVar = sysvar.begin(); currVar != sysvar.end(); ++currVar)
        {
            if (currVar->name == a)
                return currVar->value;
        }
    }

    return atoi(a.c_str());
}

// This is an all purpose tokenizer respecting Darwinbots' conventions
// Spaces and linebreaks count as delimiters and everything after "'" is
// ignored till end of line.
vector<string> DnaParser::tokenize(istream& inputStream)
{
    unsigned int pos;
    vector<string> tokenList;
    string lineBuf,token;

    while(!inputStream.eof())
    {
        getline(inputStream,lineBuf);
        pos = lineBuf.find("'");
        if (pos != string::npos)
            lineBuf.erase(pos);
        stringstream ssLineBuf(lineBuf,std::stringstream::in);
        while( !ssLineBuf.eof() )
        {
            while (isspace(ssLineBuf.peek()))
                ssLineBuf.get();

            if( ssLineBuf.eof())
                break;

            ssLineBuf>>token;
            tokenList.push_back(token);
        }
    }

    return tokenList;
};