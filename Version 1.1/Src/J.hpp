#ifndef J_HPP
#define J_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
using namespace std;

bool JFormatChecker(string inst);
void JFormat(string inst, string inst_rest, vector<pair<string, int> >& reg, bool& err, map < string, int> labels, int& pc, bool& pc_changed);


#endif
