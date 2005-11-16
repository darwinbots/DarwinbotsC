#include "GUImain.h"

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
    FXHorizontalFrame *frame=new FXHorizontalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y, 100,100,100,100, 0,0,0,0, 4,4);

    FXVerticalFrame *box=new FXVerticalFrame(frame,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);

    FXMDIClient *mdiclient=new FXMDIClient(box,LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGIFIcon *winappicon=new FXGIFIcon(getApp(),winapp);
    
    FXMDIMenu *mdimenu=new FXMDIMenu(this,mdiclient);
     
    FXMDIChild* mdichild=new FXMDIChild(mdiclient,"FOX GL Viewer",winappicon,mdimenu,MDI_TRACKING|MDI_MAXIMIZED,30,30,300,200);
    
    mdichild->maximize(true);
    
    glvisual=new FXGLVisual(getApp(),VISUAL_DOUBLEBUFFER);
    
    FXGLViewer *viewer=new FXGLViewer(mdichild,glvisual,this,ID_Viewer,LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);

    mdiclient->setActiveChild(mdichild);

    FXGLGroup *scene=new FXGLGroup;
    FXGLSphere *sphere=new FXGLSphere(0.0, 20.0, 0.0, 2);
    sphere->setTipText("Sphere");
    sphere->setStacks(20);
    sphere->setSlices(20);
    FXGLSphere *sphere2=new FXGLSphere(0.0, 30.0, 0.0, 2);
    sphere2->setTipText("Sphere2");
    sphere2->setStacks(30);
    sphere2->setSlices(30);
    FXGLCylinder * test = new FXGLCylinder(0, 21.5, 0, 7, .5);
    test->setTipText("test");
    scene->append(test);
    scene->append(sphere2);
    scene->append(sphere);

  // Add scene to GL viewer
  viewer->setScene(scene);
  
  return 1;
}
