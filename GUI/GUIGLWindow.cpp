#include "GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Globals.h"
#include "../Engine/Robot.h"
#include "../Common/Math3d.h"
#include "../GFX/DrawWorld.h"
#include "../GFX/Camera.h"
#include "../Engine/Engine.h"

const unsigned char winapp[]={
  0x47,0x49,0x46,0x38,0x37,0x61,0x10,0x00,0x10,0x00,0xf2,0x00,0x00,0xb2,0xc0,0xdc,
  0x80,0x80,0x80,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0xff,0x00,
  0x00,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x03,
  0x38,0x08,0xba,0xdc,0x10,0x30,0xca,0x09,0x85,0xbd,0xf8,0x86,0x11,0x04,0xf9,0x60,
  0xf8,0x6d,0x9d,0x48,0x14,0x03,0x8a,0x92,0x02,0xe5,0x72,0x42,0x21,0xcf,0xb4,0xcc,
  0xd6,0x78,0x71,0xe7,0xf4,0xce,0xdb,0xb0,0xdf,0xcc,0xf7,0x23,0xf2,0x48,0xae,0xd7,
  0x60,0xc9,0x6c,0x3a,0x07,0x8e,0xe8,0x22,0x01,0x00,0x3b
  };

long MainWindow::GLWindow()
{
    FXHorizontalFrame *frame;
    FXVerticalFrame *box;
    
    frame=new FXHorizontalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        100,100,100,100, 0,0,0,0, 4,4);

    box=new FXVerticalFrame(frame,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0, 0,0,0,0);

    mdiclient=new FXMDIClient(box,LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXMDIMenu *mdimenu=new FXMDIMenu(this,mdiclient);
     
    mainview=new FXMDIChild(mdiclient,"Darwinbots Main View",NULL,mdimenu,
        MDI_TRACKING | ID_MDI_MAXIMIZE,30,30,300,200);

    glvisual = new FXGLVisual(getApp(),VISUAL_DOUBLEBUFFER | VISUAL_STEREO);

    this->canvas = new FXGLCanvas(mainview, glvisual, this, ID_MainView,
        LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);

    mdiclient->setActiveChild(mainview);
    mainview->maximize();

    //this->onBotDebug();

    getApp()->addTimeout(this, ID_UpdGfx, 0);

    return 1;
}

long MainWindow::onUpdGfx(FXObject *, FXSelector, void *)
{    
    static int counter;
    
    if(GraphicsOn)
        this->DrawScene();
    else if(++counter > 16 || counter < 0)
    {
        this->DrawScene();
        counter = 0;
    }

    getApp()->addTimeout(this, ID_UpdGfx, 32);
    return 1;
}

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
    GLdouble aspect = height>0 ? width/height : 1.0;

    glViewport(0,0,(int)width,(int)height);

    glClearColor(0.0235294118f, 0.0705882353f, 0.3176470588f, 1.0);				// classic blue color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable(GL_DEPTH_TEST);

    glDisable(GL_DITHER);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.,aspect,.1,1000000);

    DrawWorld();

    // Swap if it is double-buffered
    if(glvisual->isDoubleBuffer())
        canvas->swapBuffers();

    // Make context non-current
    canvas->makeNonCurrent();

    return 1;
}



/*int Selection(void)											// This Is Where Selection Is Done
{
	GLuint	buffer[512];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected

	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);								// Tell OpenGL To Use Our Array For Selection

	glRenderMode(GL_SELECT);

	glInitNames();												// Initializes The Name Stack
	glPushName(-1);												// Push 0 (At Least One Entry) Onto The Stack

	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix

	//// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	gluPickMatrix((GLdouble) MouseX, (GLdouble) viewport[3]-MouseY-MenuHeight, 5.0f, 5.0f, viewport);

	// Apply The Perspective Matrix
	gluPerspective(45.0f,
		(GLfloat) (viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]),
		ViewMin, ViewDepth);
	
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	DrawGLScene();
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits=glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
																// Objects Were Drawn Where The Mouse Was
	if (hits)
	{
		int	choose = buffer[3];									// Make Our Selection The First Object
		int depth = buffer[1];									// Store How Far Away It Is 

		for (int loop = 1; loop < hits; loop++)					// Loop Through All The Detected Hits
		{
			// If This Object Is Closer To Us Than The One We Have Selected
			if (buffer[loop*4+1] < GLuint(depth))
			{
				choose = buffer[loop*4+3];						// Select The Closer Object
				depth = buffer[loop*4+1];						// Store How Far Away It Is
			}       
		}

		//if (!object[choose].hit)								// If The Object Hasn't Already Been Hit
		//	;

		return choose;		
    }
	return -1;
}*/