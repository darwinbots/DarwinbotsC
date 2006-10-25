#include <cmath>
#include <gl/gl.h>
#include <gl/glu.h>

#include "../GUI/MainWindow.h"
#include "../GFX/Camera.h"
#include "../Engine/Globals.h"
#include "../GFX/DrawWorld.h"
#include "../Engine/SimOptions.h"
#include "../Engine/Robot.h"
#include "../Engine/Engine.h"
#include "../GFX/DrawWorld.h"



int botSelection = 0;

enum
{
    NONE,
    ZOOM,
    TRANSLATE,
    ROTATE,
    SELECT_BOT,
    DRAG_BOT
}mode;

long MainWindow::onMouseWheel(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;
    //if(isEnabled())
    {
        MainCamera.Zoom(event->code * 0.5f);
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
            #define Factor(x) atanf(MainCamera.pos().z() / 100.0f) / float(PI) * SimOpts.FieldDimensions. x ()
            float factorx = (float)Factor(x);
            float factory = (float)Factor(y);

            float mousex = float(event->win_x - event->last_x) / 10;
            float mousey = float(event->win_y - event->last_y) / 10;

            float actualx = (float)canvas->getWidth();
            float actualy = (float)canvas->getHeight();

            float screeny = SimOpts.FieldDimensions.y() - 2 * factory;
            float screenx = SimOpts.FieldDimensions.x() - 2 * factorx;

            float DeltaMovementX = mousex / actualx * screenx;
            float DeltaMovementY = mousey / actualy * screeny;

            MainCamera.Translate(-DeltaMovementX,
                                 DeltaMovementY);
            
            getApp()->addChore(this, ID_UpdGfx, 0);
            #undef Factor
        }
        break;
    }

    return 1;
}

long MainWindow::onLeftBtnPress(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;
    botSelection = Selection(event->win_x, event->win_y);

    if(botSelection == 0)
        mode = TRANSLATE;
    else
    {
        mode = SELECT_BOT;//we've picked a robot
        //select bot
    }
    
    return 1;
}

unsigned long MainWindow::Selection(unsigned int MouseX, unsigned int MouseY)
{
    #define Factor(x) atanf(MainCamera.pos().z() / 100.0f) / float(PI)
    float factorx = (float)Factor(x);
    float factory = (float)Factor(y);

    MouseY = canvas->getHeight() - MouseY;

    float screeny = SimOpts.FieldDimensions.y() * (1.0f - 2 * factory);
    float screenx = SimOpts.FieldDimensions.x() * (1.0f - 2 * factorx);

    float ActualX = MouseX / (float)canvas->getWidth() * screenx;
    float ActualY = MouseY / (float)canvas->getHeight() * screeny;

    ActualX += MainCamera.pos().x();
    ActualY += MainCamera.pos().y();

    ActualX += SimOpts.FieldDimensions.x() * factorx;
    ActualY += SimOpts.FieldDimensions.y() * factory;

    Vector3f actualPos(ActualX, ActualY, 0.0f);

    return engineThread->findAbsNum(actualPos);
}

long MainWindow::onLeftBtnRelease(FXObject *, FXSelector, void *ptr)
{
    mode = NONE;
    
    return 1;
}

long MainWindow::onRightBtnPress(FXObject *, FXSelector, void *ptr)
{
    FXEvent* event=(FXEvent*)ptr;

    if(botSelection != 0 && engineThread->getRobot(botSelection)!=NULL)
        this->onBotDebug();

    return 1;
}

long MainWindow::onRightBtnRelease(FXObject *, FXSelector, void *ptr)
{
    mode = NONE;    
    return 1;
}
