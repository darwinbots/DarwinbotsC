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
#ifdef DB_NOGUI
int main()
{
    Engine.SetupSim();
    for(int j =0;j<50;j++){
        cout<<RandomBlock().text()<<" ";
    }
    cout<<endl;
    clock_t startTime;
    startTime=clock();
	for(int i =0;i<100;i++){
        Engine.UpdateSim();
        cout<<"+";
    }
    cout<<endl;
    int id;
    do {
        id=frnd(0,MaxRobs);
    } while (rob[id]==NULL || rob[id]->Veg==true);
    cout<<rob[id]->DNA_Text();
    
    cout<<"1000 turns in "<<difftime(clock(),startTime)/CLOCKS_PER_SEC<<" seconds.";
    
    
	cout<<system("PAUSE");
	
    return 0;    
}
#endif
