#include "GUIMain.h"
#include <FXToolBarShell.h>

char *BotDetails[] = {
"Age",
"nrg",
"Generation",
"Body",
"New Mutations",
"Shell",
"Total Mutations",
"Slime",
"DNA Length",
"Poison",
"Number of Genes",
"Venom",
"Waste",
"PWaste",
""};

const unsigned char winapp[]={
  0x47,0x49,0x46,0x38,0x37,0x61,0x10,0x00,0x10,0x00,0xf2,0x00,0x00,0xb2,0xc0,0xdc,
  0x80,0x80,0x80,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,0x80,0xff,0xff,0xff,0x00,
  0x00,0x00,0x00,0x00,0x00,0x2c,0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x03,
  0x38,0x08,0xba,0xdc,0x10,0x30,0xca,0x09,0x85,0xbd,0xf8,0x86,0x11,0x04,0xf9,0x60,
  0xf8,0x6d,0x9d,0x48,0x14,0x03,0x8a,0x92,0x02,0xe5,0x72,0x42,0x21,0xcf,0xb4,0xcc,
  0xd6,0x78,0x71,0xe7,0xf4,0xce,0xdb,0xb0,0xdf,0xcc,0xf7,0x23,0xf2,0x48,0xae,0xd7,
  0x60,0xc9,0x6c,0x3a,0x07,0x8e,0xe8,0x22,0x01,0x00,0x3b
  };

///////////////////
long MainWindow::onBotDebug()
{
    int x;

    //FXToolBarShell *dragshell= new FXToolBarShell(this,FRAME_RAISED);
    
    //FXMDIChild BotDebug(mdiclient, "Bot Debug");
    //FXDialogBox BotDebug(this, "Bot Debug Controls", DECOR_TITLE|DECOR_BORDER);
    //FXToolBarShell BotDebug(this, FRAME_RAISED|FRAME_THICK, 0, 100);
    
    FXDockSite *topdock=new FXDockSite(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
    FXToolBarShell *dragshell = new FXToolBarShell(this,FRAME_RAISED);
    
    FXToolBar *BotDebug = new FXToolBar(topdock, dragshell, LAYOUT_DOCK_NEXT|LAYOUT_SIDE_TOP|FRAME_RAISED);
    new FXToolBarGrip(BotDebug,BotDebug,FXToolBar::ID_TOOLBARGRIP,TOOLBARGRIP_DOUBLE);    
    
    FXMatrix *LayoutMatrix1=new FXMatrix(BotDebug,1,MATRIX_BY_ROWS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);
            
    //THE STACK
    
    //the frame
    FXGroupBox *group1=new FXGroupBox(LayoutMatrix1,
        "Bot Stack",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *StackMatrix=new FXMatrix(group1,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    char buffer[256];
    
    for(x = 20; x > 10; x--)
    {
        new FXLabel(StackMatrix,strcat(itoa(x, buffer, 10), "th"),NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(StackMatrix,10,NULL,0,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);

        new FXLabel(StackMatrix,strcat(itoa(x-10, buffer, 10), "th"),NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(StackMatrix,10,NULL,0,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);
    }

    //THE DNA WINDOW
    FXGroupBox *DNAFrame=new FXGroupBox(LayoutMatrix1,
        "Bot DNA",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *DNAStack=new FXMatrix(DNAFrame,1,MATRIX_BY_COLUMNS|LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);
    
    FXText *DNATextBox = new FXText(DNAStack, DNAFrame, 0, 
        TEXTFIELD_REAL|JUSTIFY_LEFT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|
        LAYOUT_FIX_WIDTH | LAYOUT_FIX_HEIGHT, 0,0,
        400,//width
        250);

    strcpy(buffer, "I am the very model of the modern major general");;
    DNATextBox->setText(buffer, strlen(buffer));

    DNATextBox->disable();

    //INTERESTING SYSVARS LIST:
    FXGroupBox *SysvarsFrame=new FXGroupBox(LayoutMatrix1,
        "Bot Memory",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    //first we'll need a list of interesting sysvars :P

    //BOT DETAILS:
    FXGroupBox *DetailsFrame=new FXGroupBox(LayoutMatrix1,
        "Bot Details",GROUPBOX_TITLE_LEFT|FRAME_RIDGE|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    FXMatrix *DetailsMatrix=new FXMatrix(DetailsFrame,4,MATRIX_BY_COLUMNS|LAYOUT_SIDE_LEFT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

    x = 0;
    while( strcmp(BotDetails[x++], "") != 0)
    {
        new FXLabel(DetailsMatrix,BotDetails[x-1],NULL,LAYOUT_RIGHT|JUSTIFY_RIGHT);
        new FXTextField(DetailsMatrix,10,NULL,0,
            TEXTFIELD_REAL|JUSTIFY_RIGHT|LAYOUT_CENTER_Y|FRAME_SUNKEN|LAYOUT_CENTER_X|FRAME_THICK|LAYOUT_FILL_ROW);   
    }
    
    dragshell->create();
    //BotDebug->create();
    //BotDebug->show();

    return getApp()->runModalFor(this);
    return 1;
}
