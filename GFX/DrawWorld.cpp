#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Robot.h"
#include "../Engine/Engine.h"
#include "../GUI/MainWindow.h"
#include "Primitives.h"
#include "Camera.h"
#include "DrawWorld.h"
#include "../Engine/EngineThread.h"

long MainWindow::DrawScene() //alias
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

void MainWindow::DrawWorld(double width, double height)
{
    GLdouble aspect = height>0 ? width/height : 1.0;

    glViewport(0,0,(int)width,(int)height);

    glClearColor(0.0235294118f, 0.0705882353f, 0.3176470588f, 1.0);				// classic blue color
    glClear(GL_COLOR_BUFFER_BIT);

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

    if(botSelection > 0)
        DrawEyeField(engineThread->getRobot(botSelection));

    glBegin(GL_LINE_LOOP);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex3f(0,0,0);
        glVertex3f(SimOpts.FieldDimensions.x(),0,0);
        glVertex3f(SimOpts.FieldDimensions.x(), SimOpts.FieldDimensions.y(),0);
        glVertex3f(0, SimOpts.FieldDimensions.y(), 0);
    glEnd();

    //DrawEyeGrid();
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    DrawTies(false);
    DrawTies(true);
    DrawRobots();
    DrawShots();
    DrawSelectHalo();
}

void MainWindow::DrawRobots()
{
    //SetupDisplayLists(); done in the setup for the GL window

    static bool DisplayListsCreated = false;

    //for some reason this needs to be setup again every frame.  I can't figure out why
    //if(!DisplayListsCreated)
    //{
        SetupDisplayLists();
    //    DisplayListsCreated = true;
    //}
    std::vector<SolidPrimitive> localBotList = this->engineThread->getRobotDisplayList();
    for (std::vector<SolidPrimitive>::iterator currBot = localBotList.begin(); currBot != localBotList.end(); ++currBot)
    {
        SolidPrimitive temp = *currBot;
        glPushMatrix();

        Vector3f pos(temp.getPos());
        glTranslatef(pos.x(), pos.y(), pos.z());
        glScalef(temp.getRadius(), temp.getRadius(), temp.getRadius());

        //Draw the bots' guts
        glColor3f(temp.color.x() / 3,temp.color.y() / 3,temp.color.z() / 3);
        glCallList(BOT_GUTS);

        //Draw the bots' perimeter
        glColor3f(temp.color.x(), temp.color.y(), temp.color.z());
        glCallList(BOT_PERIMETER);

        glPopMatrix();

        DrawRobotEye(temp);
// FIXME (Ronan#1#):
        /*if (temp.getAbsNum()==-105)
            std::cout<<"Updated bot#"<<temp.getAbsNum()
                    <<" at turn "<<SimOpts.TotRunCycle
                    <<". Position: "<<pos.x()<<","<<pos.y()<<std::endl;*/
    }
}

void MainWindow::SetupDisplayLists()
{
    //Guts
    glNewList(BOT_GUTS, GL_COMPILE);
        gluDisk(gluNewQuadric(), 0, 0.9f, 32, 1);
    glEndList();

    glNewList(BOT_PERIMETER, GL_COMPILE);
        CreateCircle(Vector3f(0,0,0), 1, 8);
    glEndList();
}

void MainWindow::DrawShots()
{
    ShotList localShotList = engineThread->getShotDisplayList();

    for (ShotIterator shot = localShotList.begin(); shot != localShotList.end(); ++shot)
    {
        Shot* temp = *shot;
        glColor3f(temp->color[0]/2, temp->color[1]/2, temp->color[2]/2);
        glBegin(GL_LINES);
        glVertex3f(temp->getOldPos().x(),
                    temp->getOldPos().y(),
                    temp->getOldPos().z());

        glVertex3f(temp->getPos().x(),
                    temp->getPos().y(),
                    temp->getPos().z());
        glEnd();

        glColor3f(temp->color[0], temp->color[1], temp->color[2]);
        CreatePoint(temp->getPos(), 2);
    }
}

void MainWindow::DrawTies(bool Perimeter)
{
    for (RobotIterator currBot = engineThread->simulation->robotList->begin();
                currBot != engineThread->simulation->robotList->end(); ++currBot)
    {
        assert(*currBot);
        for(TieList::iterator tie = (*currBot)->Ties.begin(); tie != (*currBot)->Ties.end(); ++tie)
        {
            if(*tie != NULL &&
               (*tie)->FindOther(*currBot)->getAbsNum() < (*currBot)->getAbsNum())
            {
                Robot* otherBot = (*tie)->FindOther(*currBot);
                Vector3f mypos = (*currBot)->getPos();
                Vector3f otherpos = otherBot->getPos();
                Vector3f AntiAB = mypos - otherpos;
                AntiAB /= AntiAB.Length();
                AntiAB.set(AntiAB.y(), -AntiAB.x(), 0);
                Vector3f point;

                float myrad=15, yourrad=15;

                if((*tie)->FindPhase() < 0) //birth tie
                {
                    myrad = (*currBot)->getRadius() * 0.9f;
                    yourrad = otherBot->getRadius() * 0.9f;
                }

                if(!Perimeter)
                {
                    Vector3f color = ((*currBot)->color +
                                      otherBot->color +
                                      Vector3f(1,1,1)) / 3;
                    glColor3f(color.x(), color.y(), color.z());

                    glBegin(GL_QUADS);
                    point = mypos + myrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());
                    point = mypos - myrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());
                    point = otherpos - yourrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());
                    point = otherpos + yourrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());
                    glEnd();
                }
                else
                {

                    Vector3f color = ((*currBot)->color +
                                      otherBot->color) / 3;
                    glColor3f(color.x(), color.y(), color.z());

                    glBegin(GL_LINES);

                    point = mypos + myrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());
                    point = otherpos + yourrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());

                    point = mypos - myrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());
                    point = otherpos - yourrad * AntiAB;
                    glVertex3f(point.x(), point.y(), point.z());

                    glEnd();
                }
            }
        }

    }
}

//draws the voluntary translational movement vector
void MainWindow::DrawBangs()
{
    /*for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
    {
        //draw a line representing the last translational bang,
        //or perhaps draw a rocket-type exhaust fire
    }*/
}

//draws the current bot velocity vector
void MainWindow::DrawVelocity()
{
    /*for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
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
    }*/
}

void MainWindow::DrawImpulse()
{
    /*for (currBot = robotList->begin(); currBot != robotList->end(); ++currBot)
    {
        //Draws the impulse vector of the bots
    }*/
}

void MainWindow::DrawEyeField(Robot* me) const
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
    float left = 180.0f - ((me->getAim() * 180.0f / float(PI)) + 90) - 45.0f;

    for(int x = 0; x < 9; x++)
    {
        if((*me)[EyeStart + x] > 0)
            glColor3f(.5,.5,.5);
        else
            glColor4f(0,0,0,0);

        glPushMatrix();
        glTranslatef(me->getPos().x(), me->getPos().y(), 0.);

        gluPartialDisk(quadratic, 0, 1440, 32, 1, left, 10);
        glPopMatrix();

        left += 10;
    }
    delete me;
}

void MainWindow::DrawRobotEye(const SolidPrimitive& bot) const
{
    //eyes are always white

    GLUquadricObj *quadratic;

    quadratic=gluNewQuadric();			        // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )


    glColor3f(1,1,1);
    CreatePoint(bot.getPos() + bot.getAimVector() * bot.getRadius(), 2);
    glPushMatrix();
    Vector3f eyePos=(bot.getPos() + bot.getAimVector() * bot.getRadius());
    glTranslatef(eyePos.x(), eyePos.y(), eyePos.z());
    gluDisk(quadratic, 0, 3.75, 16, 1);
    glPopMatrix();
}

void MainWindow::DrawEyeGrid()
{
    for(unsigned int x = 0; x < ceil(SimOpts.FieldDimensions / GRID_DIM).x(); x++)
        for(unsigned int y = 0; y < ceil(SimOpts.FieldDimensions / GRID_DIM).y(); y++)
        {
            glColor3f(1,0,0);
            glBegin(GL_LINE_LOOP);
                glVertex3f(float(x) * GRID_DIM,     float(y) * GRID_DIM       , 0);
                glVertex3f(float(x+1) * GRID_DIM,   float(y) * GRID_DIM       , 0);
                glVertex3f(float(x+1) * GRID_DIM,   float(y+1) * GRID_DIM   , 0);
                glVertex3f(float(x) * GRID_DIM,     float(y+1) * GRID_DIM   , 0);
            glEnd();
        }
}


void MainWindow::DrawSelectHalo()
{
    Robot* bot = engineThread->getRobot(botSelection);
    if(botSelection && bot!=NULL)
    {
        glColor3f(1,1,1);
        CreateCircle(bot->getPos(), bot->getRadius() + 50, 8);
        delete bot;
    }
}
