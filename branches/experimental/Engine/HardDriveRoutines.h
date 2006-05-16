#ifndef HDR_H
#define HDR_H

#include "SimOptions.h"
#include <vector>

string GetLine(std::istream &in);
bool ReadSett(const string &path, SimOptions &Options);
bool WriteSett(const string &path, SimOptions &Options);
bool BuildSysvars();

bool LoadSysvars();
bool LoadSysvars(std::string filename);

vector<string> tokenize(istream& inputStream);
#endif
