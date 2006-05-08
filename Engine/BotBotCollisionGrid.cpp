// BotBotCollisionGrid.cpp: implementation of the BotBotCollisionGrid class.
// Basically, the world is divided into a h(ierarchial) grid.  There are several grid layers:
// Grid 1: 64 x 64 grid squares (Roughly 1687500 grid squares at largest sim size)
// Grid 2: 128 x 128 grid squares (Roughly 421875 grid squares at largest sim size)
// Grid 3: 256 x 256 grid squares (Roughly 104469 grid squares at largest sim size)
// Grid 4: 512 x 512 grid squares (Roughly 26368 grid squares at largest sim size)
//
// Master Grid - A single grid square to cover the entire world
//
// Bots are entered into the smallest grid level at which they are entirely contained
// (that is, a bot with a radius of 120 (diameter of 240) would be eneted into Grid 3

// There are in total about 2.2 million grid squares.  Since Each grid square is a std::list,
// The memory requirements are on the order of 2.2 Million * sizeof(std::list) bytes.

#include "BotBotCollisionGrid.h"
#include "../Common/Vectors.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BotBotCollisionGrid::BotBotCollisionGrid()
{

}

BotBotCollisionGrid::~BotBotCollisionGrid()
{

}

BotBotCollisionGrid::Setup(Vector3i Dimensions)
{
    assert(Dimensions.x() > 0 && "Attempting to create a world grid with zero x dimensions");
    assert(Dimensions.y() > 0 && "Attempting to create a world grid with zero y dimensions");
    
    SetupLevel(Grid1, Dimensions, 64);
    SetupLevel(Grid2, Dimensions, 128);
    SetupLevel(Grid3, Dimensions, 256);
    SetupLevel(Grid4, Dimensions, 512);

    MasterGrid.clear();    
}

BotBotCollisionGrid::SetupLevel(vector< vector< list< Robot* > > > &Grid, Vector3i Dimensions, int GridSize)
{
    Grid.resize( (Dimensions.x() + GridSize - 1) / GridSize);//round up the number of dimensions needed
    for(unsigned int x = 0; x < Grid.size(); x++)
    {
        Grid[x].resize((Dimensions.y() + GridSize - 1) / GridSize);
        for(unsigned int y = 0; y < Grid[x].size(); y++)
        {
            Grid[x][y].clear();
        }
    }
}