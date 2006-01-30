#ifdef _MSC_VER
#pragma warning(disable : 4786)
#endif

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

string &DNA_Class::text()
{
    long t=0;
    static string returnme("");
    string temp;
    unsigned int gene = 0;

    returnme = "";
    while(this->Code[t] != DNA_END)
    {
        temp = this->Code[t].text(this->Code[t+1].tipo == btStores);
        if (temp == "")
            temp = "VOID";

        if (Code[t].tipo == btCondition || Code[t].tipo == btLogic || Code[t].tipo == btStores || Code[t].tipo == btFlow)
        {
            temp = temp + "\n";
            
            if (Code[t] == DNA_START || Code[t] == DNA_ELSE)
                gene++;
      
            if (Code[t] == DNA_STOP)
            {
                temp += "\n";
            }
        }
        else
        {
            temp = temp + " ";
        }

        returnme += temp;
        t++;
    }

    return returnme;
}

istream& DNA_Class::LoadDNA(istream &input)
{
    char *c_word = NULL; //cline is the buffer for the text line
    string line, word;
    block temp;

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
                word = c_word;

                //yet to be implemented:
                //parsing for use, def, and shp
                //parsing for Hashing

                //this->Code.reserve(this->Code.size() + 1); that's pointless
                this->Code.push_back(ParseCommand(word));
                //parse this word

                c_word = strtok(NULL, "\n\t ");
            }
        }
    }

    this->Code.reserve(this->Code.size() + 2);
    this->Code.push_back(DNA_END);

    this->length();
    this->genenum();
	return input;
}






