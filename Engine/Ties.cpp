#include "../Common/Math3D.h"
#include "Robot.h"
#include "Tie.h"

using namespace Math3D;

bool Tie::MakeTie(Robot *sender, Robot *reciever, int port)
{
	Tie *next;
	Vector4 deltapos;

	//can't tie to dead bots
	if (sender->Corpse == true || reciever->Corpse == true)
		return false;

	//no room in the tie arrays of the bots
	if (sender->numties > 10 || reciever->numties > 10)
		return false;

	//insert slime defense check
	//insert deletion of old tie
	
	NaturalLength = Length3((sender->pos - reciever->pos));

	Sharing = Communicating = Feeding = false;

	this->Port = port; //set the port number
	this->age = 0;

	//default k and b values:
	this->b = 0.01f;
    this->k = 0.005f;

	this->type = 0;
	this->next = NULL;
	
	//////////////////////////////////////////////////
	//Place pointers in the robots' respective lists//
	//////////////////////////////////////////////////
	
	next = &sender->HeadTie;
	while(next->next != NULL)
		next = next->next;
	
	//next is now the last tie in the list
	
	next->next = this;
	next = next->next;

	next = &reciever->HeadTie;
	while(next->next != NULL)
		next = next->next;
	
	//next is now the last tie in the list
	
	next->next = this;
	next = next->next;
	///////////////////////////////////////////////////
	
	this->sender = sender;
	this->reciever = reciever;

	return false;
}/*
    
    While rob(A).Ties(k).pnt > 0 And k <= max And ok
      k = k + 1
    Wend
    While rob(b).Ties(j).pnt > 0 And j <= max And ok
      j = j + 1
    Wend
    
    If k < max And j < max And ok Then
      rob(A).Ties(k).pnt = b
      rob(A).Ties(k).ptt = j
      rob(A).Ties(k).NaturalLength = length
      rob(A).Ties(k).stat = False
      rob(A).Ties(k).last = last
      rob(A).Ties(k).Port = mem
      rob(A).Ties(k).back = False
      rob(A).Numties = rob(A).Numties + 1
      rob(b).Ties(j).pnt = A
      rob(b).Ties(j).ptt = k
      rob(b).Ties(j).NaturalLength = length
      rob(b).Ties(j).stat = False
      rob(b).Ties(j).last = last
      rob(b).Ties(j).Port = mem
      rob(b).Ties(j).back = True
      rob(b).Numties = rob(b).Numties + 1
      
    End If
  End If
  
  If rob(b).Slime > 0 Then rob(b).Slime = rob(b).Slime - 20
  If rob(b).Slime < 0 Then rob(b).Slime = 0 'cost to slime layer when attacked
  rob(A).nrg = rob(A).nrg - SimOpts.Costs(TIECOST) / (rob(A).Numties + 1) 'Tie cost to form tie
	





}*/


