#include "../GUI/GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Robot.h"
#include "Primitives.h"
#include "Camera.h"

#include "DrawWorld.h"

void DrawRobots();
void DrawShots();
void DrawTies();

void DrawWorld(void)
{
    //glShadeModel(GL_SMOOTH);
  
    glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);//,0.5f);			// Full Brightness, 50% Alpha ( NEW )
        //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
        glVertex3f(0,0,0);
        glVertex3f(SimOpts.FieldDimensions.x(),0,0);
        glVertex3f(SimOpts.FieldDimensions.x(),0,0);
        glVertex3f(SimOpts.FieldDimensions.x(), SimOpts.FieldDimensions.y(),0);
        glVertex3f(SimOpts.FieldDimensions.x(), SimOpts.FieldDimensions.y(),0);
        glVertex3f(0, SimOpts.FieldDimensions.y(), 0);
        glVertex3f(0, SimOpts.FieldDimensions.y(), 0);
        glVertex3f(0,0,0);
    glEnd();
    
    //can we use display lists for the spheres for teh bots and just scale them?  Is that faster?
    DrawRobots();
    DrawShots();

    //Draw Shots
    //Draw Ties
}

void DrawRobots()
{
    for (unsigned int x = 0; x < MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //load texture
            //glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());
            
            glColor3f(1.0f,0,0);
            glLoadName(x);
            CreateCircle(rob[x]->findpos(), rob[x]->rad(), 4);
            rob[x]->DrawRobotEye();
        }
    }
}

void DrawShots()
{
    for (unsigned int x = 0; x < MaxShots; x++)
    {
        if (shots[x] != NULL)
        {
            //load texture
            //glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());
            
            glColor3f(0,1.0f,0);
            glLoadName(x + 10000);
            CreatePoint(shots[x]->findpos(), 2);
        }
    }
}

void Robot::DrawRobotEye()
{
    glColor3f(1,1,1);
    CreatePoint(this->pos + this->aimvector * this->radius, 2);
}