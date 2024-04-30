#ifndef R_HPP
#define R_HPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool RFormatChecker(string inst);
void RFormat(string inst, string inst_rest, vector<pair<string, int> > &reg, bool &err);


#endif 
