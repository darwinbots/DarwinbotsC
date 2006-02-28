#include "Tie.h"

using namespace Math3D;

// *PRIVATE* and only constructor
Tie::Tie(Robot *_sender,
         Robot *_receiver,
         int _port,
         float _k,
         float _b,
         int _type)

        :age(0),
        Sharing(false),
        Communicating(false),
        Feeding(false),
        k(_k),
        b(_b),
        sender(_sender),
        receiver (_receiver)
{
    NaturalLength = Math3D::Length3(sender->pos - receiver->pos);
}


//This function performs the necessary checks before creating a tie
//Note that it only inserts a ref to the created tie in sender's and receiver's TieList
//If it needs to be accessed immediately, use --TieList.end() just after the call to Tie::MakeTie
bool Tie::MakeTie(Robot* shooter, Robot* target, int _port)
{
	if (!shooter->canTie()||!target->canTie())
		return false;

	//insert slime defense check
	//insert deletion of old tie
	
	//create tie
	Tie* temp = new Tie(shooter, target, _port);
	
	//////////////////////////////////////////////////
	//Place pointers in the robots' respective lists//
	//////////////////////////////////////////////////
	
	shooter->addTie(temp);
	target->addTie(temp);

	return true;
}

//Before a tie can be deleted, it has to be removed from its sender's and receiver's tieList
Tie::~Tie()
{
    sender->Ties.remove(this);
    receiver->Ties.remove(this);
}

Robot *Tie::FindOther(Robot *me)
{
    if (sender == me)
        return receiver;
    else
        return sender;
}

__int16 Tie::ReadMem(Robot *me, __int16 loc)
{
    if (me == NULL)
        return 0;
    if (loc > 0)
        return (*FindOther(me))[(loc-1)%1000 + 1];

    return 0;
}

void Tie::WriteMem(Robot *me, __int16 loc, __int16 value)
{
    if (me == NULL)
        return;

    if (loc > 0)
        (*FindOther(me))[(loc - 1)%1000 + 1] = value;
    if (loc < 0)
        ;
}

//3.  tie joints
    //quite complicated

//4.  tie rotational drag
    //should be in my notebook - Numsgil

//5.  tie translational drag
    //should be in my notebook - Numsgil

//6.  tie constraints
    //ties cannot exceed some maximum length.  Later this will depend on
    //more factors, but at first a value of 1000 is fine.

//7.  tie hooke forces
    //F = -kx + bv

//8.  permanent tie sharing of a substance
//9.  tie feeding (either -6 or -1 type shots)

//  with transfer amount dependant on pumping strength
//  and cross sectional area of tie

void Tie::ShareSubstance(Robot *me, substance_ID ID, float amount)
{



}
