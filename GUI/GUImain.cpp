#include "GUImain.h"
#include <signal.h>
#include "../Engine/SimOptions.h"
#include "../Engine/Engine.h"
#include "../Engine/EngineThread.h"
#include "../GFX/Icons/icons.cpp" //I know this is unorthodox, but I get odd linker errors unless I
                                  //include the cpp file itself.

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp *app)
    : FXMainWindow(app, PROJECT_NAME, NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{
    FXMenuBar *menubar;
    
    FXToolBarShell *dragshell1 = new FXToolBarShell(this, FRAME_RAISED);
    menubar = new FXMenuBar(this, dragshell1, FRAME_RAISED|LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
    FXToolBar *toolbar = new FXToolBar(this, dragshell1);

    new FXButton(toolbar,"\tPlay",new FXGIFIcon(getApp(),PlayButtonGIF, 128, 128, 255),
    //  tgt, 'selector', opts,  x, y, w,  h,  padl, padr
        this, MainWindow::ID_PlayEngine, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);
    new FXButton(toolbar,"\tCycle",new FXGIFIcon(getApp(),CycleButtonGIF, 192, 192, 192),
        this, MainWindow::ID_StepEngine, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);
    new FXButton(toolbar,"\tPause",new FXGIFIcon(getApp(),PauseButtonGIF),
        this, MainWindow::ID_PauseEngine, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);

    //new FXToolBarGrip(menubar, menubar, FXMenuBar::ID_TOOLBARGRIP);
    
    FXStatusBar *statusbar;
    statusbar = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|/*STATUSBAR_WITH_DRAGCORNER|*/FRAME_RAISED);
    
    fileMenu = new FXMenuPane(this);
    new FXMenuCommand(fileMenu, "&New Simulation\tF1\tStart a new Simulation.", 0, this, ID_NewSimulation);
    new FXMenuCommand(fileMenu, "&Load Simulation\tF2\tLoad a old Simulation.", 0, this, ID_LoadSimulation);
    new FXMenuCommand(fileMenu, "&Save Simulation\tF3\tSave current Simulation.", 0, this, ID_SaveSimulation);
    new FXMenuCommand(fileMenu, "&Auto save\t\tAuto save Simulation.", 0, this, ID_AutoSave);
    new FXMenuCommand(fileMenu, "&Quit\tF4\tClose DarwinBots.", 0, this, ID_Quit);
    new FXMenuTitle(menubar, "&File", 0, fileMenu);
    
    editMenu = new FXMenuPane(this);
    new FXMenuCommand(editMenu, "&Insert organism", 0, 0, 0);
    new FXMenuCommand(editMenu, "&Global mutation rates", 0, 0, 0);
    new FXMenuCommand(editMenu, "&Modify costs", 0, 0, 0);
    new FXMenuCommand(editMenu, "&Physics", 0, 0, 0);
    new FXMenuCommand(editMenu, "&Draw walls", 0, 0, 0);
    new FXMenuCommand(editMenu, "&Find best", 0, 0, 0);
    new FXMenuTitle(menubar, "&Edit", 0, editMenu);
    
    robotOptionsMenu = new FXMenuPane(this);
    new FXMenuCommand(robotOptionsMenu, "&Show robot info", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Show family ties", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Mutation rates", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Change color", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Open console", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&View genes activations", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Kill robot", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Save robot's DNA", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Select entire organism", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Save entire organism", 0, 0, 0);
    new FXMenuCommand(robotOptionsMenu, "&Kill entire organism", 0, 0, 0);
    new FXMenuTitle(menubar, "&Robot Options", 0, robotOptionsMenu);
    
    internetMenu = new FXMenuPane(this);
    new FXMenuCommand(internetMenu, "Show &Options\t\tShow options.", 0, this, ID_ShowOptions);
    new FXMenuCommand(internetMenu, "&Show Log\t\t Show log.", 0, this, ID_ShowLog);
    new FXMenuTitle(menubar, "&Internet", 0, internetMenu);
    
    helpMenu = new FXMenuPane(this);
    new FXMenuCommand(helpMenu, "&about\t\tAbout DarwinBots.", 0, this, ID_About);
    new FXMenuTitle(menubar, "&Help", 0, helpMenu);
    
    GLWindow();
    ConnectVar();

    BotDebug = NULL;
}

MainWindow::~MainWindow()
{
    delete fileMenu;
}

void MainWindow::create()
{
    FXMainWindow::create();
}

MainWindow *MainWindowHandle;

#ifndef DB_NOGUI
int main(int argc, char **argv)
{
    FXApp app(PROJECT_NAME, "yo");
    app.init(argc, argv);

    MainWindowHandle = new MainWindow(&app);
        
    app.create();

    MainWindowHandle->show(PLACEMENT_CURSOR);
    MainWindowHandle->maximize();
    MainWindowHandle->setFocus();

    app.addTimeout(MainWindowHandle, MainWindow::ID_UpdGfx);
                
    //later we will move this into Engine.SetupSim()
    EngineThread.start();
    
    return app.run();
}
#endif