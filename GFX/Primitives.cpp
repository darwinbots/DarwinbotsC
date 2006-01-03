#include "../GUI/GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>

#include "../Common/Math3d.h"
#include "../Engine/Globals.h"

using namespace Math3D;

void CreatePoint(Vector4 c, float bigness)
{
	glPointSize(bigness);
	glBegin(GL_POINTS);
    glVertex3f(c.x(),c.y(),c.z());
	glEnd();
}

void CreateSphere(Vector4 c,float r,int n = 5)
{
   float i,j;
   float theta1,theta2,theta3, jalt, ialt;
   Vector4 e,p;

   if (n < 0)
	 n = -n;
   n=(int)pow(2,n);//n must be equal to a power of 2 for the iterations to meet appropriately.
   
   if (r < 0) 
     r = -r;
   
   if (n < 4 || r <= 0) {
      glBegin(GL_POINTS);
      glVertex3f(c.x(),c.y(),c.z());
      glEnd();
      return;
   }  

   for (j=(float)-n/4;j<n/4;j++)
   {
      jalt = (n / 4) - (j)-1;
	  theta1 = (float)(j * PI * 2) / (n);
      theta2 = (float)((j + 1) * PI * 2) / (n);

      glBegin(GL_TRIANGLE_STRIP);
      for (i=0;i<=n;i++)
	  {
		 ialt = n-i;
		 theta3 = (float)(i * 2 *PI)/n;
		 
         e.set(float(cos(theta2) * cos(theta3)), 
               (float)sin(theta2),
               float(cos(theta2) * sin(theta3)));

		 p.set(c.x() + r * e.x(),
               c.y() + r * e.y(),
               c.z() + r * e.z());

         glNormal3f(e.x(),e.y(),e.z());
         glTexCoord2f(ialt / n, 1 - 2 * (jalt)/ n);
		 glVertex3f(p.x(),p.y(),p.z());

         e.set(float(cos(theta1) * cos(theta3)),
               float(sin(theta1)),
               float(cos(theta1) * sin(theta3)));
		 
		 p.set(c.x() + r * e.x(),
               c.y() + r * e.y(),
               c.z() + r * e.z());

         glNormal3f(e.x(),e.y(),e.z());
         glTexCoord2f(ialt / n, 1 - 2 * (jalt+1) / n);
		 glVertex3f(p.x(),p.y(),p.z());
      }
      glEnd();
   }
}

// Draws a simple box using the given corners
void CreateBox(Vector4 min, Vector4 max) {
  glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.,0.,-1.);
    glVertex3f(min.x(), min.y(), min.z());
    glVertex3f(min.x(), max.y(), min.z());
    glVertex3f(max.x(), min.y(), min.z());
    glVertex3f(max.x(), max.y(), min.z());
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(1.,0.,0.);
    glVertex3f(max.x(), min.y(), min.z());
    glVertex3f(max.x(), max.y(), min.z());
    glVertex3f(max.x(), min.y(), max.z());
    glVertex3f(max.x(), max.y(), max.z());
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.,0.,1.);
    glVertex3f(max.x(), min.y(), max.z());
    glVertex3f(max.x(), max.y(), max.z());
    glVertex3f(min.x(), min.y(), max.z());
    glVertex3f(min.x(), max.y(), max.z());
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(-1.,0.,0.);
    glVertex3f(min.x(), min.y(), max.z());
    glVertex3f(min.x(), max.y(), max.z());
    glVertex3f(min.x(), min.y(), min.z());
    glVertex3f(min.x(), max.y(), min.z());
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.,1.,0.);
    glVertex3f(min.x(), max.y(), min.z());
    glVertex3f(min.x(), max.y(), max.z());
    glVertex3f(max.x(), max.y(), min.z());
    glVertex3f(max.x(), max.y(), max.z());
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
    glNormal3f(0.,-1.,0.);
    glVertex3f(max.x(), min.y(), max.z());
    glVertex3f(max.x(), min.y(), min.z());
    glVertex3f(min.x(), min.y(), max.z());
    glVertex3f(min.x(), min.y(), min.z());
  glEnd();
  }

void CreateCylinder(Vector4 p1, Vector4 p2, float radius)
{
    //I make no claims that this is the best way
    
    GLUquadricObj *quadric = gluNewQuadric();
    gluCylinder(quadric,radius,radius,Length3(p2 - p1),32,32);	// Draw Our Cylinder   
    gluDeleteQuadric(quadric);
}