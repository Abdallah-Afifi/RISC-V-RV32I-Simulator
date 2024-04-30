#include <bitset>
#include <algorithm>
#include "U.hpp"

bool UFormatChecker(string inst)
{
    if( inst == "lui" || inst == "auipc")
        return true;
    else
        return false;
}
void UFormat(string inst, string inst_rest, vector<pair<string, int> > reg, int pc, map< int , int >  &memory, bool &err )
{
    int rd = -1, imm;
        stringstream instruction(inst_rest);
        
        string store;
        vector <string> temp;
        while (instruction >> store) {
                    store.erase(remove(store.begin(), store.end(), ','), store.end());
                    temp.push_back(store);
        }
    for (size_t i = 0; i < reg.size(); ++i) {
        if (reg[i].first == temp[0]) {
            rd = i;
        }
    }
    imm =  stoi(temp[1]);
    if (rd == -1 ) {
		cout << "Invalid entries." << endl;
        err = true;
	}
	else
	{
        if(reg[rd] != reg[0])
        {
            if(inst == "lui")
            {
                reg[rd].second = (imm << 12);
            }
            else if(inst == "auipc")
            {
                reg[rd].second = pc + (imm << 12);
            }
        }
    }
}
