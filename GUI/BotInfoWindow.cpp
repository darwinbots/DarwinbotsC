#include "../Engine/Robot.h"
#include "../Engine/DNAClass.h"
#include "BotInfoWindow.h"

FXDEFMAP(BotInfoWindow_Class) BotInfoWindow_ClassMap[] = {
  FXMAPFUNC(SEL_COMMAND, BotInfoWindow_Class::ID_LAST, BotInfoWindow_Class::onCmdStep)
};

FXIMPLEMENT(BotInfoWindow_Class,FXDialogBox,BotInfoWindow_ClassMap,ARRAYNUMBER(BotInfoWindow_ClassMap))

BotInfoWindow_Class::BotInfoWindow_Class(Robot *bot, FXComposite *parent) :
    FXDialogBox(parent, "Bot Details", DECOR_TITLE | DECOR_BORDER)
{
    if(bot == NULL)
    {
        this->detach();
        this->destroy();
        return;
    }
    
    this->bot = bot;
    
    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    
    //Bot Heredity
    FXGroupBox *HerGroup = new FXGroupBox(LayoutMatrix, NULL, FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *HerMatrix = new FXMatrix(HerGroup, 2, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    {
        new FXLabel(HerMatrix, "Species:");
        new FXLabel(HerMatrix, bot->fname.c_str());
        
        new FXLabel(HerMatrix, "Age:");
        new FXTextField(HerMatrix, 15, new FXDataTarget((FXulong &) bot->age), FXDataTarget::ID_VALUE);
        
        new FXLabel(HerMatrix, "Generation:");
        new FXTextField(HerMatrix, 15, new FXDataTarget(bot->generation), FXDataTarget::ID_VALUE);
        
        //new FXLabel(HerMatrix, "# of Offspring:");
        //new FXTextField(HerMatrix, 9, new FXDataTarget(bot->off), FXDataTarget::ID_VALUE);
        
        new FXLabel(HerMatrix, "Mass:");
        new FXTextField(HerMatrix, 15, new FXDataTarget(bot->mass), FXDataTarget::ID_VALUE);
    }
    
    //Bot Details (mostly DNA details)
    FXGroupBox *DetailsGroup = new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *DetailsMatrix = new FXMatrix(DetailsGroup, 2, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    {
        //new FXLabel(DetailsMatrix, "DNA Length:");
        //new FXTextField(DetailsMatrix, 9, new FXDataTarget(bot->DNA->L), FXDataTarget::ID_VALUE);
        
        //new FXLabel(DetailsMatrix, "Genes:");
        //new FXTextField(DetailsMatrix, 9, new FXDataTarget(bot->DNA->DNAgenenum), FXDataTarget::ID_VALUE);
        
        new FXLabel(DetailsMatrix, "My Mutations:");
        new FXTextField(DetailsMatrix, 15, new FXDataTarget(bot->DNA->LastMut), FXDataTarget::ID_VALUE);
        
        new FXLabel(DetailsMatrix, "Mutations:");
        new FXTextField(DetailsMatrix, 15, new FXDataTarget(bot->DNA->Mutations), FXDataTarget::ID_VALUE);
    }
    
    //Substances
    #define Row(ID) new FXLabel(SubstanceMatrix, #ID ## ":"); \
                    new FXTextField(SubstanceMatrix, 15, new FXDataTarget(bot->ID), FXDataTarget::ID_VALUE);
    FXGroupBox *SubstanceGroup = new FXGroupBox(LayoutMatrix,NULL,FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *SubstanceMatrix = new FXMatrix(SubstanceGroup, 2, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    {
        Row(nrg);
        Row(Body);
        Row(Poison);
        Row(Venom);
        Row(Slime);
        Row(Shell);
        Row(Waste);       
    }
    #undef Row
    
    FXMatrix *ToolbarMatrix = new FXMatrix(LayoutMatrix, 1, MATRIX_BY_ROWS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    {
        new FXButton(ToolbarMatrix, "Close", NULL, this, FXDialogBox::ID_CLOSE);    
        new FXButton(ToolbarMatrix, "Close", NULL, this, FXDialogBox::ID_CLOSE);
    }
    
    this->create();
    this->show();
}