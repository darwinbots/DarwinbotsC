#ifndef HDR_H
#define HDR_H

#include "SimOptions.h"

string GetLine(ifstream &in);
bool ReadSett(const string &path, SimOptions &Options);
bool BuildSysvars();

bool LoadSysvars();
bool LoadSysvars(std::string filename);

#endif
