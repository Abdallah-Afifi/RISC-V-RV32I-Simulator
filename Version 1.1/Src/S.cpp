#include <bitset>
#include <algorithm>
#include "S.hpp"


bool SFormatChecker(string inst){
    if(inst == "sw" || inst == "sh" || inst == "sb")
        return true;
    else 
        return false;
}
void SFormat(string inst, string inst_rest, vector<pair<string, int> > &reg , map< int , int >  &memory, bool &err){
    int rs1 = -1, rs2 = -1, imm;
    stringstream instruction(inst_rest);
    
    string store;
    vector <string> temp;
    while (instruction >> store) {
                store.erase(remove(store.begin(), store.end(), ','), store.end());
                temp.push_back(store);
            }
    string immediate, source;
    SextractStrings(temp[1], immediate, source);
    for (size_t i = 0; i < reg.size(); ++i) {
        if (reg[i].first == temp[0]) {
            rs2 = i;
        }
        if (reg[i].first == source) {
            rs1 = i;
	    }
    }
    imm =  stoi(immediate);
    if (rs2 == -1 || rs1 == -1 ) {
		cout << "Invalid entries." << endl;
        err = true;
	}
	else
	{
        if(inst == "sw")
        {   
                memory[reg[rs1].second + imm] = reg[rs2].second;

        }
        else if(inst == "sh")
        {
            memory[reg[rs1].second + imm] = reg[rs2].second & 0XFFFF;
        }
        else if(inst == "sb")
        {
            memory[reg[rs1].second + imm] = reg[rs2].second & 0XFF;
        }
    }
}

       
        

void SextractStrings(string input, string& beforeParentheses, string& withinParentheses) {
    size_t openingParen = input.find('(');
    size_t closingParen = input.find(')');
    
    if (openingParen != string::npos && closingParen != string::npos && openingParen < closingParen) {
        beforeParentheses = input.substr(0, openingParen);
        withinParentheses = input.substr(openingParen + 1, closingParen - openingParen - 1);
    } 
}
