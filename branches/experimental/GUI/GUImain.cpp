#include "MainWindow.h"
#include "../Engine/EngineThread.h"

#ifdef NO_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ){
    int argc = 1;
    char *argv[] = {"Blah", "blah"};
#else
int main(int argc, char **argv){
#endif

    FXApp app(PROJECT_NAME, "");
    app.init(argc, argv);

    MainWindow* mainWindow = new MainWindow(&app);

    app.create();

    mainWindow->show(PLACEMENT_CURSOR);
    mainWindow->maximize();
    mainWindow->setFocus();

    app.addTimeout(mainWindow, MainWindow::ID_UpdGfx);

    mainWindow->engineThread->start(); //for debugging convenience

    app.run();

    //WriteSett(Engine.MainDir() + "\\settings\\lastexit.set", TmpOpts);

    return 0;
}
