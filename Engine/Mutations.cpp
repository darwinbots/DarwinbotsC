//NEVER allow anything after end, which must be = DNALen
//ALWAYS assume that DNA is sized right
//ALWAYS size DNA correctly when mutating

#include "DNAClass.h"
#include "Mutations.h"
#include "../Common/Random.h"

//1-(perbot+1)^(1/DNALength) = per unit

//1-(1-perunit)^DNALength = perbot

using namespace std;

bool DNA_Class::Delete(int start, int end)
{
    Code.erase(Code.begin()+start, Code.begin()+end+1);
    DNAgenenum = -1;
    return true;
};

bool DNA_Class::Reverse(unsigned int start, unsigned int end)
{
    reverse(Code.begin() + start, Code.begin() + end + 1);
    DNAgenenum = -1;
    return true;
}

bool DNA_Class::Translocate(unsigned int start, unsigned int end)
{
    vector<Block> temp;
    for(unsigned int x = start; x <= end; x++)
        temp.push_back(Code[x]);
    Delete(start, end);

    unsigned int location = frnd(1, length() + 1 - (end - start));
    Code.insert(Code.begin() + location, (end - start), Block()); //insert blanks
    for(unsigned int y = 0, z = location; y < temp.size(); z++, y++)
        Code[z] = temp[y];

    return true;
}

string &MutationType(int mode)
{
    static string temp("");

    switch(mode)
    {
        case PointUP:
            temp = "Point Mutation";
            break;
        case DeletionUP:
            temp = "Deletion";
            break;
        case ReversalUP:
            temp = "Reversal";
            break;
        case InsertionUP:
            temp = "Insertion";
            break;
        case AmplificationUP:
            temp = "Amplification";
            break;
        case CopyErrorUP:
            temp = "Copy Error";
            break;
        case DeltaUP:
            temp = "Delta Mutation";
            break;
        case TranslocationUP:
            temp = "Translocation";
            break;
    }

    return temp;
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

#define BASICMUTATIONWORK(XXX)                          \
    float mutprob = 1.0f / ((float)Mutables[ XXX ]->Prob * multiplier);  \
    if( powf(mutprob, (float)length()) > DBrand())

void DNA_Class::MutatePoint(float multiplier)
{
    BASICMUTATIONWORK(PointUP)
    {
        unsigned int location = frnd(1, length()) - 1;

        if(DBrand() > Mutables[PointUP]->DeltaValue)
            Code[location].RandomizeTipo();
        else
            Code[location].RandomizeValue();
    }

    DNAgenenum = -1;
}

void DNA_Class::MutateDelta(float multiplier)
{
    BASICMUTATIONWORK(DeltaUP)
    {
        int muttype = frnd(PointUP, MaxUP - 1);
        float percentage = 0.0f;

        int x = 0;
        while(percentage == 0)
        {
            percentage = (float)fabs(Gauss(Mutables[DeltaUP]->StdDev,
                                           Mutables[DeltaUP]->Mean));
            if(++x > 100)
                percentage = 1;
        }

        #define MUT(x) Mutables[ x ]->Prob = (unsigned long) ((float)Mutables[ x ]->Prob * (percentage / 100))
        switch(muttype)
        {
            case PointUP:           MUT(PointUP);             break;
            case DeltaUP:           MUT(DeltaUP);             break;
            case DeletionUP:        MUT(DeletionUP);          break;
            case ReversalUP:        MUT(ReversalUP);          break;
            case TranslocationUP:   MUT(TranslocationUP);     break;
            case CopyErrorUP:       MUT(CopyErrorUP);         break;
            case AmplificationUP:   MUT(AmplificationUP);     break;
            case InsertionUP:       MUT(InsertionUP);         break;
        }
        #undef MUT
    }
}

void DNA_Class::MutateCopyError(float multiplier)
{
    BASICMUTATIONWORK(CopyErrorUP)
    {
        unsigned int location = frnd(1, length()) - 1;
        if(DBrand() > Mutables[CopyErrorUP]->DeltaValue)
            Code[location].RandomizeTipo();
        else
            Code[location].RandomizeValue();
    }

    DNAgenenum = -1;
}

void DNA_Class::MutateReversal(float multiplier)
{
    BASICMUTATIONWORK(ReversalUP)
    {
        unsigned int ReversalLength = 0;

        int x = 0;
        while(ReversalLength == 0)
        {
            ReversalLength = (unsigned int)fabs(Gauss(Mutables[ReversalUP]->StdDev,
                                                      Mutables[ReversalUP]->Mean));
            if(++x > 100)
                ReversalLength = 1;
        }

        if(ReversalLength == (unsigned int)length())
            ReversalLength = (unsigned int)length();

        unsigned int location = frnd(0, length() - ReversalLength);

        Reverse(location, location + ReversalLength - 1);
    }
}

void DNA_Class::MutateTranslocation(float multiplier)
{
    BASICMUTATIONWORK(TranslocationUP)
    {
        unsigned int TranslocationLength = 0;

        int x = 0;
        while(TranslocationLength == 0)
        {
            TranslocationLength = (unsigned int)fabs(Gauss(Mutables[TranslocationUP]->StdDev,
                                                           Mutables[TranslocationUP]->Mean));
            if(++x > 100)
                TranslocationLength = 1;
        }

        if (TranslocationLength == (unsigned int)length())
            TranslocationLength = length();

        unsigned int location = frnd(0, length() - TranslocationLength);

        Translocate(location, location + TranslocationLength - 1);
    }
}

void DNA_Class::MutateInsertion(float multiplier)
{
    BASICMUTATIONWORK(InsertionUP)
    {
        unsigned int InsertLength = 0;

        unsigned int x = 0;
        while(InsertLength == 0)
        {
            InsertLength = (unsigned int)fabs(Gauss(Mutables[InsertionUP]->StdDev,
                                                    Mutables[InsertionUP]->Mean));
            if(++x > 100)
                InsertLength = 1;
        }

        if (InsertLength == (unsigned int)length())
            InsertLength = length();

        vector<Block> temp;
        Block RND;
        for(x = 0; x < InsertLength; x++)
        {
            RND.RandomizeTipo();
            RND.RandomizeValue();
            temp.push_back(RND);
        }

        unsigned int location = frnd(0, length() - 1);

        Code.insert(Code.begin() + location + 1, InsertLength, Block());

        for(x = 0; x < InsertLength; x++)
        {
            Code[location + x] = temp[x];
        }
    }
}

void DNA_Class::MutateAmplification(float multiplier)
{
    BASICMUTATIONWORK(AmplificationUP)
    {
        unsigned int AmpLength = 0;

        unsigned int x = 0;
        while(AmpLength == 0)
        {
            AmpLength = (unsigned int)fabs(Gauss(Mutables[AmplificationUP]->StdDev,
                                                 Mutables[AmplificationUP]->Mean));
            if(++x > 100)
                AmpLength = 1;
        }

        if (AmpLength == (unsigned int)length())
            AmpLength = length();

        unsigned int location = frnd(0, length() - AmpLength);

        vector<Block> temp;

        for(x = location; x < location + AmpLength; x++)
            temp.push_back(Code[location]);

        location = frnd(0, length() - 1);

        Code.insert(Code.begin() + location + 1, AmpLength, Block());
        for(unsigned int z = location, y = 0; z < AmpLength + location; z++, y++)
            Code[z] = temp[y];
    }
}
void DNA_Class::MutateDeletion(float multiplier)
{
    BASICMUTATIONWORK(DeletionUP)
    {
        unsigned int DeleteLength = 0;

        int x = 0;
        while(DeleteLength == 0)
        {
            DeleteLength = (unsigned int)fabs(Gauss(Mutables[DeletionUP]->StdDev,
                                                    Mutables[DeletionUP]->Mean));
            if(++x > 100)
                DeleteLength = 1;
        }

        if (DeleteLength >= (unsigned int)length())
            DeleteLength = length();

        unsigned int location = frnd(0, length() - DeleteLength);

        Delete(location, location + DeleteLength - 1);
    }
}
