#include "../GUI/GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Robot.h"
#include "Primitives.h"
#include "Camera.h"

#include "DrawWorld.h"

void DrawRobots();
void DrawShots();
void DrawTies(bool Perimeter);
void DrawEyeField(Robot *me);
void DrawEyes();
void DrawSelectHalo();

long MainWindow::DrawScene()
{
    return MainWindow::DrawScene(NULL, 0, NULL);
}

long MainWindow::DrawScene(FXObject *, FXSelector, void *)
{    
    // Make context current
    canvas->makeCurrent();

    GLdouble width = canvas->getWidth();
    GLdouble height = canvas->getHeight();
    
    DrawWorld(width, height);

    // Swap if it is double-buffered
    if(glvisual->isDoubleBuffer())
        canvas->swapBuffers();

    // Make context non-current
    canvas->makeNonCurrent();

    return 1;
}

void DrawWorld(double width, double height)
{
    GLdouble aspect = height>0 ? width/height : 1.0;

    glViewport(0,0,(int)width,(int)height);

    glClearColor(0.0235294118f, 0.0705882353f, 0.3176470588f, 1.0);				// classic blue color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float xfactor, yfactor;

    #define Factor(x) atanf(MainCamera.pos().z() / 100.0f) / float(PI) * SimOpts.FieldDimensions. x ()
    
    xfactor = Factor(x);
    yfactor = Factor(y);
    
    glOrtho(xfactor + MainCamera.pos().x(),
            SimOpts.FieldDimensions.x() - xfactor + MainCamera.pos().x(),
            yfactor + MainCamera.pos().y(),
            SimOpts.FieldDimensions.y() - yfactor + MainCamera.pos().y(),
            0, 10);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawEyeField(rob[0]);
    
    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex3f(0,0,0);
        glVertex3f(SimOpts.FieldDimensions.x(),0,0);
        glVertex3f(SimOpts.FieldDimensions.x(), SimOpts.FieldDimensions.y(),0);
        glVertex3f(0, SimOpts.FieldDimensions.y(), 0);
    glEnd();
    
    DrawTies(false);
    DrawTies(true);    
    DrawRobots();    
    DrawShots();
    DrawEyes();    
    DrawSelectHalo();
}

void DrawRobots()
{
    GLUquadricObj *quadratic;
    
    quadratic=gluNewQuadric();			        // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
    
    for (int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            glColor3f(rob[x]->color.x() / 3,rob[x]->color.y() / 3,rob[x]->color.z() / 3);
            glPushMatrix();
            glTranslatef(rob[x]->findpos().x(), rob[x]->findpos().y(), rob[x]->findpos().z());
            gluDisk(quadratic, 0, rob[x]->rad() * 0.9f, 32, 1);
            glPopMatrix();                

            glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());
            CreateCircle(rob[x]->findpos(), rob[x]->rad(), 8);
            
            
        }
    }
}

void DrawEyes()
{
    for(int x = 0; x <= MaxRobs; x++)
        if(rob[x] != NULL)
            rob[x]->DrawRobotEye();

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

void DrawTies(bool Perimeter)
{
    for (int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            for(unsigned int y = 0; y < rob[x]->Ties.size(); y++)
            {
                if(rob[x]->Ties[y] != NULL &&
                   rob[x]->Ties[y]->FindOther(rob[x])->AbsNum < rob[x]->AbsNum)
                {
                    
                    Vector4 otherpos = rob[x]->Ties[y]->FindOther(rob[x])->findpos();
                    Vector4 AntiAB = rob[x]->findpos() - otherpos;
                    AntiAB /= Length3(AntiAB);
                    AntiAB.set(AntiAB.y(), -AntiAB.x(), 0);
                    Vector4 point;

                    float myrad=15, yourrad=15;

                    if(rob[x]->Ties[y]->Phase < 0) //birth tie
                    {
                        myrad = rob[x]->rad() * 0.9f;
                        yourrad = rob[x]->Ties[y]->FindOther(rob[x])->rad() * 0.9f;
                    }
                    
                    if(!Perimeter)
                    {
                        Vector4 color = (rob[x]->color + 
                                         rob[x]->Ties[y]->FindOther(rob[x])->color + 
                                         Vector4(1,1,1)) / 3;
                        glColor3f(color.x(), color.y(), color.z());

                        glBegin(GL_QUADS);
                        point = rob[x]->findpos() + myrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());
                        point = rob[x]->findpos() - myrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());
                        point = otherpos - yourrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());
                        point = otherpos + yourrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());                    
                        glEnd();
                    }
                    else
                    {

                        Vector4 color = (rob[x]->color + 
                                         rob[x]->Ties[y]->FindOther(rob[x])->color) / 3;
                        glColor3f(color.x(), color.y(), color.z());

                        glBegin(GL_LINES);
                        
                        point = rob[x]->findpos() + myrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());
                        point = otherpos + yourrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());                    
                        
                        point = rob[x]->findpos() - myrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());
                        point = otherpos - yourrad * AntiAB;
                        glVertex3f(point.x(), point.y(), point.z());
                        
                        glEnd();
                    }
                }
            }
            
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
    //gluPartialDisk not only increments angles opposite how we do, they start on
    //the +y axis instead of the +x axis
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

    GLUquadricObj *quadratic;
    
    quadratic=gluNewQuadric();			        // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )


    glColor3f(1,1,1);
    CreatePoint(this->pos + this->aimvector * this->radius, 2);
    glPushMatrix();
    glTranslatef((this->pos + this->aimvector * this->radius).x(), 
                 (this->pos + this->aimvector * this->radius).y(),
                 (this->pos + this->aimvector * this->radius).z());
    gluDisk(quadratic, 0, 3.75, 16, 1);
    glPopMatrix();
}


void DrawSelectHalo()
{
    if(CurrBotUserSelected >= 0 && rob[CurrBotUserSelected] != NULL)
    {
        glColor3f(1,1,1);
        CreateCircle(rob[CurrBotUserSelected]->findpos(), rob[CurrBotUserSelected]->rad() + 50, 8);        
    }
}