#include "Tie.h"
#include "Vectors.h"

void Tie::LengthConstraints()
{
    Vector3f dir = this->Sender()->pos - this->Receiver()->pos;
    float curr = dir.Length();
    float delta = curr - this->NaturalLength;
    
    dir /= curr;
    dir *= delta;
    
    this->sender->pos += dir / 2;
    this->receiver->pos -= dir / 2;
}

//sets bots' velocities to be consistant with their ties.
//be sure that ovel is set to vel right before calling all these
//routines, so each iteration uses the same information.
void Tie::VelocityConstraints()
{
    Vector3f dir = this->Sender()->pos - this->Receiver()->pos;
    dir.Normalize();
    
    float ParallelVelS = Sender()->ovel * dir;
    float ParallelVelR = Receiver()->ovel * dir;
    
    float ParallelVel = (ParallelVelS * Sender()->mass + ParallelVelR * Receiver()->mass) / 
                            (Sender()->mass + Receiver()->mass);
    
    sender->vel += (ParallelVel - ParallelVelS) * dir;
    receiver->vel += (ParallelVel - ParallelVelR) * dir;
}