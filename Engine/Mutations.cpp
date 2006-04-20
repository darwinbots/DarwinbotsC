//NEVER allow anything after end, which must be = DNALen
//ALWAYS assume that DNA is sized right
//ALWAYS size DNA correctly when mutating

#include "DNAClass.h"
#include "Mutations.h"

//1-(perbot+1)^(1/DNALength) = per unit

//1-(1-perunit)^DNALength = perbot

bool DNA_Class::Delete(int start, int end)
{
    Code.erase(Code.begin()+start, Code.begin()+end+1);
    DNAgenenum = -1;
    return true;
};

bool DNA_Class::Reverse(unsigned int start, unsigned int end)
{
    for(unsigned int x = start, y = end; x <= (start+end) / 2; x++, y--)
        swap(Code[x], Code[y]);
    DNAgenenum = -1;
    return true;
}

bool DNA_Class::Translocate(unsigned int start, unsigned int end)
{
    vector<block> temp;
    for(unsigned int x = start; x <= end; x++)
        temp.push_back(Code[x]);
    Delete(start, end);

    unsigned int location = frnd(1, length() + 1 - (end - start));
    Code.insert(Code.begin() + location, (end - start), block()); //insert blanks
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
    float mutprob = 1.0f / ((float)Mutables. XXX .Prob * multiplier);  \
    if( powf(mutprob, (float)length()) > DBrand())

DNA_Class::MutatePoint(float multiplier)
{
    BASICMUTATIONWORK(Point)
    {
        unsigned int location = frnd(1, length()) - 1;

        if(DBrand() > Mutables.Point.DeltaValue / 100.0f)
            Code[location].RandomizeTipo();
        else
            Code[location].RandomizeValue();
    }

    DNAgenenum = -1;
}

DNA_Class::MutateDelta(float multiplier)
{
    BASICMUTATIONWORK(Delta)
    {
        int muttype = frnd(PointUP, MaxUP - 1);
        float percentage = 0.0f;
        
        int x = 0;
        while(percentage == 0)
        {
            percentage = (float)fabs(Gauss(Mutables.Delta.StdDev,
                                           Mutables.Delta.Mean));
            if(++x > 100)
                percentage = 1;
        }

        #define MUT(x) Mutables. x .Prob = unsigned long ((float)Mutables. x .Prob * (percentage / 100));
        switch(muttype)
        {            
            case PointUP:           MUT(Point);             break;
            case DeltaUP:           MUT(Delta);             break;
            case DeletionUP:        MUT(Deletion);          break;
            case ReversalUP:        MUT(Reversal);          break;
            case TranslocationUP:   MUT(Translocation);     break;
            case CopyErrorUP:       MUT(CopyError);         break;
            case AmplificationUP:   MUT(Amplification);     break;
            case InsertionUP:       MUT(Insertion);         break;            
        }
        #undef MUT
    }    
}

DNA_Class::MutateCopyError(float multiplier)
{
    BASICMUTATIONWORK(CopyError)
    {
        unsigned int location = frnd(1, length()) - 1;
        if(DBrand() > Mutables.CopyError.DeltaValue / 100.0f)
            Code[location].RandomizeTipo();
        else
            Code[location].RandomizeValue();
    }

    DNAgenenum = -1;
}

DNA_Class::MutateReversal(float multiplier)
{
    BASICMUTATIONWORK(Reversal)
    {
        unsigned int ReversalLength = 0;

        int x = 0;
        while(ReversalLength == 0)
        {
            ReversalLength = (unsigned int)fabs(Gauss(Mutables.Reversal.StdDev,
                                                      Mutables.Reversal.Mean));
            if(++x > 100)
                ReversalLength = 1;
        }

        if(ReversalLength == (unsigned int)length())
            ReversalLength = (unsigned int)length();

        unsigned int location = frnd(0, length() - ReversalLength);

        Reverse(location, location + ReversalLength - 1);
    }

    return true;
}
DNA_Class::MutateTranslocation(float multiplier)
{
    BASICMUTATIONWORK(Translocation)
    {
        unsigned int TranslocationLength = 0;
        
        int x = 0;
        while(TranslocationLength == 0)
        {
            TranslocationLength = (unsigned int)fabs(Gauss(Mutables.Translocation.StdDev,
                                                           Mutables.Translocation.Mean));
            if(++x > 100)
                TranslocationLength = 1;
        }

        if (TranslocationLength == (unsigned int)length())
            TranslocationLength = length();

        unsigned int location = frnd(0, length() - TranslocationLength);

        Translocate(location, location + TranslocationLength - 1);
    }
    return true;
    
}

DNA_Class::MutateInsertion(float multiplier)
{
    BASICMUTATIONWORK(Insertion)
    {
        unsigned int InsertLength = 0;

        unsigned int x = 0;
        while(InsertLength == 0)
        {
            InsertLength = (unsigned int)fabs(Gauss(Mutables.Insertion.StdDev,
                                                    Mutables.Insertion.Mean));
            if(++x > 100)
                InsertLength = 1;
        }

        if (InsertLength == (unsigned int)length())
            InsertLength = length();

        vector<block> temp;
        block RND;
        for(x = 0; x < InsertLength; x++)
        {
            RND.RandomizeTipo();
            RND.RandomizeValue();
            temp.push_back(RND);
        }

        unsigned int location = frnd(0, length() - 1);

        Code.insert(Code.begin() + location + 1, InsertLength, block());

        for(x = 0; x < InsertLength; x++)
        {
            Code[location + x] = temp[x];
        }
    }    
}
DNA_Class::MutateAmplification(float multiplier)
{
    BASICMUTATIONWORK(Amplification)
    {
        unsigned int AmpLength = 0;

        unsigned int x = 0;
        while(AmpLength == 0)
        {
            AmpLength = (unsigned int)fabs(Gauss(Mutables.Amplification.StdDev,
                                                 Mutables.Amplification.Mean));
            if(++x > 100)
                AmpLength = 1;
        }

        if (AmpLength == (unsigned int)length())
            AmpLength = length();

        unsigned int location = frnd(0, length() - AmpLength);

        vector<block> temp;

        for(x = location; x < location + AmpLength; x++)
            temp.push_back(Code[location]);

        location = frnd(0, length() - 1);

        Code.insert(Code.begin() + location + 1, AmpLength, block());
        for(unsigned int z = location, y = 0; z < AmpLength + location; z++, y++)
            Code[z] = temp[y];
    }    
}
DNA_Class::MutateDeletion(float multiplier)
{
    BASICMUTATIONWORK(Deletion)
    {
        unsigned int DeleteLength = 0;
        
        int x = 0;
        while(DeleteLength == 0)
        {
            DeleteLength = (unsigned int)fabs(Gauss(Mutables.Deletion.StdDev,
                                                    Mutables.Deletion.Mean));
            if(++x > 100)
                DeleteLength = 1;
        }

        if (DeleteLength >= (unsigned int)length())
            DeleteLength = length();

        unsigned int location = frnd(0, length() - DeleteLength);

        Delete(location, location + DeleteLength - 1);
    }
    return true;
}