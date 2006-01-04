#include "GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Globals.h"
#include "../Engine/Robot.h"
#include "../Common/Math3d.h"
#include "../GFX/DrawWorld.h"
#include "../GFX/Camera.h"
#include "../Engine/Engine.h"

using Math3D::Vector4;

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
    FXHorizontalFrame *frame=new FXHorizontalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        100,100,100,100, 0,0,0,0, 4,4);

    FXVerticalFrame *box=new FXVerticalFrame(frame,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,
        0,0,0,0, 0,0,0,0);

    FXMDIClient *mdiclient=new FXMDIClient(box,LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGIFIcon *winappicon=new FXGIFIcon(getApp(),winapp);
    
    FXMDIMenu *mdimenu=new FXMDIMenu(this,mdiclient);
     
    FXMDIChild* mdichild=new FXMDIChild(mdiclient,"Darwinbots Main View",winappicon,mdimenu,
        MDI_TRACKING|MDI_MAXIMIZED,30,30,300,200);
    
    glvisual = new FXGLVisual(getApp(),VISUAL_DOUBLEBUFFER | VISUAL_STEREO);

    this->canvas = new FXGLCanvas(mdichild, glvisual, this, ID_MainView, LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);

    mdiclient->setActiveChild(mdichild);

    getApp()->addTimeout(this, ID_UpdGfx, 25);    

    return 1;
}

long MainWindow::onUpdGfx(FXObject *, FXSelector, void *)
{    
    //update world if we're tying the world update to a specific speed    
    
    //Draw World    
    Engine.UpdateSim();
    this->DrawScene();

    getApp()->addTimeout(this, ID_UpdGfx, 1);
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

  glViewport(0,0,width,height);

  glClearColor(0.0235294118f, 0.0705882353f, 0.3176470588f, 1.0);				// classic blue color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glEnable(GL_DEPTH_TEST);

  glDisable(GL_DITHER);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.,aspect,.1,1000000);

  //camera (?)
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glRotatef(MainCamera.lookat().x(), 1.0f, 0.0f, 0.0f);
  glRotatef(MainCamera.lookat().y(), 0.0f, 1.0f, 0.0f);

  glTranslatef(MainCamera.pos().x() - 9327/2,
               -MainCamera.pos().y() - 6928/2,
               MainCamera.pos().z() - 9000);
  
  DrawWorld();

  // Swap if it is double-buffered
  if(glvisual->isDoubleBuffer()){
    canvas->swapBuffers();
    }

  // Make context non-current
  canvas->makeNonCurrent();

  return 1;
}