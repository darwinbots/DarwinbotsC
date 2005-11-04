#include "GUImain.h"
#include <signal.h>

const unsigned char winapp[]={
  0x47,0x49,0x46,0x38,0x37,0x61,0x10,0x00,0x10,0x00,0xf2,0x00,0x00,0xb2,0xc0,0xdc,
  0x80,0x80,0x80,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0xff,0x00,
  0x00,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x03,
  0x38,0x08,0xba,0xdc,0x10,0x30,0xca,0x09,0x85,0xbd,0xf8,0x86,0x11,0x04,0xf9,0x60,
  0xf8,0x6d,0x9d,0x48,0x14,0x03,0x8a,0x92,0x02,0xe5,0x72,0x42,0x21,0xcf,0xb4,0xcc,
  0xd6,0x78,0x71,0xe7,0xf4,0xce,0xdb,0xb0,0xdf,0xcc,0xf7,0x23,0xf2,0x48,0xae,0xd7,
  0x60,0xc9,0x6c,0x3a,0x07,0x8e,0xe8,0x22,0x01,0x00,0x3b
  };

FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(FXApp *app)
    : FXMainWindow(app, PROJECT_NAME, 0, 0, DECOR_ALL, 0, 0, 800, 600)
{
    
    ProOrFixed = 1;
    ProOrFixed_Target.connect(ProOrFixed);
    SolidOrFluid = 1;
    SolidOrFluid_Target.connect(SolidOrFluid);
    FXMenuBar *menubar;
    
    FXToolBarShell *dragshell1 = new FXToolBarShell(this, FRAME_RAISED);
    menubar = new FXMenuBar(this, dragshell1, FRAME_RAISED|LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
    new FXToolBarGrip(menubar, menubar, FXMenuBar::ID_TOOLBARGRIP);
    
    FXStatusBar *statusbar;
    statusbar = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER|FRAME_RAISED);
    
    fileMenu = new FXMenuPane(this);
    new FXMenuCommand(fileMenu, "&New Simulation\tF1\tStart a new Simulation.", 0, this, ID_NewSimulation);
    new FXMenuCommand(fileMenu, "&Load Simulation\tF2\tLoad a old Simulation.", 0, this, ID_LoadSimulation);
    new FXMenuCommand(fileMenu, "&Save Simulation\tF3\tSave current Simulation.", 0, this, ID_SaveSimulation);
    new FXMenuCommand(fileMenu, "&Auto save\t\tAuto save Simulation.", 0, this, ID_AutoSave);
    new FXMenuCommand(fileMenu, "&Quit\tF4\tClose DarwinBots.", 0, this, ID_Quit);
    new FXMenuTitle(menubar, "&File", 0, fileMenu);
    
    editMenu = new FXMenuPane(this);
    new FXMenuTitle(menubar, "&Edit", 0, editMenu);
    
    robotOptionsMenu = new FXMenuPane(this);
    new FXMenuTitle(menubar, "&Robot Options", 0, robotOptionsMenu);
    
    internetMenu = new FXMenuPane(this);
    new FXMenuCommand(internetMenu, "Show &Options\t\tShow options.", 0, this, ID_ShowOptions);
    new FXMenuCommand(internetMenu, "&Show Log\t\t Show log.", 0, this, ID_ShowLog);
    new FXMenuTitle(menubar, "&Internet", 0, internetMenu);
    
    helpMenu = new FXMenuPane(this);
    new FXMenuCommand(helpMenu, "&about\t\tAbout DarwinBots.", 0, this, ID_About);
    new FXMenuTitle(menubar, "&Help", 0, helpMenu);
    
}

MainWindow::~MainWindow()
{
    delete fileMenu;
}

void MainWindow::create()
{
    FXMainWindow::create();
}

int main(int argc, char **argv)
{
        FXApp app(PROJECT_NAME, "yo");
        app.init(argc, argv);

        MainWindow *w = new MainWindow(&app);
        app.addSignal(SIGINT, w, MainWindow::ID_Quit);
        app.create();
        w->show(PLACEMENT_CURSOR);
        w->setFocus();

        return app.run();
}
