#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "Common/Random.h"
#include "Common/Math3D.h"
#include "Engine/Robot.h"
#include "Engine/Engine.h"

using namespace std;

/* This is a rudimentary benchmark of the core engine. To use it,
define DB_NOGUI in your compiler and do not compile anything in folders GUI or
GFX, nor EngineThread.cpp. */

int main()
{
	Engine.SetupSim();
    	
    clock_t startTime, endTime;
    startTime=clock();
	for(int i =0;i<100;i++){
        Engine.UpdateSim();
        cout<<"+";
    }
    cout<<endl;
    cout<<"100 turns in "<<difftime(clock(),startTime)/CLOCKS_PER_SEC<<" seconds.";
	cout<<system("PAUSE");
	
    return 0;    
}
