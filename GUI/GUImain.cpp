#include "GUImain.h"
#include "OptionsForm.h"
#include <signal.h>
#include "../Engine/SimOptions.h"
#include "../Engine/Engine.h"
#include "../Engine/EngineThread.h"
#include "../Engine/HardDriveRoutines.h"
#include "../GFX/Icons/icons.cpp" //I know this is unorthodox, but I get odd linker errors unless I
                                  //include the cpp file itself.

void StatusBar(MainWindow *object)
{
    FXHorizontalFrame *statusbar = new FXHorizontalFrame(object, LAYOUT_SIDE_BOTTOM | FRAME_RAISED);
    
    new FXLabel(statusbar, "Cyc/Sec: ", NULL, FRAME_SUNKEN | JUSTIFY_LEFT);

    new FXTextField(statusbar,7,new FXDataTarget(SimOpts.CycSec),
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    
    new FXLabel(statusbar, "Objects: ", NULL, FRAME_SUNKEN | JUSTIFY_LEFT);

    new FXTextField(statusbar,4,new FXDataTarget((FXulong &) SimOpts.TotObjects),
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

    new FXLabel(statusbar, "Vegs: ", NULL, FRAME_SUNKEN | JUSTIFY_LEFT);

    new FXTextField(statusbar,4,new FXDataTarget((FXulong &) SimOpts.TotVegsNow),
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

    new FXLabel(statusbar, "Bots: ", NULL, FRAME_SUNKEN | JUSTIFY_LEFT);

    new FXTextField(statusbar,4,new FXDataTarget((FXulong &) SimOpts.TotBotsNow),
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

    new FXLabel(statusbar, "Cycles: ", NULL, FRAME_SUNKEN | JUSTIFY_LEFT);

    new FXTextField(statusbar,14,new FXDataTarget((FXulong &) SimOpts.TotRunCycle),
            FXDataTarget::ID_VALUE,
            TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
}

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp *app)
    : FXMainWindow(app, PROJECT_NAME, NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{
    FXToolBarShell *dragshell1 = new FXToolBarShell(this, FRAME_RAISED);
    FXMenuBar* menubar = new FXMenuBar(this, dragshell1, FRAME_RAISED|LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
    FXToolBar* toolbar = new FXToolBar(this, dragshell1);

    new FXButton(toolbar,"\tPlay",new FXGIFIcon(getApp(),PlayButtonGIF, 128, 128, 255),
    //  tgt, 'selector', opts,  x, y, w,  h,  padl, padr
        this, MainWindow::ID_PlayEngine, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);
    new FXButton(toolbar,"\tCycle",new FXGIFIcon(getApp(),CycleButtonGIF, 192, 192, 192),
        this, MainWindow::ID_StepEngine, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);
    new FXButton(toolbar,"\tPause",new FXGIFIcon(getApp(),PauseButtonGIF),
        this, MainWindow::ID_PauseEngine, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);

    new FXButton(toolbar,"\tTurn Off Graphics",new FXGIFIcon(getApp(),MonitorGIF),
        this, MainWindow::ID_TurnOffGraphics, BUTTON_NORMAL | LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0, 0, 22, 20);
    GraphicsOn = true;

    StatusBar(this);

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

    OptionsForm = new OptionsFormDialogBox(this);
}

MainWindow::~MainWindow()
{
    delete fileMenu;
}

void MainWindow::create()
{
    FXMainWindow::create();
}


long MainWindow::onCmdQuit(FXObject *, FXSelector, void *)
{
    getApp()->exit(0);
    return 1;
}

long MainWindow::onCmdNewSimulation(FXObject *, FXSelector, void *)
{
    TmpOpts = SimOpts;
    OptionsForm->show(PLACEMENT_OWNER);

    return 1;

}
long MainWindow::onCmdSaveSimulation(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdLoadSimulation(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdAutoSave(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdAbout(FXObject *, FXSelector, void *)
{
    //FXDialogBox About(this, "About " PROJECT_NAME, DECOR_TITLE|DECOR_BORDER,
// 		  0,0,0,0, 0,0,0,0, 0,0);
//
//    FXVerticalFrame *Frame =
//              new FXVerticalFrame(&About, LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y,
//             	0,0,0,0, 10,10,10,10, 0,0);
//              new FXLabel(Frame,
//                          PROJECT_NAME " Version " PROJECT_VERSION ".\n\n",
//            		          0, JUSTIFY_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
//
//              FXButton *Button = new FXButton(Frame, "OK", 0, this,
//        	      ID_Quit, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
//                0,0,0,0, 32,32,5,5);
//
//    Button->setFocus();
//    About.execute(PLACEMENT_OWNER);
    FXMessageBox::information(this, MBOX_OK, "About " PROJECT_NAME,
                                PROJECT_NAME " Version " PROJECT_VERSION ".\n");
    return 1;
}

long MainWindow::onCmdShowOptions(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdShowLog(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdNewViewer(FXObject*,FXSelector,void*){return 1;}

long MainWindow::onCycle(FXObject *, FXSelector, void *)
{
    return EngineThread.Flow.Add_Cycles(1);
}
long MainWindow::onPlay(FXObject *, FXSelector, void *)
{
    return EngineThread.Flow.Play();
}
long MainWindow::onPause(FXObject *, FXSelector, void *)
{
    return EngineThread.Flow.Pause();
}

long MainWindow::onTurnOffGraphics(FXObject *, FXSelector, void *)
{
    GraphicsOn = !GraphicsOn;
    return 1;
}


MainWindow *MainWindowHandle;

#ifndef DB_NOGUI
#ifdef _WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ){
    int argc = 1;
    char *argv[] = {""};
#else
    int main(int argc, char **argv){
#endif

    EngineThread.ProgramInitialize();
    
    FXApp app(PROJECT_NAME, "");
    app.init(argc, argv);

    MainWindowHandle = new MainWindow(&app);
        
    app.create();

    MainWindowHandle->show(PLACEMENT_CURSOR);
    MainWindowHandle->maximize();
    MainWindowHandle->setFocus();

    app.addTimeout(MainWindowHandle, MainWindow::ID_UpdGfx);
                
    EngineThread.start();
    
    app.run();
    
    //WriteSett(Engine.MainDir() + "\\settings\\lastexit.set", TmpOpts);

    return 0;
}
#endif
