#ifndef DNAPARSER_H
#define DNAPARSER_H

#include<istream>
#include<string>
#include<vector>

class Dna;
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

        Dna load(std::istream& input) const;
        Dna loadFile(std::string path) const;
        std::string getText(Dna &dna) const;

        Block toBlock(const std::string &token) const;

        std::string getSysvarName(__int16 number) const;
        __int16 getSysvarNumber(const std::string &in) const;

    protected:
        std::vector<var> sysvar;
    private:
        static std::vector<std::string> DnaParser::tokenize(std::istream& inputStream);
};

#endif // DNAPARSER_H
