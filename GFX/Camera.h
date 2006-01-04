#ifndef CAMERA_H
#define CAMERA_H

#include "../Common/Math3d.h"
#include "../GUI/GUImain.h"

using namespace Math3D;

class CameraClass
{
    //private:
    public:
    Vector4 POS;
    Vector4 LOOKAT;

    public:

    CameraClass() { POS.set(0,0,0);  LOOKAT.set(0,0,0);}

    void Zoom(float value);
    void Translate(float xvalue, float yvalue);
    void Rotate(float xvalue, float yvalue);

    const Vector4 pos() {return POS;}
    const Vector4 lookat() {return LOOKAT;}
}extern MainCamera;

#endif