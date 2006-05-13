#include "DrawWorld.h"

void DrawRobots();
void DrawShots();
void DrawTies(bool Perimeter);
void DrawEyeField(Robot *me);
void DrawEyes();
void DrawSelectHalo();
void DrawEyeGrid();
void DrawRobotEye(Robot* bot);

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

void DrawWorld(double width, double height)
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

    if(CurrBotUserSelected > 0)
        DrawEyeField(rob[CurrBotUserSelected]);
    
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
    DrawEyes();    
    DrawSelectHalo();
}

void DrawRobots()
{
    //SetupDisplayLists(); done in the setup for the GL window

    static bool DisplayListsCreated = false;

    //for some reason this needs to be setup again every frame.  I can't figure out why
    //if(!DisplayListsCreated)
    //{
        SetupDisplayLists();
    //    DisplayListsCreated = true;
    //}
    
    for (int x = 0; x <= MaxRobs; x++)
    {
        if (rob[x] != NULL)
        {
            glPushMatrix();
            
            Vector3f pos(rob[x]->findpos());
            glTranslatef(pos.x(), pos.y(), pos.z());
            glScalef(rob[x]->rad(), rob[x]->rad(), rob[x]->rad());

            //Draw the bots' guts
            glColor3f(rob[x]->color.x() / 3,rob[x]->color.y() / 3,rob[x]->color.z() / 3);
            glCallList(BOT_GUTS);
            
            //Draw the bots' perimeter
            glColor3f(rob[x]->color.x(), rob[x]->color.y(), rob[x]->color.z());
            glCallList(BOT_PERIMETER);
            
            glPopMatrix();
        }
    }
}

void SetupDisplayLists()
{
    //Guts
    glNewList(BOT_GUTS, GL_COMPILE);
        gluDisk(gluNewQuadric(), 0, 0.9f, 32, 1);
    glEndList();

    glNewList(BOT_PERIMETER, GL_COMPILE);
        CreateCircle(Vector3f(0,0,0), 1, 8);
    glEndList();
}

void DrawEyes()
{
    for(int x = 0; x <= MaxRobs; x++)
        if(rob[x] != NULL)
            DrawRobotEye(rob[x]);

}

void DrawShots()
{
    for (int x = 0; x <= MaxShots; x++)
    {
        if (shots[x] != NULL)
        {
            glColor3f(shots[x]->color[0]/2, shots[x]->color[1]/2, shots[x]->color[2]/2);
            glBegin(GL_LINES);
                glVertex3f(shots[x]->findopos().x(),
                           shots[x]->findopos().y(),
                           shots[x]->findopos().z());
                
                glVertex3f(shots[x]->findpos().x(),
                           shots[x]->findpos().y(),
                           shots[x]->findpos().z());
            glEnd();

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
                    
                    Vector3f otherpos = rob[x]->Ties[y]->FindOther(rob[x])->findpos();
                    Vector3f AntiAB = rob[x]->findpos() - otherpos;
                    AntiAB /= AntiAB.Length();
                    AntiAB.set(AntiAB.y(), -AntiAB.x(), 0);
                    Vector3f point;

                    float myrad=15, yourrad=15;

                    if(rob[x]->Ties[y]->Phase < 0) //birth tie
                    {
                        myrad = rob[x]->rad() * 0.9f;
                        yourrad = rob[x]->Ties[y]->FindOther(rob[x])->rad() * 0.9f;
                    }
                    
                    if(!Perimeter)
                    {
                        Vector3f color = (rob[x]->color + 
                                          rob[x]->Ties[y]->FindOther(rob[x])->color + 
                                          Vector3f(1,1,1)) / 3;
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

                        Vector3f color = (rob[x]->color + 
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

void DrawRobotEye(Robot* bot)
{
    //eyes are always white

    GLUquadricObj *quadratic;
    
    quadratic=gluNewQuadric();			        // Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )


    glColor3f(1,1,1);
    CreatePoint(bot->findpos() + bot->aimvector * bot->radius, 2);
    glPushMatrix();
    glTranslatef((bot->findpos() + bot->aimvector * bot->radius).x(),
                 (bot->findpos() + bot->aimvector * bot->radius).y(),
                 (bot->findpos() + bot->aimvector * bot->radius).z());
    gluDisk(quadratic, 0, 3.75, 16, 1);
    glPopMatrix();
}

void DrawEyeGrid()
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


void DrawSelectHalo()
{
    if(CurrBotUserSelected >= 0 && rob[CurrBotUserSelected] != NULL)
    {
        glColor3f(1,1,1);
        CreateCircle(rob[CurrBotUserSelected]->findpos(), rob[CurrBotUserSelected]->rad() + 50, 8);        
    }
}
