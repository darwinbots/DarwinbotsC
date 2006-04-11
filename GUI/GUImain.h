#ifndef GUIMAIN_H
#define GUIMAIN_H

#include <fx.h>
#include <fx3d.h>

class BotDebug_Window;
class OptionsFormDialogBox;

#define PROJECT_NAME "DarwinBots 2.5"
#define PROJECT_VERSION "2.5 Pre-Alpha"

#define LAYOUT_FILL_XY LAYOUT_FILL_X|LAYOUT_FILL_Y
#define LAYOUT_FILL_RC LAYOUT_FILL_COLUMN|LAYOUT_FILL_ROW
#define LAYOUT_FILL_ALL LAYOUT_FILL_XY | LAYOUT_FILL_RC
#define LAYOUT_FILL_YC LAYOUT_FILL_COLUMN | LAYOUT_FILL_Y
#define LAYOUT_FILL_XR LAYOUT_FILL_ROW | LAYOUT_FILL_X

class MainWindow : public FXMainWindow
{
    FXDECLARE(MainWindow)
    
    FXMenuPane *fileMenu ,*editMenu ,*robotOptionsMenu,*SimOptionsMenu ,*internetMenu, *helpMenu;

protected:
    MainWindow(){}
    FXDataTarget   ZGravity_Tar;
    FXDataTarget   YGravity_Tar;
    FXDataTarget   CoefficientKinetic_Tar;
    FXDataTarget   CoefficientStatic_Tar;
    FXDataTarget   Density_Tar;
    FXDataTarget   Viscosity_Tar;
    FXDataTarget   Brownian_Tar;
    FXDataTarget   MovingEfficiency_Tar;
    FXDataTarget   PlanetEaters_Tar;
    FXDataTarget   PlanetEatersG_Tar;
    
    FXGLVisual     *glvisual;
    FXGLCanvas     *canvas;

    FXMDIClient *mdiclient;

    FXMDIChild *mainview;
    
    void ConnectVar();
        
public:
    OptionsFormDialogBox *OptionsForm;

    MainWindow(FXApp *app);
    ~MainWindow();
    
    virtual void create();

    int MainWindow::Selection(unsigned int MouseX, unsigned int MouseY);
    
    enum
    {
        ID_MainView = FXMainWindow::ID_LAST,
        ID_Quit,
        ID_NewSimulation,
        ID_SaveSimulation,
        ID_LoadSimulation,
        ID_AutoSave,
        ID_About,
        ID_ShowOptions,
        ID_ShowLog,
        ID_PAndCAdv,
        ID_PCAdvancedControls,
        ID_GLV,
        ID_NewViewer,
        ID_Viewer,
        ID_UpdGfx,

        ID_PauseEngine,
        ID_StepEngine,
        ID_PlayEngine,

        ID_LAST
    };
    
    long onCmdQuit              (FXObject *, FXSelector, void *);
    long onCmdNewSimulation     (FXObject *, FXSelector, void *);
    long onCmdSaveSimulation    (FXObject *, FXSelector, void *);
    long onCmdLoadSimulation    (FXObject *, FXSelector, void *);
    long onCmdAutoSave          (FXObject *, FXSelector, void *);
    long onCmdAbout             (FXObject *, FXSelector, void *);
    long onCmdShowOptions       (FXObject *, FXSelector, void *);
    long onCmdShowLog           (FXObject *, FXSelector, void *);
    long onCmdPAndCAdv          (FXObject *, FXSelector, void *);
    
    long onCmdPCAdvancedControls(FXObject *, FXSelector, void *);
    long onCmdNewViewer         (FXObject*,FXSelector,void*);
    long onUpdGfx               (FXObject*,FXSelector,void*);
    
    long DrawScene              (FXObject *, FXSelector, void *);
    long DrawScene              ();

    long onMouseWheel           (FXObject *, FXSelector, void *);
    long onMotion               (FXObject *, FXSelector, void *);
    
    long onLeftBtnPress         (FXObject *, FXSelector, void *);
    long onLeftBtnRelease       (FXObject *, FXSelector, void *);

    long onRightBtnPress        (FXObject *, FXSelector, void *);
    long onRightBtnRelease      (FXObject *, FXSelector, void *);
    
    long onUpdSim               (FXObject *, FXSelector, void *);

    long onCycle                (FXObject *, FXSelector, void *);
    long onPlay                 (FXObject *, FXSelector, void *);
    long onPause                (FXObject *, FXSelector, void *);

    long GLWindow               ();


    long onBotDebug             ();
    
}extern *MainWindowHandle;

FXDEFMAP(MainWindow) MainWindowMap[] = {
  FXMAPFUNC(SEL_CONFIGURE, MainWindow::ID_MainView,         MainWindow::DrawScene),
  FXMAPFUNC(SEL_PAINT,     MainWindow::ID_MainView,         MainWindow::DrawScene),
  FXMAPFUNC(SEL_SIGNAL,    MainWindow::ID_Quit,             MainWindow::onCmdQuit),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_Quit,             MainWindow::onCmdQuit),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_NewSimulation,    MainWindow::onCmdNewSimulation),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_SaveSimulation,   MainWindow::onCmdSaveSimulation),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_LoadSimulation,   MainWindow::onCmdLoadSimulation),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_AutoSave,         MainWindow::onCmdAutoSave),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_About,            MainWindow::onCmdAbout),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_ShowOptions,      MainWindow::onCmdShowOptions),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_ShowLog,          MainWindow::onCmdShowLog),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_PAndCAdv,         MainWindow::onCmdPAndCAdv),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_PCAdvancedControls,MainWindow::onCmdPCAdvancedControls),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_NewViewer,        MainWindow::onCmdNewViewer),
  FXMAPFUNC(SEL_KEYPRESS,  0,			                    MainWindow::onKeyPress),
  FXMAPFUNC(SEL_TIMEOUT,   MainWindow::ID_UpdGfx,           MainWindow::onUpdGfx),
  
  FXMAPFUNC(SEL_MOUSEWHEEL,MainWindow::ID_MainView,         MainWindow::onMouseWheel),
  FXMAPFUNC(SEL_MOTION    ,MainWindow::ID_MainView,         MainWindow::onMotion),
  
  FXMAPFUNC(SEL_LEFTBUTTONPRESS, MainWindow::ID_MainView,   MainWindow::onLeftBtnPress),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE, MainWindow::ID_MainView, MainWindow::onLeftBtnRelease),

  FXMAPFUNC(SEL_RIGHTBUTTONPRESS, MainWindow::ID_MainView,   MainWindow::onRightBtnPress),
  FXMAPFUNC(SEL_RIGHTBUTTONRELEASE, MainWindow::ID_MainView, MainWindow::onRightBtnRelease),
  
  FXMAPFUNC(SEL_COMMAND, MainWindow::ID_StepEngine, MainWindow::onCycle),
  FXMAPFUNC(SEL_COMMAND, MainWindow::ID_PlayEngine, MainWindow::onPlay),
  FXMAPFUNC(SEL_COMMAND, MainWindow::ID_PauseEngine, MainWindow::onPause)
};

#endif
