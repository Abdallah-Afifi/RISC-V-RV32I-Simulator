#include <iostream>
#include <vector>
#include <sstream>
#include <bitset>
#include <algorithm>
#include "R.hpp"
using namespace std;
bool RFormatChecker(string inst)
{
	if (inst == "add" || inst == "sub" || inst == "and" || inst == "or" || inst == "xor" || inst == "sll" || inst == "srl" || inst == "sra" || inst == "slt" || inst == "sltu" || inst =="mulh" || inst =="mul")
		return true;
	return false;
}

void RFormat(string inst, string inst_rest, vector<pair<string, int> > &reg, bool &err)
{
	
	int d = -1, s1 = -1, s2 = -1;
	stringstream instruction(inst_rest);

	string store;
	vector <string> temp;
	
	while (instruction >> store)
	{
		store.erase(remove(store.begin(), store.end(), ','), store.end());
		temp.push_back(store);
	}

	for (size_t i = 0; i < reg.size(); ++i) {
		if (reg[i].first == temp[0]) {
			d = i;
		}
		if (reg[i].first == temp[1])
		{
			s1 = i;
		}
		if (reg[i].first == temp[2])
		{
			s2 = i;
		}
	}
	if (d == -1 || s1 == -1 || s2 == -1)
	{
		cout << "Invalid entries." << endl;
		err = true;
	}
	else
	{	if(reg[d] != reg[0])
		{
			if (inst == "add")
				reg[d].second = reg[s1].second + reg[s2].second;
			else if (inst == "sub")
				reg[d].second = reg[s1].second - reg[s2].second; // what if it is negative? needs consideration
			else if(inst =="sll")
				reg[d].second = reg[s1].second << reg[s2].second;
			else if(inst== "srl")
				reg[d].second = reg[s1].second >> reg[s2].second;
			else if (inst == "and")
				reg[d].second = reg[s1].second & reg[s2].second;
			else if (inst == "or")
				reg[d].second = reg[s1].second | reg[s2].second;
			else if (inst == "xor")
				reg[d].second = reg[s1].second ^ reg[s2].second;
			else if (inst == "sra")
				reg[d].second = reg[s1].second >> reg[s2].second;
			else if (inst == "slt")
			{
				if (reg[s1].second < reg[s2].second)
					reg[d].second = 0;
				else
					reg[d].second = 1;

			}
			else if (inst == "sltu")
			{
				if (reg[s1].second >= 0 && reg[s2].second>=0)
					if(reg[s1].second < reg[s2].second)
						reg[d].second = 1;
					else
						reg[d].second = 0;
				else if(reg[s1].second >= 0 && reg[s2].second < 0)
					reg[d].second = 1;
				else if (reg[s1].second < 0 && reg[s2].second < 0)
					if (reg[s1].second < reg[s2].second)
						reg[d].second = 1;
					else
						reg[d].second = 0;
				else if (reg[s1].second < 0 && reg[s2].second >= 0)
					reg[d].second = 0;
			}
			else if (inst == "mul")
			{
				reg[d].second = reg[s1].second * reg[s2].second;
			}
			else if (inst == "mulh")
			{
				
				long int x = (long int) reg[s1].second * reg[s2].second;
				reg[d].second = x >> 32;
			}
		}
	}
}
