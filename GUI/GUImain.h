#include <Fox-1.4/fx.h>
#include <Fox-1.4/fx3d.h>

#define PROJECT_NAME "DarwinBots"
#define PROJECT_VERSION "0.0.1"

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
    void ConnectVar();
        
public:
    MainWindow(FXApp *app);
    ~MainWindow();
    
    virtual void create();
    
    enum
    {
        ID_Quit = FXMainWindow::ID_LAST,
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
    long Species                (FXTabBook *TabBook,FXDialogBox *Options);
    long General                (FXTabBook *TabBook,FXDialogBox *Options);
    long PhysicsAndCosts        (FXTabBook *TabBook,FXDialogBox *Options);
    long Mutations              (FXTabBook *TabBook,FXDialogBox *Options);
    long ReststartAndL          (FXTabBook *TabBook,FXDialogBox *Options);
    long InternetOptions        (FXTabBook *TabBook,FXDialogBox *Options);
    long Recording              (FXTabBook *TabBook,FXDialogBox *Options);
    long onCmdPCAdvancedControls(FXObject *, FXSelector, void *);
    long onCmdNewViewer         (FXObject*,FXSelector,void*);
    long GLWindow               ();
    
};

FXDEFMAP(MainWindow) MainWindowMap[] = {
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
  FXMAPFUNC(SEL_COMMAND,  MainWindow::ID_PCAdvancedControls,MainWindow::onCmdPCAdvancedControls),
  FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_NewViewer,        MainWindow::onCmdNewViewer),
  FXMAPFUNC(SEL_KEYPRESS,  0,			                    MainWindow::onKeyPress)
};

