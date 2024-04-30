#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <bitset>
#include <algorithm>
#include "B.hpp"
using namespace std;

bool BFormatChecker(string inst)
{
	if (inst == "beq" || inst == "bne" || inst == "blt" || inst == "bge" || inst == "bltu" || inst == "bgeu")
		return true;
	return false;
}
void BFormat(string inst, string inst_rest, vector<pair<string, int> >& reg, bool& err, map < string, int> labels, int& pc, bool& pc_changed)
{
	int s1 = -1, s2 = -1;
	string l = "";
	stringstream instruction(inst_rest);

	string store;
	vector <string> temp;

	while (instruction >> store)
	{
		store.erase(remove(store.begin(), store.end(), ','), store.end());
		temp.push_back(store);
	}

	for (size_t i = 0; i < reg.size(); ++i)
	{
		if (reg[i].first == temp[0])
		{
			s1 = i;
		}
		if (reg[i].first == temp[1])
		{
			s2 = i;
		}
	}
	
	l = temp[2];

	
	if (l == "" || s1 == -1 || s2 == -1)
	{
		cout << "Invalid entries." << endl;
		err = true;
	}
	else
	{
		if (inst == "beq")
		{
			if (reg[s1].second == reg[s2].second)
			{
				pc = labels[l];
				pc_changed = true;
			}
		}
		else if (inst == "bne")
		{
			if (reg[s1].second != reg[s2].second)
			{
				pc = labels[l];
				pc_changed = true;
			}
		}
		else if (inst == "blt")
		{
			if (reg[s1].second < reg[s2].second)
			{
				pc = labels[l];
				pc_changed = true;
			}
		}
		else if (inst == "bge")
		{
			if (reg[s1].second >= reg[s2].second)
			{
				pc = labels[l];
				pc_changed = true;
			}
		}
		else if (inst == "bltu")
		{
			if (reg[s1].second >= 0 && reg[s2].second >= 0)
				if (reg[s1].second < reg[s2].second)
				{
					pc = labels[l];
					pc_changed = true;
				}	
				else if (reg[s1].second >= 0 && reg[s2].second < 0)
				{
					pc = labels[l];
					pc_changed = true;
				}	
			else if (reg[s1].second < 0 && reg[s2].second < 0)
				if (reg[s1].second < reg[s2].second)
				{
					pc = labels[l];
					pc_changed = true;
				}
		}	
		else if (inst == "bgeu")
		{
			if (reg[s1].second >= 0 && reg[s2].second >= 0)
				if (reg[s1].second >= reg[s2].second)
				{
					pc = labels[l];
					pc_changed = true;
				}
				else if (reg[s1].second < 0 && reg[s2].second >= 0)
				{
					pc = labels[l];
					pc_changed = true;
				}
				else if (reg[s1].second < 0 && reg[s2].second < 0)
					if (reg[s1].second >= reg[s2].second)
					{
						pc = labels[l];
						pc_changed = true;
					}
		}
	}
}
