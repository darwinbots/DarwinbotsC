#include "../GUI/MainWindow.h"
#include "Camera.h"

CameraClass MainCamera;

void CameraClass::Rotate(float xvalue, float yvalue)
{
    
    this->LOOKAT(0) += float(xvalue * .10f);
    this->LOOKAT(1) += float(yvalue * .10f);

}

void CameraClass::Translate(float xvalue, float yvalue)
{
    this->POS(0) += xvalue * 10;
    this->POS(1) += yvalue * 10;
}

void CameraClass::Zoom(float value)
{
    this->POS(2) += value;
}
