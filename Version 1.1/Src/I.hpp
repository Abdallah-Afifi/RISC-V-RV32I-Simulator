#ifndef I_HPP
#define I_HPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool IFormatChecker(string inst, bool& offset);
void IFormat(string inst, string inst_rest, vector<pair<string, int> > &reg, int &pc, bool &pc_changed , map< int , int >  &memory, bool &err , bool&offset);
void extractStrings(string input, string& beforeParentheses, string& withinParentheses);

#endif 
