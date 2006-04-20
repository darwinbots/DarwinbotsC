#include "RobotSysvars.h"
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
    return Code.size() - 1;//don't count the end
}

DNA_Class::DNA_Class()//:contMutations(),reproMutations()
{
    DNAgenenum = -1;
}

DNA_Class::DNA_Class(const DNA_Class &other):Code(other.Code),
                     Private_Variables(other.Private_Variables),
                     DNAgenenum(other.DNAgenenum),
                     Mutables(other.Mutables),
                     LastMutDetail(other.LastMutDetail),
                     Mutations(other.Mutations),
                     LastMut(other.LastMut)
{
    
}

DNA_Class::~DNA_Class()
{
    
}

bool DNA_Class::Mutate(bool reproducing, float multiplier) //returns wether we should mutate colors or not
{
    unsigned long oldMut = this->LastMut;

    if (this->Mutables.On == false)
        return false;
        
    if (!reproducing)
    {
        //Point Mutations and Delta Mutations
        
        if(Mutables.Point.On) MutatePoint(multiplier);
        if(Mutables.Delta.On) MutateDelta(multiplier);
    }
    else
    {
        if(Mutables.CopyError.On)       MutateCopyError(multiplier);
        if(Mutables.Reversal.On)        MutateReversal(multiplier);
        if(Mutables.Translocation.On)   MutateTranslocation(multiplier);
        if(Mutables.Insertion.On)       MutateInsertion(multiplier);
        if(Mutables.Amplification.On)   MutateAmplification(multiplier);
        if(Mutables.Deletion.On)        MutateDeletion(multiplier);     
    }

    if (LastMut > oldMut)
        return true; //mutate colors

    return false;
}

void DNA_Class::Occurrs(int *OccurrArray)
{
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
