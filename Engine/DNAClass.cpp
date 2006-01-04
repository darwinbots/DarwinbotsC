#include "DNAClass.h"

long DNA_Class::genenum()
{    
    long counter=0;
    long genecounter = 0;

    if (this->DNAgenenum == -1)
    {
        while(this->Code[counter] != DNA_END)
        {
            if (this->Code[counter] == DNA_START || 
                this->Code[counter] == DNA_ELSE)
                genecounter++;
            counter++;
        }

        DNAgenenum = genecounter;
    } 

    return this->DNAgenenum;
}

long DNA_Class::length()
{
    if (this->DNAlength == -1)
    {
        long counter=0;

        while(this->Code[counter++] != DNA_END);

        DNAlength = counter - 1;//don't count the end
    }

    return DNAlength;
}

DNA_Class::DNA_Class()
{
    DNAlength = -1;
    DNAgenenum = -1;
}

DNA_Class::DNA_Class(const DNA_Class &other)
{
    (*this) = other;
}
