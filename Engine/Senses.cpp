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

	lightfrompond = SimOpts.LightIntensity / powf(depth, SimOpts.Gradient) * SimOpts.Daytime;

	(*this)[SUNsys] = iceil((SimOpts.LightIntensity) * sinf(aim));

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
		angle = atanf((this->aimvector % dpos) / angle);
	else
		angle = atanf((this->aimvector % dpos) / angle) + PI;

	if (angle < 0)
		angle = angle + 2*PI;

	(*this)[HitAngsys] = iceil(angle * 200);

	////////////////////////////////

	angle = other->aimvector * dpos;

	if (angle > 0)
		angle = atanf((other->aimvector % dpos) / angle);
	else
		angle = atanf((other->aimvector % dpos) / angle) + PI;

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
	if (this->View && BasicProximity() != NULL)
		WriteRefVars(this->lastopp);

	(*this)[energy] = iceil(this->nrg);
	(*this)[pain] = iceil(onrg - nrg);
    (*this)[pleas] = iceil(nrg - onrg);
    (*this)[bodloss] = iceil(obody - Body);
    (*this)[bodgain] = iceil(Body - obody);
    (*this)[Kills] = iceil((float)this->Kills);

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
	(*this)[occurrstart + 10]= iceil((float)lastopp->age);

	(*this)[in1] = (*lastopp)[out1];
	(*this)[in2] = (*lastopp)[out2];
	(*this)[in3] = (*lastopp)[out3];
	(*this)[in4] = (*lastopp)[out4];
	(*this)[in5] = (*lastopp)[out5];
    (*this)[in6] = (*lastopp)[out6];
    (*this)[in7] = (*lastopp)[out7];
    (*this)[in8] = (*lastopp)[out8];
    (*this)[in9] = (*lastopp)[out9];
    (*this)[in10] = (*lastopp)[out10];
	
    (*this)[refaim] = (*lastopp)[Aimsys];
	(*this)[reftie] = lastopp->occurr[9];
	(*this)[refshell] = iceil(lastopp->Shell);
	(*this)[refbody] = iceil(lastopp->Body);
	(*this)[refxpos] = (*lastopp)[xpos];
	(*this)[refypos] = (*lastopp)[ypos];

	(*this)[refpoison] = (*lastopp)[poison];
	(*this)[refvenom] = (*lastopp)[venomsys];
	(*this)[refkills] = iceil((float)lastopp->Kills);

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
    Vector4 vel = lastopp->vel - this->vel;
    Vector4 aim = aimvector;
    aim.set(aim.x(), -aim.y());
	(*this)[refvelup] = iceil(vel * this->aimvector);
	(*this)[refveldn] = -iceil(float((*this)[refvelup]));
	
	//these should be double checked
	(*this)[refveldx] = -iceil(this->aimvector % vel);
	(*this)[refvelsx] = -iceil(float((*this)[refveldx]));

    (*this)[refvelscalar] = iceil(sqrtf(float((*this)[refvelup] * (*this)[refvelup] +
                                        (*this)[refveldx] * (*this)[refveldx])));
}

void Robot::occurrList()
{
	unsigned int x;

	for(x = 1; x<=12;x++)
		this->occurr[x] = 0;

	this->DNA->Occurrs(this->occurr);
	
	for(x = mystart; x<= myend; x++)
		(*this)[x] = occurr[x - mystart + 1];
}



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
    
    float magsquare = LengthSquared3(RelativePosition);
    discheck = discheck * discheck;

	if (magsquare >= discheck)
		return; //too far away to see
		
    float mag = sqrtf(magsquare);
    
    unsigned int eyecellD, eyecellC;
    Vector4 ac, ad;
	
    //ac and ad are to either end of the bot, while ab is to the center
	//|ac| = |ad| = |ab|
	
	//this vector fun below needs to be double checked for geometrical accuracy
	ac = RelativePosition / mag;
	
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
		eyecellC = EyeEnd;

	if (eyecellD == 0)
		eyecellD = EyeStart;

	discheck = RobSize * 100 / (mag - this->rad() - other->rad() + RobSize);
    for (unsigned int x = eyecellD; x <= eyecellC; x++)
	{		
		if ((*this)[x] < discheck)
		{
			if (x == EyeMid)
				this->lastopp = other;

			(*this)[x] = iceil(discheck);
		}
	}

    for(x = 0; x < 5; x++)
        swap((*this)[EyeStart + x], (*this)[EyeEnd - x]);
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
			return EyeMid - sign * A;
	}

	return 0;
}