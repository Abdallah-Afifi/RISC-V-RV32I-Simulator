#ifndef S_HPP
#define S_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

using namespace std;

bool SFormatChecker(string inst, bool& offset);
void SFormat(string inst, string inst_rest, vector<pair<string, int> > &reg, int &pc, bool &pc_changed , map< int , int >  &memory, bool &err , bool&offset);
void SextractStrings(string input, string& beforeParentheses, string& withinParentheses);

#endif 
