#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <bitset>
#include <algorithm>
#include "B.hpp"
#include "J.hpp"
using namespace std;

bool JFormatChecker(string inst)
{
	if (inst == "jal")
		return true;
	return false;
}
void JFormat(string inst, string inst_rest, vector<pair<string, int> >& reg, bool& err, map < string, int> labels, int& pc, bool& pc_changed)
{
	int d = -1;
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
			d = i;
		}
	}
	cout << "label: "<< temp[1] ;
	l = temp[1];
	if ( d == -1)
	{
		cout << "Invalid entries." << endl;
		err = true;
	}
	else
	{
		if (inst == "jal" && reg[d]!=reg[0])
		{
			reg[d].second = pc+4;
			pc = labels[l];
			pc_changed = true;
			
		}
	}

}
