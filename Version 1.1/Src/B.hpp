#ifndef B_HPP
#define B_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
using namespace std;

bool BFormatChecker(string inst);
void BFormat(string inst, string inst_rest, vector<pair<string, int> >& reg, bool &err, map < string,int> labels, int& pc, bool& pc_changed);


#endif
