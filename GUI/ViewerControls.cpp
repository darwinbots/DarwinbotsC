#include <cmath>
#include "../GUI/GUImain.h"
#include "../GFX/Camera.h"
#include "../Engine/Globals.h"
#include "../GFX/DrawWorld.h"

#include <gl/gl.h>
#include <gl/glu.h>

enum
{
    NONE,
    ZOOM,
    TRANSLATE,
    ROTATE
}mode;

unsigned int Selection(unsigned int MouseX, unsigned int MouseY);

long MainWindow::onMouseWheel(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;
    //if(isEnabled())
    {
        MainCamera.Zoom( fsgn((float)event->code) * float(pow(2,-.1*event->code/120.0)));
        return 1;
    }
  return 0;
}

long MainWindow::onMotion(FXObject *, FXSelector, void *ptr)
{
    FXEvent *event = (FXEvent *)ptr;
    
    switch(mode)
    {
        case NONE: break;
        
        case ROTATE:
        {
            MainCamera.Rotate(float(event->win_y - event->last_y), float(event->win_x - event->last_x));
        }            
        break;

        case TRANSLATE:
        {
            MainCamera.Translate(float(event->win_x - event->last_x), float(event->win_y - event->last_y));
        }
        break;
    }

    return 1;
}

long MainWindow::onLeftBtnPress(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;

    mode = TRANSLATE;
    //Selection(event->win_x, event->win_y);

    //event->state&MIDDLEBUTTONMASK
    return 1;
}

long MainWindow::onLeftBtnRelease(FXObject *, FXSelector, void *ptr)
{
    mode = NONE;
    
    return 1;
}

long MainWindow::onRightBtnPress(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;

    //mode = ROTATE;

    this->onBotDebug();

    return 1;
}

long MainWindow::onRightBtnRelease(FXObject *, FXSelector, void *ptr)
{
    mode = NONE;    
    return 1;
}

unsigned int MainWindow::Selection(unsigned int MouseX, unsigned int MouseY)
{
    GLuint buffer[256];
    GLint hits;
    
    glSelectBuffer(256, buffer);
    glRenderMode(GL_SELECT);
    
    glInitNames();
    glPushName(-1);
    
    GLdouble width = canvas->getWidth();
    GLdouble height = canvas->getHeight();
    GLdouble aspect = height>0 ? width/height : 1.0;

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspect,.1,1000000);
    
    //camera (?)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  
    glRotatef(MainCamera.lookat().x(), 1.0f, 0.0f, 0.0f);
    glRotatef(MainCamera.lookat().y(), 0.0f, 1.0f, 0.0f);

    glTranslatef(MainCamera.pos().x() - 9327/2,
                 -MainCamera.pos().y() - 6928/2,
                 MainCamera.pos().z() - 9000);

    DrawWorld();

    glFlush();
    hits = glRenderMode(GL_RENDER);
    if(hits)                          // Switch To Render Mode, Find Out How Many
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
		return choose;		
    }
	return -1;
}