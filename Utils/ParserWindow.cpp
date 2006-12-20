#include "ParserWindow.h"

FXIMPLEMENT(ParserWindow, FXMainWindow, ParserWindowMap, ARRAYNUMBER(ParserWindowMap))

ParserWindow::ParserWindow(FXApp *app)
    : FXMainWindow(app, PROJECT_NAME, NULL, NULL, DECOR_ALL, 0, 0, 800, 600)
{
    parser.buildSysvars(std::string((FXFile::getCurrentDirectory()+"/sysvars2.5.txt").text()));
    FXMenuBar* menubar = new FXMenuBar(this, FRAME_RAISED|LAYOUT_SIDE_TOP|LAYOUT_FILL_X);

    fileMenu = new FXMenuPane(this);
    new FXMenuCommand(fileMenu, "&Load File\tF2\tLoad a DNA file.", 0, this, ID_Load);
    new FXMenuCommand(fileMenu, "&Quit\tF4\tClose DarwinBots.", 0, this, ID_Quit);
    new FXMenuTitle(menubar, "&File", 0, fileMenu);

    editor=new FXText(this,this,ID_Text,LAYOUT_FILL_X|LAYOUT_FILL_Y|TEXT_SHOWACTIVE);
}

long ParserWindow::onCmdQuit(FXObject *, FXSelector, void *)
{
    getApp()->exit(0);
    return 1;
}

long ParserWindow::onCmdLoad(FXObject *, FXSelector, void *)
{
    FXFileDialog opendialog(this,"Open Document");
    opendialog.setSelectMode(SELECTFILE_EXISTING);
    opendialog.setPatternList("DNA files (*.txt)");
    if(opendialog.execute())
    {
        FXString file=opendialog.getFilename();
        dna = parser.loadFile(file.text());
        editor->setText(parser.getText(dna).c_str());
    }
    return 1;
}


ParserWindow::~ParserWindow()
{
    delete fileMenu;
}

