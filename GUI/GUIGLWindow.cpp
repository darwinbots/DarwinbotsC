#include "GUImain.h"
#include <gl/gl.h>

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
  
  viewer->setProjection(0);
  
  return 1;
}

// Render all the graphics into a world box
void FXGLViewer::drawWorld(FXViewport& wv){

  // Set viewport
  glViewport(0,0,wv.w,wv.h);

  // Reset important stuff
  glShadeModel(GL_SMOOTH);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glDisable(GL_LIGHTING);
  glDisable(GL_ALPHA_TEST);
  glDisable(GL_BLEND);
  glDisable(GL_DITHER);
  glDisable(GL_FOG);
  glDisable(GL_LOGIC_OP);
  glDisable(GL_POLYGON_SMOOTH);
  glDisable(GL_POLYGON_STIPPLE);
  glDisable(GL_STENCIL_TEST);
  glDisable(GL_CULL_FACE);
  glDisable(GL_COLOR_MATERIAL);

  // Reset matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Clear to solid background
  glClearDepth(1.0);
  glClearColor(background[0][0],background[0][1],background[0][2],background[0][3]);
  if(background[0]==background[1]){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

  // Clear to gradient background
  else{
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glBegin(GL_TRIANGLE_STRIP);
    glColor4fv(background[1]); glVertex3f(-1.0f,-1.0f,0.0f); glVertex3f( 1.0f,-1.0f,0.0f);
    glColor4fv(background[0]); glVertex3f(-1.0f, 1.0f,0.0f); glVertex3f( 1.0f, 1.0f,0.0f);
    glEnd();
    }

  // Depth test on by default
  glDepthMask(GL_TRUE);
  glEnable(GL_DEPTH_TEST);

  // Switch to projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  switch(projection){
    case PARALLEL:
      glOrtho(wv.left,wv.right,wv.bottom,wv.top,wv.hither,wv.yon);
      break;
    case PERSPECTIVE:
      glFrustum(wv.left,wv.right,wv.bottom,wv.top,wv.hither,wv.yon);
      break;
    }

  // Switch to model matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set light parameters
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0,GL_AMBIENT,light.ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,light.diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,light.specular);
  glLightfv(GL_LIGHT0,GL_POSITION,light.position);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,light.direction);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,light.exponent);
  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,light.cutoff);
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,light.c_attn);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,light.l_attn);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,light.q_attn);

  // Default material colors
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,material.ambient);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,material.diffuse);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,material.specular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,material.emission);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,material.shininess);

  // Color commands change both
  glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

  // Global ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);

  // Enable fog
  if(options&VIEWER_FOG){
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR,background[0]);                // Disappear into the background
    //glFogf(GL_FOG_DENSITY,1.0f);
    glFogf(GL_FOG_START,(GLfloat)(distance-diameter));  // Range tight around model position
    glFogf(GL_FOG_END,(GLfloat)(distance+diameter));    // Far place same as clip plane:- clipped stuff is in the mist!
    glFogi(GL_FOG_MODE,GL_LINEAR);	                // Simple linear depth cueing
    }

  // Dithering
  if(options&VIEWER_DITHER){
    glEnable(GL_DITHER);
    }

  // Enable lighting
  if(options&VIEWER_LIGHTING){
    glEnable(GL_LIGHTING);
    }

  // Set model matrix
  glLoadMatrixf(transform);
  }