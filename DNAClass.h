#ifndef DNACLASS_H
#define DNACLASS_H

#include <iostream>
#include <vector>

using namespace std;

class block
{
    public:
	int tipo;
    int value;
};

//' var structure, to store the correspondance name<->value
class var
{
    string name;
    int value;
};

class DNA_Class
{
	vector<block> Code;
	vector<var>  Private_Variables;
	unsigned int genenum; //number of genes in the genome
};

#endif