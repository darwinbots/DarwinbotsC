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

long MainWindow::onMouseWheel(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;
    //if(isEnabled())
    {
        MainCamera.Zoom( -event->code * 0.001f * __min(-10, MainCamera.pos().z() - 8000));
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

    if(Selection(event->win_x, event->win_y) == -1)
        mode = TRANSLATE;

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

int MainWindow::Selection(unsigned int MouseX, unsigned int MouseY)
{
    GLint viewport[4];
    float ratio;
    GLuint selectBuf[64];
    GLint hits;

    glSelectBuffer(64,selectBuf);

    glGetIntegerv(GL_VIEWPORT,viewport);

    glRenderMode(GL_SELECT);

    glInitNames();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluPickMatrix(MouseX,viewport[3]-MouseY,5,5,viewport);
    ratio = float((viewport[2]+0.0) / viewport[3]);
    gluPerspective(45,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);

    DrawWorld(true);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glFlush();
    hits = glRenderMode(GL_RENDER);

    if (hits)
        return selectBuf[3];									// Make Our Selection The First Object
    return -1;
}