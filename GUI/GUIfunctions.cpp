#include "GUImain.h"
#include "../Engine/Engine.h"
#include "../Engine/EngineThread.h"
//#include "../Engine/SimOptions.h"

long MainWindow::onCmdQuit(FXObject *, FXSelector, void *)
{
    getApp()->exit(0);
    return 1;
}

long MainWindow::onCmdNewSimulation(FXObject *, FXSelector, void *)
{
    FXDialogBox Options(this, "Sim options ", DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0,0,0,0,0,0,0);
    
    FXMatrix *LayoutMatrix=new FXMatrix(&Options,1,MATRIX_BY_COLUMNS|
        LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_FILL_ROW | LAYOUT_FILL_COLUMN,
        0,0,0,0,0,0);
    
    FXTabBook *tabbook=new FXTabBook(LayoutMatrix,NULL,0,
        LAYOUT_FILL_X | LAYOUT_FILL_Y | LAYOUT_FILL_ROW | LAYOUT_FILL_COLUMN);
    
    Species(tabbook, &Options);

    Veggy(tabbook, &Options);
    
    General(tabbook, &Options);
    
    PhysicsAndCosts(tabbook, &Options);
    
    Mutations(tabbook, &Options);
    
    ReststartAndL(tabbook, &Options);
    
    InternetOptions(tabbook, &Options);
    
    Recording(tabbook, &Options);
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    FXGroupBox *ButtonGroup=new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *ButtonMatrix = new FXMatrix(ButtonGroup, 1, MATRIX_BY_ROWS | LAYOUT_FILL_X | LAYOUT_FILL_ROW,
        0,0,0,0,0,0,0,0);
    
    new FXButton(ButtonMatrix, "Load Settings", 0, &Options, FXDialogBox::ID_ACCEPT);
    new FXButton(ButtonMatrix, "Save Settings", 0, &Options, FXDialogBox::ID_ACCEPT);
    
    new FXSeparator(ButtonMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
    new FXButton(ButtonMatrix, "Cancel", 0, &Options, FXDialogBox::ID_CANCEL);
    new FXSeparator(ButtonMatrix, LAYOUT_FILL_X|LAYOUT_FILL_COLUMN);
    
    new FXButton(ButtonMatrix, "Pause", 0, &Options, FXDialogBox::ID_ACCEPT);    
    new FXButton(ButtonMatrix, "Start New", 0, &Options, FXDialogBox::ID_ACCEPT);
    new FXButton(ButtonMatrix, "Change", 0, &Options, FXDialogBox::ID_ACCEPT);

    /////////////////////////////////////////////////////////////////////////////////////////////////                
    Options.execute(PLACEMENT_OWNER);   
    
    return 1;
        
}
long MainWindow::onCmdSaveSimulation(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdLoadSimulation(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdAutoSave(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdAbout(FXObject *, FXSelector, void *)
{
	  FXDialogBox About(this, "About " PROJECT_NAME, DECOR_TITLE|DECOR_BORDER,
 		  0,0,0,0, 0,0,0,0, 0,0);
 		
    FXVerticalFrame *Frame =
              new FXVerticalFrame(&About, LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y,
             	0,0,0,0, 10,10,10,10, 0,0);
              new FXLabel(Frame,
                          PROJECT_NAME " Version " PROJECT_VERSION ".\n\n",
            		          0, JUSTIFY_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

              FXButton *Button = new FXButton(Frame, "OK", 0, this,
        	      ID_Quit, BUTTON_INITIAL|BUTTON_DEFAULT|FRAME_RAISED|FRAME_THICK|LAYOUT_CENTER_X,
                0,0,0,0, 32,32,5,5);
                 	
    Button->setFocus();
    About.execute(PLACEMENT_OWNER);

    return 1;
}

long MainWindow::onCmdShowOptions(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdShowLog(FXObject *, FXSelector, void *){return 1;}
long MainWindow::onCmdNewViewer(FXObject*,FXSelector,void*){return 1;}

void MainWindow::ConnectVar()
{
     /*CoefficientKinetic_Tar.Connect(TmpOpts.CoefficientKinetic);
     CoefficientStatic_Tar.Connect(TmpOpts.CoefficientStatic);
     ZGravity_Tar.Connect(TmpOpts.ZGravity);
     YGravity_Tar.Connect(TmpOpts.YGravity);
     Density_Tar.Connect(TmpOpts.Density);
     Viscosity_Tar.Connect(TmpOpts.Viscosity);
     Brownian_Tar.Connect(TmpOpts.Brownian);
     MovingEfficiency_Tar.Connect(TmpOpts.MovingEfficiency);
     PlanetEaters_Tar.Connect(TmpOpts.PlanetEaters);
     PlanetEatersG_Tar.Connect(TmpOpts.PlanetEatersG);*/
}

//these three fxns aren't thread safe, which is a problem
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