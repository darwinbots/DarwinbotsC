#include "ParserWindow.h"

int main(int argc, char **argv){

    FXApp app(PROJECT_NAME, "");
    app.init(argc, argv);

    ParserWindow* mainWindow = new ParserWindow(&app);

    app.create();

    mainWindow->show(PLACEMENT_CURSOR);
    mainWindow->maximize();
    mainWindow->setFocus();

    app.run();

    //WriteSett(Engine.MainDir() + "\\settings\\lastexit.set", TmpOpts);

    return 0;
}
