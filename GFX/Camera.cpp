#include "../GUI/GUIMain.h"
#include "Camera.h"

CameraClass MainCamera;

void CameraClass::Rotate(float xvalue, float yvalue)
{
    
    this->LOOKAT(0) += xvalue * .10;
    this->LOOKAT(1) += yvalue * .10;

}

void CameraClass::Translate(float xvalue, float yvalue)
{
    this->POS(0) += xvalue * 10;
    this->POS(1) += yvalue * 10;
}

void CameraClass::Zoom(float value)
{
    this->POS(2) += value * 500;
}