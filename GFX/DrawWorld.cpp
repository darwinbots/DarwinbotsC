#include "../GUI/GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Robot.h"
#include "Primitives.h"
#include "Camera.h"

#include "DrawWorld.h"

void DrawRobots(bool Perimeter = true);
void DrawShots();
void DrawTies();
void DrawEyeField(Robot *me);

void DrawWorld(bool SelectionDraw)
{
    //glShadeModel(GL_SMOOTH);
    

    //camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(MainCamera.lookat().x(), 1.0f, 0.0f, 0.0f);
    glRotatef(MainCamera.lookat().y(), 0.0f, 1.0f, 0.0f);

    glTranslatef(MainCamera.pos().x() - 9327/2,
               -MainCamera.pos().y() - 6928/2,
               MainCamera.pos().z() - 9000);
  
    
    //can we use display lists for the spheres for teh bots and just scale them?  Is that faster?
    DrawRobots(!SelectionDraw);
    if(!SelectionDraw)
    {        
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

        DrawEyeField(rob[1]);
    }

    
}

void DrawRobots(bool Perimeter)
{
    GLUquadricObj *quadratic;
    
    quadratic=gluNewQuadric();			        // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
    
    for (int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //load texture
            glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());

            if(Perimeter)
                CreateCircle(rob[x]->findpos(), rob[x]->rad(), 4);
            else
            {            
                glLoadName(x);                
                glPushMatrix();
                glTranslatef(rob[x]->findpos().x(), rob[x]->findpos().y(), rob[x]->findpos().z());
                gluPartialDisk(quadratic, 0, rob[x]->rad(), 32, 1, 0, 360);
                glPopMatrix();                
            }

            rob[x]->DrawRobotEye();            
        }
    }
}

void DrawShots()
{
    for (int x = 0; x <= MaxShots; x++)
    {
        if (shots[x] != NULL)
        {
            glColor3f(shots[x]->color[0], shots[x]->color[1], shots[x]->color[2]);
            CreatePoint(shots[x]->findpos(), 2);
        }
    }
}

void DrawTies()
{
    for (int x = 0; x <= MaxRobs; x++)
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
    for (int x = 0; x <= MaxRobs; x++)
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
    for (int x = 0; x <= MaxRobs; x++)
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
    for (int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            //Draws the impulse vector of the bots
        }
    }
}

void DrawEyeField(Robot *me)
{
    if(me == NULL)
        return;
    
    GLUquadricObj *quadratic;

    quadratic=gluNewQuadric();			        // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )


    //Draws the eye fields of the bot
    float left = 180.0f - ((me->findaim() * 180.0f / float(PI)) + 90) - 45.0f;
    
    for(int x = 0; x < 9; x++)
    {
        if((*me)[EyeStart + x] > 0)
            glColor3f(.5,.5,.5);
        else
            glColor4f(0,0,0,0);
        
        glPushMatrix();
        glTranslatef(me->findpos().x(), me->findpos().y(), me->findpos().z());
        gluPartialDisk(quadratic, 0, 1440, 32, 1, left, 10);
        glPopMatrix();

        left += 10;
    }   
}

void Robot::DrawRobotEye()
{
    //eyes are always white
    glColor3f(1,1,1);
    CreatePoint(this->pos + this->aimvector * this->radius, 2);    
}
