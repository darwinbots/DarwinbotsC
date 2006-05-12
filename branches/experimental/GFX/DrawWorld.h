#ifndef DRAWWORLD_H
#define DRAWWORLD_H

#include "../GUI/GUImain.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "../Engine/Robot.h"
#include "Primitives.h"
#include "Camera.h"

enum
{
    BOT_GUTS = 10,
    BOT_PERIMETER
};

extern void SetupDisplayLists();
extern void DrawWorld(double width, double height);
extern int CurrBotUserSelected;

#endif

