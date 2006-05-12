#include "GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Globals.h"
#include "../Engine/Robot.h"
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
