#include "../Common/Vectors.h"
#include "Tie.h"
#include "Robot.h"

// *PRIVATE* and only constructor
Tie::Tie(Robot *_sender,
         Robot *_receiver,
         int _phase
         )

        :age(0),
        Sharing(false),
        Communicating(false),
        Feeding(false),
        sender(_sender),
        receiver (_receiver)        
{
    NaturalLength = (sender->pos - receiver->pos).Length();
    this->Phase = _phase;
    SenderCQ.SetBase(sender);
    ReceiverCQ.SetBase(receiver);
}

//Before a tie can be deleted, it has to be removed from its sender's and receiver's tieList
Tie::~Tie()
{
    unsigned int x;
    for(x = 0; x < sender->Ties.size(); x++)
        if(sender->Ties[x] == this)
            sender->Ties[x] = NULL;

    for(x = 0; x < receiver->Ties.size(); x++)
        if(receiver->Ties[x] == this)
            receiver->Ties[x] = NULL;
}

bool Robot::FireTie()
{
	int tieport = (*this)[mtie];

	(*this)[mtie] = 0;	

	if (tieport > 0)
	{
        if(BasicProximity() != NULL)
		{
            if((this->pos - this->lastopp->pos).Length() - this->rad() - this->lastopp->rad() <= 
               RobSize)
                return Tie::MakeTie(this, lastopp, tieport);
        }
	}
	return false;
}

bool Robot::CanTie()
{
    return !Corpse && this != NULL;
};

void Robot::AddTie(Tie *tie)
{
    int loc = -1;

    for(int x = (int)Ties.size() - 1; x >= 0; x--)
        if(Ties[x] == NULL)
            loc = x;

    if(loc == -1)
        this->Ties.push_back(tie);
    else
        Ties[loc] = tie;
}
    
void Robot::RemoveTie(Tie* tie)
{
    delete tie;
}

void Robot::RemoveTie(Robot *other)
{
    for(unsigned int x = 0; x < Ties.size(); x++)
        if(Ties[x] != NULL && (Ties[x]->Sender() == other
                           ||  Ties[x]->Receiver() == other))
        {
            delete Ties[x];
        }
        
}

void Robot::RemoveAllTies()
{
    for(unsigned int x = 0; x < Ties.size(); x++)
        RemoveTie(Ties[x]);
}


//This function performs the necessary checks before creating a tie
//Note that it only inserts a ref to the created tie in sender's and receiver's TieList
//If it needs to be accessed immediately, use --TieList.end() just after the call to Tie::MakeTie
bool Tie::MakeTie(Robot *shooter, Robot *target, int _port)
{
	if (!(shooter->CanTie() && target->CanTie()))
		return false;

	//insert slime defense check
	shooter->RemoveTie(target);
    target->RemoveTie(shooter);
	
	//create tie
	Tie* temp = new Tie(shooter, target, _port);
	
	shooter->AddTie(temp);
	target->AddTie(temp);

	return true;
}

Robot *Tie::FindOther(Robot *me)
{
    if(this==NULL)
        return NULL;

    if (sender == me)
        return receiver;
    else
        return sender;
}

CommandQueueClass &Tie::FindOtherCQ(Robot *me)
{
    if(me == sender)
        return ReceiverCQ;
    else
        return SenderCQ;
}

__int16 Tie::ReadMem(Robot *me, __int16 loc)
{
    if (me == NULL)
        return 0;
    
    if (loc > 0)
        return FindOtherCQ(me).FilterRead((loc-1)%1000 + 1);

    return 0;
}

void Tie::WriteMem(Robot *me, __int16 loc, __int16 value)
{
    if (me == NULL)
        return;

    if (loc > 0)
        FindOtherCQ(me).Add((loc - 1)%1000 + 1, value);
    if (loc < 0)
        ShareSubstance(me, (substance_ID)((-loc - 1)%10 + 1), value);
}

//3.  tie joints
    //quite complicated

//4.  tie rotational drag
    //should be in my notebook - Numsgil

//5.  tie translational drag
    //should be in my notebook - Numsgil

//6.  tie constraints
    //set tie to natural tie length

#define FindMin(substance) __min(amount, Bot->substance)
void Tie::ShareSubstance(Robot *me, substance_ID ID, float amount)
{
    //Bot does the transfering, other recieves
    Robot *Bot, *other;
    
    if(amount == 0)
        return;
    if(age < 20) //"soft" ties must be capped at 1000 material per cycle
        amount = __min(1000, amount); 
    
    if(amount < 0)
    {
        Bot = FindOther(me);
        other = me;
        amount = -amount;
    }
    else
    {
        Bot = me;
        other = FindOther(me);
    }
    
    switch(ID)
    {
        case NRG_ID:
        {
            amount = FindMin(nrg);
            Bot->nrg -= amount;
            other->nrg += amount;
        }break;
        
        case SHELL_ID:
        {
            amount = FindMin(Shell);
            Bot->Shell -= amount;
            other->Shell += amount;
        }break;
        
        case VENOM_ID:
        {
            amount = FindMin(Venom);
            Bot->Venom -= amount;
            other->Venom += amount;
        }break;
        
        case WASTE_ID:
        {
            amount = FindMin(Waste);
            Bot->Waste -= amount;
            other->Waste += amount;
        }break;
        
        case POISON_ID:
        {
            amount = FindMin(Poison);
            Bot->Poison -= amount;
            other->Poison += amount;
        }break;
        
        case BODY_ID:
        {
            amount = FindMin(Body);
            Bot->Body -= amount;
            other->Body += amount;
        }break;
        
        case SLIME_ID:
        {
            amount = FindMin(Slime);
            Bot->Slime -= amount;
            other->Slime += amount;
        }break;
        
        default:
            return;
            break;
    }   
    
    this->Sharing = true;
}
#undef FindMin

void Tie::UpdateTie()
{
    this->age++;
    if(this->Phase < 0 && this->age >= 100)
        delete this;
}

void Robot::UpdateTies()
{
    for(unsigned int x = 0; x < Ties.size(); x++)
        if(Ties[x] != NULL)
            Ties[x]->UpdateTie();
}

__int16 Robot::NextTie()
{
    int max = (int)Ties.size();
    for(int x = max - 1; x >= 0; x--)
    {
        if(Ties[x] != NULL)
            max = x;
    }

    if(currtie <= 0)
    {
        if(max == 0)
            currtie = 0;
        else
        {
            do
            {
                currtie--;
                if(abs(currtie) >= max)
                    currtie = -1;
            }while(Ties[abs(currtie)] == NULL);
        }
    }
    else
    {
        //cycle to next phase

    }

    return currtie;
}

Tie *Robot::CurrTie()
{
    if(currtie < 0)
        return Ties[abs(currtie)];
    if(currtie > 0)
        return NULL;//return first tie with current phase
    return NULL;
}

void Robot::WriteTie(__int16 location, __int16 number, __int16 tienum)
{
    Tie *tie = NULL;

    if(tienum == 0)
        tienum = currtie;
    
    if(tienum < 0)
    {
        if(abs(tienum) < (int)Ties.size())
            Ties[abs(tienum)]->WriteMem(this, location, number);
    }

    if(tienum > 0)
    {
        for(unsigned int x = 0; x < Ties.size(); x++)
            if(Ties[x]->FindPhase() == tienum)
            {
                Ties[x]->WriteMem(this, location, number);
            }
    }
}

__int16 Robot::ReadTie(__int16 loc, __int16 tienum)
{
    long sum=0;
    int num=0;

    if(tienum == 0)
        tienum = currtie;

    if(tienum < 0)
    {
        if(abs(tienum) < (int)Ties.size())
            return Ties[abs(tienum)]->ReadMem(this, loc);
    }

    if(tienum > 0)
    {
        for(unsigned int x = 0; x < Ties.size(); x++)
            if(Ties[x]->FindPhase() == tienum)
            {
                sum += Ties[x]->ReadMem(this, loc);
                num++;
            }
    }

    return __int16(sum / num);
}

void Tie::ApplyCQ()
{
    SenderCQ.Apply();
    ReceiverCQ.Apply();
}

void Robot::ApplyNewTieSysvars()
{
    Tie *tie = CurrTie();

    if(tie != NULL)
    {
        DNACommands.Add(readtielen, (__int16)tie->FindVector().Length());
        DNACommands.Add(writetielen, DNACommands.FilterRead(readtielen));
        DNACommands.Add(tieangle, tie->FindAngle(this));
        DNACommands.Add(currtiesys, currtie);
    }

    else
    {
        DNACommands.Add(readtielen, 0);
        DNACommands.Add(writetielen, 0);
        DNACommands.Add(tieangle, 0); 
        DNACommands.Add(currtiesys, 0);
    }
}

Vector3f Tie::FindVector()
{
    return (sender->findpos() - receiver->findpos());
}

__int16 Tie::FindAngle(Robot *me)
{
    Vector3f unit = FindVector().Normal();

    //some magic vector math
    
    return 0;

}
