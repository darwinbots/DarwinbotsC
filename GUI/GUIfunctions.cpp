#include "GUImain.h"

long MainWindow::onCmdQuit(FXObject *, FXSelector, void *)
{
        getApp()->exit(0);
        return 1;
}
long MainWindow::onCmdNewSimulation(FXObject *, FXSelector, void *){
	FXDialogBox Options(this, "Sim options ", DECOR_TITLE|DECOR_BORDER,
 		0,0,0,0, 0,0,0,0, 0,0);
 		
    FXTabBook *tabbook=new FXTabBook(&Options,NULL,0,LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_RIGHT);
    
    Species(tabbook, &Options);
    
    General(tabbook, &Options);
    
    PhysicsAndCosts(tabbook, &Options);
    
    Mutations(tabbook, &Options);
    
    ReststartAndL(tabbook, &Options);
    
    InternetOptions(tabbook, &Options);
    
    Recording(tabbook, &Options);
    
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
