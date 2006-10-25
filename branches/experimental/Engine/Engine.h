#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <string>
#include <list>

#include "UniformEyeGrids.h"
#include "DnaParser.h"
#include "Robot.h"

typedef std::list<Robot *> RobotList;
typedef RobotList::iterator RobotIterator;

typedef std::list<Shot *> ShotList;
typedef std::list<Shot *>::iterator ShotIterator;

class Simulation
{
	//friend void DrawEyeGrid();

    public:
        RobotList* robotList;
        ShotList* shotList;

        Simulation();
        ~Simulation(){};
        bool BuildSysvars();

        void ExecuteDNA();
        void UpdateSim();
        void setup();
        const string& MainDir() {return mainDir;}
        void SetMainDir(string newDir) {mainDir=newDir;}

        void WhatCanSeeMe(Robot *me, list<Robot *> &BotList);
        void EyeGridRemoveDeadBot(Robot *bot);

        Robot* getRobot(unsigned long serial) const;  //find a robot with this serial number or return NULL
        void getRobotDisplayList(std::vector<SolidPrimitive> &displayList) const;
        void getShotDisplayList(ShotList& displayList) const;

        std::string getDnaText(unsigned long serial) const;

        void clear(); //poor man's destructor
	private:
        void LoadRobots();
        void ExecuteShots();
        void RepopulateVeggies();
        string mainDir;
        EyeGrid_Class EyeGrid;
        void ManipulateEyeGrid(Robot *bot);
        void handleBotCollisions();
        float BotCollisionsPos(Robot* bot);

        void createShot(Robot* parent);
        ShotIterator killShot(ShotIterator shot);

        DnaParser parser;
}extern Engine;

inline std::string Simulation::getDnaText(unsigned long serial) const
{
    return parser.getText(*(getRobot(serial)->dna));
}

#endif
