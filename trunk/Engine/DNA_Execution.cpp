#include "DNA_Execution.h"
#include "EngineThread.h"
#include "DNADebugFlowControls.h"

//the conditions stack
BoolStack condStack;

//the integer stack
intstack_type IntStack;

//the current state (DNA executes based on a sort of FSM)
FlowType CurrentFlow;

//wether we execute BODY or ELSE statements
bool CurrentCondFlag;

Robot *currbot;
unsigned long currgene;

/*********************************************
FUNCTION PROTOTYPES
************************************************/

bool ExecuteFlowCommands(int n);
void ExecuteBasicCommand(int n);
void ExecuteAdvancedCommand(int n);
void ExecuteBitwiseCommand(int n);
void ExecuteStores(int n);
void ExecuteTies(int n);
void ExecuteConditions(int n);
void ExecuteLogic(int n);

//'''''''''''''''''''''''''''''''''''''''''''''''''
//'''''''''''handle the stacks ''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''''''''

__int32 StackCeil(float value)
{
    if (value < -2147483647.0f)
        return -(signed)2147483647;
    else if (value > 2147483647.0f)
        return 2147483647;
    else
        return (__int32)value;
}

//intstack.pos points to the Least Upper Bound element of the stack
void PushIntStack(__int32 value)
{
    IntStack.push_back(value);
}

__int32 PopIntStack(void)
{
    if(IntStack.empty())
        return 0;
    else
    {    __int32 returnme = IntStack.back();
        IntStack.pop_back();
        return returnme;
    }
}

//////////////////////////////////////////////
///////////// BoolStack class ////////////////
//////////////////////////////////////////////
void BoolStack::push(const bool& value)
{
    val.push_back(value);
}

bool BoolStack::pop()
{
    if(val.empty())
        return true; //this should never happen
    else
    {   bool returnme = val.back();
        val.pop_back();
        return returnme;
    }
}

bool BoolStack::Addup()
{
    bool returnme = true;
    while(!val.empty())
    {
        returnme = returnme && val.back();
        val.pop_back();
    }
    return returnme;
}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

void DNA_Class::Execute(Robot* bot)
{
    assert(bot != NULL && "Attempting to execute DNA that belongs to a non existant robot");
    assert(this != NULL && "Attempting to execute non existant DNA");
    assert(this->Code.size() > 0 && "Attempting to execute 0 length DNA");
    currbot=bot;
    currgene = 0;
    CurrentCondFlag = NEXTBODY;
    CurrentFlow = CLEAR;
    
    while(!IntStack.empty())
        IntStack.pop_back();
    
    unsigned long pointer=0;
    
    bool idle = false; //to tell the debugging controls that this was an idle step
    while(this->Code[pointer] != DNA_END)
    {    
        //DNA Debugging controls:
        if(CurrBotDebugControls.Bot() == bot)
            while(CurrBotDebugControls.Wait())
                EngineThread.sleep(0, 0);  //simple thread blocking
        
        switch (this->Code[pointer].tipo)
        {
            case btValue: //number
            {
                if (CurrentFlow != CLEAR)
                {   
                    PushIntStack (this->Code[pointer].value);
                    bot->ChargeNRG(SimOpts.Costs[btValue]);
                }
                else
                    idle = true;
                   
                break;
            }
            case btPointer:
            {
                if (CurrentFlow != CLEAR && this->Code[pointer].value > 0)
                {
                    __int16 loc = (this->Code[pointer].value - 1) % 1000 + 1;
                    PushIntStack(currbot->DNACommands.FilterRead(loc));
                    if (loc > EyeStart && loc < EyeEnd)
                        currbot->View = true;
                    bot->ChargeNRG(SimOpts.Costs[btPointer]);
                }
                else
                    idle = true;
                break;
            }
            
            case btBasicCommand:
            {
                if (CurrentFlow != CLEAR)
                {
                    ExecuteBasicCommand(this->Code[pointer].value);
                    bot->ChargeNRG(SimOpts.Costs[btBasicCommand]);
                }
                else
                    idle = true;
                break;
            }
            
            case btAdvancedCommand:
            {
                if (CurrentFlow != CLEAR)
                {
                    ExecuteAdvancedCommand(this->Code[pointer].value);
                    bot->ChargeNRG(SimOpts.Costs[btAdvancedCommand]);
                }
                else
                    idle = true;
                break;
            }
            
            case btBitwiseCommand:
            {
                if (CurrentFlow != CLEAR)
                {
                    ExecuteBitwiseCommand(this->Code[pointer].value);
                    bot->ChargeNRG(SimOpts.Costs[btBitwiseCommand]);
                }
                else
                    idle = true;
                break;
            }

            case btCondition:
            {
                if (CurrentFlow == COND)
                {
                    ExecuteConditions(this->Code[pointer].value);
                    bot->ChargeNRG(SimOpts.Costs[btCondition]);
                }
                else
                    idle = true;
                break;
            }

            case btLogic:
            {
                if (CurrentFlow == COND)
                {
                    ExecuteLogic(this->Code[pointer].value);
                    bot->ChargeNRG(SimOpts.Costs[btLogic]);
                }
                else
                    idle = true;
                break;
            }

            case btStores:
            {
                if (CurrentFlow == BODY || CurrentFlow == ELSEBODY)
                {
                    //costs calculated inside
                    ExecuteStores(this->Code[pointer].value);
                }
                else
                    idle = true;
                break;
            }

            case btTies:
            {
                if (CurrentFlow == BODY || CurrentFlow == ELSEBODY)
                {
                    ExecuteTies(Code[pointer].value);
                    currbot->ChargeNRG(SimOpts.Costs[btTies]);
                }
                else
                    idle = true;
                break;
            }

            case btFlow:
            {
                //execute flow command seeks forward until it finds executable DNA
                ExecuteFlowCommands(this->Code[pointer].value);

                currbot->ChargeNRG(SimOpts.Costs[btFlow]);
                currbot->DNACommands.Add(thisgene, (__int16)currgene);

                break;
            }

            case btMasterFlow:
            {
                //ONLY end exists at this point, so this is sort of pointless
                //later this will include things like codule headers, etc.
                //ExecuteMasterFlow(this->Code[pointer].value);
            }

            default:
                break;
        }
        
        pointer++;
        if(CurrBotDebugControls.Bot() == bot)
            CurrBotDebugControls.UpdatePosition(pointer, idle);
        idle = false;
    }
}


//''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''
//''''''''''''''''''''''''''''''''''''''''''

void DNAadd()
{
    //floats to handle overflows
    __int32 a;

    a = StackCeil(float(PopIntStack()) + float(PopIntStack()));
    PushIntStack(a);
}

void DNAsub()
{
    //floats to handle overflows
    __int32 a;

    a = StackCeil(float(-PopIntStack()) + float(PopIntStack()));
    PushIntStack(a);
}

void DNAmult()
{
    //floats to handle overflows
    __int32 a;

    a = StackCeil(float(PopIntStack()) * float(PopIntStack()));
    PushIntStack(a);
}

void DNAdiv()
{
    long a,b;

    b = PopIntStack();
    a = PopIntStack();

    if (b != 0)
        PushIntStack(a/b);
    else
        PushIntStack(0);
}

void DNArnd()
{
    PushIntStack(frnd(0, PopIntStack()));
}

void DNAderef()
{
    long b;

    b = PopIntStack();

    if (b > EyeStart && b < EyeEnd)
        currbot->View = true;

    if (b > 0)
        PushIntStack(currbot->DNACommands.FilterRead((__int16)((b - 1) % 1000 + 1)));
    else
        PushIntStack(0);
}

void DNAmod()
{
    long b;

    b = PopIntStack();

    if (b == 0)
    {
        PopIntStack();
        PushIntStack(0);
    }
    else
        PushIntStack(PopIntStack() % b);
}

void DNAsgn()
{
    if (PopIntStack() >= 0)
        PushIntStack(1);
    else
        PushIntStack(-1);
}

void DNAabs()
{
    PushIntStack(labs(PopIntStack()));
}

void DNAdup()
{
    long b;

    b = PopIntStack();
    PushIntStack(b);
    PushIntStack(b);
}

void ExecuteBasicCommand(int n)
{
    switch(n)
    {
        case 1:
        {
            DNAadd();      
            break;
        }
        case 2:
        {
            DNAsub();
            break;
        }
        case 3:
        {
            DNAmult();
            break;
        }
        case 4:
        {
            DNAdiv();
            break;
        }
        case 5:
        {
            DNArnd();
            break;
        }
        case 6:
        {
            DNAderef();
            break;
        }
        case 7:
        {
            DNAmod();
            break;
        }
        case 8:
        {
            DNAsgn();
            break;
        }
        case 9:
        {
            DNAabs();
            break;
        }
        case 10:
        {
            DNAdup();
            break;
        }
        default:
            break;
    }
}

//'''''''''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''''''''

//possibly buggy post C++ port
void findang()
{
    long a,b;
    float e;

    b = long(currbot->y()) - PopIntStack();
    a = long(currbot->x()) - PopIntStack();

    if (a == 0)
    {
        if (b < 0)
            e = 3/4*PI;
        else
            e = 0;
    }
    else
    {
        if (b < 0)
            e = atanf(float(b)/float(a)) + float(PI);
        else
            e = atanf(float(b)/float(a));
    }

    if (e < 0)
        e += 2*float(PI);

    if (e > 2 * PI)
        e -= 2.0f * float(PI);

    PushIntStack(StackCeil(e*200));
}

void finddist()
{
    float a,b,c;

    b = float(long(currbot->y()) - PopIntStack());
    a = float(long(currbot->x()) - PopIntStack());
    c = sqrtf(b*b+a*a);

    PushIntStack(StackCeil(c));
}

//'applies a ceiling to a value on the stack.
//'Usage: val ceilingvalue ceil.
void DNAceil()
{
    long a,b;

    b = PopIntStack();
    a = PopIntStack();

    if (a > b)
        PushIntStack(b);
    else
        PushIntStack(a);
}

void DNAfloor()
{
    long a,b;

    b = PopIntStack();
    a = PopIntStack();

    if (b > a)
        PushIntStack(b);
    else
        PushIntStack(a);    
}

void DNAsqr()
{
    float a = (float)PopIntStack();

    if (a > 0)
        PushIntStack(StackCeil(sqrtf(a)));
    else
        PushIntStack(0);
}

//'returns a power number. Raises a (top number) to the power of b (second number)
//possibly buggy post C++ port
void DNApow()
{
    double b = PopIntStack();
    double a = PopIntStack();
    
    double c = pow(b,a);

    PushIntStack(StackCeil(float(c)));
}

void DNApyth()
{
    float b = (float)PopIntStack();
    float a = (float)PopIntStack();

    float c = sqrtf(a*a+b*b);
    PushIntStack(StackCeil(c));
}

void ExecuteAdvancedCommand(int n)
{
    switch(n)
    {
        case 1:
            findang();
            break;
        case 2:
            finddist();
            break;
        case 3:
            DNAceil();
            break;
        case 4:
            DNAfloor();
            break;
        case 5:
            DNAsqr();
            break;
        case 6:
            DNApow();
            break;
        case 7:
            DNApyth();
            break;
        default:
            break;
    }
}

/*'''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''*/

void DNABitwiseCompliment()
{
    PushIntStack(~PopIntStack());
}

void DNABitwiseAND()
{
    __int32 a,b;
    
    b = PopIntStack();
    a = PopIntStack();
    
    PushIntStack(a & b);
}

void DNABitwiseOR()
{
    __int32 a,b;
    
    b = PopIntStack();
    a = PopIntStack();
    
    PushIntStack(a | b);
}
void DNABitwiseXOR()
{
    __int32 a,b;
    
    b = PopIntStack();
    a = PopIntStack();
    
    PushIntStack(a ^ b);   
}

void DNABitwiseINC()
{
    PushIntStack(PopIntStack()+1);
}

void DNABitwiseDEC()
{
    PushIntStack(PopIntStack()-1);
}

void DNABitwiseShiftLeft()
{
    __int32 a,b;

    b = PopIntStack();
    a = PopIntStack();

    PushIntStack(a << b);
}

void DNABitwiseShiftRight()
{
    __int32 a,b;

    b = PopIntStack();
    a = PopIntStack();

    PushIntStack(a >> b);
}

void ExecuteBitwiseCommand(int n)
{
    switch(n)
    {
        case 1:
            DNABitwiseCompliment();
            break;
        case 2:
            DNABitwiseAND();            
            break;
        case 3:
            DNABitwiseOR();
            break;
        case 4:
            DNABitwiseXOR();
            break;
        case 5:
            DNABitwiseINC();
            break;
        case 6:
            DNABitwiseDEC();
            break;
        case 7:
            PushIntStack(-PopIntStack());
            break;
        case 8: // <<
            DNABitwiseShiftLeft();
            break;
        case 9: // >>
            DNABitwiseShiftRight();      
            break;
        default:
            break;
    }
}

//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''

void ExecuteConditions(int n)
{
    bool cond = true;
    switch(n)
    {
        case 1: // <
            cond = (PopIntStack() > PopIntStack());
            break;
        case 2: // >
            cond = (PopIntStack() < PopIntStack());
            break;
        case 3: // =
            cond = (PopIntStack() == PopIntStack());
            break;
        case 4: // !=
            cond = (PopIntStack() != PopIntStack());
            break;
        case 5: //>=
            cond = (PopIntStack() >= PopIntStack());
            break;
        case 6: //<=
            cond = (PopIntStack() <= PopIntStack());
            break;
        default:
            break;
    }
    condStack.push(cond);
}


//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''

void ExecuteLogic(int n)
{
    bool b = condStack.pop();

    switch(n)
    {
        case 1: //and
            condStack.push( condStack.pop() && b );
            break;
        case 2: //or
            condStack.push( condStack.pop() || b );
            break;
        case 3: //xor
            condStack.push( condStack.pop() ^ b );
            break;
        case 4:
            condStack.push( !b );
            break;
        default:
            break;
    }
}

//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''

void DNAstore()
{
    __int32 b;

    b = PopIntStack();
    if (b > 0)
    {
        b = (b - 1) % 1000 + 1; //place into range 1-1000 if > 1000
        currbot->DNACommands.Add((__int16)b, (__int16)PopIntStack());
        currbot->ChargeNRG(SimOpts.Costs[btStores]); 
    }
    else
        PopIntStack();
}

void DNAinc()
{
    __int16 a;

    a = (__int16)PopIntStack();

    if (a > 0)
    {
        a = (a - 1) % 1000 + 1;
        currbot->DNACommands.Add((__int16)a, currbot->DNACommands.FilterRead(a) + 1);
        currbot->ChargeNRG(SimOpts.Costs[btStores] / 10); 
    }
}

void DNAdec()
{
    __int16 a;

    a = (__int16)PopIntStack();

    if (a > 0)
    {
        a = (a - 1) % 1000 + 1;
        currbot->DNACommands.Add((__int16)a, currbot->DNACommands.FilterRead(a) - 1);
        currbot->ChargeNRG(SimOpts.Costs[btStores] / 10); 
    }
}

void ExecuteStores(int n)
{
    switch(n)
    {
        case 1:
            DNAstore();
            break;
        case 2:
            DNAinc();
            break;
        case 3:
            DNAdec();
            break;
        default:
            break;
    }
}

//'''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''

void DNAsettie()
{
    long a;

    a = PopIntStack();

    if (a != 0)
        currbot->SetTie((__int16)a);
}

void DNAnexttie()
{
    PushIntStack(currbot->NextTie());
}

void DNAwritetie()
{
    if(currbot->CurrTie() != NULL)
    {
        long a, b;

        a = PopIntStack(); //location
        b = PopIntStack(); //number;

        a = (a - 1) % 1000 + 1;

        currbot->WriteTie((__int16)a, (__int16)b);
    }
    else
    {
        long a, b, c;

        a = PopIntStack();
        b = PopIntStack();
        c = PopIntStack();

        a = (a - 1) % 1000 + 1;

        currbot->WriteTie((__int16)a, (__int16)b, (__int16)c);
    }
}

void DNAreadtie()
{
    __int16 a, b = 0;
    
    if(currbot->CurrTie() != NULL)
    {
        a = __int16(PopIntStack()); //location
    }
    else
    {
        a = __int16(PopIntStack()); //location
        b = __int16(PopIntStack()); //tie num
    }

    a = (a - 1) % 1000 + 1; //put location in appropriate range

    currbot->ReadTie(a, b);
}

void ExecuteTies(int n)
{
    switch(n)
    {
        case 1:
            DNAsettie(); break;
        case 2:
            DNAnexttie(); break;
        case 3: //writetie
            DNAwritetie(); break;
        case 4: //readtie
            DNAreadtie(); break;
    }
}

//'''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''

bool ExecuteFlowCommands(int n)
{
    //returns true if a stop command was found (start, stop, or else)
    //returns false if cond was found

    if(n == 1)
    {
        CurrentFlow = COND;
        return false;
    }

    //assume a stop command, or it really is a stop command
    //this is supposed to come before case 2 and 3, since these commands
    //must be executed before start and else have a chance to go
    if (CurrentFlow == COND)
        CurrentCondFlag = condStack.Addup();
    CurrentFlow = CLEAR;

    if (n == 4) //stop
        return false;

    if (n == 2 && CurrentCondFlag == NEXTBODY)
        CurrentFlow = BODY;

    if (n == 3 && CurrentCondFlag == NEXTELSE)
        CurrentFlow = ELSEBODY;

    currgene++;
    return true;
}
