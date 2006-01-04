#include <gl/gl.h>
#include <gl/glu.h>
#include "../GUI/GUImain.h"
#include "../Engine/Robot.h"
#include "Primitives.h"
#include "Camera.h"

#include "DrawWorld.h"

void DrawRobots();
void DrawShots();
void DrawTies();

void DrawWorld(void)
{
  glShadeModel(GL_SMOOTH);
  
  /*Begin(GL_QUADS);
    
   glColor3f(1.0f,1.0f,1.0f);//,0.5f);			// Full Brightness, 50% Alpha ( NEW )
   //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glVertex3f(0,0,1000);
    glVertex3f(9327,0,1000);
    glVertex3f(9327, 6928,1000);
    glVertex3f(0, 6928, 1000);
  glEnd();*/
    
    //can we use display lists for the spheres for teh bots and just scale them?  Is that faster?
    DrawRobots();


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
            
            glColor3f(0,0,0);
            CreateSphere(rob[x]->findpos(), rob[x]->rad());
            rob[x]->DrawRobotEye();
            //CreateSphere(Vector4(0,0,0), rob[x]->rad());
        }

        //MainCamera.LOOKAT = rob[0]->findpos();
        //MainCamera.POS    = rob[1]->findpos();
    }
}

void Robot::DrawRobotEye()
{
    glColor3f(1,1,1);
    CreatePoint(this->pos + this->aimvector * (1.1 * this->radius), 2);
}
