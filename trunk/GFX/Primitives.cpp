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

    divisions = (long)pow(2.0, divisions);

	glBegin(GL_LINE_LOOP);
    for(int i =0;i<divisions;i++)
	{
        angle = float(i*2*PI/divisions);
        glVertex2f(c.x()+cosf(angle)*radius,c.y()+sinf(angle)*radius);
    }
	glEnd();
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