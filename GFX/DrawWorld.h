#ifndef DRAWWORLD_H
#define DRAWWORLD_H

enum
{
    BOT_GUTS = 10,
    BOT_PERIMETER
};

extern void SetupDisplayLists();
extern void DrawWorld(double width, double height);
extern int CurrBotUserSelected;

#endif

