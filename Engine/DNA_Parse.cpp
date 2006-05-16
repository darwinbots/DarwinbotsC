#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

#include "DNAClass.h"
#include "Engine.h"
#include "HardDriveRoutines.h"

std::string &DNA_Class::text()
{
    long t=0;
    static string returnme("");
    string temp;
    unsigned int gene = 0;

    returnme = "";
    while(this->Code[t] != DNA_END)
    {
        temp = Code[t].UnparseCommand(Code[t+1].tipo == btStores);
        if (temp == "")
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

        returnme += temp;
        t++;
    }

    return returnme;
}

//yet to be implemented:
//parsing for use, def, and shp
istream& DNA_Class::LoadDNA(istream &input)
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
}

istream& DNA_Class::load(istream &inputStream)
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
}

string &DNA_Class::SysvarDetok(__int16 number)
{
    int t;
    char buffer[256];
    static string detok = "UNKNOWN_SYMBOL";

    detok = "UNKNOWN_SYMBOL";
    detok = itoa(number, buffer, 10);

    for(t = 0; t < (int)sysvar.size(); t++)
        if (sysvar[t].value == number)
            detok = "." + sysvar[t].name;

    for (t = 0; t < (int)this->Private_Variables.size(); t++)
        if (number == this->Private_Variables[t].value)
            detok = "." + this->Private_Variables[t].name;

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


