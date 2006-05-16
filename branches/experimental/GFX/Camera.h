#ifndef CAMERA_H
#define CAMERA_H

#include "../Common/Vectors.h"
#include "../GUI/MainWindow.h"

class CameraClass
{
    private:
    Vector3f POS;
    Vector3f LOOKAT;

    public:

    CameraClass() { POS.set(0,0,0);  LOOKAT.set(0,0,0);}

    void Zoom(float value);
    void Translate(float xvalue, float yvalue);
    void Rotate(float xvalue, float yvalue);

    const Vector3f pos() {return POS;}
    const Vector3f lookat() {return LOOKAT;}
};

extern CameraClass MainCamera;

#endif
