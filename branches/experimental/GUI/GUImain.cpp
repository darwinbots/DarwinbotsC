#include "MainWindow.h"
#include "../Engine/EngineThread.h"

#ifdef NO_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include "windows.h"
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ){
    int argc = 1;
    char *argv[] = {""};
#else
int main(int argc, char **argv){
#endif

    FXApp app(PROJECT_NAME, "");
    app.init(argc, argv);

    MainWindow* MainWindowHandle = new MainWindow(&app);

    app.create();

    MainWindowHandle->show(PLACEMENT_CURSOR);
    MainWindowHandle->maximize();
    MainWindowHandle->setFocus();

    app.addTimeout(MainWindowHandle, MainWindow::ID_UpdGfx);

    MainWindowHandle->engineThread->start();

    app.run();

    //WriteSett(Engine.MainDir() + "\\settings\\lastexit.set", TmpOpts);

    return 0;
}
