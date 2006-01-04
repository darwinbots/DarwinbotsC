#include "DNAClass.h"
#include "Robot.h"

/*****************************************
TODO: be sure DNA costs are being exacted
******************************************/

//the conditions stack
struct boolstack_type
{
    bool val[21];
    int pos;
}Condst;

//the integer stack
struct intstack_type
{
    __int32 val[21];
    int pos;
}IntStack;

enum
{
    CLEAR,
    COND,
    BODY,
    ELSEBODY
}CurrentFlow;

bool CurrentCondFlag;
const bool NEXTBODY = true;
const bool NEXTELSE = false;

Robot *currbot;
unsigned long currgene;

/*********************************************
FUNCTION PROTOTYPES
************************************************/

bool ExecuteFlowCommands(int n);
bool AddupCond();
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
        return -2147483648;
    else if (value > 2147483647.0f)
        return 2147483647;
    else
        return value;
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

    return IntStack.val[IntStack.pos];
}

void PushBoolStack(bool value)
{
    if (Condst.pos >= 21) //next push will overfill
    {
        for (int a = 0; a < 20; a++)
            Condst.val[a] = Condst.val[a+1];

        Condst.val[20] = 0;
        Condst.pos = 20;
    }

    Condst.val[Condst.pos] = value;
    Condst.pos++;
}

int PopBoolStack(void)
{
    Condst.pos--;

    if (Condst.pos < 0)
    {
        Condst.pos = 0;
        return -5;
    }

    return Condst.val[Condst.pos];
}

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////

void Robot::ExecuteDNA()
{
    currbot = this;
    currgene = 0;
    CurrentCondFlag = NEXTBODY;
    
    IntStack.pos = 0;
    IntStack.val[0] = 0;

    if (this->DNA != NULL)
        this->DNA->Execute();
}

void DNA_Class::Execute()
{
    unsigned long pointer=0;

    while(this->Code[pointer] != DNA_END)
    {
        switch (this->Code[pointer].tipo)
        {
            case 0: //number            
            {
                if (CurrentFlow != CLEAR)
                    PushIntStack (this->Code[pointer].value);
                break;
            }
            case 1:
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
            
            case 2:
            {
                if (CurrentFlow != CLEAR)
                    ExecuteBasicCommand(this->Code[pointer].value);
                break;
            }
            
            case 3:
            {
                if (CurrentFlow != CLEAR)
                    ExecuteAdvancedCommand(this->Code[pointer].value);
                break;
            }
            
            case 4:
            {
                if (CurrentFlow != CLEAR)
                    ExecuteBitwiseCommand(this->Code[pointer].value);
                break;
            }

            case 5:
            {
                if (CurrentFlow == COND)
                    ExecuteConditions(this->Code[pointer].value);
                break;
            }

            case 6:
            {
                if (CurrentFlow == COND)
                    ExecuteLogic(this->Code[pointer].value);
                break;
            }

            case 7:
            {
                if (CurrentFlow == BODY || CurrentFlow == ELSEBODY)
                    ExecuteStores(this->Code[pointer].value);
                break;
            }

            case 8:
            {
                //reserved for later type
                break;
            }

            case 9:
            {
                //execute flow command seeks forward until it finds executable DNA
                ExecuteFlowCommands(this->Code[pointer].value);

                //'If .VirusArray(currgene) > 1 Then 'next gene is busy, so clear flag
                //'  CurrentFlow = CLEAR
                //'End If

                (*currbot)[thisgene] = currgene;

                break;
            }

            case 10:
            {
                //ONLY end exists at this point, so this is sort of pointless
                //ExecuteMasterFlow(this->Code[pointer].value);
            }

            default:
                break;
        }
        
        pointer++;
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
            e = atan(b/a) + PI;
        else
            e = atan(b/a);        
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
    c = sqrt(b*b+a*a);

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
    float a;

    a = PopIntStack();

    if (a > 0)
        PushIntStack(StackCeil(sqrt(a)));
    else
        PushIntStack(0);
}

//'returns a power number. Raises a (top number) to the power of b (second number)
//possibly buggy post C++ port
void DNApow()
{
    double a,b,c;

    b = PopIntStack();
    a = PopIntStack();
    
    c = pow(b,a);

    PushIntStack(StackCeil(c));
}

void DNApyth()
{
    float a,b,c;

    b = PopIntStack();
    a = PopIntStack();

    c = sqrt(a*a+b*b);
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

void Min()
{
    PushBoolStack(PopIntStack() > PopIntStack());
}

void magg()
{
    PushBoolStack(PopIntStack() < PopIntStack());
}

void equa()
{
    PushBoolStack(PopIntStack() == PopIntStack());
}

void diff()
{
    PushBoolStack(PopIntStack() != PopIntStack());
}

void minequal()
{
    PushBoolStack(PopIntStack() >= PopIntStack());
}

void maggequal()
{
    PushBoolStack(PopIntStack() <= PopIntStack());
}

void ExecuteConditions(int n)
{
    switch(n)
    {
        case 1:
            Min();
            break;
        case 2:
            magg();
            break;
        case 3:
            equa();
            break;
        case 4:
            diff();
            break;
        case 5: //>=
            maggequal();
            break;
        case 6: //<=
            minequal();
            break;
        default:
            break;
    }
}


//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''
//'''''''''''''''''''''''''''''''''''''''

void ExecuteLogic(int n)
{
    int a,b;
    
    b = PopBoolStack();
    
    if (b != 5) switch(n)
    {
        case 1: //and
            a = PopBoolStack();
            if (a != 5)
                PushBoolStack(a && b);
            else
                PushBoolStack(b && b);
            break;
        case 2: //or
            a = PopBoolStack();
            if (a != 5)
                PushBoolStack(a || b);
            else
                PushBoolStack(b || b);
            break;
        case 3: //xor
            a = PopBoolStack();
            if (a != 5)
                PushBoolStack((a ^ b) != 0);
            else
                PushBoolStack(b && b);
            break;
        case 4:
            PushBoolStack(b == 0);
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
                CurrentCondFlag = AddupCond();
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

bool AddupCond()
{
    int a;
    bool returnme=true;

    a = PopBoolStack();
    while(a != -5)
    {
        returnme = returnme && a;
        a = PopBoolStack();
    }

    return returnme;
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
