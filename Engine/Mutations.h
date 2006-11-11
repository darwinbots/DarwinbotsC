#ifndef MUTATIONS_H
#define MUTATIONS_H

#include <iostream>
#include <string>
#include <algorithm>

enum
{
    PointUP = 1,
    DeltaUP,
    CopyErrorUP,
    ReversalUP,
    TranslocationUP,
    InsertionUP,
    AmplificationUP,
    DeletionUP,
    MaxUP
};

struct MutationTypeInformationHolder
{
    unsigned long Prob;
    bool On;
    float Mean, StdDev;
    float DeltaValue; //used for Point and Copy Error

    MutationTypeInformationHolder::MutationTypeInformationHolder()
    {
        Prob = 1000000; // 1 in a million
        On = false;
        Mean = 0;
        StdDev = 1;
        DeltaValue = 80;
    }
};

class mutationprobs
{
    private:

    MutationTypeInformationHolder
        Point,
        Delta,
        CopyError,
        Reversal,
        Translocation,
        Insertion,
        Amplification,
        Deletion;
    bool On; //Are Global Mutations On or Off?

    public:
    mutationprobs::mutationprobs(bool on = false)
    {
        On = on;
    }

    bool GlobalMutationOn()
    {
        return On;
    }

    void SetGlobalMutations(bool set)
    {
        On = set;
    }

    MutationTypeInformationHolder *operator [] (unsigned int x)
    {
        switch(x)
        {
            case PointUP:
                return &Point;
            case DeltaUP:
                return &Delta;
            case CopyErrorUP:
                return &CopyError;
            case ReversalUP:
                return &Reversal;
            case TranslocationUP:
                return &Translocation;
            case InsertionUP:
                return &Insertion;
            case AmplificationUP:
                return &Amplification;
            case DeletionUP:
                return &Deletion;
            default:
                return NULL;
        }
    }
};

#endif //MUTATIONS_H
