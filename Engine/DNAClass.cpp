#include "RobotSysvars.h"
#include "DNAClass.h"

long Dna::genenum()
{
    assert(this != NULL && "Attempting to count the number of genes in non existant DNA in Dna::genenum()");
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

long Dna::length()
{
    assert(this != NULL && "Attempting to find the size of non existant DNA");
    if(this == NULL)
        return 0;
    return (long)Code.size() - 1;//don't count the end
}

Dna::Dna()//:contMutations(),reproMutations()
{
    DNAgenenum = -1;
    Code.push_back(DNA_END);
}

Dna::Dna(const Dna &other):Code(other.Code),
                     //Private_Variables(other.Private_Variables),
                     DNAgenenum(other.DNAgenenum),
                     Mutables(other.Mutables),
                     LastMutDetail(other.LastMutDetail),
                     Mutations(other.Mutations),
                     LastMut(other.LastMut)
{

}

Dna::~Dna()
{
    Code.clear();
    LastMutDetail.clear();
}

bool Dna::Mutate(bool reproducing, float multiplier) //returns wether we should mutate colors or not
{
    assert(this != NULL && "Attempting to mutate non existant DNA in DNAClass::Mutate()");
    unsigned long oldMut = this->LastMut;

    if (this->Mutables.GlobalMutationOn() == false)
        return false;

    if (!reproducing)
    {
        //Point Mutations and Delta Mutations

        if(Mutables[PointUP]->On) MutatePoint(multiplier);
        if(Mutables[DeltaUP]->On) MutateDelta(multiplier);
    }
    else
    {
        if(Mutables[CopyErrorUP]->On)       MutateCopyError(multiplier);
        if(Mutables[ReversalUP]->On)        MutateReversal(multiplier);
        if(Mutables[TranslocationUP]->On)   MutateTranslocation(multiplier);
        if(Mutables[InsertionUP]->On)       MutateInsertion(multiplier);
        if(Mutables[AmplificationUP]->On)   MutateAmplification(multiplier);
        if(Mutables[DeletionUP]->On)        MutateDeletion(multiplier);
    }

    if (LastMut > oldMut)
        return true; //mutate colors

    return false;
}

void Dna::Occurrs(int *OccurrArray)
{
    assert(this != NULL && "Attempting to count up the occurr array for non existant DNA in Dna::Occurrs()");
    int counter = 0;

    while(this->Code[counter] != DNA_END)
    {
        //myshoot
        /*
          If .DNA(t).tipo = 0 Then 'number
            If .DNA(t).value < 8 And .DNA(t).value > 0 Then 'if we are dealing with one of the first 8 sysvars
              If .DNA(t + 1).tipo = 7 Then 'DNA is going to store to this value, so it's probably a sysvar
                .occurr(.DNA(t).value) = .occurr(.DNA(t).value) + 1 'then the occur listing for this fxn is incremented
              End If
            End If
          End If
          */

        if(Code[counter].tipo == btPointer)
        {
            if(Code[counter].value >= EyeStart &&
               Code[counter].value <= EyeEnd)
               OccurrArray[8]++;

            if(Code[counter].value == mtie)
               OccurrArray[9]++;

            if(Code[counter].value == mkpoison ||
               Code[counter].value == poison)
               OccurrArray[10]++;

            if(Code[counter].value == mkvenom ||
               Code[counter].value == venomsys)
               OccurrArray[11]++;
        }

        counter++;
    }
}
