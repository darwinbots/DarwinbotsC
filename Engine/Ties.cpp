#include "Tie.h"

using namespace Math3D;

// *PRIVATE* and only constructor
Tie::Tie(Robot* _sender, Robot* _receiver, int _port,
                float _k , float _b, int _type)
        :age(0),Sharing(false),Communicating(false),Feeding(false),
            k(_k), b(_b), sender(_sender), receiver (_receiver)
        {NaturalLength = Math3D::Length3(sender->pos - receiver->pos);}


//This function performs the necessary checks before creating a tie
//Note that it only inserts a ref to the created tie in sender's and receiver's TieList
//If it needs to be accessed immediately, use --TieList.end() just after the call to Tie::MakeTie
bool Tie::MakeTie(Robot* _sender, Robot* _receiver, int _port)
{
	//can't tie to dead bots
	if (_sender->Corpse == true || _receiver->Corpse == true)
		return false;

	//no room in the tie arrays of the bots
	if (_sender->tieList.size() > 10 || _receiver->tieList.size() > 10)
		return false;

	//insert slime defense check
	//insert deletion of old tie
	
	//create tie
	Tie* temp = new Tie(_sender, _receiver, _port);
	
	//////////////////////////////////////////////////
	//Place pointers in the robots' respective lists//
	//////////////////////////////////////////////////
	
	//this causes the illegal operation - Numsgil
    _sender->tieList.push_back(temp);
	_receiver->tieList.push_back(temp);

	return true;
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

//Before a tie can be deleted, it has to be removed from its sender's and receiver's tieList
Tie::~Tie()
{
    sender->tieList.remove(this);
    receiver->tieList.remove(this);
}
