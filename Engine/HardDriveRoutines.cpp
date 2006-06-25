#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fx.h>

#include "SimOptions.h"
#include "DNAClass.h"
#include "Engine.h"
#include "HardDriveRoutines.h"
#include "block.h"
#include "..\GUI\OptionsForm.h"
#include "..\GUI\GUIMain.h"

ofstream settingsout;

void ReadSettPre2_4(istream &in, SimOptions &Options);
void ReadSettPort(istream &in, SimOptions &Options);
string GetLine(istream &in);

bool ReadSett(const string &path, SimOptions &Options)
{
	ifstream settingsin( path.c_str() );

	if (settingsin.fail() == true)
	{
		//this isn't a valid settings file
		cout << "Settings file " << path.c_str() << " not found." << endl;
		settingsin.close();
		return false;
	}

	//if the first line reads "-2", then it is the old school settings file
	//if the first line reads "-3", then it's the C++ file version
	//otherwise it's not a valid settings file

	string line = GetLine(settingsin);
	
	if (line == "-2")
	{
		ReadSettPre2_4(settingsin, Options);
	}
	else if (line == "-3")
	{
		ReadSettPort(settingsin, Options);
	}		
	else
	{
		std::cout << "Unknown settings file version." << endl;
		settingsin.close();
		return false;
	}

	settingsin.close();
	return true;
}

void ChopWhiteSpace(string &line)
{
    line = line.substr(line.find_first_not_of(" "), line.size());
    line = line.substr(0, line.find_last_not_of(" ")+1);
}

string ChopOffComments(istream &in)
{
    string line;
    while(line == "" || line == "  ")
    {
        while(line == "" || line == "  ")
            line = GetLine(in);
    
        line.append(";");
        line = line.substr(0, line.find_first_of(";")); //chop off comments        
    }
    ChopWhiteSpace(line);
    
    return line;
}

string EatWord(string &line)
{
    string word;

    line += " ";
    line.c_str();
    word = line.substr(0, line.find_first_of(" "));
    word.c_str();
    line = line.substr(line.find_first_of(" ")+1, line.size());
    line.c_str();
    return word;
}

void ReadSettPort(istream &in, SimOptions &Options)
{
    string line;
    
    line = ChopOffComments(in);

    Options.SpeciesNum = atoi(line.c_str());
    #define GO line = ChopOffComments(in); if(line=="End Species") continue;
    for(unsigned int x = 0; x < Options.SpeciesNum; x++)
    {
        GO Options.Specie[x].Name = line;
        GO Options.Specie[x].path = line;

        GO
        {
            Options.Specie[x].qty = atoi(EatWord(line).c_str());
            Options.Specie[x].nrg = atoi(EatWord(line).c_str());
            Options.Specie[x].body = atoi(EatWord(line).c_str());
        }

        GO Options.Specie[x].color = FXRGBA(atoi(EatWord(line).c_str()),
                                            atoi(EatWord(line).c_str()),
                                            atoi(EatWord(line).c_str()),
                                            255);
        GO Options.Specie[x].Veg = ((line == "veg") ? true : false);
        GO Options.Specie[x].PosLowRight.set((float)atof(EatWord(line).c_str()),
                                             (float)atof(EatWord(line).c_str()),
                                             (float)atof(EatWord(line).c_str()));

        GO Options.Specie[x].PosTopLeft.set ((float)atof(EatWord(line).c_str()),
                                             (float)atof(EatWord(line).c_str()),
                                             (float)atof(EatWord(line).c_str()));

        while(line != "End Species")
            line = ChopOffComments(in);
    }
    #undef GO

    #define GO line = ChopOffComments(in); if(line=="End General") break;
    while(line != "End General")
    {
        GO Options.FieldSize = atoi(EatWord(line).c_str());
        GO
        {
            Options.FieldDimensions(0) = (float)atof(EatWord(line).c_str());
            Options.FieldDimensions(1) = (float)atof(EatWord(line).c_str());
            Options.FieldDimensions(2) = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.UserSeedToggle = (EatWord(line) == "true" ? true : false);
            Options.UserSeedNumber = atoi(EatWord(line).c_str());
        }

        GO
        {
            Options.Dxsxconnected = (EatWord(line) == "true" ? true : false);
            Options.Updnconnected = (EatWord(line) == "true" ? true : false);
        }

        GO Options.BadWasteLevel = atoi(EatWord(line).c_str());
        GO Options.CorpseEnabled = (EatWord(line) == "corpse" ? true : false);

        GO
        {
            Options.DecayType  = atoi(EatWord(line).c_str());
            Options.DecaySize  = (float)atof(EatWord(line).c_str());
            Options.DecayDelay = atoi(EatWord(line).c_str());
        }

        while(line != "End General")
            line = ChopOffComments(in);
    }
    #undef GO

    #define GO line = ChopOffComments(in); if(line=="End Veggies") break;
    while(line != "End Veggies")
    {
        GO Options.PondMode = (EatWord(line) == "PondOn" ? true : false);
        GO
        {
            Options.LightIntensity = (float)atof(EatWord(line).c_str());
            Options.Gradient       = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.MaxPopulation  = atoi(EatWord(line).c_str());
            Options.MinVegs        = atoi(EatWord(line).c_str());
            Options.RepopAmount    = atoi(EatWord(line).c_str());
            Options.RepopCooldown  = atoi(EatWord(line).c_str());
        }

        GO
        {
            Options.VegFeedingMethod = atoi(EatWord(line).c_str());
            Options.VegFeedingToBody = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.DayNight = (EatWord(line) == "DayOn" ? true : false);
            Options.CycleLength = atoi(EatWord(line).c_str());
        }

        while(line != "End Veggies")
            line = ChopOffComments(in);
    }
    #undef GO

    #define GO line = ChopOffComments(in); if(line=="End Physics") break;
    while(line != "End Physics")
    {
        GO
        {
            Options.Density = atof(EatWord(line).c_str());
            Options.Viscosity = atof(EatWord(line).c_str());            
        }

        GO
        {
            Options.ZGravity = (float)atof(EatWord(line).c_str());
            Options.CoefficientStatic = (float)atof(EatWord(line).c_str());
            Options.CoefficientKinetic = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.MovingEfficiency = (float)atof(EatWord(line).c_str());
            Options.YGravity = (float)atof(EatWord(line).c_str());
            Options.Brownian = (float)atof(EatWord(line).c_str());
        }

        GO Options.ZeroMomentum = (EatWord(line) == "ZMon" ? true : false);
        GO Options.PlanetEatersG = (float)atof(EatWord(line).c_str());

        GO
        {
            Options.EnergyExType = (EatWord(line) == "PropShot" ? true : false);
            Options.EnergyFix =  atoi(EatWord(line).c_str());
            Options.EnergyProp = atoi(EatWord(line).c_str());
        }

        GO Options.MaxSpeed = atoi(EatWord(line).c_str());
        
        while(line != "End Physics")
            line = ChopOffComments(in);
    }
    #undef GO

    #define GO line = ChopOffComments(in); if(line=="End Costs") break;
    while(line != "End Costs")
    {
        GO
        {
            Options.Costs[btValue] = (float)atof(EatWord(line).c_str());
            Options.Costs[btPointer] = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.Costs[btBasicCommand] = (float)atof(EatWord(line).c_str());
            Options.Costs[btBitwiseCommand] = (float)atof(EatWord(line).c_str());
            Options.Costs[btAdvancedCommand] = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.Costs[btLogic] = (float)atof(EatWord(line).c_str());
            Options.Costs[btCondition] = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.Costs[btStores] = (float)atof(EatWord(line).c_str());
            Options.Costs[btFlow] = (float)atof(EatWord(line).c_str());
        }

        GO
        GO
        {
            Options.Costs[MOVECOST] = (float)atof(EatWord(line).c_str());
            Options.Costs[TURNCOST] = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.Costs[SHOTCOST] = (float)atof(EatWord(line).c_str());
            Options.Costs[TIECOST] = (float)atof(EatWord(line).c_str());
        }

        GO
        {
            Options.Costs[BPCYCCOST] = (float)atof(EatWord(line).c_str());
            Options.Costs[BPCOPYCOST] = (float)atof(EatWord(line).c_str());
        }

        GO Options.Costs[BODYUPKEEP] = (float)atof(EatWord(line).c_str());

        GO
        {
            Options.Costs[VENOMCOST] = (float)atof(EatWord(line).c_str());
            Options.Costs[SLIMECOST] = (float)atof(EatWord(line).c_str());
            Options.Costs[POISONCOST] = (float)atof(EatWord(line).c_str());
            Options.Costs[SHELLCOST] = (float)atof(EatWord(line).c_str());
        }
        
        while(line != "End Costs")
            line = ChopOffComments(in);
    }
    #undef GO
}

bool WriteSett(const string &path, SimOptions &Options)
{
    ofstream settingsout (path.c_str());
    string END;

    END.append("\n  ");

    if (settingsout.fail() == true)
    {
        //can't make the file for some reason
        std::cout << "Settings file " << path << "isn't valid for some reason." << endl;
        settingsout.close();
        return false;
    }

    //this is the new version of C++ settings file
    settingsout << "-3" << endl;

    settingsout << Options.SpeciesNum << "; Species" << endl;
    unsigned int x = 0;
    for(x = 0; x < Options.SpeciesNum; x++)
    {
        settingsout << endl;
        settingsout << Options.Specie[x].Name << " ;Species" << END;
        settingsout << Options.Specie[x].path << " ;path" << END;

        settingsout << Options.Specie[x].qty << " " <<
                       Options.Specie[x].nrg << " " <<
                       Options.Specie[x].body << " ;QTY NRG BODY" << END;

        settingsout << (int)FXREDVAL(Options.Specie[x].color) << " " <<
                       (int)FXGREENVAL(Options.Specie[x].color) << " " <<
                       (int)FXBLUEVAL(Options.Specie[x].color) << " " << 
                       ";Color (Red Green Blue) [0-255]" << END;

        settingsout << ((Options.Specie[x].Veg == true) ? "veg" : "notveg") << END;

        settingsout << Options.Specie[x].PosLowRight.z() << " " <<
                       Options.Specie[x].PosLowRight.y() << " " <<
                       Options.Specie[x].PosLowRight.x() << " " << 
                       ";PosLowRight z y x" << END;

        settingsout << Options.Specie[x].PosTopLeft.z() << " " <<
                       Options.Specie[x].PosTopLeft.y() << " " <<
                       Options.Specie[x].PosTopLeft.x() << " " << 
                       ";PosTopLeft z y x" << endl;

        settingsout << "End Species" << endl;
    }

    settingsout << endl << "; General Settings" << END;
    {
        settingsout << Options.FieldSize << "; Field Size" << END;
        settingsout << Options.FieldDimensions.x() << " " <<
                       Options.FieldDimensions.y() << " " <<
                       Options.FieldDimensions.z() << "; Field Dimensions" << END;

        settingsout << (Options.UserSeedToggle ? "true" : "false") << " " << 
                        Options.UserSeedNumber << "; User Seed toggle and number" << END;

        settingsout << (Options.Dxsxconnected ? "true" : "false") << " "
                    << (Options.Updnconnected ? "true" : "false") << "; left/right up/dn connected" << END;

        settingsout << Options.BadWasteLevel << "; Bad Waste Level" << END;
        settingsout << (Options.CorpseEnabled ? "corpse" : "nocorpse") << END;
        settingsout << Options.DecayType << " " <<
                       Options.DecaySize << " " <<
                       Options.DecayDelay << " " <<
                       ";Decay type/size/delay" << endl;

        settingsout << "End General" << endl << endl;
    }

    settingsout << "; Veggy Settings" << END;
    {
        settingsout << (Options.PondMode ? "PondOn" : "PondOff") << END;
        settingsout << Options.LightIntensity << " " <<
                       Options.Gradient << ";Light Intensity / Gradient" << END;
        settingsout << Options.MaxPopulation << " " <<
                       Options.MinVegs << " " <<
                       Options.RepopAmount << " " <<
                       Options.RepopCooldown << " " <<
                       "; Max Min Amt Cooldown" << END;
        settingsout << Options.VegFeedingMethod << " " <<
                       Options.VegFeedingToBody << " " <<
                       "; Method ToBody" << END;
        settingsout << (Options.DayNight ? "DayOn" : "DayOff") << " "
                    << Options.CycleLength << " " <<
                    ";Day On/Off / Day Length";
        
        settingsout << endl << "End Veggies" << endl << endl;        
    }

    settingsout << ";Physics Settings" << END;
    {
        settingsout << Options.Density << " " <<
                       Options.Viscosity << " " <<
                       ";Density Viscosity" << END;

        settingsout << Options.ZGravity << " " <<
                       Options.CoefficientStatic << " " <<
                       Options.CoefficientKinetic << " " <<
                       ";ZGravity Static Kinetic" << END;

        settingsout << Options.MovingEfficiency << " " <<
                       Options.YGravity << " " <<
                       Options.Brownian << " " <<
                       "; Efficiency YGravity Brownian" << END;

        settingsout << (Options.ZeroMomentum ? "ZMon" : "ZMoff") << " " <<
                       "; Zero Momentum" << END;

        settingsout << Options.PlanetEatersG << " " <<
                       "; Planet Eaters" << END;

        settingsout << (Options.EnergyExType ? "PropShot" : "FixedShot") << " " <<
                       Options.EnergyFix << " " <<
                       (int)Options.EnergyProp << " " <<
                       "; Energy hit type / fixed return value / proportional shot power" << END;

        settingsout << Options.MaxSpeed << " ;Max Speed";
        
        settingsout << endl << "End Physics" << endl << endl;

    }

    settingsout << ";Costs Settings" << END;
    {
        settingsout << ";DNA Costs" << END;
        
        settingsout << Options.Costs[btValue] << " " <<
                       Options.Costs[btPointer] << " " <<
                       "; Value Pointer" << END;

        settingsout << Options.Costs[btBasicCommand] << " " <<
                       Options.Costs[btBitwiseCommand] << " " <<
                       Options.Costs[btAdvancedCommand] << " " <<
                       ";Basic Bitwise Advanced Commands" << END;

        settingsout << Options.Costs[btLogic] << " " <<
                       Options.Costs[btCondition] << " " <<
                       ";Logic Conditions" << END;

        settingsout << Options.Costs[btStores] << " " <<
                       Options.Costs[btFlow] << " " <<
                       ";Stores Flow" << END;

        for(x = btMAX; x <= 20; x++)
            settingsout << "0 ";

        settingsout << END;
        settingsout << Options.Costs[MOVECOST] << " " <<
                       Options.Costs[TURNCOST] <<
                       "; Move Turn" << END;

        settingsout << Options.Costs[SHOTCOST] << " " <<
                       Options.Costs[TIECOST]  << " " <<
                       "; Shot Tie" << END;

        settingsout << Options.Costs[BPCYCCOST] << " " <<
                       Options.Costs[BPCOPYCOST] << " " <<
                       "; DNA upkeep / copy cost" << END;

        settingsout << Options.Costs[BODYUPKEEP] << " " <<
                       ";Body Upkeep" << END;

        settingsout << Options.Costs[VENOMCOST] << " " <<
                       Options.Costs[SLIMECOST] << " " <<
                       Options.Costs[POISONCOST] << " " <<
                       Options.Costs[SHELLCOST] << " " <<
                       ";Venom Slime Poison Shell" << END;
        
        settingsout << endl << "End Costs" << endl << endl;
    }    
    
    return true;  
}

string GetLine(istream &in)
{
	string line;
	char buffer[1024];

	in.getline(buffer, 1024, '\n');
    line = buffer;
	//line.assign(buffer);
    if (line != "" && line.at(line.length() -1) == '\r')
        line.resize(line.length() - 1); //to get rid of the carriage return sequence at the end of buffer

	return line;
}

double GrabNumber(istream &in)
{
	return atof(GetLine(in).c_str());
}

string &GrabString(istream &in)
{
	static string line;
	string saveto;
	const char quote = '\"';

	saveto = GetLine(in);
	if ((saveto.c_str())[0] == quote && (saveto.c_str())[saveto.size() - 1]) //quotation marks at either end
		line.assign(saveto, 1, saveto.size() - 2);
	else
		line = saveto;

	return line;
}

bool GrabBool(istream &in)
{
	if (GetLine(in) == "#TRUE#")
		return true;
	return false;
}

//prevent warnigns about type castings
#pragma warning(disable : 4244)
void ReadSettPre2_4(istream &in, SimOptions &Options)
{
	string line;
	unsigned int x = 0;

	Options.SpeciesNum = (unsigned int)(GrabNumber(in)) + 1;

	for (x = 0; x < Options.SpeciesNum; x++)
	{
		Options.Specie[x].PosLowRight.set(GrabNumber(in),
										  GrabNumber(in),
										  0.0f);

		Options.Specie[x].PosTopLeft.set(GrabNumber(in),
										 GrabNumber(in),
										 0.0f);
		/////////////////////////////////////////

		
		/*Options.Specie[x].Mutables.mutarray[0] =*/ GrabNumber(in);
		Options.Specie[x].path =				 GrabString(in);
		Options.Specie[x].qty =					 GrabNumber(in);
		Options.Specie[x].Name =				 GrabString(in);
		Options.Specie[x].Veg =					 GrabBool(in);
		                                         GrabBool(in);
				
		Options.Specie[x].color =	             GrabNumber(in);
		line =									 GrabString(in);  //obsolete
		Options.Specie[x].nrg =					 GrabNumber(in);

		for (unsigned int k = 0; k <= 13; k++)
		{
			/*Options.Specie[x].Mutables.mutarray[k] =*/ GrabNumber(in);
		}

		for (unsigned int l = 0; l <= 12; l++)
		{
			line =								GrabString(in);
		}
	}

	Options.SimName =							GrabString(in);
	line =										GrabString(in);  //obsolete
	Options.FieldSize =							GrabNumber(in);
	Options.FieldDimensions.set(				GrabNumber(in), GrabNumber(in), 0.0f);
    Options.FieldDimensions.set(Options.FieldDimensions.y(), Options.FieldDimensions.x(), 0);
	Options.MaxPopulation =						GrabNumber(in);
	line =										GrabString(in);  //obsolete
	                                            GrabBool(in);
	                                            GrabNumber(in);
	Options.Toroidal =							GrabBool(in);
	                							GrabNumber(in);
	Options.MinVegs =							GrabNumber(in);
	Options.Costs[CONDCOST] =					GrabNumber(in);
	Options.Costs[COSTSTORE] =					GrabNumber(in);
	Options.Costs[SHOTCOST] =					GrabNumber(in);
	Options.Costs[TIECOST] = Options.Costs[SHOTCOST];
	Options.EnergyProp =						GrabNumber(in);
	Options.EnergyFix =							GrabNumber(in);
	Options.EnergyExType =						GrabBool(in);

	Options.YGravity =							GrabNumber(in);
	Options.ZGravity =							GrabNumber(in);
	Options.Brownian  =							GrabNumber(in);
	Options.MovingEfficiency =					GrabNumber(in);
	line =										GrabString(in); //obsolete

	Options.AutoSimPath =						GrabString(in);
	Options.AutoSimTime =						GrabNumber(in);
	Options.AutoRobPath =						GrabString(in);
	Options.AutoRobTime =						GrabNumber(in);

	Options.MutCurrMult =						GrabNumber(in);
	Options.MutOscill =							GrabBool(in);
	Options.MutCycMax =							GrabNumber(in);
	Options.MutCycMin =							GrabNumber(in);

	Options.DBName =							GrabString(in);
	Options.DBEnable =							GrabBool(in);
	Options.DBExcludeVegs =						GrabBool(in);
	
	if (!in.eof()) Options.PondMode =			GrabBool(in);
	if (!in.eof()) line =						GrabString(in); //obsolete
	if (!in.eof()) Options.LightIntensity =		GrabNumber(in);
	if (!in.eof()) Options.CorpseEnabled  =		GrabBool(in);
	if (!in.eof()) Options.DecaySize =  		GrabNumber(in);
	if (!in.eof()) Options.Gradient  =			GrabNumber(in);
	if (!in.eof()) Options.DayNight  =			GrabBool(in);
	if (!in.eof()) Options.CycleLength  =		GrabNumber(in);
	if (!in.eof()) Options.DecayType  =			GrabNumber(in);
	if (!in.eof()) Options.DecayDelay  =		GrabNumber(in);
	if (!in.eof()) line =						GrabString(in); //obsolete

	if (!in.eof()) Options.F1 =					GrabBool(in);
	if (!in.eof()) Options.Restart =			GrabBool(in);
	
	for (x = 0; x < 9; x++)
	{	
		if (!in.eof()) line =					GrabString(in);
		if (!in.eof()) line =					GrabString(in);
		if (!in.eof()) line =					GrabString(in);
		if (!in.eof()) line =					GrabString(in);
	}
	if (!in.eof()) Options.Dxsxconnected  =		GrabBool(in);
	if (!in.eof()) Options.Updnconnected  =		GrabBool(in);
	if (!in.eof()) Options.RepopAmount  =		GrabNumber(in);
	if (!in.eof()) Options.RepopCooldown  =		GrabNumber(in);
	if (!in.eof()) Options.ZeroMomentum  =		GrabBool(in);
	if (!in.eof()) Options.UserSeedToggle  =	GrabBool(in);
	if (!in.eof()) Options.UserSeedNumber  =	GrabNumber(in);
	
	
	for (x = 0; x < Options.SpeciesNum; x++)
	{
		for (int k = 14; k <= 20; k++)
		{
			if (!in.eof())
				/*Options.Specie[x].Mutables.mutarray[k] =*/ GrabNumber(in);
		}

		if (!in.eof())
				/*Options.Specie[x].Mutables.Mutations =*/ GrabBool(in);
	}
	
	if (!in.eof()) Options.VegFeedingMethod =	GrabNumber(in);
	if (!in.eof()) Options.VegFeedingToBody =	GrabNumber(in); else Options.VegFeedingToBody = 0.1f;
	
	if (!in.eof()) Options.CoefficientStatic =	GrabNumber(in);
	if (!in.eof()) Options.CoefficientKinetic =	GrabNumber(in);

	if (!in.eof()) Options.PlanetEatersG  =		GrabNumber(in);

	if (!in.eof()) Options.Viscosity   =		GrabNumber(in);
	if (!in.eof()) Options.Density =			GrabNumber(in);
	
	//above this line reads correctly from the old VB version

	for (x = 0; x < Options.SpeciesNum ; x++)
	{
		if (!in.eof()) /*Options.Specie[x].Mutables.CopyErrorWhatToChange =*/ GrabNumber(in);
		if (!in.eof()) /*Options.Specie[x].Mutables.PointWhatToChange =*/ GrabNumber(in);

		for (int k = 0; k <= 20; k++)
		{
			if (!in.eof()) /*Options.Specie[x].Mutables.Mean[k] =*/ GrabNumber(in);
			if (!in.eof()) /*Options.Specie[x].Mutables.StdDev[k] =*/ GrabNumber(in);
		}
	}

	for (int k = 0; k < 70; k++)
	{
		if (!in.eof()) Options.Costs[k] = GrabNumber(in);
	}

	//extra cost we're not storing
	if (!in.eof()) line = GrabString(in);
	
	/*if (!in.eof())
	{
		cout << "This settings file is to a newer version." << endl;
		cout << "Not all the information contained in it can be transfered to this version." << endl;
		unsigned int k=0;

		while(!in.eof())
		{
			GrabString(in);
			k++;
		}

		cout << k << " lines were not grabed." << endl;
	}*/

	if (Options.FieldDimensions.x() == 0)
		Options.FieldDimensions.set(16000, Options.FieldDimensions.y(), Options.FieldDimensions.z());
	if (Options.FieldDimensions.y() == 0)
		Options.FieldDimensions.set(Options.FieldDimensions.x(), 12000, Options.FieldDimensions.z());
    if (Options.BadWasteLevel == 0)
        Options.BadWasteLevel = 400;
    if (Options.MaxSpeed == 0)
        Options.MaxSpeed = 60;
}
//enable warnings about conversions
#pragma warning(default: 4244)

bool BuildSysvars()
{
    string line;

    string path = Engine.MainDir() + "\\sysvars2.5.txt";
	ifstream in(path.c_str());

    if (in.fail() == true)
    {
        //can't find sysvars file
        std::cout << "Sysvars file " << path.c_str() << " not found." << endl;
		in.close();
		return false;
    }

    while (!in.eof())
    {
        var temp;

        in >> line;
        temp.value = atoi(line.c_str());
        
        in >> line;
        temp.name = line;

        sysvar.push_back(temp);
    }

    in.close();

    return true;
}

bool DNA_Class::LoadDNA(string path)
{
    ifstream DNAfile(path.c_str() );
	if (DNAfile.fail() == true)
	{
		//this isn't a valid settings file
		cout << "Robot file " << path.c_str() << " not found." << endl;
		DNAfile.close();
		return false;
	}
    
    this->LoadDNA(DNAfile);
    
    DNAfile.close();
    return true;
}

/*
// This is an all purpose tokenizer respecting Darwinbots' conventions
// Spaces and linebreaks count as delimiters and everything after "'" is
// ignored till end of line.
vector<string> tokenize(istream& inputStream)
{
    int pos;
    vector<string> tokenList;
    string lineBuf,token;

    while(!inputStream.eof())
    {
        getline(inputStream,lineBuf);
        pos = lineBuf.find("'");
        if (pos != string::npos)
            lineBuf.erase(pos);
        stringstream ssLineBuf(lineBuf,std::stringstream::in);
        while( !ssLineBuf.eof() )
        {
            while (isspace(ssLineBuf.peek()))
                ssLineBuf.get();

            if( ssLineBuf.eof())
                break;

            ssLineBuf>>token;
            tokenList.push_back(token);
        }
    }

    return tokenList;
};

bool LoadSysvars() {
    string path = Engine.MainDir() + "\\sysvars2.4.txt";
    return LoadSysvars(path);
};

bool LoadSysvars(string path) {
    vector<string> tokenList;
    ifstream in(path.c_str() );

    if (in.fail() == true)
    {
        //can't find sysvars file
        cout << "Sysvars file " << path.c_str() << " not found." << endl;
		in.close();
		return false;
    }
    tokenList=tokenize(in);
    if (tokenList.size() % 2 == 1) return false;

    vector<string>::iterator tIter;
    pair<string,short> tmpPair;
    for(tIter = tokenList.begin(); tIter!=tokenList.end(); tIter++){
        if(!from_string<short>(tmpPair.second, *tIter, std::dec)) {
            std::cout<<"from_string failed while loading sysvars."<<std::endl;
            return false;
        }
        tIter++;
        tmpPair.first=*tIter;
        vSysvars.push_back(tmpPair);
    }
  
  int i=0;
  
  
  for(vector<pair<string,__int16> >::iterator iter = vSysvars.begin(); iter!=vSysvars.end(); ++iter){
    sysvar[i].name=iter->first;
    sysvar[i].value=iter->second;
    i++;
  }
  
  maxsysvar=vSysvars.size();
  return true;
};
*/
