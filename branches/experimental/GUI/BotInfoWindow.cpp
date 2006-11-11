#include "../Engine/Robot.h"
#include "../Engine/DNAClass.h"
#include "BotInfoWindow.h"

FXIMPLEMENT(BotInfoWindow,FXDialogBox,BotInfoWindowMap,ARRAYNUMBER(BotInfoWindowMap))

BotInfoWindow::BotInfoWindow(Robot *bot, FXComposite *parent) :
    FXDialogBox(parent, "Bot Details", DECOR_TITLE | DECOR_BORDER),
    _bot(bot)
{
    std::cout<<"info window"<<std::endl;
    if(_bot == NULL)
    {
        this->detach();
        this->destroy();
        return;
    }

    FXMatrix *LayoutMatrix = new FXMatrix(this, 1, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);

    //Bot Heredity
    FXGroupBox *HerGroup = new FXGroupBox(LayoutMatrix, NULL, FRAME_RIDGE | LAYOUT_FILL_X | LAYOUT_FILL_ROW);
    FXMatrix *HerMatrix = new FXMatrix(HerGroup, 2, MATRIX_BY_COLUMNS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    {
        new FXLabel(HerMatrix, "Species:");
        new FXLabel(HerMatrix, _bot->getName().c_str());

        new FXLabel(HerMatrix, "ID number:");
        new FXTextField(HerMatrix, 15, new FXDataTarget((FXulong &) _bot->getAbsNum()), FXDataTarget::ID_VALUE, TEXTFIELD_READONLY);

        new FXLabel(HerMatrix, "Age:");
        new FXTextField(HerMatrix, 15, new FXDataTarget((FXulong &) _bot->getAge()), FXDataTarget::ID_VALUE, TEXTFIELD_READONLY);

        new FXLabel(HerMatrix, "Generation:");
        new FXTextField(HerMatrix, 15, new FXDataTarget(_bot->generation), FXDataTarget::ID_VALUE, TEXTFIELD_READONLY);

        new FXLabel(HerMatrix, "# of Offspring:");
        new FXTextField(HerMatrix, 15, new FXDataTarget(_bot->SonNumber), FXDataTarget::ID_VALUE, TEXTFIELD_READONLY);
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
        new FXTextField(DetailsMatrix, 15,
                new FXDataTarget(_bot->dna->LastMut), FXDataTarget::ID_VALUE);

        new FXLabel(DetailsMatrix, "Mutations:");
        new FXTextField(DetailsMatrix, 15,
                new FXDataTarget(_bot->dna->Mutations), FXDataTarget::ID_VALUE);
    }

    //Substances
    #define Row(ID) new FXLabel(SubstanceMatrix, #ID); \
                    new FXTextField(SubstanceMatrix, 15, new FXDataTarget(_bot->ID), FXDataTarget::ID_VALUE);
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

        new FXLabel(HerMatrix, "Mass:");
        new FXTextField(HerMatrix, 15, new FXDataTarget(_bot->mass),
                            FXDataTarget::ID_VALUE, TEXTFIELD_READONLY);
    }
    #undef Row

    FXMatrix *ToolbarMatrix = new FXMatrix(LayoutMatrix, 1, MATRIX_BY_ROWS | LAYOUT_SIDE_TOP | LAYOUT_FILL);
    {
        new FXButton(ToolbarMatrix, "Close", NULL, this, FXDialogBox::ID_CLOSE);
        //new FXButton(ToolbarMatrix, "Close", NULL, this, FXDialogBox::ID_CLOSE);
    }

    this->create();
    this->show();
}
