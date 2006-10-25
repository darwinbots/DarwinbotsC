#ifndef DNAPARSER_H
#define DNAPARSER_H

#include<istream>
#include<string>
#include<vector>

class DNA_Class;
class Block;

struct var
{
    std::string name;
    __int16 value;
};

class DnaParser
{
    public:
        DnaParser();
        ~DnaParser();
        bool buildSysvars(std::string path);

        DNA_Class load(std::istream& input) const;
        DNA_Class loadFile(std::string path) const;
        std::string getText(DNA_Class &dna) const;

        Block toBlock(const std::string &token) const;

        std::string getSysvarName(__int16 number) const;
        __int16 getSysvarNumber(const std::string &in) const;

    protected:
        std::vector<var> sysvar;
    private:
};

#endif // DNAPARSER_H
