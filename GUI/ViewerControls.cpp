#include <cmath>
#include "../GUI/GUImain.h"
#include "../GFX/Camera.h"
#include "../Engine/Globals.h"

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