#include "../GUI/GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>

#include "../Common/Vectors.h"
#include "../Engine/Globals.h"

void CreatePoint(Vector3f c, float bigness)
{
	glPointSize(bigness);
	glBegin(GL_POINTS);
    glVertex3f(c.x(),c.y(), c.z());
	glEnd();
}

void CreateCircle(Vector3f c, float radius, long divisions)
{
	float angle;

    divisions = (long)pow(2, divisions);

	glBegin(GL_LINE_LOOP);
    for(int i =0;i<divisions;i++)
	{
        angle = float(i*2*PI/divisions);
        glVertex2f(c.x()+cosf(angle)*radius,c.y()+sinf(angle)*radius);
    }
	glEnd();
}

void CreateSphere(Vector3f c,float r,int n = 5)
{
   float i,j;
   float theta1,theta2,theta3, jalt, ialt;
   Vector3f e,p;

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
		 
         e.set(cosf(theta2) * cosf(theta3), 
               sinf(theta2),
               cosf(theta2) * sinf(theta3));

		 p.set(c.x() + r * e.x(),
               c.y() + r * e.y(),
               c.z() + r * e.z());

         glNormal3f(e.x(),e.y(),e.z());
         glTexCoord2f(ialt / n, 1 - 2 * (jalt)/ n);
		 glVertex3f(p.x(),p.y(),p.z());

         e.set(cosf(theta1) * cosf(theta3),
               sinf(theta1),
               cosf(theta1) * sinf(theta3));
		 
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
void CreateBox(Vector3f min, Vector3f max) {
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

void CreateCylinder(Vector3f p1, Vector3f p2, float radius)
{
    //I make no claims that this is the best way
    
    GLUquadricObj *quadric = gluNewQuadric();
    gluCylinder(quadric,radius,radius,(p2 - p1).Length(),32,32);	// Draw Our Cylinder   
    gluDeleteQuadric(quadric);
}
