#include "GUImain.h"

long MainWindow::GLWindow()
{
    FXHorizontalFrame *frame=new FXHorizontalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y, 0,0,0,0, 0,0,0,0, 4,4);

    FXVerticalFrame *box=new FXVerticalFrame(frame,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);

    FXMDIClient *mdiclient=new FXMDIClient(box,LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXGIFIcon *winappicon=new FXGIFIcon(getApp(),winapp);
    
    FXMDIMenu *mdimenu=new FXMDIMenu(this,mdiclient);
    
    new FXMDIWindowButton(menubar,mdimenu,mdiclient,FXMDIClient::ID_MDI_MENUWINDOW,LAYOUT_LEFT);
    new FXMDIDeleteButton(menubar,mdiclient,FXMDIClient::ID_MDI_MENUCLOSE,FRAME_RAISED|LAYOUT_RIGHT);
    new FXMDIRestoreButton(menubar,mdiclient,FXMDIClient::ID_MDI_MENURESTORE,FRAME_RAISED|LAYOUT_RIGHT);
    new FXMDIMinimizeButton(menubar,mdiclient,FXMDIClient::ID_MDI_MENUMINIMIZE,FRAME_RAISED|LAYOUT_RIGHT);
    
    FXMDIChild* mdichild=new FXMDIChild(mdiclient,"FOX GL Viewer",winappicon,mdimenu,MDI_TRACKING|MDI_MAXIMIZED,30,30,300,200);
    
    mdichild->maximize(true);
    
    glvisual=new FXGLVisual(getApp(),VISUAL_DOUBLEBUFFER);
    
    FXGLViewer *viewer=new FXGLViewer(mdichild,glvisual,this,ID_Viewer,LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);

    mdiclient->setActiveChild(mdichild);

    FXGLGroup *scene=new FXGLGroup;
    scene->append(new FXGLPoint(2,0,0));
    scene->append(new FXGLPoint(0,2,0));
    scene->append(new FXGLPoint(2,2,0));
    scene->append(new FXGLPoint(0,0,0));
    scene->append(new FXGLLine(0,0,0, 1,0,0));
    scene->append(new FXGLLine(0,0,0, 0,1,0));
    scene->append(new FXGLLine(0,0,0, 0,0,1));
    scene->append(new FXGLLine(0,0,0, 1,1,1));
    FXGLGroup *gp2=new FXGLGroup;
    scene->append(gp2);
    FXGLSphere *sphere=new FXGLSphere(1.0, 1.0, 0.0, 0.5);
    FXGLSphere *sphere2=new FXGLSphere(0.0, 0.0, 0.0, 0.8);
    sphere->setTipText("Sphere");
    gp2->append(new FXGLCube(-1.0, 0.0, 0.0,  1.0, 1.0, 1.0));
    gp2->append(new FXGLCube( 1.0, 0.0, 0.0,  1.0, 1.0, 1.0));
    gp2->append(new FXGLCube( 0.0,-1.0, 0.0,  1.0, 1.0, 1.0));
    gp2->append(new FXGLCube( 0.0, 1.0, 0.0,  1.0, 1.0, 1.0));
    gp2->append(new FXGLCone(1.0,-1.5, 0.0, 1.0, 0.5));
    gp2->append(new FXGLCylinder(-1.0, 0.5, 0.0, 1.0, 0.5));
    gp2->append(sphere);
    gp2->append(sphere2);

  // Add scene to GL viewer
  viewer->setScene(scene);
  
  return 1;
}
