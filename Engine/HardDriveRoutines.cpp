#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "SimOptions.h"
#include "DNAClass.h"
#include "Engine.h"
#include "HardDriveRoutines.h"



ofstream settingsout;

void ReadSettPre2_4(istream &in, SimOptions &Options);
//bool VBTrue(ifstream &file);
string GetLine(istream &in);

bool ReadSett(const string &path, SimOptions &Options)
{
	ifstream settingsin( path.c_str() );

	if (settingsin.fail() == true)
	{
		//this isn't a valid settings file
		std::cout << "Settings file " << path.c_str() << " not found." << endl;
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
		//ReadSett2_4(settingsin);
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

#ifdef _MSC_VER
//disable warnings about conversions
#pragma warning(disable : 4244)
#endif
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

		
		Options.Specie[x].Mutables.mutarray[0] = GrabNumber(in);
		Options.Specie[x].path =				 GrabString(in);
		Options.Specie[x].qty =					 GrabNumber(in);
		Options.Specie[x].Name =				 GrabString(in);
		Options.Specie[x].Veg =					 GrabBool(in);
		Options.Specie[x].Fixed =				 GrabBool(in);
				
		Options.Specie[x].color =	Vector4(GrabNumber(in), 0,0);
		line =									 GrabString(in);  //obsolete
		Options.Specie[x].nrg =					 GrabNumber(in);

		for (unsigned int k = 0; k <= 13; k++)
		{
			Options.Specie[x].Mutables.mutarray[k] = GrabNumber(in);
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
	Options.DisableTies =						GrabBool(in);
	Options.PopLimMethod =						GrabNumber(in);
	Options.Toroidal =							GrabBool(in);
	Options.NrgCyc =							GrabNumber(in);
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
	if (!in.eof()) Options.Decay =				GrabNumber(in);
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
				Options.Specie[x].Mutables.mutarray[k] = GrabNumber(in);
		}

		if (!in.eof())
				Options.Specie[x].Mutables.Mutations = GrabBool(in);
	}
	
	if (!in.eof()) Options.VegFeedingMethod =	GrabNumber(in);
	if (!in.eof()) Options.VegFeedingToBody =	GrabNumber(in); else Options.VegFeedingToBody = 0.1f;
	
	if (!in.eof()) Options.CoefficientStatic =	GrabNumber(in);
	if (!in.eof()) Options.CoefficientKinetic =	GrabNumber(in);

	if (!in.eof()) Options.PlanetEaters  =		GrabBool(in);
	if (!in.eof()) Options.PlanetEatersG  =		GrabNumber(in);

	if (!in.eof()) Options.Viscosity   =		GrabNumber(in);
	if (!in.eof()) Options.Density =			GrabNumber(in);
	
	//above this line reads correctly from the old VB version

	for (x = 0; x < Options.SpeciesNum ; x++)
	{
		if (!in.eof()) Options.Specie[x].Mutables.CopyErrorWhatToChange = GrabNumber(in);
		if (!in.eof()) Options.Specie[x].Mutables.PointWhatToChange = GrabNumber(in);

		for (int k = 0; k <= 20; k++)
		{
			if (!in.eof()) Options.Specie[x].Mutables.Mean[k] = GrabNumber(in);
			if (!in.eof()) Options.Specie[x].Mutables.StdDev[k] = GrabNumber(in);
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
    if (SimOpts.BadWasteLevel == 0)
        SimOpts.BadWasteLevel = 400;
    if (SimOpts.MaxSpeed == 0)
        SimOpts.MaxSpeed = 60;
}

#ifdef _MSC_VER
//enable warnings about conversions
#pragma warning(default: 4244)
#endif

bool BuildSysvars()
{
    string line;

    std::string path = Engine.MainDir() + "\\sysvars2.4.txt";
	ifstream in(path.c_str() );

    if (in.fail() == true)
    {
        //can't find sysvars file
        std::cout << "Sysvars file " << path.c_str() << " not found." << endl;
		in.close();
		return false;
    }

    maxsysvar = 0;

    while (!in.eof())
    {
        in >> line;
        sysvar[maxsysvar].value = atoi(line.c_str());
        
        in >> line;
        sysvar[maxsysvar].name = line;

        maxsysvar++;
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
		std::cout << "Robot file " << path.c_str() << " not found." << endl;
		DNAfile.close();
		return false;
	}
    
    this->LoadDNA(DNAfile);
    
    DNAfile.close();
    return true;
}

//none below is used yet

// This is an all purpose tokenizer respecting Darwinbots' conventions
// Spaces and linebreaks count as delimiters and everything after "'" is
// ignored till end of line.
vector<string> tokenize(std::istream& inputStream) {
  int pos;
  vector<string> tokenList;
  string lineBuf,token;

  while(!inputStream.eof()){
    getline(inputStream,lineBuf);
    //DEBUG: myNotify("Line : "+lineBuf);
    pos=lineBuf.find("'");
    if (pos!=string::npos) lineBuf.erase(pos);
    std::stringstream ssLineBuf(lineBuf,std::stringstream::in);
    while( !ssLineBuf.eof() ){
      while (isspace(ssLineBuf.peek()))
        ssLineBuf.get();
      if( ssLineBuf.eof()) break;
      ssLineBuf>>token;
      tokenList.push_back(token);
    }
  }
  return tokenList;
};

bool LoadSysvars() {
    std::string path;
    path = Engine.MainDir() + "\\sysvars2.4.txt";
    return LoadSysvars(path);
};

bool LoadSysvars(std::string path) {
    vector<string> tokenList;
    ifstream in(path.c_str() );

    if (in.fail() == true)
    {
        //can't find sysvars file
        std::cout << "Sysvars file " << path.c_str() << " not found." << endl;
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
  
  //the below gives me errors.  Probably has to do with iostream.h instead of
  //iostream  Moving this to a seperate file may cure this issue. - Numsgil
  for(vector<pair<string,__int16> >::iterator iter = vSysvars.begin(); iter!=vSysvars.end(); ++iter){
    sysvar[i].name=iter->first;
    sysvar[i].value=iter->second;
    i++;
  }
  
  maxsysvar=vSysvars.size();
  return true;
};
