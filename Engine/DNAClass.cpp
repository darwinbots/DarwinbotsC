#include "DNAClass.h"

long DNA_Class::genenum()
{    
    assert(this);
    assert(DNAgenenum > -2);
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
    assert(this);
    assert(DNAlength > -2);
    DNAlength = Code.size() - 1;//don't count the end
    return DNAlength;
}

DNA_Class::DNA_Class():contMutations(),reproMutations()
{
    DNAlength = -1;
    DNAgenenum = -1;
}

DNA_Class::DNA_Class(const DNA_Class &other):Code(other.Code),
                            Private_Variables(other.Private_Variables),
                            DNAgenenum(other.DNAgenenum),
                            DNAlength(other.DNAlength),
                            Mutables(other.Mutables),
                            PointMutCycle(other.PointMutCycle),
                            PointMutBP(other.PointMutBP),
                            LastMutDetail(other.LastMutDetail),
                            Mutations(other.Mutations),
                            LastMut(other.LastMut),
                            contMutations(other.contMutations),
                            reproMutations(other.reproMutations)
{
    //The init list copied the addresses, but we need new objects.
    if(!contMutations.empty())
        for (cMutList::iterator p=contMutations.begin();p!=contMutations.end();++p)
        {
            *p=(*p)->clone();
        }
    if(!reproMutations.empty())
        for (cMutList::iterator p=reproMutations.begin();p!=reproMutations.end();++p)
        {
            *p=(*p)->clone();
        }
}

DNA_Class::~DNA_Class()
{
    if(!contMutations.empty())
    {
        for (cMutList::iterator p=contMutations.begin();p!=contMutations.end();++p)
        {
            delete *p;
        }
        contMutations.clear();
    }
    if(!reproMutations.empty())
    {
        for (cMutList::iterator p=reproMutations.begin();p!=reproMutations.end();++p)
        {
            delete *p;
        }
        reproMutations.clear();
    }
}

bool DNA_Class::Delete(int start, int end)
{
    Code.erase(Code.begin()+start, Code.begin()+end);
    return true;
};

bool DNA_Class::Mutate(bool reproducing) //returns wether we should mutate colors or not
{
    long oldMut = this->LastMut;

    /*if (this->Mutables.Mutations == false)
        return false;*/
        
    
    if (!reproducing)
    {
        if (contMutations.empty())
            {
                return false;
            }
        for(cMutList::iterator p=contMutations.begin();p!=contMutations.end();++p)
        {
            (*p)->mutate(*this);
        }
    }
    else
    {
        if (reproMutations.empty())
            return false;
        //if (this->Mutables.mutarray[CopyErrorUP] > 0) this->CopyError();
        //if (this->Mutables.mutarray[InsertionUP] > 0) this->Insertion();
        //if (this->Mutables.mutarray[ReversalUP] > 0) this->Reversal();
        //if (this->Mutables.mutarray[TranslocationUP] > 0) this->Translocation();
        //if (this->Mutables.mutarray[AmplificationUP] > 0) this->Amplification();
        //if (this->Mutables.mutarray[MajorDeletionUP] > 0) this->MajorDeletion();
        //if (this->Mutables.mutarray[MinorDeletionUP] > 0) this->MinorDeletion();
    }

    if (LastMut > oldMut)
        return true; //mutate colors

    return false;
}
