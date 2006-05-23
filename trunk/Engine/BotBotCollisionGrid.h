#ifndef AFX_BOTBOTCOLLISIONGRID_H__A6803755_21F8_4F9B_8D92_6D24D9A1E4DA__INCLUDED_
#define AFX_BOTBOTCOLLISIONGRID_H__A6803755_21F8_4F9B_8D92_6D24D9A1E4DA__INCLUDED_

#include <iostream>
#include <vector>
#include <list>
#include "../Common/Vectors.h"
class Robot;

#pragma warning(disable : 4786) //disable warnings about symbol length needing to be truncated

using namespace std;

class BotBotCollisionGrid  
{
    private:
    // Grid 1: 64 x 64 grid squares (Roughly 1687500 grid squares at largest sim size)
    // Grid 2: 128 x 128 grid squares (Roughly 421875 grid squares at largest sim size)
    // Grid 3: 256 x 256 grid squares (Roughly 104469 grid squares at largest sim size)
    // Grid 4: 512 x 512 grid squares (Roughly 26368 grid squares at largest sim size)
    //
    // Master Grid - A single grid square to cover the entire world
    vector< vector< list< Robot *> > > Grid1;
    vector< vector< list< Robot *> > > Grid2;
    vector< vector< list< Robot *> > > Grid3;
    vector< vector< list< Robot *> > > Grid4;
    list <Robot*> MasterGrid;

    void SetupLevel(vector< vector< list< Robot* > > > &Grid, Vector3i Dimensions, int GridSize);
    
    public:
	
    BotBotCollisionGrid();
	virtual ~BotBotCollisionGrid();

    void Insert(Robot *bot);

    void Setup(Vector3i Dimensions);

};

#endif // !defined(AFX_BOTBOTCOLLISIONGRID_H__A6803755_21F8_4F9B_8D92_6D24D9A1E4DA__INCLUDED_)
