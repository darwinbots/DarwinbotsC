#include "DNA_Execution.h"

#ifndef DB_NOGUI
#include "../GUI/GUIMain.h"
#include "../GUI/GUIBotDebug.h"
#include "EngineThread.h"
#endif


/*****************************************
TODO: be sure DNA costs are being exacted
******************************************/

//the conditions stack
BoolStack condStack;
const int BoolStack::BOOLSTACK_MAX = 20;

//the integer stack
intstack_type IntStack;

FlowType CurrentFlow;

bool CurrentCondFlag;

Robot* currbot;
unsigned long currgene;

/*********************************************
FUNCTION PROTOTYPES
************************************************/

bool ExecuteFlowCommands(int n);
void ExecuteBasicCommand(int n);
void ExecuteAdvancedCommand(int n);
void ExecuteBitwiseCommand(int n);
void ExecuteStores(int n);
void ExecuteConditions(int n);
void ExecuteLogic(int n);

//'''''''''''''''''''''''''''''''''''''''''''''''''
//'''''''''''handle the stacks ''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''''''''''''

__int32 StackCeil(float value)
{
    if (value < -2147483648.0f)
        return -(signed)2147483648;
    else if (value > 2147483647.0f)
        return 2147483647;
    else
        return (__int32)value;
}

//intstack.pos points to the Least Upper Bound element of the stack
void PushIntStack(__int32 value)
{
    if (IntStack.pos >= 21) //next push will overfill
    {
        for (int a = 0; a < 20; a++)
            IntStack.val[a] = IntStack.val[a+1];

        IntStack.val[20] = 0;
        IntStack.pos = 20;
    }

    IntStack.val[IntStack.pos] = value;
    IntStack.pos++;
}

__int32 PopIntStack(void)
{
    IntStack.pos--;

    if (IntStack.pos < 0)
    {
        IntStack.pos = 0;
        IntStack.val[0] = 0;
    }
#ifndef DB_NOGUI
    if (MainWindowHandle->BotDebug &&
        MainWindowHandle->BotDebug->DebugMode() &&
        currbot == MainWindowHandle->BotDebug->ThatBot())
    {
        __int32 temp = IntStack.val[IntStack.pos];
        IntStack.val[IntStack.pos] = 0;
        return temp;
    }
#endif
    return IntStack.val[IntStack.pos];
}

//////////////////////////////////////////////
///////////// BoolStack class ////////////////
//////////////////////////////////////////////
void BoolStack::push(const bool& value)
{
    val.push_front(value);
    if(val.size() > BOOLSTACK_MAX)
        val.pop_back();
}

bool BoolStack::pop()
{
    if ( this->val.empty() )
        return true;
    else
    {
        bool res = val.front();
        val.pop_front();
        return res;
    }
}

bool BoolStack::Addup()
{
    bool returnme = true;
    for(deque<bool>::iterator ptr=val.begin();ptr!=val.end();++ptr)
    {
        returnme = returnme && *ptr;
    }
    val.clear();
    return returnme;
}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

void DNA_Class::Execute(Robot* bot)
{
    currbot=bot;
    currgene = 0;
    CurrentCondFlag = NEXTBODY;

    IntStack.pos = 0;
    IntStack.val[0] = 0;
    
    unsigned long pointer=0;

    while(this->Code[pointer] != DNA_END)
    {
#ifndef DB_NOGUI
        if (MainWindowHandle->BotDebug &&
            MainWindowHandle->BotDebug->DebugMode() &&
            currbot == MainWindowHandle->BotDebug->ThatBot() &&
            (CurrentFlow != CLEAR || this->Code[pointer].tipo == btFlow))
        {
            //the below isn't thread safe, so there can be occassional display problems
            
            //1.  Tell the window where in the DNA we're executing
            MainWindowHandle->BotDebug->BotTargetInfo.DNA_pos = pointer;
            
            //2.  Update any information the Bot Debug window
            //      has about this bot

            MainWindowHandle->BotDebug->BotTargetInfo.Initialize(currbot);
            MainWindowHandle->BotDebug->BotTargetInfo.Update(currbot);
            MainWindowHandle->BotDebug->Update();

            //if this->Code[pointer].tipo == 0 || 1, we need to add that entry
            //to the interesting sysvars list
            if(this->Code[pointer].tipo == btPointer || 
               (this->Code[pointer].tipo == btValue &&
               this->Code[pointer+1].tipo == btStores))
            {
                MainWindowHandle->BotDebug->AddInterestingSysvars(
                    this->Code[pointer].value);
            }

            //3.  Wait for user info on wether to continue or wait
            EngineThread.sleep(0, 100000000);
        }
#endif
        switch (this->Code[pointer].tipo)
        {
            case btValue: //number
            {
                if (CurrentFlow != CLEAR)
                    PushIntStack (this->Code[pointer].value);
                break;
            }
            case btPointer:
            {
                if (CurrentFlow != CLEAR && this->Code[pointer].value > 0 &&
                                            this->Code[pointer].value <= 1000)
                {
                    PushIntStack ((*currbot)[this->Code[pointer].value]);
                    if (this->Code[pointer].value > EyeStart && 
                        this->Code[pointer].value < EyeEnd)
                            currbot->View = true;
                }
                break;
            }
            
            case btBasicCommand:
            {
                if (CurrentFlow != CLEAR)
                    ExecuteBasicCommand(this->Code[pointer].value);
                break;
            }
            
            case btAdvancedCommand:
            {
                if (CurrentFlow != CLEAR)
                    ExecuteAdvancedCommand(this->Code[pointer].value);
                break;
            }
            
            case btBitwiseCommand:
            {
                if (CurrentFlow != CLEAR)
                    ExecuteBitwiseCommand(this->Code[pointer].value);
                break;
            }

            case btCondition:
            {
                if (CurrentFlow == COND)
                    ExecuteConditions(this->Code[pointer].value);
                break;
            }

            case btLogic:
            {
                if (CurrentFlow == COND)
                    ExecuteLogic(this->Code[pointer].value);
                break;
            }

            case btStores:
            {
                if (CurrentFlow == BODY || CurrentFlow == ELSEBODY)
                    ExecuteStores(this->Code[pointer].value);
                break;
            }

            case btReserved:
            {
                //reserved for later type
                break;
            }

            case btFlow:
            {
                //execute flow command seeks forward until it finds executable DNA
                ExecuteFlowCommands(this->Code[pointer].value);

                //'If .VirusArray(currgene) > 1 Then 'next gene is busy, so clear flag
                //'  CurrentFlow = CLEAR
                //'End If

                (*currbot)[thisgene] = (__int16)currgene;

                break;
            }

            case btMasterFlow:
            {
                //ONLY end exists at this point, so this is sort of pointless
                //ExecuteMasterFlow(this->Code[pointer].value);
            }

            default:
                break;
        }
        
        pointer++;
    }

    for(int x = 0; x < 20; x++)
        IntStack.val[x] = 0;
    
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

    if (b >= 1 && b <= 1000)
        PushIntStack((*currbot)[b]);
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
            e = atanf(b/a) + PI;
        else
            e = atanf(b/a);        
    }

    if (e < 0)
        e += 2*PI;

    if (e > 2 * PI)
        e -= 2 * PI;

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
    if (b > 0 && b <= 1000)
        (*currbot)[b] = __int16(PopIntStack());
    else
        PopIntStack();
}

void DNAinc()
{
    long a;

    a = PopIntStack();

    if (a > 0 && a <= 1000)
        (*currbot)[a]++;
}

void DNAdec()
{
    long a;

    a = PopIntStack();

    if (a > 0 && a <= 1000)
        (*currbot)[a]--;
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

bool ExecuteFlowCommands(int n)
{
    //'returns true if a stop command was found (start, stop, or else)
    //'returns false if cond was found

    switch(n)
    {
        case 1:
        {
            CurrentFlow = COND;
            return false;
        }
        case 2:
        case 3:
        case 4:
        {
            //'assume a stop command, or it really is a stop command
            //'this is supposed to come before case 2 and 3, since these commands
            //'must be executed before start and else have a chance to go
            if (CurrentFlow == COND)
                CurrentCondFlag = condStack.Addup();
            CurrentFlow = CLEAR;

            switch(n)
            {
                case 2:
                {
                    if (CurrentCondFlag == NEXTBODY)
                        CurrentFlow = BODY;
                    currgene++;
                }break;
                case 3:
                {
                    if (CurrentCondFlag == NEXTELSE)
                        CurrentFlow = ELSEBODY;
                    currgene++;
                }break;
            }
            return true;
        }
        default:
            break;
    }

    return false;
}

/*'''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''
'''''''''''''''''''''''''''''''''''''''''''

'
'   L O A D I N G   A N D   P A R S I N G
'

' root of the dna execution part
' takes each robot and passes it to the interpreter
' with some variations for console debug and genes activation
Public Sub ExecRobs()
  Dim t As Integer
  For t = 1 To MaxRobs
    If rob(t).Exist And Not rob(t).Wall And Not rob(t).Corpse Then
      ExecuteDNA t
    'rob(t).pntr = 1
    'If Not (rob(t).console Is Nothing) Then
    '  rob(t).console.textout ""
    '  rob(t).console.textout "robot genes execution: - =not executed"
    '  eseguidebug t
    'Else
    '  If t = robfocus Then
    '    If ActivForm.Visible Then
    '      exechighlight t
    '    Else
    '      eseguirob2 t
    '    End If
    '  Else
    '    eseguirob2 t
    '  End If
    'End If
    End If
  Next t
End Sub
*/
