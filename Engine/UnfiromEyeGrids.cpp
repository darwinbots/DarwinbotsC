#include "Robot.h"

/*******************************
Basic idea:

Divide the world into 1440 sized grid cells that contain linked lists
of robot pointers.

For every robot that can see, put his pointer into all the grids'
linked list for every grid he can see.

During eye tests, check every bot against the cell(s) it's presently in
to see what bots can see it.  Since bots have radius and aren't just single points,
bots may need to test multiple 
*//////////////////////////////////////////

#define GRID_DIM 1440 //this is the eye sight range, which is capped here

class EyeGrid_Class
{
    list<Robot *> **Grid;
    Vector4 Dim;

    public:
    Setup(Vector4 Dimensions);    
    EyeGrid_Class();
    Insert(Robot *bot);
    Remove(Robot *bot, bool opos = false);
    Move(Robot *bot);
        
}EyeGrid;

EyeGrid_Class::EyeGrid_Class()
{
    Grid = NULL;
    Dim.set(-1,-1,-1);
}

EyeGrid_Class::Setup(Vector4 Dimensions)
{
    if(Grid != NULL)
    {
        for(int y = 0; y < Dim.y(); y++)
            delete Grid[y];

        delete Grid;
    }    
    
    Grid = new list<Robot *>*[(int)Dimensions.y()];    

    for(int y = 0; y < Dimensions.y(); y++)
        Grid[y] = new list<Robot *>[(int)Dimensions.x()];

    Dim = Dimensions;
}

EyeGrid_Class::Insert(Robot *bot)
{
    Vector4 grid = floorV(bot->findpos() / GRID_DIM);

    Grid[(int)grid.x()][(int)grid.y()].push_back(bot);
}

EyeGrid_Class::Remove(Robot *bot, bool opos)
{
    Vector4 pos;

    if(opos)
        pos = bot->findopos();
    else
        pos = bot->findpos();

    Vector4 grid = floorV(pos / GRID_DIM);
    Grid[(int)grid.x()][(int) grid.y()].remove(bot);
}

EyeGrid_Class::Move(Robot *bot)
{
    if(floorV(bot->findpos()  / GRID_DIM) ==
       floorV(bot->findopos() / GRID_DIM))
    {
        return 0; //we haven't moved enough 
    }

    Remove(bot, true);
    Insert(bot);

    return 1;
}