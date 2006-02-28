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
  
    //can we use display lists for the spheres for teh bots and just scale them?  Is that faster?
    DrawRobots();
    DrawShots();

    //Draw Ties

	glBegin(GL_LINES);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex3f(0,0,0);
        glVertex3f(SimOpts.FieldDimensions.x(),0,0);
        glVertex3f(SimOpts.FieldDimensions.x(),0,0);
        glVertex3f(SimOpts.FieldDimensions.x(), SimOpts.FieldDimensions.y(),0);
        glVertex3f(SimOpts.FieldDimensions.x(), SimOpts.FieldDimensions.y(),0);
        glVertex3f(0, SimOpts.FieldDimensions.y(), 0);
        glVertex3f(0, SimOpts.FieldDimensions.y(), 0);
        glVertex3f(0,0,0);
    glEnd();
}

void DrawRobots()
{
    for (unsigned int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //load texture
            //glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());
            
            glColor3f(1.0f,0,0);

            CreateCircle(rob[x]->findpos(), rob[x]->rad(), 4);
            rob[x]->DrawRobotEye();
        }
    }
}

void DrawShots()
{
    for (unsigned int x = 0; x <= MaxShots; x++)
    {
        if (shots[x] != NULL)
        {
            //load texture
            //glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());
            
            glColor3f(shots[x]->color[0], shots[x]->color[1], shots[x]->color[2]);
            CreatePoint(shots[x]->findpos(), 2);
        }
    }
}

void DrawTies()
{
    for (unsigned int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //draw all ties this bot has that haven't been
            //drawn already
        }
    }
}

//draws the voluntary translational movement vector
void DrawBangs()
{
    for (unsigned int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //draw a line representing the last translational bang,
            //or perhaps draw a rocket-type exhaust fire
        }
    }
}

//draws the current bot velocity vector
void DrawVelocity()
{
    for (unsigned int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //I'm not sure how best to do this actually.
            //either we could draw a slightly ghosted
            //afterimage of where the bot used to be,
            //or draw a line to where the velocity
            //vector is directing the bot

            //or maybe draw a long time-cylinder between
            //opos and pos, sort of like motion blur
            //this would help capture movement in a still
            //picture

            //drawing wake lines is also an option, though a
            //bit above what I know how to do at the moment

            //-Numsgil
        }
    }
}

void DrawImpulse()
{
    for (unsigned int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //Draws the impulse vector of the bots
        }
    }
}

void DrawEyeField()
{
    //Draws the eye fields of the bot
}

void Robot::DrawRobotEye()
{
    //eyes are always white
    glColor3f(1,1,1);
    CreatePoint(this->pos + this->aimvector * this->radius, 2);    
}