#include "../Common/Math3D.h"
#include "Robot.h"

using namespace Math3D;

const float TanLookup[5] = {
0.0874886635f,
0.2679491924f,
0.4663096582f,
0.7002075382f,
1.0000000000f};

void Robot::FacingSun()
{
	//this function only checks for /Direct/ light sources.  Scattered light isn't looked at
	float lightfrompond;
	float depth;

	depth = (this->pos.y() / 2000) + 1;
	if (depth < 1) depth = 1;

	lightfrompond = SimOpts.LightIntensity / pow(depth, SimOpts.Gradient) * SimOpts.Daytime;

	(*this)[SUNsys] = iceil((SimOpts.LightIntensity + SimOpts.NrgCyc) * sin(aim));

	//we don't see negative brightness if we look downwards, we see 0.
	if ((*this)[SUNsys] < 0)
		(*this)[SUNsys] = 0;
}

//call this function when you flag a collision
//this is really slow:
//1 square root and 2 arctans taken
void Robot::Touch(Robot *other, float distance)
{
	Vector4 dpos;
	float angle;
	float hitstrength;

	dpos = other->pos - this->pos;
	dpos /= distance;
	//dpos is now the angle unit vector

	/////////////////////////////
	angle = this->aimvector * dpos;

	if (angle > 0)
		angle = atan((this->aimvector % dpos) / angle);
	else
		angle = atan((this->aimvector % dpos) / angle) + PI;

	if (angle < 0)
		angle = angle + 2*PI;

	(*this)[HitAngsys] = iceil(angle * 200);

	////////////////////////////////

	angle = other->aimvector * dpos;

	if (angle > 0)
		angle = atan((other->aimvector % dpos) / angle);
	else
		angle = atan((other->aimvector % dpos) / angle) + PI;

	if (angle < 0)
		angle = angle + 2*PI;

	(*other)[HitAngsys] = iceil(angle * 200);
	
	///////////////////////////////

	hitstrength = Length3((other->pos - other->opos) - (this->pos - this->opos));

	(*this)[hit] = iceil(hitstrength * other->mass);
	(*other)[hit] = iceil(hitstrength * this->mass);
}

/*void Robot::Taste()
{
	




}

' taste: same as for touch, but for shots, and gives back
' also the flavour of the shot, that is, its shottype
' value
Public Sub taste(A As Integer, ByVal x As Long, ByVal y As Long, value As Integer)
  Dim xc As Single
  Dim yc As Single
  Dim dx As Single
  Dim dy As Single
  Dim tn As Single
  Dim ang As Single
  Dim aim As Single
  Dim dang As Single
  aim = 6.28 - rob(A).aim
  xc = rob(A).pos.x
  yc = rob(A).pos.y
  dx = x - xc
  dy = y - yc
  If dx <> 0 Then
    tn = dy / dx
    ang = Atn(tn)
    If dx < 0 Then ang = ang - 3.14
  Else
    ang = 1.57 * Sgn(dy)
  End If
  dang = ang - aim
  While dang < 0
    dang = dang + 6.28
  Wend
  While dang > 6.28
    dang = dang - 6.28
  Wend
  If dang > 5.49 Or dang < 0.78 Then rob(A).mem(shup) = value
  If dang > 2.36 And dang < 3.92 Then rob(A).mem(shdn) = value
  If dang > 0.78 And dang < 2.36 Then rob(A).mem(shdx) = value
  If dang > 3.92 And dang < 5.49 Then rob(A).mem(shsx) = value
  rob(A).mem(209) = dang * 200  'sysvar = .shang just returns the angle of the shot without the flavor
  rob(A).mem(shflav) = value    'sysvar = .shflav returns the flavor without the angle
End Sub
*/

void Robot::EraseSenses()
{
    int x;
	(*this)[HitAngsys] = 0;
	(*this)[shangsys] = 0;
	(*this)[shflav] = 0;

	(*this)[edgesys] = 0;
	for (x = 0; x < 10; x++)
	{
		(*this)[456 + x] = 0;
		(*this)[trefxpos + x] = 0;
	}
	(*this)[trefxpos] = 0;
    (*this)[trefbody] = 0;

	for (x = EyeStart; x <= EyeEnd; x++)
		(*this)[x] = 0;
	
	this->lastopp = NULL;
}

//returns a pointer to the robot in lastopp
Robot *Robot::BasicProximity()
{
	for (int counter = 0; counter <= MaxRobs; counter++)
	{
		if (rob[counter] != this)
			CompareRobots(rob[counter], 12);
	}

	return this->lastopp;
}

void Robot::WriteSenses()
{
	FacingSun();
	if (BasicProximity() != NULL)
		WriteRefVars(this->lastopp);

	(*this)[energy] = iceil(this->nrg);
	(*this)[pain] = iceil(onrg - nrg);
    (*this)[pleas] = iceil(nrg - onrg);
    (*this)[bodloss] = iceil(obody - Body);
    (*this)[bodgain] = iceil(Body - obody);
    onrg = nrg;
    obody = Body;

	if (SimOpts.Daytime == true) (*this)[daytime] = 1;
	else (*this)[daytime] = 0;

}

//' copies the occurr array of a viewed robot
//' in the ref* vars of the viewing one
void Robot::WriteRefVars(const Robot *lastopp)
{
 	for(unsigned int t = 1; t<=8; t++)
		(*this)[occurrstart + t] = lastopp->occurr[t];

	(*this)[occurrstart + 9] = iceil(lastopp->nrg);
	(*this)[occurrstart + 10]= iceil(lastopp->age);

	(*this)[in1] = (*lastopp)[out1];
	(*this)[in2] = (*lastopp)[out2];
	(*this)[in3] = (*lastopp)[out3];
	(*this)[in4] = (*lastopp)[out4];
	(*this)[in5] = (*lastopp)[out5];
	(*this)[refaim] = (*lastopp)[Aimsys];
	(*this)[reftie] = lastopp->occurr[9];
	(*this)[refshell] = iceil(lastopp->Shell);
	(*this)[refbody] = iceil(lastopp->Body);
	(*this)[refxpos] = (*lastopp)[xpos];
	(*this)[refypos] = (*lastopp)[ypos];

	(*this)[refpoison] = (*lastopp)[poison];
	(*this)[refvenom] = (*lastopp)[venomsys];
	(*this)[refkills] = iceil(lastopp->Kills);

	if (lastopp->Multibot == true)
		(*this)[refmulti] = 1;
	else
		(*this)[refmulti] = 0;

	if ((*this)[memloc] >= 1 && (*this)[memloc] <= 1000)
		(*this)[memval] = (*lastopp)[(*this)[memloc]];

	if (lastopp->Fixed == true)
		(*this)[reffixed] = 1;
	else
		(*this)[reffixed] = 0;

	//these should be double checked
    Vector4 vel = (lastopp->pos - lastopp->opos) - (this->pos - this->opos);
	(*this)[refvelup] = iceil(vel * this->aimvector);
	(*this)[refveldn] = iceil((*this)[refvelup] * -1);
	
	//these should be double checked
	(*this)[refveldx] = iceil(this->aimvector % vel);
	(*this)[refvelsx] = iceil((*this)[refveldx] * -1);

	(*this)[refvelscalar] = iceil(sqrt((*this)[refvelup] * (*this)[refvelup] +
                                       (*this)[refveldx] * (*this)[refveldx]));
}

void Robot::occurrList()
{
	unsigned int x;

	for(x = 1; x<=12;x++)
		this->occurr[x] = 0;

	/********************************************
	Go through DNA and increase the occurr list
	*********************************************/

	
	for(x = mystart; x<= myend; x++)
		(*this)[x] = occurr[x - mystart + 1];
}

/*
    While Not (.DNA(t).tipo = 10 And .DNA(t).value = 1)
      
      If .DNA(t).tipo = 0 Then 'number
        If .DNA(t).value < 8 And .DNA(t).value > 0 Then 'if we are dealing with one of the first 8 sysvars
          If .DNA(t + 1).tipo = 7 Then 'DNA is going to store to this value, so it's probably a sysvar
            .occurr(.DNA(t).value) = .occurr(.DNA(t).value) + 1 'then the occur listing for this fxn is incremented
          End If
        End If
      End If
      
      If .DNA(t).tipo = 1 Then '*number
        If .DNA(t).value > 500 And .DNA(t).value < 510 Then 'the bot is referencing an eye
          .occurr(8) = .occurr(8) + 1 'eyes
        End If
      
        If .DNA(t).value = 330 Then 'the bot is referencing .tie
          .occurr(9) = .occurr(9) + 1 'ties
        End If
      
        If .DNA(t).value = 826 Or .DNA(t).value = 827 Then 'referencing either .strpoison or .poison
          .occurr(10) = .occurr(10) + 1   'poison controls
        End If
      
        If .DNA(t).value = 824 Or .DNA(t).value = 825 Then 'refencing either .strvenom or .venom
          .occurr(10) = .occurr(11) + 1   'venom controls
        End If
      End If
      
      t = t + 1
    Wend
exitwhile:
    
    'this is for when two bots have identical eye values in the league
    If n = 11 Then Record_11eyes .occurr(8)
    If n >= 16 And n <= 20 And LeagueMode Then League_Eyefudge n, t
    
    'creates the "ownvars" our own readbacks as versions of the refvars seen by others
  End With
End Sub
*/

/********************************************
field's default value is 12 from the VB days
********************************************/
void Robot::CompareRobots(Robot *const other, const unsigned int field)
{
//the few lines below are the most performance-critical in the whole code

    if (other == NULL) return; //must be first to avoid unnecessary inits

    Vector4 RelativePosition = VectorSub2D(other->pos, this->pos);
	float discheck = field * RobSize + other->radius;
	if (fabs(RelativePosition.x())>discheck || fabs(RelativePosition.y())>discheck)
        return;
	
//END extremely critical section

    
    
    float magsquare = LengthSquared3(RelativePosition);
    discheck = discheck * discheck;

	if (magsquare >= discheck)
		return; //too far away to see
		
    float mag = 1.0f / sqrtf(magsquare);

    unsigned int eyecellD, eyecellC;
    Vector4 ac, ad;
	//ac and ad are to either end of the bot, while ab is to the center
	//|ac| = |ad| = |ab|

	
	//this vector fun below needs to be double checked for geometrical accuracy
	ac = RelativePosition * mag;
	
	ad.set(ac.y(), -ac.x());
	ad = RelativePosition + ad * other->radius;

	ac.set(-ac.y(), ac.x());
	ac = RelativePosition + ac * other->radius;

	eyecellD = EyeCells(ad);
	eyecellC = EyeCells(ac);

	//bot is not visible
	if (eyecellD == 0 && eyecellC == 0)
		return;
	
	if (eyecellC == 0)
		eyecellC = EyeStart + 9;

	if (eyecellD == 0)
		eyecellD = EyeStart + 1;

	for (int x = eyecellD; x <= eyecellC; x++)
	{
		discheck = RobSize * 100 * mag;
		if ((*this)[x] < discheck)
		{
			if (x == EyeStart + 5)
				this->lastopp = other;

			(*this)[x] = iceil(discheck);
		}
	}
}

unsigned int Robot::EyeCells(const Vector4 &ab)
{
	float tantheta;
	int sign;
	int A;
  
	tantheta = (ab * this->aimvector);
	
	//check for visibility
	if (tantheta <= 0)
		return 0;
	
	tantheta = (ab % this->aimvector) / tantheta;
    if (fabs(tantheta) > 1.0f)
		return 0;
		
	if (tantheta > 0.0f)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
		tantheta = -tantheta;
	}

	for (A = 0; A <= 4; A++)
	{
		if (tantheta < TanLookup[A]) //haha!  it's visible
			return EyeStart + 5 - sign * A;
	}

	return 0;
}
